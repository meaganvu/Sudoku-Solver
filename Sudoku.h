#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
using namespace std;

class Sudoku{
private:
    int grid [9][9];
    vector<int> possible [9][9];
    int defaultNumber; // how many numbers are filled in
    bool scanRow(int collum, int num); // does this row contain this number?
    bool scanCollum(int row, int num); // does this collum contain this number?
    void addPossible(); // looks at the entire grid and adds all possible numbers to each box
    bool scanBox(int row, int collum, int num); // looks at the 3x3 box the spot is in
    //bool Solve(); // overall solver
    bool addDigit(); // after adding possible number, add the obvious digits
    void clearPossible(); //resets possible
public:
    Sudoku();
    Sudoku(int defNum, int g[9][9]);
    void print();
    void printPossible(int row, int collum);
    void Solve(); // overall solver
    bool filled();
    bool checkPossible(int row, int collum, int num); // check to see if this is the only possible number in box row collum every if there is other numbers in possible
    void clearPosRC(); // clear possible row collum of a number if it can only 
};

#include "Sudoku.cpp"
#endif