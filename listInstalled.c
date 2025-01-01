#include "listInstalled.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void listInstalledCommand(void) {
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error: Unable to determine the home directory.\n");
        return;
    }

    // Construct the path to the Documents/Sources_CORE directory
    char coreSourcesPath[1024];
    snprintf(coreSourcesPath, sizeof(coreSourcesPath), "%s/Documents/Sources_CORE", homeDir);

    // Construct the path to the 'installed' file
    char installedPath[1024];
    snprintf(installedPath, sizeof(installedPath), "%s/installed", coreSourcesPath);

    // Check if the 'installed' file exists
    struct stat st;
    if (stat(installedPath, &st) != 0) {
        perror("Error");
        return;
    }

    // Open the 'installed' file for reading
    FILE *installedFile = fopen(installedPath, "r");
    if (installedFile == NULL) {
        perror("Error opening installed file");
        return;
    }

    // Read and print each line from the 'installed' file (each line is an installed package)
    char line[256];
    printf( RED "Installed packages:\n"RESET);
    while (fgets(line, sizeof(line), installedFile) != NULL) {
        // Remove the newline character at the end of each line
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n", line);
    }

    // Close the file
    fclose(installedFile);
}
