#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Kismet/GameplayStatics.h"
#include "World/SG_Grid.h"

#if WITH_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(
    FSnakeWorld, "Snake", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriority)
UWorld* World;

END_DEFINE_SPEC(FSnakeWorld)

void FSnakeWorld::Define()
{
    using namespace Snake;

    Describe("WorldGrid",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("/Game/Levels/GameLevel");
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this]()
                        {
                            World = AutomationCommon::GetAnyGameWorld();
                            return World != nullptr;
                        }));
                });
            It("GameMapShouldExist",
                [this]()
                {
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this]()
                        {
                            TestNotNull("World exists", World);
                            return true;
                        }));
                });
            It("OnlyOneGridActorShouldExist",
                [this]()
                {
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this]()
                        {
                            TArray<AActor*> Grids;
                            UGameplayStatics::GetAllActorsOfClass(World, ASG_Grid::StaticClass(), Grids);

                            TestTrueExpr(Grids.Num() == 1);

                            if (Grids.Num() > 0)
                            {
                                TestNotNull("Snake grid actor exists", Grids[0]);
                            }

                            return true;
                        }));
                });
        });
}
#endif