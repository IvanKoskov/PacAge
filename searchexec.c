#include "searchexec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to check if a file is executable
int is_executable(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return (st.st_mode & S_IXUSR) != 0;  // Check if the file is executable
    }
    return 0;
}

// Function to search for executable files in the repository directory
const char *find_executable(const char *repoDir) {
    DIR *dir = opendir(repoDir);
    if (dir == NULL) {
        perror("Error opening directory");
        return NULL;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", repoDir, entry->d_name);

        if (is_executable(path)) {
            closedir(dir);
            return entry->d_name;  // Return only the executable name
        }
    }

    closedir(dir);
    return NULL;  // No executable found
}


// Function to copy the executable to /usr/local/bin

void move_executable_to_bin(const char *exePath) {
    // Prepare the shell command to call the move script
    char command[1024];
    snprintf(command, sizeof(command), "./move_executable.sh \"%s\"", exePath);

    // Execute the shell script
    int result = system(command);

    if (result == 0) {
        printf("Executable moved successfully.\n");
    } else {
        printf("Error moving executable.\n");
    }
}
