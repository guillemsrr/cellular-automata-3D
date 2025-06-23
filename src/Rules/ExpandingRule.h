// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "IRule.h"

class ExpandingRule final : public IRule
{
    const char* GetName() override
    {
        return "Expanding";
    }
    CellState GetCellState(Cell* cell) override;
};