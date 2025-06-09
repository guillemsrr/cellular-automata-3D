#include "CellularAutomata.h"

CellularAutomata::CellularAutomata() : _grid(nullptr), rule(nullptr)
{
}

void CellularAutomata::SetRule(std::shared_ptr<IRule> rule)
{
    this->rule = rule;
}

void CellularAutomata::Randomize(float probability)
{
    for (int x = 0; x < _grid->_width; x++)
    {
        for (int y = 0; y < _grid->_height; y++)
        {
            for (int z = 0; z < _grid->_depth; z++)
            {
                CellState state = CellState::Dead;
                float random = rand() % 1000 / 1000.f;
                if (random < probability)
                {
                    state = CellState::Alive;
                }
                _grid->GetCell(x, y, z)->SetState(state);
            }
        }
    }
}

void CellularAutomata::Update()
{
    std::vector<CellState> nextStates;
    nextStates.reserve(_grid->_width * _grid->_height * _grid->_depth);

    for (int z = 0; z < _grid->_depth; z++)
    {
        for (int y = 0; y < _grid->_height; y++)
        {
            for (int x = 0; x < _grid->_width; x++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                nextStates.push_back(rule->GetCellState(cell));
            }
        }
    }

    int index = 0;
    for (int z = 0; z < _grid->_depth; z++)
    {
        for (int y = 0; y < _grid->_height; y++)
        {
            for (int x = 0; x < _grid->_width; x++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                cell->SetState(nextStates[index++]);
            }
        }
    }
}

void CellularAutomata::Draw() const
{
    for (int x = 0; x < _grid->_width; x++)
    {
        for (int y = 0; y < _grid->_height; y++)
        {
            for (int z = 0; z < _grid->_depth; z++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                cell->Draw();
            }
        }
    }
}

void CellularAutomata::SetGrid(Grid* grid)
{
    this->_grid = grid;
}