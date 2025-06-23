// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <vector>
#include "Cell.h"

class Grid
{
public:
    Grid();

    Cell* GetCell(int x, int y, int z);
    void SetDimensions(int width, int height, int depth);

    int Width, Height, Depth;

private:
    enum NeighborhoodType
    {
        Moore,
        VonNeumann,
    };

    std::vector<Cell> _cells;

    NeighborhoodType _neighborhoodType = NeighborhoodType::Moore;

    const std::vector<Vector3> VonNeumannOffsets = {
        {1, 0, 0},
        {-1, 0, 0},
        {0, 1, 0},
        {0, -1, 0},
        {0, 0, 1},
        {0, 0, -1}
    };

    int Index(int x, int y, int z) const;
    std::vector<Cell*> GetNeighbors(const Cell* cell);
};