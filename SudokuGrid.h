/*
  Authour: Jihoon Og
  Date: 3/15/18

  This class implements a Sudoku puzzle grid

  All valid coordinates are 1-9 (row and column)
*/

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <iostream>

class SudokuGrid {
public:
  static const int SIZE = 9;

  SudokuGrid();
  ~SudokuGrid() {};

  bool empty(int row, int col) const;
  bool isValid(int row, int col, int val) const;
  bool isValid() const;
  void put(int row, int col, int val);
  void clear(int row, int col);
  void clear();

  friend std::istream& operator>>(std::istream& is, SudokuGrid& sgrid);
  friend std::ostream& operator<<(std::ostream& os, SudokuGrid& sgrid);

private:
  static const int EMPTY = 0;
  int grid[SIZE][SIZE];
};

#endif
