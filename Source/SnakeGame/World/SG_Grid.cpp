#include "World/SG_Grid.h"
#include "Components/LineBatchComponent.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All);

ASG_Grid::ASG_Grid()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASG_Grid::BeginPlay()
{
    Super::BeginPlay();
}

void ASG_Grid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawGrid();
}

void ASG_Grid::SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 InCellSize)
{
    if (!Grid.IsValid())
    {
        UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null"));
    }

    GridDim = Grid.Get()->dim();
    CellSize = InCellSize;
    WorldWidth = GridDim.width * CellSize;
    WorldHeight = GridDim.height * CellSize;
}

void ASG_Grid::DrawGrid()
{
    const auto World = GetWorld();

    if (!World)
        return;

    const auto LineBatcher = World->GetLineBatcher(UWorld::ELineBatcherType::World);

    if (!LineBatcher)
        return;

    for (int32 i = 0; i < GridDim.height + 1; ++i)
    {
        const auto StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
        LineBatcher->DrawLine(StartLocation, StartLocation + GetActorRightVector() * WorldWidth, FLinearColor::Red, 0, 2.0f);
    }

    for (int32 i = 0; i < GridDim.width + 1; ++i)
    {
        const auto StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
        LineBatcher->DrawLine(StartLocation, StartLocation + GetActorForwardVector() * WorldWidth, FLinearColor::Red, 0, 2.0f);
    }
}