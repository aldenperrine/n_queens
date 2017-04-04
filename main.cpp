//  Brute Force Solution for the Eight Queens Puzzle
//  Only works on small board sizes
//  O(n^n)
//
//  Created by Alden Perrine on 12/21/16.
//  Copyright © 2016 All rights reserved.
//

//int SIZE is the length of one side of the board
//Change SIZE to find solutions to different size boards
const int SIZE = 8;

//Counter of number of solutions found
int counter = 0;

//Include output library to output solutions
#include <iostream>

//Class location
//Used to compare whether queens can be placed in different
// locations on the board
class location
{
    public:
        //Default constructor to allow grid to be created
        location()
        {
            row = 0;
            col = 0;
            des = ' ';
        }
        //Constructor that sets the row and column of the location
        // and sets the description to 0
        location(int r, int c)
        {
            row = r;
            col = c;
            des = '0';
        }
        //Function that takes in a character and sets the description
        // to the character
        void setDes(char d)
        {
            des = d;
        }
        //Function that increases the value of the description by one
        void incDes()
        {
            ++des;
        }
        //Function that decreases the value of the description by one
        void decDes()
        {
            --des;
        }
        //Function that returns the description of the location
        char getDes() const
        {
            return des;
        }
        //Function that returns the row of the location
        int getRow() const
        {
            return row;
        }
        //Function that returns the column of the location
        int getCol() const
        {
            return col;
        }
    private:
        //Row the location is at
        int row;
        //Column the location is at
        int col;
        //Description of the location
        //  Q: Queen at the location
        //  0: No queen and no queen can attack the location
        //  Any other integer: The number of queens that
        //   can attack the location
        char des;
};

//Function setAttack
//Parameters:
//  2 dimentional array of locations with both dimentions length SIZE
//  Pointer to a location
bool setAttack(location grid[SIZE][SIZE], location* loc)
{
    int row = loc->getRow();
    int col = loc->getCol();
    while(row>0)
    {
        --row;
        grid[row][col].incDes();
    }
    row = loc->getRow()+1;
    while(row<SIZE)
    {
        grid[row][col].incDes();
        ++row;
    }
    row = loc->getRow();
    while(col>0)
    {
        --col;
        grid[row][col].incDes();
    }
    col = loc->getCol()+1;
    while(col<SIZE)
    {
        grid[row][col].incDes();
        ++col;
    }
    row = loc->getRow()-1;
    col = loc->getCol()-1;
    while(row>-1&&col>-1)
    {
        grid[row][col].incDes();
        --row;
        --col;
    }
    row = loc->getRow()-1;
    col = loc->getCol()+1;
    while(row>-1&&col<SIZE)
    {
        grid[row][col].incDes();
        --row;
        ++col;
    }
    row = loc->getRow()+1;
    col = loc->getCol()-1;
    while(row<SIZE&&col>-1)
    {
        grid[row][col].incDes();
        ++row;
        --col;
    }
    row = loc->getRow()+1;
    col = loc->getCol()+1;
    while(row<SIZE&&col<SIZE)
    {
        grid[row][col].incDes();
        ++row;
        ++col;
    }
    return true;
}

bool undoAttack(location grid[SIZE][SIZE], location* loc)
{
    int row = loc->getRow();
    int col = loc->getCol();
    while(row>0)
    {
        --row;
        grid[row][col].decDes();
    }
    row = loc->getRow()+1;
    while(row<SIZE)
    {
        grid[row][col].decDes();
        ++row;
    }
    row = loc->getRow();
    while(col>0)
    {
        --col;
        grid[row][col].decDes();
    }
    col = loc->getCol()+1;
    while(col<SIZE)
    {
        grid[row][col].decDes();
        ++col;
    }
    row = loc->getRow()-1;
    col = loc->getCol()-1;
    while(row>-1&&col>-1)
    {
        grid[row][col].decDes();
        --row;
        --col;
    }
    row = loc->getRow()-1;
    col = loc->getCol()+1;
    while(row>-1&&col<SIZE)
    {
        grid[row][col].decDes();
        --row;
        ++col;
    }
    row = loc->getRow()+1;
    col = loc->getCol()-1;
    while(row<SIZE&&col>-1)
    {
        grid[row][col].decDes();
        ++row;
        --col;
    }
    row = loc->getRow()+1;
    col = loc->getCol()+1;
    while(row<SIZE&&col<SIZE)
    {
        grid[row][col].decDes();
        ++row;
        ++col;
    }
    return true;
}

bool printBoard(location grid[SIZE][SIZE])
{
    for(int r = 0; r < SIZE; ++r)
    {
        for(int c = 0; c < SIZE; ++c)
        {
            if(grid[r][c].getDes()=='Q')
                std::cout << grid[r][c].getDes() << " ";
            else
                std::cout << 'X' << " ";
            
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return true;
}

bool placeQueen(location grid[SIZE][SIZE], int iter)
{
    if(iter==SIZE)
    {
        printBoard(grid);
        ++counter;
        return true;
    }
    location* row = grid[iter];
    for(int i = 0; i < SIZE; ++i)
    {
        if((row+i)->getDes()=='0')
        {
            location* loc = row+i;
            char hold = loc->getDes();
            loc->setDes('Q');
            setAttack(grid, loc);
            placeQueen(grid, iter+1);
            undoAttack(grid, loc);
            loc->setDes(hold);
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    location grid[SIZE][SIZE];
    for(int r = 0; r < SIZE; ++r)
        for(int c = 0; c < SIZE; ++c)
            grid[r][c] = location(r, c);
    placeQueen(grid, 0);
    std::cout << counter << std::endl << std::endl;
    return 0;
}
