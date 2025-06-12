// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class GameOfLifeRule final : public IRule
{
    const char* GetName() override
    {
        return "Game of Life";
    }

    CellState GetCellState(Cell* cell) override;
};