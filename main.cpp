#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    Board sudoku("sudoku1.txt"); // constructor for board class
    sudoku.print();
    if (sudoku.isSolved()) // tests if board is solved
    {
        cout << endl << "Puzzle: Solved" << endl;
    }
    else
    {
        cout << endl << "Puzzle: Not Solved" << endl;
    }
    return 0;
}
