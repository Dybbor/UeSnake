#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Game.h"

#if WITH_AUTOMATION_TESTS

DEFINE_SPEC(
    FSnakeGame, "Snake", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriority)

void FSnakeGame::Define()
{
    using namespace Snake;

    Describe("CoreGame",
        [this]()
        {
            It("GridShouldExist",
                [this]()
                {
                    const Settings GameSettings{.gridDims = {10, 40}};
                    const Game CoreGame = Game(GameSettings);
                    TestTrueExpr(CoreGame.grid().IsValid());
                });
        });
}
#endif