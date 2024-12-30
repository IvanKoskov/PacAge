#include <stdio.h>
#include <stdlib.h>
 #include "createconf.h"
 #include "alert.h"
 #include "config.h"
 #include <string.h>

 #define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided

    confCommand();

    if (argc != 3) {
        printf("Usage: %s <arg1> <arg2>\n", argv[0]);
        printf("Use arguments to pass commands\n");
        printf("arguments will be parsed\n");
        return 1;
    } 
    printf(" \n");
    printf(GREEN"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" RESET);
    printf(" \n");
    if (argc > 1 && strcmp(argv[1], "wha") == 0) {
        whaCommand();
    } else if (argc > 1 && strcmp(argv[1], "modify") == 0) {
        //modifyCommand();
        printf("hi");
    } else if (argc > 1 && strcmp(argv[1], "control") == 0) {
      displayConfig();

    }




    

    
     







    // Access the arguments example
    //printf("Argument 1: %s\n", argv[1]);
    //printf("Argument 2: %s\n", argv[2]);

   //displayConfig(); example

    return 0;
}
