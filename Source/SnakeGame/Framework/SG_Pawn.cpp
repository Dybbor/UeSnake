#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

namespace
{
    float HalfFOVTan(float FOVDegrees)
    {
        return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5f));
    }

    float CalculateHalfVerticalFOVTan(float HorizontalFOVDegress, float ViewportAspectRatioHW)
    {
        const float HorizontalFOVRadians = FMath::DegreesToRadians(HorizontalFOVDegress);
        return FMath::RadiansToDegrees(2.0f * FMath::Atan(FMath::Tan(HorizontalFOVRadians * 0.5) * ViewportAspectRatioHW));
    }
}

ASG_Pawn::ASG_Pawn()
{
    PrimaryActorTick.bCanEverTick = false;
    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    check(Camera);
    Camera->SetupAttachment(Origin);
}
void ASG_Pawn::UpdateLocation(const Snake::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin)
{
    Dim = InDim;
    CellSize = InCellSize;
    GridOrigin = InGridOrigin;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.AddUObject(this, &ASG_Pawn::OnViewportResized);

#if WITH_EDITOR
    OnViewportResized(Viewport, 0.0f);
#endif
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Value)
{
    if (!Viewport || !Viewport->GetSizeXY().Y || !Dim.height )
    {
        return;
    }

    const float WorldWidth = Dim.width * CellSize;
    const float WorldHeight = Dim.height * CellSize;

    const float ViewportAspectRatio = static_cast<float>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const float GridAspectRatio = static_cast<float>(Dim.width) / Dim.height;

    float LocationZ = 0.0f;

    if (ViewportAspectRatio <= GridAspectRatio)
    {
        LocationZ = WorldWidth / HalfFOVTan(Camera->FieldOfView);
    }
    else
    {
        check(ViewportAspectRatio) const float VerticalFOV = CalculateHalfVerticalFOVTan(Camera->FieldOfView, 1.0 / ViewportAspectRatio);
        LocationZ = WorldHeight / HalfFOVTan(VerticalFOV);
    }

    const FVector NewPawnLocation = GridOrigin.GetLocation() + 0.5f * FVector(WorldHeight, WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}
