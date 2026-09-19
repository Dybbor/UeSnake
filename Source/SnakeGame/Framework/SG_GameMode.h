#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"));
    FIntPoint GridSize{10, 10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"));
    int32 CellSize{10};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_Grid> GridVisualClass;

private:
    TUniquePtr<Snake::Game> Game;

    UPROPERTY()
    TObjectPtr<ASG_Grid> GridVisual;
};
