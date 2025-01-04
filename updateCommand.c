#include "updateCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "searchexec.h"
void updtCommand(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: pacage updt <path_to_repo>\n");
        return;
    }

    const char *repoPath = argv[2];
    char logFilePath[512];
    snprintf(logFilePath, sizeof(logFilePath), "%s/Documents/Sources_CORE/installed", getenv("HOME"));

    FILE *logFile = fopen(logFilePath, "r");
    if (!logFile) {
        perror("Failed to open installed file");
        return;
    }

    char line[512];
    char foundRepoPath[256] = {0};
    char githubUrl[256] = {0};

    // Search for the repository in the installed file
    while (fgets(line, sizeof(line), logFile)) {
        char *path = strtok(line, " ");
        char *url = strtok(NULL, "\n");

        if (path && url && strcmp(path, repoPath) == 0) {
            strncpy(foundRepoPath, path, sizeof(foundRepoPath) - 1);
            strncpy(githubUrl, url, sizeof(githubUrl) - 1);
            break;
        }
    }

    fclose(logFile);

    if (foundRepoPath[0] == '\0' || githubUrl[0] == '\0') {
        fprintf(stderr, "Repository not found in the installed file.\n");
        return;
    }

    // Download the latest release .tar.gz using wget
    char downloadCommand[512];
    snprintf(downloadCommand, sizeof(downloadCommand), "wget -O /tmp/repo.tar.gz https://github.com/IvanKoskov/Shelld/archive/refs/heads/main.tar.gz");
    
    if (system(downloadCommand) != 0) {
        fprintf(stderr, "Failed to download the repository.\n");
        return;
    }

    // Extract the tar.gz file into the repo directory, overwriting existing files
    char extractCommand[512];
    snprintf(extractCommand, sizeof(extractCommand), "tar -xzf /tmp/repo.tar.gz -C %s --strip-components=1", repoPath);
    
    if (system(extractCommand) != 0) {
        fprintf(stderr, "Failed to extract the repository.\n");
        return;
    }

    // Clean up the downloaded tar.gz file
    system("rm -f /tmp/repo.tar.gz");

    // Repeat the installation process (reuse the find_executable logic)
    printf("Reinstalling executables from %s...\n", repoPath);
    find_executable(repoPath, githubUrl);

    printf("Repository %s has been successfully updated and reinstalled.\n", repoPath);
}
