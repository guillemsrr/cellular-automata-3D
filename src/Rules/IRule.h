// Copyright (c) Guillem Serra. All Rights Reserved.

#pragma once
#include "../Cell.h"

class IRule
{
public:
    virtual ~IRule() = default;

    virtual const char* GetName()
    {
        return "Rule";
    }

    virtual CellState GetCellState(Cell* cell) = 0;
};