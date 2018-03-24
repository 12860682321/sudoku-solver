/*
  Author: Jihoon Og
  Date: 3/15/18

  This class implements a Sudoku puzzle grid

  All valid coordinates are 1-9 (row and column)
*/

#include <algorithm>
#include <cctype>
#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(){
  for(int i = 0; i < SIZE; ++i){
    for(int j = 0; j < SIZE; ++j){
      grid[i][j] = EMPTY;
    }
  }
}

bool SudokuGrid::empty(int row, int col) const {
  return grid[row-1][col-1] == EMPTY;
}

bool SudokuGrid::isValid(int row, int col, int val) const {

  // check row
  for(int j = 0; j < SIZE; ++j){
    if(j != col-1 && val == grid[row-1][j]){
      return false;
    }
  }

  // check col
  for(int i = 0; i < SIZE; ++i){
    if(i != row-1 && val == grid[i][col-1]){
      return false;
    }
  }

  int boxr = (row-1) / 3 * 3;
  int boxc = (col-1) / 3 * 3;
  for(int i = boxr; i < boxr+SIZE/3; ++i){
    for(int j = boxc; j < boxc+SIZE/3; ++j){
      if((i != row-1 || j != col-1) && val == grid[i][j]) {
        return false;
      }
    }
  }

  return true;
}


bool SudokuGrid::isValid() const{
  bool used[SIZE+1];

  // check each row to check for duplicates
  for(int i = 0; i < SIZE; ++i){
    std::fill(used+1, used+SIZE+1, false);
    for(int j = 0; j < SIZE; ++j){
      if(grid[i][j] != EMPTY && used[grid[i][j]]){
        return false;
      }
      used[grid[i][j]] = true;
    }
  }

  // check each col to check for duplicates
  for(int j = 0; j < SIZE; ++j){
    std::fill(used+1, used+SIZE+1, false);
    for(int i = 0; i < SIZE; ++i){
      if(grid[i][j] != EMPTY && used[grid[i][j]]){
        return false;
      }
      used[grid[i][j]] = true;
    }
  }

  // checking each block
  for(int bi = 0; bi < SIZE; bi += SIZE/3){
    for(int bj = 0; bj < SIZE; bj += SIZE/3){
      std::fill(used+1, used+SIZE+1, false);
      for(int i = 0; i < SIZE/3; ++i){
        for(int j = 0; j < SIZE/3; ++j){
          if(grid[bi+i][bj+j] != EMPTY && used[grid[bi+i][bj+j]]){
            return false;
          }
          used[grid[bi+i][bj+j]] = true;
        }
      }
    }
  }
  return true;
}

void SudokuGrid::put(int row, int col, int val){
  grid[row-1][col-1] = val;
}

void SudokuGrid::clear(int row, int col){
  grid[row-1][col-1] = EMPTY;
}

void SudokuGrid::clear(){
  for(int i = 0; i < SIZE; ++i){
    for(int j = 0; j < SIZE; ++j){
      grid[i][j] = EMPTY;
    }
  }
}

std::istream& operator>>(std::istream& is, SudokuGrid& sgrid){
  char c;
  for(int i = 0; i < SudokuGrid::SIZE; ++i){
    for(int j = 0; j < SudokuGrid::SIZE; ++j){
      is>>c;
      sgrid.grid[i][j] = (std::isdigit(c)) ? c - '0' : SudokuGrid::EMPTY;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, SudokuGrid& sgrid){
  for(int i = 0; i < SudokuGrid::SIZE; ++i){
    if(i > 0 && i % (SudokuGrid::SIZE/3) == 0){
      os <<"---+---+---\n";
    }
    for(int j = 0; j < SudokuGrid::SIZE; ++j){
      if(j > 0 && j % (SudokuGrid::SIZE/3) == 0){
        os<<"|";
      }
      os << static_cast<char>(sgrid.grid[i][j]+'0');
    }
    os<<"\n";
  }
  return os;
}