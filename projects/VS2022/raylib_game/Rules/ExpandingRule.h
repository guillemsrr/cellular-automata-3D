// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class ExpandingRule final : public IRule
{
    CellState GetCellState(Cell* cell) override;
};