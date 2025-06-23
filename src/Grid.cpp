#include "Grid.h"

Grid::Grid() : Width(5), Height(5), Depth(5)
{
}

void Grid::SetDimensions(int width, int height, int depth)
{
    if (width <= 0)
    {
        width = 1;
    }
    if (height <= 0)
    {
        height = 1;
    }
    if (depth <= 0)
    {
        depth = 1;
    }

    Width = width;
    Height = height;
    Depth = depth;

    const int totalSize = width * height * depth;
    Vector3 offset = {static_cast<float>(width) / 2.f, 0.f, static_cast<float>(depth) / 2.f};

    if (_cells.size() != totalSize)
    {
        _cells.resize(totalSize);
    }

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int idx = Index(x, y, z);
                _cells[idx] = Cell(x, y, z);
                Vector3 position = {
                    static_cast<float>(x) - offset.x,
                    static_cast<float>(y) - offset.y,
                    static_cast<float>(z) - offset.z
                };
                _cells[idx].Position = position;
            }
        }
    }

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                Cell* currentCell = GetCell(x, y, z);
                if (!currentCell)
                {
                    continue;
                }

                currentCell->CachedNeighbors = GetNeighbors(currentCell);
            }
        }
    }
}

int Grid::Index(const int x, const int y, const int z) const
{
    return x + y * Width + z * Width * Height;
}

std::vector<Cell*> Grid::GetNeighbors(const Cell* cell)
{
    std::vector<Cell*> neighbors;

    if (_neighborhoodType == NeighborhoodType::Moore)
    {
        for (int offsetZ = -1; offsetZ <= 1; ++offsetZ)
        {
            for (int offsetY = -1; offsetY <= 1; ++offsetY)
            {
                for (int offsetX = -1; offsetX <= 1; ++offsetX)
                {
                    Cell* neighbor = GetCell(cell->GridX + offsetX, cell->GridY + offsetY, cell->GridZ + offsetZ);
                    if (!neighbor || neighbor == cell)
                    {
                        continue;
                    }
                    neighbors.push_back(neighbor);
                }
            }
        }
    }
    else
    {
        for (const Vector3& offset : VonNeumannOffsets)
        {
            Cell* neighbor = GetCell(cell->GridX + static_cast<int>(offset.x),
                                     cell->GridY + static_cast<int>(offset.y),
                                     cell->GridZ + static_cast<int>(offset.z));

            if (!neighbor || neighbor == cell)
            {
                continue;
            }
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

Cell* Grid::GetCell(int x, int y, int z)
{
    if (x < 0 || x >= Width || y < 0 || y >= Height || z < 0 || z >= Depth)
    {
        return nullptr;
    }

    int index = Index(x, y, z);
    if (index < 0 || index >= _cells.size())
    {
        return nullptr;
    }
    return &_cells[index];
}