/*
    Authour: Jihoon Og
    Date: 3/17/18

    This is the driver program that solves sudoku puzzles
*/
#include <iostream>
#include <fstream>
#include "SudokuGrid.h"

bool solve(SudokuGrid& grid, int row, int col, int& count);
void nextcell(int& row, int& col);
bool unassignedLocation(SudokuGrid& grid);
void mainmenu();
void inputformat();

int main(){
    SudokuGrid grid;
    std::ifstream file;
    std::string str;
    int menu;
    mainmenu();
    std::cin>>menu;
    switch(menu){
        case 1:
            inputformat();
            std::cin>>grid;
            break;
        case 2:
            std::cout<<"Enter the filename of the unsolved puzzle: ";
            std::cin>>str;
            file.open(str);
            file>>grid;
            file.close();
            break;
        default:
            std::cout<<"Not a valid input. Exiting\n";
            return 0;
    }
    // clearing the screen
    std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    int row = 1;
    int col = 1;
    int count = 0;
    if(!grid.isValid()){
        std::cout<<"Puzzle is invalid\n";
        return 0;
    }
    if(solve(grid,row,col,count)){
        std::cout<<"Solution\n\n";
        std::cout<<grid<<"\n";
    }else{
        std::cout<<"No solution was found\n";
    }
    return 0;
}

void nextcell(int& row, int& col){
    ++col;
    if(col == 10){
        col = 1;
        ++row;
    }
    if(row == 10 && col == 10){
        row = 1;
        col = 1;
    }
}

bool solve(SudokuGrid& grid, int row, int col, int& count){
    int rowtemp, coltemp;
    // returns successful if all the locations are assigned
    if(!unassignedLocation(grid)){
        return true;
    }
    // skip the cell if it's not empty
    if(!grid.empty(row,col)){
        rowtemp = row;
        coltemp = col;
        // return the indices for the next cell [row-major]
        nextcell(rowtemp, coltemp);
        // solve for the next cell
        return solve(grid, rowtemp, coltemp,count);
    }else{
        // testing values from 1 to 9 seeing if the assignment works 
        for(int d = 1; d <= 9; ++d){
            // testing to see if d is a valid assignment
            if(grid.isValid(row,col,d)){
                // if d is a valid assignment it is written into the cell
                grid.put(row,col,d);
                rowtemp = row;
                coltemp = col;
                // return the indices for the next cell [row-major]
                nextcell(rowtemp,coltemp);
                // solve for the bext cell returns true if successful
                if(solve(grid,rowtemp,coltemp,count)){
                    return true;
                }
            }
        }
    }
    // clear the cell as it was an invalid
    grid.clear(row,col); 
    // backtrack as no assignments are successful
    return false;   
}

bool unassignedLocation(SudokuGrid& grid){
    for(int row = 1; row <= 9; ++row){
        for(int col = 1; col <= 9; ++col){
            if(grid.empty(row,col)){
                return true;
            }
        }
    }
    return false;
}

void mainmenu(){
    std::cout   <<"\n"
                <<"+---------------------------+\n"
                <<"|       Sudoku Solver       |\n"
                <<"| Press 1 for manual input  |\n"
                <<"| Press 2 for file input    |\n"
                <<"+---------------------------+\n"
                <<"\n"
                <<"Input: ";
}

void inputformat(){
    std::cout   <<"\n"
                <<"Input format\n\n"
                <<"....9.2.1\n"
                <<"4......3.\n"
                <<".785.....\n"
                <<".....864.\n"
                <<"7...4...9\n"
                <<".412.....\n"
                <<".....681.\n"
                <<".3......6\n"
                <<"8.2.5....\n\n"
                <<"The blank spaces are .\n"
                <<"Enter only valid numbers [1-9].\n"
                <<"There are no error checking for invalid inputs.\n\n"
                <<"Puzzle input:\n\n";
}