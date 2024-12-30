#include "showrepos.h"
#include <stdio.h>
#include <stdlib.h>

void showreposCommand(void) {
    // Get the HOME environment variable
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error: Unable to determine the home directory on your machine.\n");
        return;
    }

    // Construct the path to the `list` file
    char listPath[1024];
    snprintf(listPath, sizeof(listPath), "%s/Documents/Sources_CORE/list", homeDir);

    // Open the `list` file for reading
    FILE *file = fopen(listPath, "r");
    if (file == NULL) {
        perror("Error opening 'list' file");
        return;
    }
    
    char myString[100];

    // Read the content and print it
    while (fgets(myString, sizeof(myString), file) != NULL) {
        printf("%s", myString);
    }
   
    // Close the file
    fclose(file);

    printf("Exited with no errors!\n");
}
