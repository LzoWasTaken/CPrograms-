/* This program is meant to be piped into ls -l.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "listingdetails.h"

void formatJson(output o) {
    fprintf(o.destination, "data=[\n");
    fprintf(o.destination, "{'Subdirectories': %i, 'Files': %i, 'Symbolic Links': %i}\n", o.directoryCount, o.fileCount, o.symbolicLinkCount); 
    fprintf(o.destination, "]\n");
}

void formatCsv(output o) {
    fprintf(o.destination, "%i,%i,%i\n", o.directoryCount, o.fileCount, o.symbolicLinkCount);
}

void formatDefault(output o) {
    fprintf(o.destination, "This directory has: \n");
    fprintf(o.destination, "\t%i subdirectories\n", o.directoryCount);
    fprintf(o.destination, "\t%i files\n", o.fileCount);
    fprintf(o.destination, "\t%i symbolic links\n", o.symbolicLinkCount);
}


int main(int argc, char *argv[]) {
    char *validFormats[] = {
        "Default", 
        "JSON",
        "CSV"
    };
    char line[80];
    output programOutput = {0, 0, 0, "", stdout};

    char ch;
    while ((ch = getopt(argc, argv, "f:o:")) != EOF) {
        switch (ch) {
            case 'f': 
                for (int i = 0; i < 3; i++) 
                    if (!(strcasecmp(optarg, validFormats[i])))
                        programOutput.format = validFormats[i];
                if (!(programOutput.format[0])) {
                    fprintf(stderr, "Error: Format is invalid\n");
                    return 1;
                }
                break;
            case 'o':
                programOutput.destination = fopen(optarg, "w");
                break;
        }
    
    }

    programOutput.format = "Default"; 

    while (fgets(line, sizeof(line), stdin)) { // Removed != NULL from here.
        line[strlen(line) - 1] = '\0';
        switch (line[0]) {
            case 'd':
                programOutput.directoryCount += 1;
                break;
            case '-':
                programOutput.fileCount += 1;
                break;
            case 'l':
                programOutput.symbolicLinkCount += 1;

        }

    }

    if (!(strcmp(programOutput.format, validFormats[0])))
        formatDefault(programOutput);
    else if (!(strcmp(programOutput.format, validFormats[1])))
        formatJson(programOutput);        
    else if (!(strcmp(programOutput.format, validFormats[2])))
        formatCsv(programOutput);        

    fclose(programOutput.destination);
    return 0;
}
