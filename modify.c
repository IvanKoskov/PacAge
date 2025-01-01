#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "modify.h"
#include "clone.h" //cloning the repo
#include "searchingforfiles.h"
#include "searchexec.h"

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

 if (argc < 3) {
        fprintf(stderr, "Error: Missing repository URL. Usage: modifyCommand <repo_url>\n");
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

    // Check if the repo URL exists in the list
    FILE *file = fopen(listPath, "r");
    if (file == NULL) {
        perror("Error opening 'list' file");
        return;
    }

    int repoExists = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline
        if (strcmp(line, repoUrl) == 0) {
            repoExists = 1;
            break;
        }
    }
    fclose(file);

    if (!repoExists) {
        printf("Repository '%s' not found in the list. Please add it first.\n", repoUrl);
        printf("Use wha command for help and guides\n");
        return;
    }

    // Now fetch the `manager` file (or any metadata file)
    // Simulate fetching and parsing the metadata (for now it's hardcoded, can be fetched with Git or HTTP later)
    printf("Fetching metadata for the package...\n");
    
    

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

    find_metadata_file(destinationPath);

   

    // Prompt user for confirmation
    printf("Do you want to install this package? (Y/N): ");
    char response;
    scanf(" %c", &response); // space before %c to consume any leftover newline characters

    if (response != 'Y' && response != 'y') {
        printf("Installation canceled.\n");
        return;
    }

    
    printf("Installing...\n");
    printf("...\n");
    printf(".........\n");

    printf("Locating the executables.....\n");

   


    // installation process (e.g., clone the repository, extract files, etc.)
    // In reality, you'd probably clone the repo or download necessary files here

     const char *executable = find_executable(destinationPath);;

    if (executable) {
        printf("Executable found at: %s\n", executable);
    } else {
        printf("No executable found in the package.\n");
    }

}