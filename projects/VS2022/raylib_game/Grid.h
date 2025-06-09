// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include <vector>
#include "Cell.h"

class Grid {
public:
    Grid();

    Cell* GetCell(int x, int y, int z);
    void SetDimensions(int width, int height, int depth);
    
    int _width, _height, _depth;

private:
    std::vector<Cell> _cells;

    int Index(int x, int y, int z) const;
};