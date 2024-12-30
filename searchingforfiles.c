#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "searchingforfiles.h"

void print_file_contents(const char *file_path) {
    printf("#########################################\n");
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

void find_metadata_file(const char *dir) {
    char manager_path[1024], control_path[1024], readme_path[1024];

    // Check for 'manager' file
    snprintf(manager_path, sizeof(manager_path), "%s/manager", dir);
    FILE *file = fopen(manager_path, "r");
    if (file != NULL) {
        printf("Found metadata file: manager\n");
        print_file_contents(manager_path);
        fclose(file);
        return;
    }

    // Check for 'control' file
    snprintf(control_path, sizeof(control_path), "%s/control", dir);
    file = fopen(control_path, "r");
    if (file != NULL) {
        printf("Found metadata file: control\n");
        print_file_contents(control_path);
        fclose(file);
        return;
    }

    // If neither 'manager' nor 'control' are found, check for 'README'
    snprintf(readme_path, sizeof(readme_path), "%s/README", dir);
    file = fopen(readme_path, "r");
    if (file != NULL) {
        printf("No metadata file found. Displaying README:\n");
        print_file_contents(readme_path);
        fclose(file);
    } else {
        printf("No metadata or README file found.\n");
    }
}
