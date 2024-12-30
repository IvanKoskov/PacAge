 #include <stdio.h>
 #include "createconf.h"
 #include <stdlib.h>
 #include "alert.h"

 void confCommand() {
 
 FILE *file_check = fopen("settingpc", "r");

    if (file_check != NULL) {
        // File exists
        
        fclose(file_check);  // Close the file pointer
    } else {
        // File doesn't exist, create and write to it
        whaCommand();
        FILE *file = fopen("settingpc", "w");

        if (file == NULL) {
            // If file creation failed, print an error and return
            perror("Error creating config");
            exit(1);
        }

        // Write one line of text to the file
        fprintf(file, ">Pacage launched with no errors : log file settingpc created!\n");

        // Close the file
        fclose(file);

        
    }

 }