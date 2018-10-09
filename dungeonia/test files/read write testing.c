#include <stdio.h>
#include <stdlib.h>

int main () {
/*
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

   FILE * fp;

   fp = fopen ("save.txt", "w+");
   fprintf(fp, "%d %d %d %d %d %d %d", playermaxhp, playerhp, playerexp, playerlvl, exptolvl, expneeded, playerclass);

   fclose(fp);


   FILE *fp;
   int c;

   fp = fopen("file.txt","r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);

*/
          FILE *in_file  = fopen("save.txt", "r"); // read only
          FILE *out_file = fopen("save.txt", "w+"); // read/write only

          // test for files not existing.
          if (in_file == NULL || out_file == NULL)
            {
              printf("Error! Could not open file\n");
              exit(-1); // must include stdlib.h
            }

          // write to file vs write to screen
          fprintf(file, "this is a test %d\n", integer); // write to file

          fprintf(stdout, "this is a test %d\n", integer); // write to screen
          printf(         "this is a test %d\n", integer); // write to screen

          // read from file/keyboard. remember the ampersands!
          fscanf(file, "%d %d", &int_var_1, &int_var_2);

          fscanf(stdin, "%d %d", &int_var_1, &int_var_2);
          scanf(        "%d %d", &int_var_1, &int_var_2);
   return(0);
}
