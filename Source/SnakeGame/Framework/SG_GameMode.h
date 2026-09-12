#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Game.h"
#include "GameFramework/GameModeBase.h"
#include "SG_GameMode.generated.h"

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
    GENERATED_BODY()

    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"));
    FIntPoint GridSize{10, 10};

private:
    TUniquePtr<Snake::Game> Game;
};
