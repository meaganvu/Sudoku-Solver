#include <iostream>
using namespace std;
#include <vector>

Sudoku::Sudoku(){
    defaultNumber = 0;
};

Sudoku::Sudoku(int defNum, int g [9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            grid[i][j] = g[i][j];
        }
    }
    defaultNumber = 0;
    cout << "Intital Grid: Unsolved" <<endl;
    print();
    cout << endl;
    Solve();
    cout << "Final Grid: Solved" <<endl;
    print();
    cout << checkPossible(6,5,9) <<endl;
};

void Sudoku::print(){
    for(int i = 0; i < 9; i ++){ // row up down
        for(int j = 0; j < 9; j++){ //collum left right
            cout << grid[j][i] << " ";
        }
        cout << endl;
    }
};
   

bool Sudoku:: scanRow(int collum, int num){
    bool search = false;
    for(int i = 0; i < 9; i++){
        if(grid[collum][i] == num){
            search = true;
        }
    }
    return search;
};

bool Sudoku:: scanCollum(int row, int num){
    bool search = false;
    for(int i = 0; i < 9; i++){
        if(grid[i][row] == num){
            search = true;
        }
    }
    return search;
};

void Sudoku::addPossible(){
    for(int i = 0; i < 9; i++){ // row index
        for(int j = 0; j < 9; j++){ // collum index
            for(int num = 1; num < 10; num++){
                if(!scanCollum(i, num)&& !scanRow(j, num)&&grid[j][i] == 0&& !scanBox(i,j,num)){
                    possible[j][i].push_back(num);
                }
            }
        }
        
    }
};

bool Sudoku::scanBox(int row, int collum, int num){
    /*
    - find the box this is in
    - search for the number
    */
    bool search = false;
    int boxRow = row/3 * 3;
    int boxCollum = collum/3 * 3;   
    for(int i = boxRow; i < boxRow + 3; i++){ // row up down
        for(int j = boxCollum; j < boxCollum + 3; j++){
            if(grid[j][i] == num){
            search = true;
        }
        }
    }
    return search;
};

void Sudoku::printPossible(int row, int collum){
    if(possible[collum][row].size() == 0){
            cout << "this spot is filled in" << endl;
            cout << grid[collum][row] << endl;
        }
    for(int i = 0; i < possible[collum][row].size(); i++){
            cout << possible[collum][row][i] << endl;
    }
};

bool Sudoku:: addDigit(){
    bool adds = false;
        for(int i = 0; i < 9; i++){ // row index
        for(int j = 0; j < 9; j++){ // collum index
            if(possible[j][i].size() == 1){ // one option left
                adds = true;
                grid[j][i] = possible[j][i][0];
            }
            else{
                for(int num = 0; num < 10; num++){
                    if(checkPossible(i,j,num) && possible[j][i].size() != 0){
                        grid[j][i] = num;
                        adds = true;
                    }
                }
            }
        }
    }

    return adds;
}

void Sudoku:: Solve(){
    int i = 0;
    while(!filled()){
        addPossible();
        if(!addDigit()){
            cout << "stuck" <<endl;
            cout << i << endl;
            break;
        }
        
        clearPossible();
        i++;
    }
}

void Sudoku:: clearPossible(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            possible[j][i].clear();
        }
    }
}

bool Sudoku::filled(){
    bool filled = true;
    int row = 0;

    while(row < 9 && filled == true){
        int collum =0;
        while (collum < 9 && filled == true){
            if(grid[collum][row] == 0){
                filled = false;
                //cout << "collum: " << collum << endl;
            }
            collum ++;
        }
        //cout << "row: " << row << endl;
        row++;
    }
    return filled;
};

bool Sudoku::checkPossible(int row, int collum, int num){
    if(find(possible[collum][row].begin(), possible[collum][row].end(), num) != possible[collum][row].end()){
    int countCol = 0;
    int countRow = 0;
    int countBox = 0;
    for(int i = 0; i < 9; i++){
        if(find(possible[collum][i].begin(), possible[collum][i].end(), num) != possible[collum][i].end()){
            countCol ++;
        }
        if(find(possible[i][row].begin(), possible[i][row].end(), num) != possible[i][row].end()){
            countRow ++;
        }
    }
    int boxRow = row/3 * 3;
    int boxCollum = collum/3 * 3;   
    for(int i = boxRow; i < boxRow + 3; i++){ // row up down
        for(int j = boxCollum; j < boxCollum + 3; j++){
            if(find(possible[j][i].begin(), possible[j][i].end(), num) != possible[j][i].end()){
            countBox ++;
        }
        }
    }
    if(row == 6 && collum ==5 && num == 9){
    //    cout << countCol <<endl;
    //     cout << countRow << endl;
    //     cout << countBox <<endl; 
    }
    if(countCol == 1 || countRow == 1 || countBox == 1){
        return true; // not the only possible number 
    }
    return false; // only possible number
    }
    return false; // only possible number
}
