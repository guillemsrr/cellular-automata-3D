#include "CustomRule.h"

CellState CustomRule::GetCellState(Cell* cell)
{
    int numberNeighbors = 0;
    for (auto neighbor : cell->CachedNeighbors)
    {
        if (!neighbor->IsDead())
        {
            numberNeighbors++;
        }
    }

    if (cell->IsAlive())
    {
        return (numberNeighbors >= 5 && numberNeighbors <= 7) ? CellState::Alive : CellState::Decaying;
    }
    else
    {
        return (numberNeighbors == 6) ? CellState::Alive : CellState::Dead;
    }
}