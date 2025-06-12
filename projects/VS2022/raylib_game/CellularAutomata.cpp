#include "CellularAutomata.h"

CellularAutomata::CellularAutomata() : _probability(0.2f), _grid(nullptr), _rule(nullptr)
{
}

void CellularAutomata::Initialize()
{
    _grid = new Grid();
    SetDefault();
}

void CellularAutomata::SetRule(std::shared_ptr<IRule> rule)
{
    this->_rule = rule;
}

void CellularAutomata::SetDefault()
{
    Cell::MaxDecayTicks = 6;
    _probability = 0.2f;
    SetDimensions(30, 30, 30);
}

void CellularAutomata::Randomize()
{
    for (int x = 0; x < _grid->Width; x++)
    {
        for (int y = 0; y < _grid->Height; y++)
        {
            for (int z = 0; z < _grid->Depth; z++)
            {
                CellState state = CellState::Dead;
                float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                if (random < _probability)
                {
                    state = CellState::Alive;
                }
                Cell* cell = _grid->GetCell(x, y, z);
                if (cell)
                {
                    cell->SetState(state);
                }
            }
        }
    }
}

void CellularAutomata::Update()
{
    std::vector<CellState> nextStates;
    nextStates.reserve(_grid->Width * _grid->Height * _grid->Depth);

    for (int z = 0; z < _grid->Depth; z++)
    {
        for (int y = 0; y < _grid->Height; y++)
        {
            for (int x = 0; x < _grid->Width; x++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                cell->Update();
                nextStates.push_back(_rule->GetCellState(cell));
            }
        }
    }

    int index = 0;
    for (int z = 0; z < _grid->Depth; z++)
    {
        for (int y = 0; y < _grid->Height; y++)
        {
            for (int x = 0; x < _grid->Width; x++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                cell->SetState(nextStates[index++]);
            }
        }
    }
}

void CellularAutomata::Draw() const
{
    for (int x = 0; x < _grid->Width; x++)
    {
        for (int y = 0; y < _grid->Height; y++)
        {
            for (int z = 0; z < _grid->Depth; z++)
            {
                Cell* cell = _grid->GetCell(x, y, z);
                cell->Draw();
            }
        }
    }
}

Vector3 CellularAutomata::GetDimensions() const
{
    return {static_cast<float>(_grid->Width), static_cast<float>(_grid->Height), static_cast<float>(_grid->Depth)};
}

void CellularAutomata::SetAliveProbability(float probability)
{
    this->_probability = probability;
}

void CellularAutomata::SetDimensions(int x, int y, int z)
{
    _grid->SetDimensions(x, y, z);
}

void CellularAutomata::AddDimensions(int x, int y, int z)
{
    SetDimensions(_grid->Width + x, _grid->Height + y, _grid->Depth + z);
}

IRule* CellularAutomata::GetRule()
{
    return _rule.get();
}