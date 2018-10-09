#include <stdio.h>
#include <stdlib.h>

int main (){

/**
int floor[5][5] = {
{0, 1, 0, 0, 1},
{1, 1, 0, 0, 1},
{1, 0, 0, 1, 1},
{1, 1, 1, 1, 0},
{0, 0, 1, 0, 0}
};
*/

int floor[10][16] = {
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0},
{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
{0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
{0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
};

int cardinal;
int x;
    x = 9;
int y;
    y = 9;
int north;
int south;
int east;
int west;

char emptyroom[] = "[]";
char activeroom[] = "{}";


//printf("%d\n\n", floor[9][9]);

do{
    printf("\n\nTHE HALL GOES: ");

    //NORTH
    if (floor[y-1][x] == 1){
        printf("[NORTH] ");
        north = 1;
    }
    else{
        north = 0;
        //printf("THERE IS NOT A ROOM TO THE NORTH\n");
    }

    //SOUTH
    if (floor[y+1][x] == 1){
        printf("[SOUTH] ");
        south = 1;
    }
    else{
        south = 0;
        //printf("THERE IS NOT A ROOM TO THE SOUTH\n");
    }

    //EAST
    if (floor[y][x+1] == 1){
        printf("[EAST] ");
        east = 1;
    }
    else{
        east = 0;
        //printf("THERE IS NOT A ROOM TO THE EAST\n");
    }

    //WEST
    if (floor[y][x-1] == 1){
        printf("[WEST] ");
        west = 1;
    }
    else{
        west = 0;
        //printf("THERE IS NOT A ROOM TO THE WEST\n");
    }
        //Printing Map Grid
        printf("\n\n\n\n");
        printf("     []      []  [][][][][]   \n");
        printf(" []  []  []  []  []      []   \n");
        printf(" []  [][][][][]  []  [][][]   \n");
        printf(" [][][]      []  []  []  []   \n");
        printf(" []      [][][]      []  []   \n");
        printf(" [][][][][]      [][][]  [][] \n");
        printf("     []  []          []       \n");
        printf(" []  []  []  [][][][][][][]   \n");
        printf(" [][][]  [][][]  []      []   \n");
        printf("                 {}    [][]   \n");
        printf("\n\n\n");


    printf("\nCHOOSE A DIRECTION:\n\n");
    printf("1:\tNORTH\n");
    printf("2:\tSOUTH\n");
    printf("3:\tEAST\n");
    printf("4:\tWEST\n\n\n\n");

    //printf("5:\tMAP\n");

    scanf("%d", &cardinal);

    if (cardinal == 1 && north == 1){
        y = y - 1;
    }
    else if (cardinal == 2 && south == 1){
        y = y + 1;
    }
    else if (cardinal == 3 && east == 1){
        x = x + 1;
    }
    else if (cardinal == 4 && west == 1){
        x = x - 1;
    }
    /*else if (cardinal == 5){
        printf("\n\n");
        printf("     []      []  [][][][][]   \n");
        printf(" []  []  []  []  []      []   \n");
        printf(" []  [][][][][]  []  [][][]   \n");
        printf(" [][][]      []  []  []  []   \n");
        printf(" []      [][][]      []  []   \n");
        printf(" [][][][][]      [][][]  [][] \n");
        printf("     []  []          []       \n");
        printf(" []  []  []  [][][][][][][]   \n");
        printf(" [][][]  [][][]  []      []   \n");
        printf("                 {}    [][]   \n");
        printf("\n\n");

    }
*/
}while (1);



//


/*
do{

    if (roomtype == floor[4][2]){
        printf("A LOCKED DOOR IS DIRECTLY SOUTH. THE CORRIDOR CONTINUES NORTH, PRESS '1' TO GO NORTH\n");
        scanf("%d", &cardinal);
            if (cardinal == 1){
                roomtype = floor[3][2];
                cardinal = 0;
            }
    }
    else if (roomtype == floor[3][2]){
        printf("THE CORRIDOR COMES TO AN INTERSECTION.  PRESS '1' TO GO NORTH, '2' TO GO SOUTH, '3' TO GO EAST, '4' TO GO WEST.");
        scanf("&d", cardinal);
            if (cardinal == 1){
                roomtype == floor[2][2];
            }
            else if (cardinal == 2){
                roomtype == floor[4][2];
            }
            else if (cardinal == 3){
                roomtype == floor[3][4];
            }
            else if (cardinal == 4){
                roomtype == floor[3][1];
            }
    }


printf("\n%d\n",roomtype);
}while (1);
*/

return (0);
}

