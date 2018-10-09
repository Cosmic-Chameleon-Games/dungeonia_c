#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_i 12
#define SIZE_j 16
#define ROOMCHAR 2

int mapGen(int floor[SIZE_i][SIZE_j]);
void mapPrint(int floor[SIZE_i][SIZE_j]);

int main()
{
    int floor[SIZE_i][SIZE_j] = {0};
    int i = 0;
    int j = 0;
    //char floordisplay[SIZE_i][SIZE_j] = {'[]'};
    //char empty[] = '  ';
    //char room[] = '[]';
    //char roomactive[] = '{}';
    mapGen(*floor);
    mapPrint(floor);
}
int mapGen(int floor[SIZE_i][SIZE_j])
{
    //int i = 0;
    //int j = 0;
    int i = 5;
    int j = 5;
    //int floorgrid[SIZE_i][SIZE_j] = {0};
    int type = 0;
    int direction = 0;
    int count = 0;
    int next = 0;
    ///Seed
    floor[i][j] = 1;
    srand(time(NULL));
    while(count < 30)
    {
        count++;
        next = 0;
        while(next != 1)
        {
            direction = rand()% 4;
            if (direction == 0)
            {
                if (floor[i][j+1] != 1 && j+1 != SIZE_j)
                {
                    floor[i][j+1] = 1;
                    j++;
                    next = 1;
                }
            }
            else if (direction == 1)
            {
                if (floor[i][j-1] != 1 && j-1 != 0)
                {
                    floor[i][j-1] = 1;
                    j--;
                    next = 1;
                }
            }
            else if (direction == 2)
            {
                if (floor[i+1][j] != 1 && i+1 != SIZE_i)
                {
                    floor[i+1][j] = 1;
                    j++;
                    next = 1;
                }
            }
            else if (direction == 3)
            {
                if (floor[i-1][j] != 1 && i-1 != 0)
                {
                    floor[i-1][j] = 1;
                    i--;
                    next = 1;
                }
            }
        }
    }
    /*for (i = 0; i < SIZE_i; i++)
    {
        for (j = 0; j < SIZE_j; j++)
        {
            if (i == 0 || j == 0 || i == SIZE_i-1 || j == SIZE_j-1) floor[i][j] = 0;
            else
            {
                //type = rand()% 2;
                //floor[i][j] = rand()% 2;
                ///if (floor[i+1][j+1] == 1 || floor[i+1][j-1] == 1 || floor[i-1][j+1] == 1 || floor[i-1][j-1] == 1) floor[i][j] = 0;
            }

        }
    }*/
    return(floor);
}

void mapPrint(int floor[SIZE_i][SIZE_j])
{
    int i = 0;
    int j = 0;
    int printgrid[SIZE_i][SIZE_j] = {0};

    for (i = 0; i < SIZE_i; i++)
    {
        printf("\n");
        for (j = 0; j < SIZE_j; j++)
        {
            //printf("%d ", floor[i][j]);
            switch(floor[i][j])
            {
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("[]");
                    break;
                case 2:
                    printf("{}");
                    break;
            }
        }
    }

}
