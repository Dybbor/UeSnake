#include "Core/Game.h"

#include "Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

namespace Snake
{
    Snake::Game::Game(const Settings& settings)
        : c_settings{settings}
        , m_grid{MakeShared<Grid>(settings.gridDims)}
    {
    }

    TSharedPtr<Grid> Game::grid() const
    {
        return m_grid;
    }
}