#include "alert.h"

#include <stdio.h>

// Function definition
void whaCommand(void) {
        printf("<arg1> : modify (install package)\n");
        printf("<arg1> : updt (update package)\n");
        printf("<arg1> : clean (remove the installed program)\n");
        printf("<arg1> : ls-pac (all installed packages)\n");
        printf("<arg1> : updt-totall (update all installed packages)\n");
        printf("pacage wha : Show this message again\n");
        printf("<arg1> : Release to get the info of the current verion of pacage\n");
        printf("Wrap single word commands or argumnets in pacage <<your argument>> pacage\n");
        printf("Use <<pacage wha package>> to get help message");
        printf("More are at Pacage GitHub!\n");
}

