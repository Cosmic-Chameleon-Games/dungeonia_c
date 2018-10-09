#include <stdio.h>
#include <stdlib.h>

int main (){

int floor[5][5] = {
{0, 0, 0, 0, 0},
{0, 0, 1, 1, 0},
{1, 0, 1, 0, 1},
{1, 1, 1, 1, 1},
{1, 0, 1, 0, 0}
};

int roomtype;
int cardinal;
int coord;


roomtype = floor[4][2];

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

return (0);
}
