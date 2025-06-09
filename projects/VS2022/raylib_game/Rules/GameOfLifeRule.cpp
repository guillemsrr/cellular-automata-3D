#include "GameOfLifeRule.h"
#include "../Grid.h"

CellState GameOfLifeRule::GetCellState(Cell* cell)
{
    int numberNeighbors = 0;
    for (auto neighbor : cell->CachedNeighbors)
    {
        if (neighbor->IsAlive())
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