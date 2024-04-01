#ifndef board_h
#define board_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include "matrix.h"

using namespace std;

class Board
{
    matrix<bool> column;
    matrix<bool> square;
    matrix<int> grid;
    matrix<bool> rows;
    int grid_size = 9;

    
public:
    Board(string filename);
    void print();
    int index_square(int x, int y);
    void changeVal(int x, int y, int value);
    void rechangeVal(int x, int y, int value);
    bool isSolved();
    
};

#endif /* board_h */

