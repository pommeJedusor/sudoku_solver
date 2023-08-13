#include <stdlib.h>
#include <stdio.h>

#define EMPTY_CASE 0

int get_moves(int* grid, int index)
{
    //set the moves to playable by default
    //111 111 111
    int moves = 511;
    //vertical check
    for (int i = index-index/9*9;i<81;i+=9)
    {
        if (grid[i]==0)
        {
            continue;
        }
        if (moves & (1 << (grid[i]-1)))
        {
            //printf("vertical: %d\n",moves);
            moves ^= (1 << (grid[i]-1));
            //printf("%d\n\n",moves);
        }
    }
    //horizontal check
    for (int i=index-index%9; i<index-index%9+9; i++)
    {
        if (grid[i]==0)
        {
            continue;
        }
        if (moves & (1 << (grid[i]-1)))
        {
            //printf("horizontal: %d\n",moves);
            moves ^= (1 << (grid[i]-1));
            //printf("%d\n\n",moves);
        }
    }
    //square check
    int square_index;
    //horizontal loop
    //printf("square, index: %d\n",index);
    for (int x=index%9/3*3; x<index%9/3+3; x++)
    {
        //vertical loop
        for (int y=index/27*3; y<index/27*3+3; y++)
        {
            square_index = y*9 + x;
            //printf("square: %d\n",square_index);
            if (grid[square_index]==0)
            {
                continue;
            }
            if (moves & (1 << (grid[square_index]-1)))
            {
                //printf("square: %d\ni: %d\nsquare: %d\nx: %d\ny: %d\n",moves,square_index,grid[square_index],x,y);
                moves ^= (1 << (grid[square_index]-1));
                //printf("%d\n\n",moves);
            }
        }
    }
    return moves;
}

int sudoku(int* grid)
{
    int result;
    //get the first empty case
    char index = 81;
    for (int i=0;i<81;i++)
    {
        //printf("%d\n",i);
        if (grid[i]==EMPTY_CASE)
        {
            index = i;
            break;
        }
    }
    //si complet retourne la position
    if (index==81)
    {
        return 1;
    }
    int moves = get_moves(grid, index);
    for (int i=1; i<=9; i++)
    {
        if (moves & (1 << (i-1)))
        {
            //printf("truc: %d\n",i);
            grid[index] = i;
            result = sudoku(grid);
            if (result)
            {
                return 1;
            }
            grid[index] = 0;
            
        }
    }
    return 0;
}

void see_grid(int* grid)
{
    for (int i=0; i<81; i++)
    {
        printf("%d",grid[i]);
        if ((i+1)%9==0)
        {
            printf("\n");
        }
    }
}

void main()
{
    int grid[81] = {8,5,2,1,3,7,6,4,9,9,3,4,8,0,0,2,0,0,0,6,0,0,0,0,0,3,0,4,0,0,3,5,9,0,0,0,0,9,0,0,0,0,0,5,0,0,0,0,6,7,2,0,0,4,0,2,0,0,0,0,0,6,0,0,0,9,0,0,0,4,2,7,6,4,1,7,2,3,0,0,5};
    int result = sudoku(grid);
    printf("result: %d\n",result);
    see_grid(grid);
    //printf("moves: %d\n",get_moves(grid, 13));
}