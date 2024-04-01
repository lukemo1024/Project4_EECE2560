// this is the majority of the code. It initializes a board and prints the boards and the corresponding conflicts.
#include "board.h"

Board::Board(string filename)  // constructor for Board class, takes file name as string
{
    // set length to grid size (9)
    grid.resize(grid_size, grid_size);
    square.resize(grid_size, grid_size);
    rows.resize(grid_size, grid_size);
    column.resize(grid_size, grid_size);
    

   // input of board
    ifstream inFile;
    inFile.open(filename);
    // fail to open file check
    if (!inFile)
    {
        cout << "Cannot open file" << endl;
        exit(0);
    }

    char ch;
    for (int i = 0; i < grid_size; i++) // navigates through the input file
    {
        for (int j = 0; j < grid_size; j++)
        {
            inFile >> ch;
            if (ch != '.')
            {
                // update value of cell
                grid[i][j] = ch - '0';
            } // end if
            if (ch == '.')
            {
                // blank cell is -1
                grid[i][j] = -1;
            }
        }
    }
    inFile.close();
    
    // the following code gives the conflicts in the rows
    rows = false;
    // nested for loop to get through grid
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != -1)
            {
                // this updates to true if there is a conflict
                rows[i][(grid[i][j] - 1)] = true;
            }
        }
    }

    // the following code gives the conflicts in the cols
    column = false;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[j][i] != -1)
            {
                // this updates to true if there is a conflict
                column[i][(grid[j][i] - 1)] = true;
            }
        }
    }

    // the following code gives the conflicts in the squares
    square = false;
    //defines which square we are using
    int intSqr1 = 0;
    int intSqr2 = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int i = intSqr1; i < ((grid_size / 3) + intSqr1); i++)
        {
            for (int j = intSqr2; j < ((grid_size / 3) + intSqr2); j++)
            {
                if (grid[i][j] != -1)
                {
                    square[x][(grid[i][j] - 1)] = true;
                } // end if
            } // end for
        } // end for
        
        switch (x)
        {
            case 0:
            case 1:
            case 6:
            case 7: intSqr1 = intSqr1 + 3;
                break;
            case 3:
            case 4: intSqr1 = intSqr1 - 3;
                break;
            case 2:
            case 5: intSqr2 = intSqr2 + 3;
                break;
        }
        
    }
    
}

// this function prints the board, and prints three additional conflict boards for rows, cols, and squares
void Board::print()
{
    cout << "BOARD: " << endl;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cout << grid[i][j] << " ";
        }
        
        cout << "\n";
    }
    cout << endl << endl << "ROW CONFLICTS: " << endl;
    
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cout << rows[i][j] << " ";
        }
        
        cout << "\n";
    }
    
    cout << endl << endl << "COLUMN CONFLICTS:" << endl;
    
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cout << column[i][j] << " ";
        }
        
        cout << "\n";
    }
    
    cout << endl << endl << "SQUARE CONFLICTS: " << endl;
    
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cout << square[i][j] << " ";
        }
        
        cout << "\n";
    }
}

// this function returns the square the cell is located in. It counts down first and then right, instead of left to right then up and down.
int Board::index_square(int x, int y)
{
    if (x >= 0 && x <= 2)
    {
        switch(y)
        {
            case 0:
            case 1:
            case 2: return 0;
                break;
            case 3:
            case 4:
            case 5: return 5;
                break;
            case 6:
            case 7:
            case 8: return 6;
                break;
        }
    }
    else if (x >= 3 && x <= 5)
    {
        switch (y)
        {
            case 0:
            case 1:
            case 2: return 1;
                break;
            case 3:
            case 4:
            case 5: return 4;
                break;
            case 6:
            case 7:
            case 8: return 7;
                break;
        }
    }
    else
    {
        switch (y)
        {
            case 0:
            case 1:
            case 2: return 2;
                break;
            case 3:
            case 4:
            case 5: return 3;
                break;
            case 6:
            case 7:
            case 8: return 8;
                break;
        }
    }
    return -1;
} 

// changeVal function allows for the changing of the value in empty cell and corrects the conflicts
void Board::changeVal(int x, int y, int value)
{
    // changes square
    grid[x][y] = value;

    // update all conflicts
    rows[x][value - 1] = true;
    column[y][value - 1] = true;
    square[index_square(x, y)][value - 1] = true;
}

// does the opposite of chnageVal function, sets a cell to -1 (empty)
void Board::rechangeVal(int x, int y, int value)
{
    // make value empty
    grid[x][y] = -1;

    // updates all conflicts
    rows[x][value - 1] = false;
    column[y][value - 1] = false;
    square[index_square(x, y)][value - 1] = false;
}

// this function is used to see if the puzzle is solved
// makes sure there is no -1 values in the puzzle
// this proves it is solved, as if there are no conflicts, it is fully solved
bool Board::isSolved()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] == -1)
            {
                return false;
            }
        }
    }
    return true; 
}
