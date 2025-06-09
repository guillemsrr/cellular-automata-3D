// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class FocusedRule final : public IRule
{
public:
    FocusedRule();

private:
    std::vector<int> _neighboursAlive;
    std::vector<int> _neighboursBorn;
    CellState GetCellState(Cell* cell) override;
};