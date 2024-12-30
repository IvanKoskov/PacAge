#include "clone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int directoryExists(const char *path) {
    struct stat info;
    return (stat(path, &info) == 0 && (info.st_mode & S_IFDIR));
}

void cloneCommand(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please provide the repository URL.\n");
        return;
    }

    // Get the repo URL from command-line arguments
    const char *repoUrl = argv[2]; // assuming the URL is provided as the third argument

    // Ask for the destination path
    printf("Provide destination path for the project: \n");
    char destinationPath[1024];
    scanf("%s", destinationPath);

    // Check if the destination directory exists
    if (directoryExists(destinationPath)) {
        printf("Error: The destination path '%s' already exists and is not empty.\n", destinationPath);
        return;
    }

    // Form the git clone command
    char command[1024];
    snprintf(command, sizeof(command), "git clone %s %s", repoUrl, destinationPath);

    // Execute the command
    int result = system(command);

    if (result == 0) {
        printf("Repository cloned successfully to: %s\n", destinationPath);
    } else {
        fprintf(stderr, "Failed to clone repository.\n");
    }
}