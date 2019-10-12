#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void takeInputs();
void resultInFile();
static int grid[9][9];

int checkValidation(int row, int col, int number);
bool subgridValidation(int row, int col, int number);
bool colValidation(int col,int number);
bool rowValidation(int row,int number);

int f(int row, int col)
{
    if(col == 9 && row < 9)
    {
        col = 0;
        row +=1;
    }

    if(row == 9)    //base case: grid in end point
    {
        return 1;
    }
   /* if(col == 9)    //base case 1: reaches outside the grid from right side
    {
        row += 1;
        col = 0;
    }
    //base case 2: reaches end position in grid
    else if(row == 8 && col == 9)  return 1;    //end recursion calling
*/
    if(grid[row][col] == 0) // if cell is empty
    {
        int number = 1;
        for( ; number < 10 ; number++ )
        {
            if(row == 4 && col == 1)    //testing
            {
                printf("number:%d, grid[%d][%d]=%d\n",number,row,col,grid[row][col]);
                 printf("subgridVali:%d\n",subgridValidation((row/3)*3, (col/3)*3, number));
                printf("colValidation:%d\n",colValidation(col, number));
                printf("rowValidation:%d\n",rowValidation(row, number));
                int index=0;
                for( ; index < 9 ; index++)
                {
                    printf("%d, ",grid[row][index]);
                }
                printf("\n....................\n");
            }
            if(checkValidation(row, col, number))
            {
              //  if(row == 6 && (col == 4 || col == 5 || col == 6 || col ==7))    //testing
                //{
                  //  printf("number:%d, grid[%d][%d]=%d\n",number,row,col,grid[row][col]);
                //}

                grid[row][col] = number;    //adding valid number in grid
                if( f(row, col+1)== 1)  //if able to solve then try with new number
                {
                    return 1;
                }
                else
                {
                    grid[row][col] = 0; // current grid cell is to make zero
                }
            }

        }
       // grid[row][col] == 0;    //testing
    }
    else    //if cell is not empty
    {
        return f( row, col+1 );  //calling for next column (or cell) to solve
    }

    //testing
  //  printf("\nfalse return start: Row = %d, Col = %d\n",row, col);
    //cell remains as empty, unable to solve current cell to fill with nonzero number
    return 0;
}
int main()
{
    takeInputs();
    f(0,0);
    /*
    printf("grid value:\n");
    int row =0 , col=0;
    for( ;row < 9; row++)
    {
        for(col =0 ; col <9 ; col++)
        {
            printf("%d, ", grid[row][col]);
        }
         printf("\n");
     }
     */
    resultInFile();
    return 0;
}

int checkValidation(int row, int col, int number)
{
    int sub_grid_row = (row/3)*3;   //extract sub grid initial row index
    int sub_grid_col = (col/3)*3;   //extract sub grid initial col index
    if(subgridValidation(sub_grid_row, sub_grid_col, number) && colValidation(col,number) && rowValidation(row,number))
        return 1;
    return 0;
}

bool subgridValidation(int row, int col, int number)
{
    int tempCol=0;
    int subgrid_row_length, subgrid_col_length;
    subgrid_row_length = row + 3;
    subgrid_col_length = col + 3;

    for( ; row < subgrid_row_length ; row++)
    {
        for(tempCol = col ; tempCol < subgrid_col_length ; tempCol++)
        {
            if(grid[row][tempCol] == number)
            {
                return false;
            }
        }
    }
    //printf("subgridVali:tryNubmer= %d\n",number);
    return true;
}

bool colValidation(int col,int number)
{
    int row;
    for( row= 0; row < 9; row++)
    {
        if(grid[row][col] == number)
        {
            return false;
        }
    }
    return true;
}

bool rowValidation(int row,int number)
{
    int col;
    for( col= 0; col < 9; col++)
    {
        if(grid[row][col] == number)
        {
            return false;
        }
    }
    return true;
}

void takeInputs()
{
    FILE *myFile;
    myFile = fopen("input.txt", "r");
    //myFile = fopen("input2.txt", "r");

    int i,j;

    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
        //read file into array
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            fscanf(myFile, "%d,", &grid[i][j]);
        }
    }

    /*for (i = 0; i < 9; i++){
        printf("Number is: %d\n\n", grid[i]);
    }
    */
    fclose(myFile);
}

void resultInFile()
{
    FILE *fp;
    int i,j;
    fp = fopen("output.txt", "w+");
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            fprintf(fp,"%d ", grid[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
