#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace Snake
{
    class Grid
    {
    public:
        Grid(const Dim& dim);

        [[nodiscard]] Dim dim() const;

    private:
        void initWalls();
        void printDebug() const;
        int32 posToIndex(int32 x, int32 y) const;

    private:
        const Dim c_dim;
        TArray<CellType> m_cells;
    };
}