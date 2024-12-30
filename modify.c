#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "modify.h"

void createCoreSourcesFolder(void) {
    // Get the HOME environment variable
    const char *homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error: Unable to determine the home directory.\n");
        return;
    }

    // Construct the path to the Documents/Sources_CORE directory
    char coreSourcesPath[1024];
    snprintf(coreSourcesPath, sizeof(coreSourcesPath), "%s/Documents/Sources_CORE", homeDir);

    // Check if the directory already exists
    struct stat st;
    if (stat(coreSourcesPath, &st) == 0 && S_ISDIR(st.st_mode)) {
        printf("The directory '%s' already exists.\n", coreSourcesPath);
    } else {
        // Create the directory
        if (mkdir(coreSourcesPath, 0755) == 0) {
            printf("Directory '%s' created successfully.\n", coreSourcesPath);
        } else {
            perror("Error creating the directory");
            return;
        }
    }

    // File paths for `list` and `installed`
    char listPath[1024], installedPath[1024];
    snprintf(listPath, sizeof(listPath), "%s/list", coreSourcesPath);
    snprintf(installedPath, sizeof(installedPath), "%s/installed", coreSourcesPath);

    // Ensure the `list` file exists
    int listFile = open(listPath, O_CREAT | O_EXCL, 0644);
    if (listFile >= 0) {
        printf("File '%s' created successfully.\n", listPath);
        close(listFile);
    } else {
        printf("File '%s' already exists.\n", listPath);
    }

    // Ensure the `installed` file exists
    int installedFile = open(installedPath, O_CREAT | O_EXCL, 0644);
    if (installedFile >= 0) {
        printf("File '%s' created successfully.\n", installedPath);
        close(installedFile);
    } else {
        printf("File '%s' already exists.\n", installedPath);
    }
}




void modifyCommand(int argc, char *argv[]){




}