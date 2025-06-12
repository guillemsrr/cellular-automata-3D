#include "GameOfLifeRule.h"
#include "../Grid.h"

CellState GameOfLifeRule::GetCellState(Cell* cell)
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
        if (neighborCount == 2 || neighborCount == 3)
        {
            return CellState::Alive;
        }
        return CellState::Dead;
    }

    if (cell->IsDecaying())
    {
        return CellState::Dead; // Or remove this block entirely if you want strict Conway behavior
    }

    if (neighborCount == 3)
    {
        return CellState::Alive;
    }

    return CellState::Dead;
}