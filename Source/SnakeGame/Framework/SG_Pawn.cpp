#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

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
void ASG_Pawn::UpdateLocation(const Snake::Dim& Dim, int32 CellSize, const FTransform& GridOrigin)
{
    const float WorldWidth = Dim.width * CellSize;
    const float WorldHeight = Dim.height * CellSize;
    const float HalfAngleRad = FMath::DegreesToRadians(Camera->FieldOfView * 0.5f);
    float LocationZ = 0.5f * WorldWidth / FMath::Tan(HalfAngleRad);
    const FVector NewPawnLocation = GridOrigin.GetLocation() + FVector(0.5f * WorldHeight, 0.5f * WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}
