// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class InfiniteRule : public IRule
{
public:
    InfiniteRule();

private:
    const char* GetName() override
    {
        return "Infinite";
    }

    std::vector<int> _neighboursAlive;
    std::vector<int> _neighboursBorn;
    CellState GetCellState(Cell* cell) override;
};