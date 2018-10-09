/***
 *     _____    __  __   __   __   ______   ______   ______   __   __   __   ______
 *    /\  __-. /\ \/\ \ /\ "-.\ \ /\  ___\ /\  ___\ /\  __ \ /\ "-.\ \ /\ \ /\  __ \
 *    \ \ \/\ \\ \ \_\ \\ \ \-.  \\ \ \__ \\ \  __\ \ \ \/\ \\ \ \-.  \\ \ \\ \  __ \
 *     \ \____- \ \_____\\ \_\\"\_\\ \_____\\ \_____\\ \_____\\ \_\\"\_\\ \_\\ \_\ \_\
 *      \/____/  \/_____/ \/_/ \/_/ \/_____/ \/_____/ \/_____/ \/_/ \/_/ \/_/ \/_/\/_/
 *
 *  Code by Nathan MacAdam
 *
 *  Todo:
 *  -Make towns do more
 *  -Add floors
 *  -Add more classes
 *  -Saves??????
 *  -Add more bosses
    -shop mp potions
    -Add item menu in combat rather than potion stuff
 *
 *  Fix:
 *  -dagger is all screwy with its strings(Make sure all class features work)
 *  -make sure encounters all work
 *  -Get floors filled out
 *  -Fix death health problem
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 128

void print_image(FILE *fptr);

void play_game();
//Do the other functions need to go here
void combat();

//Global Variables

    //Player Variables
    int playermaxhp;
        playermaxhp = 20;
    int playerhp;
        playerhp = 20;
    int playerexp;
        playerexp = 0;
    int playerlvl;
        playerlvl = 1;
    int exptolvl;
        exptolvl = 100;
    int expneeded;
        expneeded = 100;
    int playerclass;
        playerclass = 0;

    int playermaxmp;
        playermaxmp = 20;
    int playermp;
        playermp = 20;

    int weaponactive;
        weaponactive = 1;

    int weaponavailable[5] = {1, 1, 0, 0, 0};//{FIST, SHORTSWORD, LONGSWORD, WHIP, DAGGER}

    int playergp = 0;
    int potioncount;
        potioncount = 1;
    int mppotioncount;
        mppotioncount = 0;

    int devmode = 0;

    int flooritems[4] = {1, 1, 1, 1};
    int bossonoff[4] = {1, 1, 1, 1};//Minotaur, Oculant...

    int run;

    //Developer Variables
    int dev_monstertype;

    //Mapping & Travel Variables

    int floornumber = 0;
    int flooractive[12][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int floor1[12][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int floor2[12][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int cardinal;
    int x;
        x = 9;
    int y;
        y = 10;
    int north;
    int south;
    int east;
    int west;

    //Not Yet Implemented (Map Marker)
    //char emptyroom[] = "[]";
    //char activeroom[] = "{}";

//Welcome Message & Log
int main()
{
    int enter;

    //Title Splash
    char *filename = "image.txt";
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }

    print_image(fptr);

    fclose(fptr);


    printf("\n\n\n\nWELCOME TO DUNGEONIA\n");
    printf("ENTER DUNGEONIA BY PRESSING '1'\n");
    scanf("%d", &enter);

    if (enter == 1){
        printf("\n\nYOU HAVE ENTERED DUNGEONIA.  THE DOOR CLOSES AND LOCKS BEHIND YOU.\n\n");
        play_game();
    }
    //REVISION HISTORY/LOG
    else if (enter == 0){
        printf("\n\nREVISION HISTORY:\n\n");
        printf("ALPHA 1.4\tMADE STATUS MENU STATIC MAP DISPLAY\n");
        printf("ALPHA 1.4\tADDED FLOOR BASED ENCOUNTERS\n");
        printf("ALPHA 1.4\tADDED FLOORS\n");
        printf("ALPHA 1.3\tADDED CRITITCAL HITS\n");
        printf("ALPHA 1.3\tADDED DISCOVERABLE FLOOR ITEMS\n");
        printf("ALPHA 1.3\tUPDATED DEVELOPER MODE\n");
        printf("ALPHA 1.3\tADDED STATUS EFFECTS\n");
        printf("ALPHA 1.3\tADDED NEW CLASS\n");
        printf("ALPHA 1.3\tADDED MAP TRACKING\n");
        printf("ALPHA 1.3\tADDED BOSS FIGHTS AND MECHANICS\n");
        printf("ALPHA 1.3\tADDED MORE DUNGEON ENCOUNTERS\n");
        printf("ALPHA 1.3\tADDED MONSTERS AND SCALING RANDOM ENCOUNTERS\n");
        printf("ALPHA 1.3\tUPDATED CLASS FEATURES\n");
        printf("ALPHA 1.3\tUPDATED WEAPON SYSTEM\n");
        printf("ALPHA 1.3\tUPDATED DEVELOPER MODE\n");
        printf("ALPHA 1.3\tADDED SHOPS\n");
        printf("ALPHA 1.3\tADDED TOWN\n");
        printf("ALPHA 1.3\tADDED NAVIGATIBLE DUNGEON\n");
        printf("ALPHA 1.2\tADDED CLASS SYSTEM\n");
        printf("ALPHA 1.2\tADDED WEAPON SYSTEM\n");
        printf("ALPHA 1.2\tADDED DEVELOPER MODE\n");
        printf("ALPHA 1.2\tADDED ENCOUNTER DIALOGUE\n");
        printf("ALPHA 1.2\tUPDATED STATUS MENU\n");
        printf("ALPHA 1.1\tADDED RNG GOLD DROPS\n");
        printf("ALPHA 1.1\tADDED HEALTH POTIONS\n");
        printf("ALPHA 1.1\tADDED PLAYER LEVEL\n");
        printf("ALPHA 1.1\tADDED EXPERIENCE POINTS\n");
        printf("ALPHA 1.1\tADDED DYNAMIC MONSTER STATS\n");
        printf("ALPHA 1.1\tADDED RNG MONSTER SPAWN\n");
        printf("ALPHA 1.1\tADDED STATUS MENU\n");
        printf("ALPHA 1.1\tADDED RNG BASED DAMAGE VALUES\n");

        printf("\n\n\nCODE BY NATHAN MACADAM\n");
        printf("Q/A BY ETHAN SUTLEY\n");

        printf("\nRESUME BY PRESSING '1' , OR PRESS '0' FOR DEVELOPER MODE\n");
        scanf("%d", &enter);

        if (enter == 1){
            printf("\n\nYOU HAVE ENTERED DUNGEONIA.  THE DOOR CLOSES AND LOCKS BEHIND YOU.\n\n");
            play_game();
        }
        else if (enter == 0){
            devmode = 1;
            developer_mode();
        }
    }
    //REFUSAL MESSAGE
    else if (enter != 1){
        printf("\nTHEN GO BACK TO THE POOR LANDS FROM WHICH YOU CAME, PEASANT.\n\n");
        return 0;
    }
}

//Title Splash Function
void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];

    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}


void developer_mode()
{

    int devmenu;

    do{
        printf("\n\nDEVELOPER MODE:\n\n");
        printf("1:\tPLAYER MAX HP:\t%d\n", playermaxhp);
        printf("2:\tPLAYER HP:\t%d\n", playerhp);
        printf("3:\tPLAYER MAX MP:\t%d\n", playermaxmp);
        printf("4:\tPLAYER MP:\t%d\n", playermp);

        printf("5:\tPLAYER XP:\t%d\n", playerexp);
        printf("6:\tPLAYER LEVEL:\t%d\n", playerlvl);
        printf("7:\tPLAYER CLASS:\t%d\n", playerclass);
        printf("8:\tPLAYER GP:\t%d\n", playergp);

        printf("\n9:\tACTIVE WEAPON:\t%d\n", weaponactive);
        printf("10:\tUNLOCK ALL WEAPONS\n");
        printf("11:\tTURN OFF RANDOM ENCOUNTERS\n");
        printf("12:\tFORCE COMBAT\n");
        printf("\n0:\tEXIT DEVELOPER MODE\n\n");

        scanf("%d", &devmenu);
        if (devmenu == 1){
            printf("\nENTER NEW MAX PLAYER HP VALUE: ");
            scanf("%d", &playermaxhp);
        }
        else if (devmenu == 2){
            printf("\nENTER NEW PLAYER HP VALUE: ");
            scanf("%d", &playerhp);
        }
        if (devmenu == 3){
            printf("\nENTER NEW MAX PLAYER MP VALUE: ");
            scanf("%d", &playermaxmp);
        }
        else if (devmenu == 4){
            printf("\nENTER NEW PLAYER MP VALUE: ");
            scanf("%d", &playermp);
        }
        else if (devmenu == 5){
            printf("\nENTER NEW PLAYER XP VALUE: ");
            scanf("%d", &playerexp);
        }
        else if (devmenu == 6){
            printf("\nENTER NEW PLAYER LEVEL VALUE: ");
            scanf("%d", &playerlvl);
        }
        else if (devmenu == 7){
            printf("\nENTER NEW PLAYER CLASS VALUE: ");
            scanf("%d", &playerclass);
        }
        else if (devmenu == 8){
            printf("\nENTER NEW PLAYER GP VALUE: ");
            scanf("%d", &playergp);
        }
        else if (devmenu == 9){
            printf("\nENTER ACTIVE WEAPON VALUE: ");
            scanf("%d", &weaponactive);
        }
        else if (devmenu == 10){
            weaponavailable[0] = 1;
            weaponavailable[1] = 1;
            weaponavailable[2] = 1;
            weaponavailable[3] = 1;
            weaponavailable[4] = 1;
            printf("\nALL WEAPON VALUES SET TO TRUE\n\n");
        }
        else if (devmenu == 11){
            printf("\nTURNING OFF RANDOM ENCOUNTERS...\n\n");
            play_game();
        }
        else if (devmenu == 12){
            printf("\nENTER MONSTER VARIABLE: ");
            scanf("%d", &dev_monstertype);
            combat();
        }
        else if (devmenu == 0){
            printf("\nEXITING DEVELOPER MODE...\n\n");
            devmode = 0;
            play_game();
        }
    }while(devmode == 1);
}

void floor_swap()
{
    int yn;
    int xn;

    if (floornumber == 0){
        for (yn = 0; yn < 11; yn++){

            for (xn = 0; xn < 15; xn++){

            flooractive[yn][xn] = floor1[yn][xn];

            }
        }
        floornumber = 1;
        play_game();
    }

    //Floor 1->2 Stairs
    if (y == 4 && x == 9 && floornumber == 1){
        for (yn = 0; yn < 11; yn++){

            for (xn = 0; xn < 15; xn++){

            flooractive[yn][xn] = floor2[yn][xn];

            }
        }
        floornumber = 2;
        y = 5;
        x = 9;
        play_game();
    }
    //Floor 2->1 Stairs
    else if (y == 4 && x == 9 && floornumber == 2){
        for (yn = 0; yn < 11; yn++){

            for (xn = 0; xn < 15; xn++){

            flooractive[yn][xn] = floor1[yn][xn];

            }
        }
        floornumber = 1;
        y = 3;
        x = 9;
        play_game();
    }
}

//********Begin Game Code********

void play_game()
{
    if (floornumber == 0){
        floor_swap();
    }

    int monsterencounter;

    srand(time(NULL));

    //Do Pause for Menu Readability
    int resumeadventure;

    //Map Tracking Variables
    char crossmapxtrue[] = "||";
    char crossmapytrue[] = " =";

    char crossmapfalse[] = "  ";

    int x1;
    int x2;
    int x3;
    int x4;
    int x5;
    int x6;
    int x7;
    int x8;
    int x9;
    int x10;
    int x11;
    int x12;
    int x13;
    int x14;

    int y1;
    int y2;
    int y3;
    int y4;
    int y5;
    int y6;
    int y7;
    int y8;
    int y9;
    int y10;



    //Weapon Exchange System Variables
    int slot0;
    int slot1;
    int slot2;
    int slot3;
    int slot4;
    int slot5;

    char weapon0[] = "FIST";
    char weapon1[] = "SHORTSWORD";
    char weapon2[] = "LONGSWORD";
    char weapon3[] = "WHIP";
    char weapon4[] = "DAGGER";
    char weapon5[] = "PLACEHOLDER";

    char weaponempty[] = " ";

    int weapontype;
    int weaponswap;

    //Weapon Variable Assignment
    weapontype = weaponactive;

    //Fists
    if (weapontype == 0){
        weapontype = weapon0;
    }
    //Shortsword
    else if (weapontype == 1){
        weapontype = weapon1;
    }
    //Longsword
    else if (weapontype == 2){
        weapontype = weapon2;
    }
    //Whip
    else if (weapontype == 3){
        weapontype = weapon3;
    }
    //DAGGER
    else if (weapontype == 4){
        weapontype = weapon4;
    }
    //PLACEHOLDER
    else if (weapontype == 5){
        weapontype = weapon5;
    }

    //Weapon Available Array Check
    //Fists
    if (weaponavailable[0] == 1){
        slot0 = weapon0;
    }
    else if (weaponavailable[0] == 0){
        slot0 = weaponempty;
    }

    //Shortsword
    if (weaponavailable[1] == 1){
        slot1 = weapon1;
    }
    else if (weaponavailable[1] == 0){
        slot1 = weaponempty;
    }

    //Longsword
    if (weaponavailable[2] == 1){
        slot2 = weapon2;
    }
    else if (weaponavailable[2] == 0){
        slot2 = weaponempty;
    }

    //Whip
    if (weaponavailable[3] == 1){
        slot3 = weapon3;
    }
    else if (weaponavailable[3] == 0){
        slot3 = weaponempty;
    }

    //DAGGER
    if (weaponavailable[4] == 1){
        slot4 = weapon4;
    }
    else if (weaponavailable[4] == 0){
        slot4 = weaponempty;
    }

    //PLACEHOLDER
    if (weaponavailable[5] == 1){
        slot5 = weapon5;
    }
    else if (weaponavailable[5] == 0){
        slot5 = weaponempty;
    }

    //Traveling and RNG for Encounters
    do{

        //Encounter Location Function Mapping

        //Town
        if (y == 6 && x == 9 && floornumber == 1){
            town();
        }
        //Class Changer
        if (y == 8 && x == 1 && floornumber == 1){
            encounter();
        }
        //Fortune Teller
        if (y == 1 && x == 3 && floornumber == 1){
            encounter();
        }
        //Minotaur Boss Fight
        if (y == 2 && x == 9 && floornumber == 1 && bossonoff[1] == 1){
            //bossmode = 1;
            combat();
        }
        //Oculant Boss Fight
        if (y == 4 && x == 7 && floornumber == 2 && bossonoff[1] == 1){
            combat();
        }
        //Floor 1->2 Stairs
        if (y == 4 && x == 9 && floornumber == 1){
            floor_swap();
        }

        //Floor 2->1 Stairs
        if (y == 4 && x == 9 && floornumber == 2){
            floor_swap();
        }

        //Potion 1
        if (y == 1 && x == 7 && flooritems[1] == 1 && floornumber == 1){
            encounter();

        }
        //Potion 2
        if (y == 2 && x == 1 && flooritems[2] == 1 && floornumber == 1){
            encounter();

        }
        //Potion 3
        if (y == 6 && x == 14 && flooritems[3] == 1 && floornumber == 1){
            encounter();

        }
        //Potion 4
        if (y == 10 && x == 12 && flooritems[4] == 1 && floornumber == 1){
            encounter();

        }

        //Grid System Movement
        printf("\n\nTHE HALL GOES: ");

        //NORTH
        if (flooractive[y-1][x] == 1){
            printf("[NORTH] ");
            north = 1;
        }
        else{
            north = 0;
            //printf("THERE IS NOT A ROOM TO THE NORTH\n");
        }

        //SOUTH
        if (flooractive[y+1][x] == 1){
            printf("[SOUTH] ");
            south = 1;
        }
        else{
            south = 0;
            //printf("THERE IS NOT A ROOM TO THE SOUTH\n");
        }

        //EAST
        if (flooractive[y][x+1] == 1){
            printf("[EAST] ");
            east = 1;
        }
        else{
            east = 0;
            //printf("THERE IS NOT A ROOM TO THE EAST\n");
        }

        //WEST
        if (flooractive[y][x-1] == 1){
            printf("[WEST] ");
            west = 1;
        }
        else{
            west = 0;
            //printf("THERE IS NOT A ROOM TO THE WEST\n");
        }

        //Map Tracking
        if (x == 1){
            x1 = crossmapxtrue;
        }
        else{
            x1 = crossmapfalse;
        }

        if (x == 2){
            x2 = crossmapxtrue;
        }
        else{
            x2 = crossmapfalse;
        }

        if (x == 3){
            x3 = crossmapxtrue;
        }
        else{
            x3 = crossmapfalse;
        }

        if (x == 4){
            x4 = crossmapxtrue;
        }
        else{
            x4 = crossmapfalse;
        }

        if (x == 5){
            x5 = crossmapxtrue;
        }
        else{
            x5 = crossmapfalse;
        }

        if (x == 6){
            x6 = crossmapxtrue;
        }
        else{
            x6 = crossmapfalse;
        }

        if (x == 7){
            x7 = crossmapxtrue;
        }
        else{
            x7 = crossmapfalse;
        }

        if (x == 8){
            x8 = crossmapxtrue;
        }
        else{
            x8 = crossmapfalse;
        }

        if (x == 9){
            x9 = crossmapxtrue;
        }
        else{
            x9 = crossmapfalse;
        }

        if (x == 10){
            x10 = crossmapxtrue;
        }
        else{
            x10 = crossmapfalse;
        }

        if (x == 11){
            x11 = crossmapxtrue;
        }
        else{
            x11 = crossmapfalse;
        }

        if (x == 12){
            x12 = crossmapxtrue;
        }
        else{
            x12 = crossmapfalse;
        }

        if (x == 13){
            x13 = crossmapxtrue;
        }
        else{
            x13 = crossmapfalse;
        }

        if (x == 14){
            x14 = crossmapxtrue;
        }
        else{
            x14 = crossmapfalse;
        }

        if (y == 1){
            y1 = crossmapytrue;
        }
        else{
            y1 = crossmapfalse;
        }

        if (y == 2){
            y2 = crossmapytrue;
        }
        else{
            y2 = crossmapfalse;
        }

        if (y == 3){
            y3 = crossmapytrue;
        }
        else{
            y3 = crossmapfalse;
        }

        if (y == 4){
            y4 = crossmapytrue;
        }
        else{
            y4 = crossmapfalse;
        }

        if (y == 5){
            y5 = crossmapytrue;
        }
        else{
            y5 = crossmapfalse;
        }

        if (y == 6){
            y6 = crossmapytrue;
        }
        else{
            y6 = crossmapfalse;
        }

        if (y == 7){
            y7 = crossmapytrue;
        }
        else{
            y7 = crossmapfalse;
        }

        if (y == 8){
            y8 = crossmapytrue;
        }
        else{
            y8 = crossmapfalse;
        }

        if (y == 9){
            y9 = crossmapytrue;
        }
        else{
            y9 = crossmapfalse;
        }

        if (y == 10){
            y10 = crossmapytrue;
        }
        else{
            y10 = crossmapfalse;
        }

    //Leveling Variables
    if (playerlvl == 1){
        expneeded = 100;
    }
    else{
        expneeded = exptolvl - playerexp;
    }

    //Class Block
    int classname;

    char playerclass0[] = "NONE";
    char playerclass1[] = "SWORDMASTER";
    char playerclass2[] = "MONSTER HUNTER";
    char playerclass3[] = "MONK";
    char playerclass4[] = "THIEF";
    char playerclass5[] = "MAGICIAN";

    //Class Variable Assignment
    if (playerclass == 0){
        classname = playerclass0;
    }
    else if (playerclass == 1){
        classname = playerclass1;
    }
    else if (playerclass == 2){
        classname = playerclass2;
    }
    else if (playerclass == 3){
        classname = playerclass3;
    }
    else if (playerclass == 4){
        classname = playerclass4;
    }
    else if (playerclass == 5){
        classname = playerclass5;
    }
    if (floornumber == 1){
            //Printing Map Grid
            printf("\n\n\n\n");
            printf("   %s%s%s%s%s%s%s%s%s%s%s%s%s%s \n\n", x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14);
            printf("%s     {}      []  [][][][][]   \tHEALTH:\t\t%d/%d\n", y1, playerhp, playermaxhp);
            printf("%s []  []  []  []  []      []   \tGOLD:\t\t%dGP\n", y2, playergp);
            printf("%s []  [][][][][]  []  [][][]   \tCLASS:\t\t%s\n", y3, classname);
            printf("%s [][][]      []  !!  []  []   \tLEVEL:\t\t%d\n", y4, playerlvl);
            printf("%s []      [][][]      []  []   \tEXPERIENCE:\t%dXP\n", y5, playerexp);
            printf("%s [][][][][]      {}[][]  [][] \tXP->NEXT LEVEL:\t%dXP\n", y6, expneeded);
            printf("%s     []  []          []       \tCURRENT WEAPON:\t%s\n", y7, weapontype);
            printf("%s {}  []  []  [][][][][][][]   \tHEALTH POTIONS:\t%d\n", y8, potioncount);
            printf("%s [][][]  [][][]  []      []   \tMAGIC POTIONS:\t%d\n", y9, mppotioncount);
            printf("%s                 !!    [][]   \n", y10);
            printf("\n\n\n");
    }
    else if (floornumber == 2){
            printf("\n\n\n\n");
            printf("   %s%s%s%s%s%s%s%s%s%s%s%s%s%s \n\n", x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14);
            printf("%s [][][][][]    [][][][][][][] \n", y1);
            printf("%s []      [][][][]  {}  []  [] \n", y2);
            printf("%s [][]        []            [] \n", y3);
            printf("%s   [][][][]  !!  !!  {}[]  [] \n", y4);
            printf("%s [][]  []        []    []  [] \n", y5);
            printf("%s []    [][][][][][][][][]  [] \n", y6);
            printf("%s []    []        []        [] \n", y7);
            printf("%s [][][][]  []{}  [][][]  [][] \n", y8);
            printf("%s   []      []        [][][]   \n", y9);
            printf("%s   [][][][][][][][][][]  [][] \n", y10);
            printf("\n\n\n");

    }

            /**
            printf0("     FT      Po  [][][][][]   \n" FORTUNE TELLER);
            printf1(" Po  []  []  []  []      []   \n");
            printf2(" []  [][][][][]  MB  [][][]   \n" MINOTAUR BOSS);
            printf3(" [][][]      []  ST  []  []   \n" STAIRWELL);
            printf4(" []      [][][]      []  []   \n");
            printf5(" [][][][][]      TN[][]  []Po \n" TOWN);
            printf6("     []  []          []       \n");
            printf7(" CC  []  []  [][][][][][][]   \n" CLASS CHANGER);
            printf8(" [][][]  [][][]  []      []   \n");
            printf9("                 ||    Po[]   \n");
            */


        printf("\nCHOOSE A DIRECTION:\n\n");
        printf("1:\tNORTH\n");
        printf("2:\tSOUTH\n");
        printf("3:\tEAST\n");
        printf("4:\tWEST\n\n");
        //printf("5:\tSTATUS\n");
        printf("5:\tCHANGE WEAPON\n\n");



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
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\nHEALTH:\t\t%d/%d\n", playerhp, playermaxhp);
            printf("GOLD:\t\t%dGP\n", playergp);
            printf("CLASS:\t\t%s\n", classname);
            printf("LEVEL:\t\t%d\n", playerlvl);
            printf("EXPERIENCE:\t%dXP\n", playerexp);
            printf("XP->NEXT LEVEL:\t%dXP\n", expneeded);
            printf("CURRENT WEAPON:\t%s\n", weapontype);
            printf("HEALTH POTIONS:\t%d\n", potioncount);
            printf("MAGIC POTIONS:\t%d\n", mppotioncount);

            do{
                printf("\nPRESS '1' TO RESUME ADVENTURING\n");
                scanf("%d", &resumeadventure);
            }while(resumeadventure == 0);
        }*/
         //Action : Change Weapon
        else if (cardinal == 5){
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\nWEAPONS:\n");
            printf("\n1:\t%s\n", slot0);
            printf("2:\t%s\n", slot1);
            printf("3:\t%s\n", slot2);
            printf("4:\t%s\n", slot3);
            printf("5:\t%s\n", slot4);
                //PLACEHOLDER//printf("6:\t%s\n", slot5);

            scanf("%d", &weaponswap);
            //scanf("%d", weaponactive);
            if (weaponswap == 1 && weaponavailable[0] == 1){
                weaponactive = 0;
                weapontype = weapon0;
            }

            else if (weaponswap == 2 && weaponavailable[1] == 1){
                weaponactive = 1;
                weapontype = weapon1;
            }

            else if (weaponswap == 3 && weaponavailable[2] == 1){
                weaponactive = 2;
                weapontype = weapon2;

            }

            else if (weaponswap == 4 && weaponavailable[3] == 1){
                weaponactive = 3;
                weapontype = weapon3;
            }

            else if (weaponswap == 5 && weaponavailable[4] == 1){
                weaponactive = 4;
                weapontype = weapon4;
            }
            printf("THE %s IS NOW YOUR ACTIVE WEAPON\n", weapontype);
            do{
                printf("\nPRESS '1' TO RESUME ADVENTURING\n");
                scanf("%d", &resumeadventure);
            }while(resumeadventure == 0);
        }

        //Random Encounter Generator
        if (devmode == 0){
            monsterencounter = rand()%  4 + 1;
            //clear to view encounter RNG
            //printf("%d", encounter);
        }
        else if (devmode == 1){
                monsterencounter = 0;
        }

        /*else{
            printf("\nREFUSING TO OPEN THE DOOR, YOU SUCCUMB TO STARVATION AND DIE.");
        }*/
    }while (monsterencounter != 3);

    combat();
}

void encounter()
{
    srand(time(NULL));

    int action;
    int secret;
    int potiontype;

    if (y == 8 && x == 1 && floornumber == 1){
        if (playerclass >= 3){
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            printf("\nHELLO DUNGEON CRAWLER, I AM THE CLASS CHANGER\n");
            printf("IF YOU WOULD LIKE, I WILL CHANGE YOUR CLASS FREE OF CHARGE\n\n");

                do{
                    printf("SELECT A CLASS\n");
                    printf("1:\tSWORDMASTER\n2:\tMONSTER HUNTER\n3:\tMONK\n4:\tTHIEF\n5:\tMAGICIAN\n");
                    scanf("%d", &playerclass);
                    if (playerclass == 1){
                        printf("\nYOU ARE NOW A SWORDMASTER, YOUR FAVORED WEAPON IS THE LONGSWORD\n");
                    }
                    else if (playerclass == 2){
                        printf("\nYOU ARE NOW A MONSTER HUNTER, YOUR FAVORED WEAPON IS THE WHIP\n");
                    }
                    else if (playerclass == 3){
                        printf("\nYOU ARE NOW A MONK, YOUR FAVORED WEAPON IS THE FIST\n");
                    }
                    else if (playerclass == 4){
                        printf("\nYOU ARE NOW A THIEF, YOUR FAVORED WEAPON IS THE DAGGER\n");
                    }
                    else if (playerclass == 5){
                        printf("\nYOU ARE NOW A MAGICIAN, YOU HAVE LEARNED SIMPLE SPELLS\n");
                    }
                    printf("\nSEE YOU AROUND, DUNGEON CRAWLER\n");
                    printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                    scanf("%d", &action);

                }while(playerclass > 5 || playerclass == 0 && action == 0);
            }

        else {
            printf("\nCOME BACK WHEN YOU'RE A MORE EXPERIENCED DUNGEON CRAWLER\n");
            printf("MY SERVICES HAVE NO USE FOR YOU UNTIL THEN\n");
        }
    }
    if (y == 1 && x == 3 && floornumber == 1){
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\nHELLO TRAVELER, I AM THE KNOWLEDGE KEEPER\n");
        printf("I KNOW MANY SECRETS ABOUT THE DESOLATE DUNGEONIA--WOULD YOU LIKE TO KNOW SOME?\n");
        do{
                printf("\nYOU HAVE %dGP\n", playergp);
                printf("\n1:\tLEARN A SECRET\t(5GP)\n");
                printf("0:\tLEAVE\n");

                scanf("%d", &action);
                if (action == 1 && playergp >= 5){
                    playergp = playergp - 5;
                    printf("\nHMMM... LET ME SEE...\n");

                    secret = rand()% 3;
                    if (secret == 0){
                        printf("\nTHERE IS A TOWN IN THE EAST--THEY HAVE MANY WARES AN ADVENTURER LIKE YOU WOULD BE INTERESTED IN\n");
                    }
                    else if (secret == 1){
                        printf("\nSOME SAY A GREAT BEAST RESTS IN THE NORTHEAST REACHES OF THIS FLOOR\n");
                    }
                    else if (secret == 2 && playerclass >= 3){
                        printf("\nA MYSTERIOUS FIGURE SOUTH OF HERE CAN HELP YOU CHANGE YOUR SKILL SET\n");
                    }

                }
                else if (action == 1 && playergp < 5){
                    printf("\nI'M AFRAID I MUST KEEP MY LIPS SEALED IF YOU CANNOT PROVIDE A MEASLY 5GP\nNO WORRIES, I'M SURE YOU'LL HAVE ENOUGH SOONER OR LATER\n");
                }
            }while(action != 0);
    }

    //Potion 1
    if (y == 1 && x == 7 && floornumber == 1){
        flooritems[1] = 0;
        if (playerclass == 5){
            potiontype = rand()% 2;
            if (potiontype == 0){
                potioncount = potioncount + 1;
                printf("\nYOU FIND A HEALTH POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
            else if (potiontype == 1){
                mppotioncount = mppotioncount + 1;
                printf("\nYOU FIND A MAGIC POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
        }
        else if (playerclass != 5){
            potioncount = potioncount + 1;
            printf("\nYOU FIND A HEALTH POTION");
            printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
            scanf("%d", &action);

        }
    }
    //Potion 2
    if (y == 2 && x == 1 && floornumber == 1){
        flooritems[2] = 0;
        if (playerclass == 5){
            potiontype = rand()% 2;
            if (potiontype == 0){
                potioncount = potioncount + 1;
                printf("\nYOU FIND A HEALTH POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
            else if (potiontype == 1){
                mppotioncount = mppotioncount + 1;
                printf("\nYOU FIND A MAGIC POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
        }
        else if (playerclass != 5){
            potioncount = potioncount + 1;
            printf("\nYOU FIND A HEALTH POTION");
            printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
            scanf("%d", &action);

        }

    }
    //Potion 3
    if (y == 6 && x == 14 && floornumber == 1){
        flooritems[3] = 0;
        if (playerclass == 5){
            potiontype = rand()% 2;
            if (potiontype == 0){
                potioncount = potioncount + 1;
                printf("\nYOU FIND A HEALTH POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
            else if (potiontype == 1){
                mppotioncount = mppotioncount + 1;
                printf("\nYOU FIND A MAGIC POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
        }
        else if (playerclass != 5){
            potioncount = potioncount + 1;
            printf("\nYOU FIND A HEALTH POTION");
            printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
            scanf("%d", &action);

        }
    }
    //Potion 4
    if (y == 10 && x == 12 && floornumber == 1){
        flooritems[4] = 0;
        if (playerclass == 5){
            potiontype = rand()% 2;
            if (potiontype == 0){
                potioncount = potioncount + 1;
                printf("\nYOU FIND A HEALTH POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
            else if (potiontype == 1){
                mppotioncount = mppotioncount + 1;
                printf("\nYOU FIND A MAGIC POTION");
                printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
                scanf("%d", &action);
            }
        }
        else if (playerclass != 5){
            potioncount = potioncount + 1;
            printf("\nYOU FIND A HEALTH POTION");
            printf("\nPRESS '0' TO CONTINUE ADVENTURING\n");
            scanf("%d", &action);

        }
    }

}

void town()
{
    int action;

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\nYOU HAVE ENTERED THE QUAINT TOWN OF BOOL\n");
    do{
        printf("\nWHERE DO YOU WANT TO GO:\n");
        printf("\n1:\tHEALER\n");
        printf("2:\tWEAPONSMITH\n");
        printf("3:\tSHOP\n");
        printf("\n4:\tLEAVE\n\n");

        scanf("%d", &action);

        if (action == 1){
            printf("\nWELCOME WEARY TRAVELER--\nI CAN HEAL YOUR WOUNDS FOR A SMALL COST, OF COURSE\n");
            do{
                printf("\nYOU HAVE %dGP\n", playergp);
                printf("\n1:\tPAY FOR HEALING\t(25GP)\n");
                printf("2:\tLEAVE\n");

                scanf("%d", &action);
                if (action == 1 && playergp >= 25 && playerhp != playermaxhp){
                    playergp = playergp - 25;
                    playerhp = playermaxhp;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOUR HP IS NOW %d/%d\n", playerhp, playermaxhp);
                }
                else if (action == 1 && playergp >=25 && playerhp == playermaxhp){
                    printf("\nIT APPEARS THAT YOU ARE ALREADY AT FULL HEALTH, TRAVELER");
                }
                else if (action == 1 && playergp < 25){
                    printf("\nFORGIVE ME TRAVELER, BUT YOU CANNOT COVER THE COST FOR HEALING\n\n");
                }
            }while(action != 2);
        }

        else if (action == 2){
            printf("\nWELCOME TO THE FORGE, BROTHER--\nIF ANYTHING CATCHES YOUR EYE, LET ME KNOW\n");
            do{
                printf("\nYOU HAVE %dGP\n", playergp);
                printf("\n1:\tLONGSWORD\t(300GP)\n");
                printf("2:\tWHIP\t\t(200GP)\n");
                printf("3:\tDAGGER\t\t(100GP)\n");
                printf("4:\tLEAVE\n");

                scanf("%d", &action);
                if (action == 1 && playergp >= 300 && weaponavailable[2] == 0){
                    playergp = playergp - 300;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOU PURCHASED THE LONGSWORD\n");
                    weaponavailable[2] = 1;
                }
                else if (action == 1 && weaponavailable[2] == 1){
                    printf("\nYOU'VE ALREADY GOT A LONGSWORD, BROTHER");
                }
                else if (action == 1 && playergp < 300){
                    printf("\nYOU'RE A BIT SHORT ON GOLD TO BUY THAT ONE, BROTHER\n\n");
                }

                if (action == 2 && playergp >= 200 && weaponavailable[3] == 0){
                    playergp = playergp - 200;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOU PURCHASED THE WHIP\n");
                    weaponavailable[3] = 1;
                }
                else if (action == 2 && weaponavailable[3] == 1){
                    printf("\nYOU'VE ALREADY GOT A WHIP, BROTHER");
                }
                else if (action == 2 && playergp < 200){
                    printf("\nYOU'RE A BIT SHORT ON GOLD TO BUY THAT ONE, BROTHER\n\n");
                }

                if (action == 3 && playergp >= 100 && weaponavailable[4] == 0){
                    playergp = playergp - 100;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOU PURCHASED THE DAGGER\n");
                    weaponavailable[4] = 1;
                }
                else if (action == 3 && weaponavailable[4] == 1){
                    printf("\nYOU'VE ALREADY GOT A DAGGER, BROTHER");
                }
                else if (action == 3 && playergp < 100){
                    printf("\nYOU'RE A BIT SHORT ON GOLD TO BUY THAT ONE, BROTHER\n\n");
                }
            }while(action != 4);
        }
        else if (action == 3){
            printf("\nWELCOME TO MY HUMBLE SHOP, DUNGEONEER--\nI HOPE YOU FIND MY WARES WORTH YOUR COIN\n");
            do{
                printf("\nYOU HAVE %dGP\n", playergp);
                printf("\n1:\tHEALTH POTION\t(20GP)\n");
                if (playerclass == 5){
                    printf("2:\tMAGIC POTION\t(25GP)\n");
                }
                printf("0:\tLEAVE\n");

                scanf("%d", &action);
                if (action == 1 && playergp >= 20){
                    playergp = playergp - 20;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOU PURCHASED A HEALTH POTION\n");

                    potioncount = potioncount + 1;
                }
                else if (action == 2 && playergp >= 25 && playerclass == 5){
                    playergp = playergp - 25;
                    printf("\nTHANK YOU FOR YOUR PATRONAGE\n");
                    printf("YOU PURCHASED A MAGIC POTION\n");

                    mppotioncount = mppotioncount + 1;
                }
                else if (action == 1 && playergp < 20){
                    printf("\nFORGIVE ME DUNGEONEER, BUT THAT ITEM IS A BIT OUT OF YOUR PRICE RANGE\n\n");
                }
            }while(action != 0);
        }

    }while (action != 4);
}

void combat()
{
    srand(time(NULL));

    //Commands
    int action;
    int resumeadventure = 0;

    int mhdodge;
    int thiefsneak;
    int playermaxhpvalue = playermaxhp;
    int playermaxmpvalue = playermaxmp;

    //Player Variables (Combat Only)
    int playerdmg;
    int playercrit;

    int curseactive = 0;
    int cursecount = 0;
    int monstermaxhpdisplay;

    //Conditions and Status Effects
    int statusaffected = 0;

    int paralysisonoff = 0;
    int paralysiscount = 0;
    int slowonoff = 0;
    int slowcount = 0;
    int antimagiconoff = 0;
    int antimagiccount = 0;

    int monstercrit;

    //Boss Tracking
    int bossmode = 0;

/**
    int classname;
    char playerclass0[] = "NONE";
    char playerclass1[] = "SWORDMASTER";
    char playerclass2[] = "MONSTER HUNTER";
    char playerclass3[] = "MONK";

    //Class Variable Assignment
    if (playerclass == 0){
        classname = playerclass0;
    }
    else if (playerclass == 1){
        classname = playerclass1;
    }
    else if (playerclass == 2){
        classname = playerclass2;
    }
    else if (playerclass == 3){
        classname = playerclass3;
    }
*/

/**
    //Weapon Exchange System Variables
    int slot0;
    int slot1;
    int slot2;
    int slot3;
    int slot4;
    int slot5;

    char weaponempty[] = " ";

    int weaponswap;
*/

    //Weapon Block
    int weapontype;
    int weaponbase;
    int weaponbonus;


    //Fists
    //char weapon0[] = "FISTS";
        int weapon0base = 2;
        int weapon0bonus = 1;
        if (playerclass == 3){
            weapon0base = 4;
            weapon0bonus = 3;
        }

    //Shortsword
    //char weapon1[] = "SHORTSWORD";
        int weapon1base = 4;
        int weapon1bonus = 2;

    //Longsword
    //char weapon2[] = "LONGSWORD";
        int weapon2base = 5;
        int weapon2bonus = 3;
        if (playerclass == 1){
            weapon2base = 8;
            weapon2bonus = 3;
        }

    //Whip
    //char weapon3[] = "WHIP";
        int weapon3base = 4;
        int weapon3bonus = 3;
        if (playerclass == 2){
            weapon3base = 5;
            weapon3bonus = 6;
        }

    //DAGGER
    //char weapon4[] = "DAGGER";
        int weapon4base = 3;
        int weapon4bonus = 2;
        if (playerclass == 4){
            weapon4base = 4;
            weapon4bonus = 4;
        }

    //Placeholder/Template
    //char weapon4[] = "PLACEHOLDER";
        int weapon5base = 0;
        int weapon5bonus = 0;


    //Weapon Variable Assignment
    weapontype = weaponactive;

    if (weapontype == 0){
        //weapontype = weapon0;
        weaponbase = weapon0base;
        weaponbonus = weapon0bonus;
    }
    else if (weapontype == 1){
        //weapontype = weapon1;
        weaponbase = weapon1base;
        weaponbonus = weapon1bonus;
    }
    else if (weapontype == 2){
        //weapontype = weapon2;
        weaponbase = weapon2base;
        weaponbonus = weapon2bonus;
    }
    else if (weapontype == 3){
        //weapontype = weapon3;
        weaponbase = weapon3base;
        weaponbonus = weapon3bonus;
    }
    else if (weapontype == 4){
        //weapontype = weapon4;
        weaponbase = weapon4base;
        weaponbonus = weapon4bonus;
    }
    else if (weapontype == 5){
        //weapontype = weapon4;
        weaponbase = weapon5base;
        weaponbonus = weapon5bonus;
    }

    //Monster Block
    char monster0[] = "OOZE";
        int monster0hp = 3;
        int monster0maxdmg = 2;
        int monster0bonus = 0;
        int monster0run = 0;
        int monster0exp = 5;
        int monster0talk;
            monster0talk = rand()%  2;
            char monster0text0[] = "**SLORP**";
            char monster0text1[] = "**GLUG**";

    char monster1[] = "GOBLIN";
        int monster1hp = 4;
        int monster1maxdmg = 3;
        int monster1bonus = 1;
        int monster1run = 2;
        int monster1exp = 10;
        int monster1talk;
            monster1talk = rand()%  3;
            char monster1text0[] = "'COME HERE ADVENTURER, I WANT TO BASH YOUR SHINS IN WITH MY HAMMER'";
            char monster1text1[] = "'YOUR HEAD WILL MAKE A GREAT GIFT FOR MY WIFE'";
            char monster1text2[] = "'LOOKS LIKE I'M EATING TONIGHT'";

    char monster2[] = "SKELETON";
        int monster2hp = 5;
        int monster2maxdmg = 4;
        int monster2bonus = 1;
        int monster2run = 3;
        int monster2exp = 20;
        int monster2talk;
            monster2talk = rand()%  3;
            char monster2text0[] = "**SHAMBLING**";
            char monster2text1[] = "'AH, A NEW SKIN SUIT'";
            char monster2text2[] = "'I WILL FREE YOU FROM THIS JAIL OF FLESH, MY BROTHER'";

    char monster3[] = "ORC";
        int monster3hp = 8;
        int monster3maxdmg = 5;
        int monster3bonus = 2;
        int monster3run = 4;
        int monster3exp = 30;
        int monster3talk;
            monster3talk = rand()%  4;
            char monster3text0[] = "'LOOKS LIKE MEAT'S BACK ON THE MENU, BOYS'";
            char monster3text1[] = "'I AM DURG OF CLAN ORCUS--MEET YOUR DOOM, ADVENTURER'";
            char monster3text2[] = "'PREPARE TO BE FLAYED'";
            char monster3text3[] = "'ADVENTURERS WHO ENTER DUNGEONIA ARE ADVENTURERS WHO DIE'";

    char monster4[] = "OGRE";
        int monster4hp = 10;
        int monster4maxdmg = 6;
        int monster4bonus = 2;
        int monster4run = 5;
        int monster4exp = 40;
        int monster4talk;
            monster4talk = rand()%  3;
            char monster4text0[] = "'THIS IS THE PART WHERE YOU RUN AWAY'";
            char monster4text1[] = "'GET OUT OF MY CORRIDOR'";
            char monster4text2[] = "'OGRES ARE LIKE ONIONS'";

    char monster5[] = "EYE DEMON";
        int monster5hp = 20;
        int monster5maxdmg = 10;
        int monster5bonus = 2;
        int monster5run = 7;
        int monster5exp = 70;
        int monster5talk;
            monster5talk = rand()%  1;
            char monster5text0[] = "THE SINGULAR FLOATING EYE LOCKS ITS GAZE ON YOU";

        int eyedemonparalysis;

    //Boss Block
    char boss0[] = "MINOTAUR";
        int boss0hp = 50;
        int boss0maxdmg = 15;
        int boss0bonus = 5;
        int boss0run = 1000;
        int boss0exp = 200;
        int boss0gp = 500;
        int boss0talk;
            boss0talk = rand()%  1;
            char boss0text0[] = "THE MINOTAUR BEFORE YOU STANDS MUCH TALLER THAN YOURSELF--ITS HORNS PROTRUDE MEANACINGLY AND LOOK HORRIBLY SHARP\n'YOU WERE FOOLISH TO ENTER THIS PLACE, ADVENTURER--I WILL BE YOUR DEMISE'";

        int minotaurgore;

    char boss1[] = "OCULANT";//BOSS NEEDS BALANCING
        int boss1hp = 100;
        int boss1maxdmg = 10;
        int boss1bonus = 5;
        int boss1run = 1000;
        int boss1exp = 350;
        int boss1gp = 750;
        int boss1talk;
            boss1talk = rand()%  1;
            char boss1text0[] = "THE OCULANT FLOATS BEFORE YOU--THE LARGE ORB OF FLESH THAT IS ITS BODY HAS A SINGLE CENTRAL EYE\nSURROUNDED BY A MULTITUDE OF PROTRUDING EYESTALKS\n'I SEE ALL THINGS, ADVENTURER, INCLUDING YOUR IMMINENT DEATH'";

        int oculantray;
        int disintegratemaxdmg = 20;
        int disintegratebonus = 10;

    /*
    char boss1[] = "LICH";//BOSS NEEDS BALANCING
        int boss1hp = 125;
        int boss1maxdmg = 10;
        int boss1bonus = 5;
        int boss1run = 1000;
        int boss1exp = 350;
        int boss1gp = 750;
        int boss1talk;
            boss1talk = rand()%  1;
            char boss1text0[] = "THE OCULANT FLOATS BEFORE YOU--THE LARGE ORB OF FLESH THAT IS ITS BODY HAS A SINGLE CENTRAL EYE\nSURROUNDED BY A MULTITUDE OF PROTRUDING EYESTALKS\n'I SEE ALL THINGS, ADVENTURER, INCLUDING YOUR IMMINENT DEATH'";

        int oculantray;
        int disintegratemaxdmg = 20;
        int disintegratebonus = 10;
    */



    //Broad Enemy Variables
    int monstertype;
    int monsterhp;
    int monstermaxdmg;
    int monsterbonus;
    int monsterrun;
    int monsterexp;
    int monstertalk;

    int monsterdmg;

    int bossgp;

    /*
    int monsterhp;
        monsterhp = 6;
    int monsterdmg;
        monsterdmg = 3;
    int mrunstat;
        mrunstat = 3;
    */

    //RNG Monster Selection & Variable Assignment
    if (devmode == 1){
        monstertype = dev_monstertype;
    }
    else if (devmode == 0 && playerlvl >=3){
        monstertype = rand()%  6;
    }
    else if (devmode == 0 && playerlvl < 3){
        monstertype = rand()%  5;
    }
    if (y == 2 && x == 9 && floornumber == 1){
        bossmode = 1;
        monstertype = boss0;
    }
    else if (y == 4 && x == 7 && floornumber == 2){
        bossmode = 1;
        monstertype = boss1;
    }

        if (monstertype == 0){
            monstertype = monster0;
            monsterhp = monster0hp;
            monstermaxdmg = monster0maxdmg;
            monsterbonus = monster0bonus;
            monsterrun = monster0run;
            monsterexp = monster0exp;

                if (monster0talk == 0){
                    monster0talk = monster0text0;
                }
                else if (monster0talk == 1){
                    monster0talk = monster0text1;
                }
            monstertalk = monster0talk;
        }
        else if (monstertype == 1){
            monstertype = monster1;
            monsterhp = monster1hp;
            monstermaxdmg = monster1maxdmg;
            monsterbonus = monster1bonus;
            monsterrun = monster1run;
            monsterexp = monster1exp;

                if (monster1talk == 0){
                    monster1talk = monster1text0;
                }
                else if (monster1talk == 1){
                    monster1talk = monster1text1;
                }
                else if (monster1talk == 2){
                    monster1talk = monster1text2;
                }
            monstertalk = monster1talk;
        }
        else if (monstertype == 2){
            monstertype = monster2;
            monsterhp = monster2hp;
            monstermaxdmg = monster2maxdmg;
            monsterbonus = monster2bonus;
            monsterrun = monster2run;
            monsterexp = monster2exp;

                if (monster2talk == 0){
                    monster2talk = monster2text0;
                }
                else if (monster2talk == 1){
                    monster2talk = monster2text1;
                }
                else if (monster2talk == 2){
                    monster2talk = monster2text2;
                }
            monstertalk = monster2talk;
        }
        else if (monstertype == 3){
            monstertype = monster3;
            monsterhp = monster3hp;
            monstermaxdmg = monster3maxdmg;
            monsterbonus = monster3bonus;
            monsterrun = monster3run;
            monsterexp = monster3exp;

                if (monster3talk == 0){
                    monster3talk = monster3text0;
                }
                else if (monster3talk == 1){
                    monster3talk = monster3text1;
                }
                else if (monster3talk == 2){
                    monster3talk = monster3text2;
                }
                else if (monster3talk == 3){
                    monster3talk = monster3text3;
                }
            monstertalk = monster3talk;
        }
        else if (monstertype == 4){
            monstertype = monster4;
            monsterhp = monster4hp;
            monstermaxdmg = monster4maxdmg;
            monsterbonus = monster4bonus;
            monsterrun = monster4run;
            monsterexp = monster4exp;

                if (monster4talk == 0){
                    monster4talk = monster4text0;
                }
                else if (monster4talk == 1){
                    monster4talk = monster4text1;
                }
                else if (monster4talk == 2){
                    monster4talk = monster4text2;
                }
            monstertalk = monster4talk;
        }
        else if (monstertype == 5){
            monstertype = monster5;
            monsterhp = monster5hp;
            monstermaxdmg = monster5maxdmg;
            monsterbonus = monster5bonus;
            monsterrun = monster5run;
            monsterexp = monster5exp;

                if (monster5talk == 0){
                    monster5talk = monster5text0;
                }

            monstertalk = monster5talk;
        }
        else if (monstertype == -1 || monstertype == boss0){
            bossmode = 1;
            monstertype = boss0;
            monsterhp = boss0hp;
            monstermaxdmg = boss0maxdmg;
            monsterbonus = boss0bonus;
            monsterrun = boss0run;
            monsterexp = boss0exp;
            bossgp = boss0gp;

                if (boss0talk == 0){
                    boss0talk = boss0text0;
                }

            monstertalk = boss0talk;
        }
        else if (monstertype == -2 || monstertype == boss1){
            bossmode = 1;
            monstertype = boss1;
            monsterhp = boss1hp;
            monstermaxdmg = boss1maxdmg;
            monsterbonus = boss1bonus;
            monsterrun = boss1run;
            monsterexp = boss1exp;
            bossgp = boss1gp;

                if (boss1talk == 0){
                    boss1talk = boss1text0;
                }

            monstertalk = boss1talk;
        }

    //Wealth
    int gpdrop;
    if (bossmode == 0) {
        gpdrop = 3 * (rand()%  monstermaxdmg + 3);
    }
    else if (bossmode == 1){
        gpdrop = bossgp;
    }

    //Begin Combat
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\nA %s APPROACHES\n", monstertype);

    monstermaxhpdisplay = monsterhp;

    if (playerclass == 4 && weaponactive == 4){
        srand(time(NULL));
        thiefsneak = rand()% 3;
        if (thiefsneak == 2){
            playerdmg = rand()%  (weaponbase + playerlvl) + weaponbonus;
            playerdmg = playerdmg * 2;
            printf("\nYOU SNEAK ATTACK THE %s, DEALING %d DAMAGE\n", monstertype, playerdmg);
            monsterhp = monsterhp - playerdmg;
            //if (monsterhp <= 0){
            //    monsterhp = 1;
            //}
        }
    }

    printf("%s\n", monstertalk);

    do{
        srand(time(NULL));

        if (playerclass == 2){
            printf("\n%s'S HEALTH:\t%d/%d\n", monstertype, monsterhp, monstermaxhpdisplay);
        }
        if (playerclass == 5){
            printf("\nHEALTH:\t%d/%d HP\nMAGIC:\t%d/%d MP\n1:\tATTACK\n2:\tRUN\n3:\tUSE HEALTH POTION (%d)\n4:\tUSE MAGIC POTION (%d)\n5:\tMAGIC\n",playerhp, playermaxhp, playermp, playermaxmp, potioncount, mppotioncount);
            scanf("%d", &action);
        }
        else {
            printf("\nHEALTH: %d/%d\n1:\tATTACK\n2:\tRUN\n3:\tUSE POTION (%d)\n",playerhp, playermaxhp, potioncount);
            scanf("%d", &action);
        }

        //Action : Attack
        if (action == 1){

            playerdmg = rand()%  (weaponbase + playerlvl) + weaponbonus;
            //playerdmg = rand()%  (4 + playerlvl) + 2;
            monsterdmg = rand()%  monstermaxdmg + monsterbonus;

            if (monstertype == monster5){
                    srand(time(NULL));

                    eyedemonparalysis = rand()%  3;
                    if (eyedemonparalysis == 2){
                        playerdmg = 0;
                        printf("\nTHE %s'S GAZE BORES INTO YOU", monstertype);
                    }
            }
            if (monstertype == boss1 && paralysisonoff == 1){
                playerdmg = 0;
                printf("\nTHE EFFECT OF THE OCULANT'S PARALYSIS RAY STILL LINGERS ON YOU");
                paralysiscount = paralysiscount - 1;
                if (paralysiscount == 0){
                    paralysisonoff = 0;
                    statusaffected = 0;
                }
            }
            if (monstertype == boss1 && slowonoff == 1){
                printf("\nTHE EFFECT OF THE OCULANT'S SLOWING RAY STILL LINGERS ON YOU");
                slowcount = slowcount - 1;
                if (slowcount == 0){
                    slowonoff = 0;
                    statusaffected = 0;
                }
            }
            if (monstertype == boss1 && antimagiconoff == 1){
                printf("\nTHE EFFECT OF THE OCULANT'S ANTI-MAGIC RAY STILL LINGERS ON YOU");
                antimagiccount = antimagiccount - 1;
                if (antimagiccount == 0){
                    antimagiconoff = 0;
                    statusaffected = 0;
                }
            }

            printf("\nYOU ATTACK THE %s, DEALING %d DAMAGE\n", monstertype, playerdmg);
            monsterhp = monsterhp - playerdmg;

                playercrit = rand()% 10;
                if (playercrit == 0){
                    playerdmg = playerlvl * 2;
                    printf("YOUR ATTACK IS A CRITITCAL HIT, DEALING AN ADDITIONAL %d DAMAGE", playerdmg);
                }

                if (playerclass == 2 && slowonoff == 0){
                    mhdodge = rand()% 4 + 1;
                    if (mhdodge == 1){
                        monsterdmg = 0;
                        printf("\nYOU PREEMPTIVELY DODGE THE %s'S ATTACK\n", monstertype);
                    }
                }

                else if (playerclass == 3 && weaponactive == 0 && slowonoff == 0){
                    playerdmg = rand()%  (weaponbase + playerlvl) + weaponbonus;
                    printf("\nYOU ATTACK THE %s, DEALING %d DAMAGE\n", monstertype, playerdmg);

                    monsterhp = monsterhp - playerdmg;
                }
                else if (playerclass == 2 || playerclass == 3 && slowonoff == 1){
                    printf("\nYOU ARE SLOWED--YOUR SECONDARY ACTION TO HAVE NO EFFECT\n");
                }

                else if (playerclass == 5 && curseactive == 1 && antimagiconoff == 0){
                    srand(time(NULL));
                    playerdmg = rand()%  playerlvl + 2;
                    printf("YOUR CURSE DOES %d DAMAGE TO THE %s\n", playerdmg, monstertype);
                    cursecount = cursecount - 1;
                    if (cursecount == 0){
                        printf("\nYOUR CURSE WEARS OFF\n\n");
                        curseactive = 0;
                    }
                }
                else if (playerclass == 5 && curseactive == 1 && antimagiconoff == 1){
                    printf("THE ANTI-MAGIC EFFECT WARDS AWAY YOUR CURSE ON THE %s\n", monstertype);
                    curseactive = 0;
                    cursecount = 0;
                }



            if (monsterhp >= 0){
            printf("THE %s ATTACKS YOU, DEALING %d DAMAGE\n", monstertype, monsterdmg);
            playerhp = playerhp - monsterdmg;

                monstercrit = rand()% 15;
                if (playercrit == 0){
                    monsterdmg = monsterbonus;
                    printf("THE %s ATTACK IS A CRITITCAL HIT, DEALING AN ADDITIONAL %d DAMAGE", monstertype, monsterdmg);
                }

                if (monstertype == boss0){
                        srand(time(NULL));

                        minotaurgore = rand()%  2;

                        if (minotaurgore == 1){

                            monsterdmg = rand()% monsterbonus + 3;
                            printf("THE MINOTAUR GORES YOU, DEALING AN ADDITIONAL %d DAMAGE\n", monsterdmg);
                            playerhp = playerhp - monsterdmg;
                        }

                }
                if (monstertype == boss1){
                        srand(time(NULL));

                        oculantray = rand()%  8;

                        if (oculantray == 0 && statusaffected == 0){
                            monsterdmg = rand()%  disintegratemaxdmg + disintegratebonus;
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF DISINTEGRATION DEALING %d DAMAGE\n", monsterdmg);
                            playerhp = playerhp - monsterdmg;
                        }
                        else if (oculantray == 1 && statusaffected == 0){
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF PARALYSIS\n");
                            paralysisonoff = 1;
                            paralysiscount = 3;
                            statusaffected = 1;
                        }
                        else if (oculantray == 2 && statusaffected == 0){
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF SLOWING\n");
                            slowonoff = 1;
                            slowcount = 3;
                            statusaffected = 1;
                        }
                        else if (oculantray == 3 && statusaffected == 0){
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF ANTI-MAGIC\n");
                            antimagiconoff = 1;
                            antimagiccount = 2;
                            statusaffected = 1;
                        }
                        else if (oculantray == 4 && statusaffected == 0){
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF DISEASE, REDUCING YOUR MAX HP BY 5\n");
                            if (playerhp == playermaxhp){
                                playerhp = playerhp - 5;
                            }
                            playermaxhp = playermaxhp - 5;
                        }
                        else if (oculantray == 5 && statusaffected == 0){
                            printf("ONE OF THE EYESTALKS FIRES A RAY OF MAGIC ABSORBTION, REDUCING YOUR MAX MP BY 5\n");
                            if (playermp >= playermaxmp){
                                playermp = playermaxmp;
                                playermp = playermp - 5;
                            }
                            if (playermaxmp > 0 ){
                                playermaxmp = playermaxmp - 5;
                            }
                            if (playermaxmp < 0){
                                playermaxmp = 0;
                                playermp = 0;
                            }
                        }
                        else if (oculantray == 6 || oculantray == 7){
                            printf("ONE OF THE EYESTALKS FIRES A RAY, BUT IT MISSES\n");
                        }
                    }
                }
        }
        //Action : Run
        else if (action == 2){
            printf("\nYOU ATTEMPT TO RUN\n");

            srand(time(NULL));

            run = rand()%  5 + 1;

            monsterdmg = rand()%  monstermaxdmg + monsterbonus;

            //clear to view run RNG when playing
            //printf("%d", run);
            if (run >= monsterrun){
                printf("YOU FLEE SUCCESSFULLY\n");

                do{
                    printf("\nPRESS '1' TO RESUME ADVENTURING\n");
                    scanf("%d", &resumeadventure);
                }while(resumeadventure == 0);

                if (devmode == 1){
                    developer_mode();
                }
                else{
                    play_game();
                }
            }
            else {
                printf("THE %s ATTACKS YOU, DEALING %d DAMAGE\n", monstertype, monsterdmg);
                playerhp = playerhp - monsterdmg;

                monstercrit = rand()% 10;
                if (playercrit == 0){
                    monsterdmg = monsterbonus;
                    printf("THE %s ATTACK IS A CRITITCAL HIT, DEALING AN ADDITIONAL %d DAMAGE", monstertype, monsterdmg);
                }


                if (monstertype == boss0){
                        printf("'YOU CANNOT RUN ME ADVENTURER--ONLY ONE OF US LEAVES THIS ORDEAL ALIVE'\n");
                }
                else if (monstertype == boss1){
                        printf("'YOU CANNOT ESCAPE MY GAZE WHILE I LIVE, ADVENTURER'\n");
                }
            }
        }

        //Action : Use Health Potion
        else if (action == 3){
            if (playerhp == playermaxhp){
                printf("\nYOUR HP IS ALREADY ITS MAX\n");
            }
            else if (potioncount >= 1){
                potioncount = potioncount - 1;
                playerhp = playerhp + 10;
                if (playerhp > playermaxhp){
                    playerhp = playermaxhp;
                }
            }
            else{
                printf("\nYOU HAVE NO HEALTH POTIONS\n");
            }

        }

        //Action : Use Magic Potion
        else if (action == 4){
            if (playermp == playermaxmp){
                printf("\nYOUR MP IS ALREADY ITS MAX\n");
            }
            else if (mppotioncount >= 1){
                mppotioncount = mppotioncount - 1;
                playermp = playermp + 10;
                if (playermp > playermaxmp){
                    playermp = playermaxmp;
                }
            }
            else{
                printf("\nYOU HAVE NO MAGIC POTIONS\n");
            }

        }

        //Action : Magic
        else if (action == 5 && playerclass == 5){
            printf("\nSPELLS:\t\t%d/%d MP\n", playermp, playermaxmp);
            printf("1:\tCURSE\t(10MP)\n2:\tCURE\t(10MP)\n\n0:\tBACK\n");
            scanf("%d", &action);

            if (antimagiconoff == 1){
                    printf("THE ANTI-MAGIC EFFECT PREVENTS YOU FROM SPELLCASTING\n", monstertype);
            }
            else if (action == 1 && playermp >= 10){
                srand(time(NULL));

                cursecount = rand()%  playerlvl + 2;

                printf("\nYOU CAST CURSE ON THE %s\n", monstertype);
                curseactive = 1;

                playermp = playermp - 10;
            }
            else if (action == 1 && playermp < 10){
                printf("YOU DO NOT HAVE ENOUGH MP TO CAST CURSE\n");
            }
            else if (action == 2 && playermp >= 10){
                if (playerhp == playermaxhp){
                    printf("\nYOUR HP IS ALREADY ITS MAX\n");
                }
                else if (playerhp < playermaxhp){
                    printf("\nYOU CAST CURE ON YOURSELF\n");

                    playerhp = playerhp + 10;

                    if (playerhp > playermaxhp){
                        playerhp = playermaxhp;
                    }
                    playermp = playermp - 10;
                }
            }
            else if (action == 2 && playermp < 10){
                printf("YOU DO NOT HAVE ENOUGH MP TO CAST CURE\n");
            }
        }

        if (playerhp <= 0){
            printf("\nYOU DIED.\n\n");
            /*printf("PRESS '1' TO RESTART, OR ANY OTHER KEY TO QUIT\n");
            scanf("%d", restartquit);

            if (restartquit == 1){
                play_game();
            }

            else{
            */
                system("pause");
                return (0);
            //}

        }
        //clear to let player set monsterhp = 0
        /*else if (action == 3){
            monsterhp = 0;
        }
        */

    } while(monsterhp > 0);

    if (bossmode == 1){
        bossmode = 0;

        if (monstertype == boss0){
            bossonoff[1] = 0;
        }
        else if (monstertype == boss1){
            bossonoff[2] = 0;
        }
    }

    printf("\nYOU HAVE DEFEATED THE %s\n", monstertype);
    playerexp = playerexp + monsterexp;
    playergp = playergp + gpdrop;
    printf("THE %s DROPPED %dGP AND %dXP\n", monstertype, gpdrop, monsterexp);

    if (playermaxhp != playermaxhpvalue){
        printf("\nYOUR MAXIMUM HP IS NO LONGER DIMINISHED\n");
        playermaxhp = playermaxhpvalue;
    }
    if (playermaxmp != playermaxmpvalue){
        printf("\nYOUR MAXIMUM MP IS NO LONGER DIMINISHED\n");
        playermaxmp = playermaxmpvalue;
    }

    if (playerexp >= exptolvl){
        exptolvl = exptolvl * 2.25;
        playerlvl = playerlvl + 1;
        playermaxhp = playermaxhp + 10;
        playerhp = playermaxhp;
        printf("\nYOU ARE NOW LEVEL %d\n", playerlvl);
        printf("YOUR HP IS NOW %d\n", playermaxhp);

        //Player Class Assignment
        if (playerclass == 0){
            if (playerlvl == 3){
                do{
                    printf("\nYOU ARE BECOMING A SEASONED DUNGEON CRAWLER\n\n");
                    printf("SELECT A CLASS\n");
                    printf("1:\tSWORDMASTER\n2:\tMONSTER HUNTER\n3:\tMONK\n4:\tTHIEF\n5:\tMAGICIAN\n");
                    scanf("%d", &playerclass);
                    if (playerclass == 1){
                        printf("\nYOU ARE NOW A SWORDMASTER, YOUR FAVORED WEAPON IS THE LONGSWORD\n");
                    }
                    else if (playerclass == 2){
                        printf("\nYOU ARE NOW A MONSTER HUNTER, YOUR FAVORED WEAPON IS THE WHIP\n");
                    }
                    else if (playerclass == 3){
                        printf("\nYOU ARE NOW A MONK, YOUR FAVORED WEAPON IS THE FIST\n");
                    }
                    else if (playerclass == 4){
                        printf("\nYOU ARE NOW A THIEF, YOUR FAVORED WEAPON IS THE DAGGER\n");
                    }
                    else if (playerclass == 5){
                        printf("\nYOU ARE NOW A MAGICIAN, YOU HAVE LEARNED SIMPLE SPELLS\n");
                    }
                }while(playerclass > 5 || playerclass == 0);
            }
        }
    }

    do{
    printf("\nPRESS '1' TO RESUME ADVENTURING\n");
    scanf("%d", &resumeadventure);
    }while(resumeadventure == 0);

    if (devmode == 1){
        developer_mode();
    }
    else{
        play_game();
    }


    int rand_int (int n)
    {
        return rand()%n + 10;
    }

}



