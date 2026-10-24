#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Framework/SG_GameMode.h"
#include "Framework/SG_Pawn.h"

#if WITH_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext | EAutomationTestFlags::HighPriority)
UWorld* World;

END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
    using namespace Snake;

    Describe("Framework",
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
            It("SnakeGameModeShouldSetupCorrectly",
                [this]()
                {
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this]()
                        {
                            TestTrueExpr(World->GetAuthGameMode<ASG_GameMode>() != nullptr);
                            return true;
                        }));
                });
            It("SnakePawnShouldSetupCorrectly",
                [this]()
                {
                    ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
                        [this]()
                        {
                            auto Pawn = World->GetFirstPlayerController()->GetPawn<ASG_Pawn>();
                            TestTrueExpr(Pawn != nullptr);
                            return true;
                        }));
                });
        });
}
#endif