#pragma once

#include "CoreMinimal.h"

namespace Snake
{
    struct Dim
    {
        int32 width;
        int32 height;

        bool operator==(const Dim&) const = default;
    };

    enum class CellType
    {
        Empty = 0,
        Wall,
        Food,
        Snake
    };

    struct Settings
    {
        Dim gridSize;

        bool operator==(const Settings&) const = default;
    };
}