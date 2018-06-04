#pragma once
#include <vector>

class Grid
{
public:
  std::vector<int> LoadGrid(const std::string& _file);
  int GetValue(const int _x, const int _y) const;
  void PrintGrid() const;
private:
  std::vector<int> m_grid;
};
