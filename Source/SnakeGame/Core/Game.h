#pragma once

#include "Types.h"

namespace Snake
{
    class Grid;

    class Game
    {
    public:
        Game(const Settings&);

        TSharedPtr<Grid> grid() const;

    private:
        const Settings c_settings;
        TSharedPtr<Grid> m_grid;
    };
}