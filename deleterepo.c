#include "deleterepo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rmCommand(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: Missing repository URL. Usage: rmCommand <repo_url>\n");
        return;
    }

    const char *repoUrl = argv[2];

    // Get the HOME environment variable
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error: Unable to determine the home directory.\n");
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

    // Temporary buffer for storing lines
    char tempPath[1024];
    snprintf(tempPath, sizeof(tempPath), "%s/Documents/Sources_CORE/list.temp", homeDir);

    FILE *tempFile = fopen(tempPath, "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character for comparison
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, repoUrl) == 0) {
            found = 1;
            continue; // Skip writing this line
        }
        fprintf(tempFile, "%s\n", line);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temp file
    if (rename(tempPath, listPath) != 0) {
        perror("Error replacing the original file");
        return;
    }

    if (found) {
        printf("Repository '%s' removed successfully.\n", repoUrl);
    } else {
        printf("Repository '%s' not found in the list.\n", repoUrl);
    }
}
