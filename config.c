#include "config.h"
#include <stdio.h>

void displayConfig() {

printf("Project: %s\n", PROJECT_NAME);
    printf("Version: %s\n", VERSION);
    printf("Author: %s\n", AUTHOR);
    printf("Maintainer: %s\n", MAINTAINER);
    printf("License: %s\n", LICENSE);
    printf("Platform: %s\n", PLATFORM);

    // Print version numbers
    printf("Version: %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    
    printf("Compiled with: %s\n", COMPILER);

    printf("Compiled on: %s\n", COMPILED_ON);



}
