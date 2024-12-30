#include "newrepo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crCommand(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: Missing repository URL. Usage: crCommand <repo_url>\n");
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

    // Append the repository URL to the `list` file
    FILE *file = fopen(listPath, "a");
    if (file == NULL) {
        perror("Error opening 'list' file");
        return;
    }

    fprintf(file, "%s\n", repoUrl);
    fclose(file);

    printf("Repository '%s' added successfully.\n", repoUrl);
}
