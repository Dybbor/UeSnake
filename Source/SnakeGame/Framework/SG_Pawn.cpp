#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

namespace
{
    double HalfFOVTan(double FOVDegrees)
    {
        return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5));
    }

    double CalculateHalfVerticalFOVTan(double HorizontalFOVDegress, double ViewportAspectRatioHW)
    {
        const double HorizontalFOVRadians = FMath::DegreesToRadians(HorizontalFOVDegress);
        return FMath::RadiansToDegrees(2.0 * FMath::Atan(FMath::Tan(HorizontalFOVRadians * 0.5) * ViewportAspectRatioHW));
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
void ASG_Pawn::UpdateLocation(const Snake::Dim& InDim, uint32 InCellSize, const FTransform& InGridOrigin)
{
    Dim = InDim;
    CellSize = InCellSize;
    GridOrigin = InGridOrigin;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto Viewport = GEngine->GameViewport->Viewport;

    Viewport->ViewportResizedEvent.Remove(ResizedWindowHandle);
    ResizedWindowHandle = Viewport->ViewportResizedEvent.AddUObject(this, &ASG_Pawn::OnViewportResized);

#if WITH_EDITOR
    OnViewportResized(Viewport, 0);
#endif
}

void ASG_Pawn::EndPlay(const EEndPlayReason::Type Reason)
{
    FViewport::ViewportResizedEvent.Remove(ResizedWindowHandle);
    Super::EndPlay(Reason);
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Value)
{
    if (Viewport != GetOwnViewport())
        return;

    if (!Viewport || !Viewport->GetSizeXY().Y || !Dim.height)
        return;

    const double WorldWidth = Dim.width * CellSize;
    const double WorldHeight = Dim.height * CellSize;

    const double ViewportAspectRatio = static_cast<double>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const double GridAspectRatio = static_cast<double>(Dim.width) / Dim.height;

    double LocationZ = 0.0;

    if (ViewportAspectRatio <= GridAspectRatio)
    {
        LocationZ = WorldWidth / HalfFOVTan(Camera->FieldOfView);
    }
    else
    {
        check(ViewportAspectRatio) const double VerticalFOV = CalculateHalfVerticalFOVTan(Camera->FieldOfView, 1.0 / ViewportAspectRatio);
        LocationZ = WorldHeight / HalfFOVTan(VerticalFOV);
    }

    const FVector NewPawnLocation = GridOrigin.GetLocation() + 0.5 * FVector(WorldHeight, WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}

FViewport* ASG_Pawn::GetOwnViewport() const
{
    const auto World = GetWorld();
    const auto GVC = World ? World->GetGameViewport() : nullptr;
    return GVC ? GVC->Viewport : nullptr;
}
