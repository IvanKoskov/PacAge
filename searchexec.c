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

const char *find_executable(const char *repoDir) {
    const char *locations[] = {
        "bin/",             // bin/<executable_name>
        "usr/bin/",         // usr/bin/<executable_name>
        "usr/local/bin/",   // usr/local/bin/<executable_name>
        "sbin/",            // sbin/<executable_name>
        "usr/sbin/",        // usr/sbin/<executable_name>
        "libexec/",         // libexec/<executable_name>
        ""                  // root-level <executable_name>
    };

    static char fullPath[512];
    char destPath[512];

    for (size_t i = 0; i < sizeof(locations) / sizeof(locations[0]); ++i) {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", repoDir, locations[i]);

        struct stat sb;
        if (stat(fullPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            // Directory found, iterate through its files
            DIR *dir = opendir(fullPath);
            if (dir) {
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] == '.') {
                        continue; // Skip hidden files and "." or ".."
                    }

                    snprintf(destPath, sizeof(destPath), "%s/%s", fullPath, entry->d_name);

                    // Check if the file is executable
                    if (stat(destPath, &sb) == 0 && (sb.st_mode & S_IXUSR)) {
                        // Move executable to /usr/local/bin
                        snprintf(fullPath, sizeof(fullPath), "/usr/local/bin/%s", entry->d_name);

                        if (rename(destPath, fullPath) == 0) {
                            printf("Moved executable to: %s\n", fullPath);
                            closedir(dir);
                            return fullPath;
                        } else {
                            perror("Failed to move executable");
                            closedir(dir);
                            return NULL;
                        }
                    }
                }
                closedir(dir);
            }
        } else if (stat(fullPath, &sb) == 0 && (sb.st_mode & S_IXUSR)) {
            // Single executable file at this location
            snprintf(destPath, sizeof(destPath), "/usr/local/bin/%s", strrchr(fullPath, '/') + 1);

            if (rename(fullPath, destPath) == 0) {
                printf("Moved executable to: %s\n", destPath);
                return destPath;
            } else {
                perror("Failed to move executable");
                return NULL;
            }
        }
    }

    return NULL; // No executable found
}
