#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SnakeGame/Core/Grid.h"

#if WITH_AUTOMATION_TESTS

DEFINE_SPEC(
    FSnakeGrid, "Snake", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
    using namespace Snake;

    Describe("CoreGrid",
        [this]()
        {
            It("DimMightIncludeWalls",
                [this]()
                {
                    const Snake::Grid Grid{Dim{10, 12}};
                    TestTrueExpr(Grid.dim() == Dim{12, 14});
                });
        });
}
#endif