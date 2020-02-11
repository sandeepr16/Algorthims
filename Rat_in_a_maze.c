#include<stdio.h>
#include<conio.h>
#define ROW 7
#define COL 5


/*Similar to rat in a maze.
* Given a 2d matrix and a start location, find the nearest exit location.
* There would be blockages at certain positions and they would be marked with 0.
* You cannot go through those locations.
* Locations through which we can move are marked as 1
* The solution is to bactrack when we cannot move further
The algorithm has been checked with many mazes including

1 1 1 1 1
0 0 0 0 1
1 1 1 0 1
1 0 1 1 1
1 0 0 0 0
1 0 1 1 1
1 1 1 0 1
*/

    static int x = -1;
    static int y = -1;
    enum movement {FORWARD, BACKWARD, UP, DOWN}move;

    void Maze(int arr[ROW][COL], int row, int column,int ansr[30],int ansc[30],enum movement move)
    {
        int i;
        if (arr[row][column] == 1)//If there is a path
        {
        ansr[++x] = row;
        ansc[++y] = column;
        if ((column == COL - 1) && (row == ROW-1))//Rat has reached exit
        {
            printf("\nSolution\n");
            for (i = 0; i <= x; i++)

            {
            printf("(%d,%d) ",ansr[i], ansc[i]);
            }
            getch();
            exit(0);
        }
        else if(column == COL-1)//Last column
        {
            if(move == DOWN)//Moved from last column down
            {
              if(arr[row+1][column] == 0)
              {
                Maze(arr, row, column-1, ansr, ansc,BACKWARD);//Move to previous column
              }
            }
            Maze(arr,row+1,column,ansr,ansc,DOWN);//Move to next row
        }
        else if(row == ROW-1)//Last row
        {
            if(move == FORWARD)
            {
              if(arr[row][column+1] == 0)
              {
                Maze(arr, row-1, column, ansr, ansc,UP);//Move to previous column
              }
            }
            Maze(arr,row,column+1,ansr,ansc,FORWARD);//Move to next column
        }
        else if(move == BACKWARD)
        {
            if(arr[row+1][column] == 1)
               Maze(arr, row+1, column, ansr, ansc,DOWN);//Move to next row
            else if(arr[row][column-1] == 1)
               Maze(arr, row, column-1, ansr, ansc,BACKWARD);
            else if(arr[row-1][column] == 1)
               Maze(arr, row-1, column, ansr, ansc,UP);
        }
        else if(move == UP)//Moved up
        {
          if(arr[row][column-1] == 1)
            Maze(arr, row, column-1, ansr, ansc,BACKWARD);//Move to previous column
          else
            Maze(arr, row, column+1, ansr, ansc,FORWARD);
        }
        else
        {
            Maze(arr, row, column + 1, ansr, ansc,FORWARD);//Move to next column
            Maze(arr, row + 1, column, ansr, ansc,DOWN);//Move to next row

          if((arr[row][column+1] == 0) && (arr[row+1][column] == 0))
          {
            Maze(arr, row, column-1, ansr, ansc,BACKWARD);//Move to previous column
          }
        }
        }//if

        if((ansr[x] == row) && (ansc[y] == column))//Erase the paths bactracked
        {
        ansc[y--]=0;
        ansr[x--]=0;
        }
    }//Maze

    void main()
    {
        int arr[ROW][COL],i,j;//Maze
        int ansr[30] = { 0 };//Row value of solution
        int ansc[30] = { 0 };//Column value of solution
        clrscr();
        //Input with either 0/1
        for (i = 0; i < ROW; i++)
        {
        for (j = 0; j < COL; j++)
        {
            scanf("%d",&arr[i][j]);
        }
        }
        printf("Maze Structure\n");
        for (i = 0; i < ROW; i++)
        {
        for (j = 0; j < COL; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
        }
        Maze(arr,0,0,ansr,ansc,FORWARD);//Rat starts at location (0,0)
        printf("No solution");
        
    }

