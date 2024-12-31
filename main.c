#include <stdio.h>
#include <stdlib.h>
#include "createconf.h"
#include "alert.h"
#include "config.h"
#include <string.h>
#include "clone.h"
#include "modify.h"
#include "newrepo.h"
#include "showrepos.h"
#include "deleterepo.h"

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
        modifyCommand(argc, argv);
        createCoreSourcesFolder();
    } else if (argc > 1 && strcmp(argv[1], "control") == 0) {
      displayConfig();

    } else if (argc > 1 && strcmp(argv[1], "clone") == 0) {
      cloneCommand(argc, argv);

    } else if (argc > 1 && strcmp(argv[1], "cr") == 0) { //add repo 
      crCommand(argc, argv);

    } else if (argc > 1 && strcmp(argv[1], "rm") == 0) { //remove repo
      rmCommand(argc, argv);

    } else if (argc > 1 && strcmp(argv[1], "listr") == 0) {
      showreposCommand();
    } else if (argc > 1 && strcmp(argv[1], "CORE_CREATE_FILES") == 0) {

     createCoreSourcesFolder();
    }

    return 0;
}
