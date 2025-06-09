// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class CustomRule final : public IRule
{
public:
    CellState GetCellState(Cell* cell) override;
};