// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "../Cell.h"

class Grid;

class IRule
{
public:
    virtual ~IRule() = default;

    virtual CellState GetCellState(Cell* cell) = 0;
};