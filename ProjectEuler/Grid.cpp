#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sstream>

typedef unsigned int ui;

std::vector<int> Grid::LoadGrid(const std::string& _file)
{
  std::fstream file(_file);
  std::string str;
  while (std::getline(file, str, ' '))
  {
    m_grid.push_back(std::atoi(str.c_str()));  // NOLINT
  }
  return m_grid;
}

int Grid::GetValue(const int _x, const int _y) const
{
  if (_x < 0 || _x >= 20)
    return 0;

  if (_y < 0 || _y >= 20)
    return 0;

  if (m_grid.size() != 400)
    return 0;

  return m_grid[_x + _y * 20];
}

void Grid::PrintGrid() const
{
  if (m_grid.size() < 400)
  {
    std::cout << "Grid is not properly loaded" << std::endl;
    return;
  }

  for (ui j = 0; j < 20; j++)
  {
    for (ui i = 0; i < 20; i++)
    {
      std::cout << GetValue(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

