// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class InfiniteRule: public IRule
{
public:
    InfiniteRule();

private:
    std::vector<int> _neighboursAlive;
    std::vector<int> _neighboursBorn;
    CellState GetCellState(Cell* cell) override;
};