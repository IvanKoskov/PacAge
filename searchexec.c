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




const char *find_executable(const char *repoDir, const char *repoUrl) {
    const char *locations[] = {
        "bin/",             // bin/<executable_name>
        "usr/bin/",         // usr/bin/<executable_name>
        "usr/local/bin/",   // usr/local/bin/<executable_name>
        "sbin/",            // sbin/<executable_name>
        "usr/sbin/",        // usr/sbin/<executable_name>
        "libexec/",         // libexec/<executable_name>
        ""                  // root-level <executable_name>
    };

    static char sourcePath[512];  // For source path
    char destPath[512];           // For destination path
    char fullDestPath[512];       // For full destination path
    char repoName[256];           // To hold the repo name

    // Extract repository name (assumes repoDir is a full path)
    const char *repoBase = strrchr(repoDir, '/');
    if (repoBase != NULL) {
        strncpy(repoName, repoBase + 1, sizeof(repoName) - 1);  // Extracts the last part of the repoDir path
        repoName[sizeof(repoName) - 1] = '\0';  // Ensure null termination
    } else {
        repoName[0] = '\0';  // If there's no '/' in the path, leave repoName empty
    }

    // Iterate over all locations
    for (size_t i = 0; i < sizeof(locations) / sizeof(locations[0]); ++i) {
        snprintf(sourcePath, sizeof(sourcePath), "%s/%s", repoDir, locations[i]);

        struct stat sb;
        if (stat(sourcePath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            // Directory found, iterate through its files
            DIR *dir = opendir(sourcePath);
            if (dir) {
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] == '.') {
                        continue; // Skip hidden files and "." or ".."
                    }

                    snprintf(destPath, sizeof(destPath), "%s/%s", sourcePath, entry->d_name);

                    // Check if the file is executable (and not a directory)
                    if (stat(destPath, &sb) == 0 && (sb.st_mode & S_IXUSR) && !S_ISDIR(sb.st_mode)) {
                        // Construct the full destination path for /usr/local/bin/
                        snprintf(fullDestPath, sizeof(fullDestPath), "/usr/local/bin/%s", entry->d_name);

                        if (rename(destPath, fullDestPath) == 0) {
                            printf("Moved executable to: %s\n", fullDestPath);

                            // Log the full path to the installed file inside Sources_CORE
                            char logFilePath[512];
                            snprintf(logFilePath, sizeof(logFilePath), "%s/Documents/Sources_CORE/installed", getenv("HOME"));

                            FILE *logFile = fopen(logFilePath, "a");
                            if (logFile) {
                                fprintf(logFile, "%s/%s %s\n", repoDir, entry->d_name, repoUrl);  // Log full path and repo URL
                                fclose(logFile);
                            } else {
                                perror("Failed to open installed file");
                            }
                        } else {
                            perror("Failed to move executable");
                        }
                    }
                }
                closedir(dir);
            }
        } else if (stat(sourcePath, &sb) == 0 && (sb.st_mode & S_IXUSR) && !S_ISDIR(sb.st_mode)) {
            // If it's a file and executable (non-directory case)
            snprintf(fullDestPath, sizeof(fullDestPath), "/usr/local/bin/%s", strrchr(sourcePath, '/') + 1);

            if (rename(sourcePath, fullDestPath) == 0) {
                printf("Moved executable to: %s\n", fullDestPath);

                // Log the full path to the installed file inside Sources_CORE
                char logFilePath[512];
                snprintf(logFilePath, sizeof(logFilePath), "%s/Documents/Sources_CORE/installed", getenv("HOME"));

                FILE *logFile = fopen(logFilePath, "a");
                if (logFile) {
                    fprintf(logFile, "%s/%s %s\n", repoDir, strrchr(sourcePath, '/') + 1, repoUrl);  // Log full path and repo URL
                    fclose(logFile);
                } else {
                    perror("Failed to open installed file");
                }
            } else {
                perror("Failed to move executable");
            }
        }
    }

    return NULL; // No executable found
}

