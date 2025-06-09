#include "ExpandingRule.h"

CellState ExpandingRule::GetCellState(Cell* cell)
{
    int neighborCount = 0;
    for (auto neighbor : cell->CachedNeighbors)
    {
        if (neighbor->IsAlive())
        {
            neighborCount++;
        }
    }

    if (cell->IsAlive())
    {
        if (neighborCount >= 4 && neighborCount <= 8)
        {
            return CellState::Alive;
        }
        return CellState::Decaying;
    }

    if (cell->IsDecaying())
    {
        if (--cell->decayTicks <= 0)
        {
            return CellState::Dead;
        }
        return CellState::Decaying;
    }

    if (neighborCount >= 6 && neighborCount <= 7)
    {
        return CellState::Alive;
    }

    return CellState::Dead;
}