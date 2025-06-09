// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class GameOfLifeRule final : public IRule
{
    CellState GetCellState(Cell* cell) override;
};