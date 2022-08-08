/* This program is meant to be piped into ls -l.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "listingdetails.h"

void formatJson(int directoryCount, int fileCount, int symbolicLinkCount, FILE *outputDestination) {
    fprintf(outputDestination, "data=[\n");
    fprintf(outputDestination, "{'Subdirectories': %i, 'Files': %i, 'Symbolic Links': %i}\n", directoryCount, fileCount, symbolicLinkCount); 
    fprintf(outputDestination, "]\n");
}

void formatCsv(int directoryCount, int fileCount, int symbolicLinkCount, FILE *outputDestination) {
    fprintf(outputDestination, "%i,%i,%i\n", directoryCount, fileCount, symbolicLinkCount);
}

void formatDefault(int directoryCount, int fileCount, int symbolicLinkCount, FILE *outputDestination) {
    fprintf(outputDestination, "This directory has: \n");
    fprintf(outputDestination, "\t%i subdirectories\n", directoryCount);
    fprintf(outputDestination, "\t%i files\n", fileCount);
    fprintf(outputDestination, "\t%i symbolic links\n", symbolicLinkCount);
}


int main(int argc, char *argv[]) {
    char *validFormats[] = {
        "Default", 
        "JSON",
        "CSV"
    };
    char line[80];
    int directoryCount = 0;
    int fileCount = 0;
    int symbolicLinkCount = 0;

    char *format = "Default";
    FILE *outputDestination = stdout;
    char ch;

    while ((ch = getopt(argc, argv, "f:o:")) != EOF) {
        switch (ch) {
            case 'f': 
                for (int i = 0; i < 3; i++) 
                    if (!(strcasecmp(optarg, validFormats[i])))
                        format = validFormats[i];
                if (!(format[0])) {
                    fprintf(stderr, "Error: Format is invalid or has not been specified.\n");
                    return 1;
                }
                break;
            case 'o':
                outputDestination = fopen(optarg, "w");
        }
    } 
    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strlen(line) - 1] = '\0';
        switch (line[0]) {
            case 'd':
                directoryCount += 1;
                break;
            case '-':
                fileCount += 1;
                break;
            case 'l':
                symbolicLinkCount += 1;

        }

    }

    if (!(strcmp(format, validFormats[0])))
        formatDefault(directoryCount, fileCount, symbolicLinkCount, outputDestination);
    else if (!(strcmp(format, validFormats[1])))
        formatJson(directoryCount, fileCount, symbolicLinkCount, outputDestination);        
    else if (!(strcmp(format, validFormats[2])))
        formatCsv(directoryCount, fileCount, symbolicLinkCount, outputDestination);        

    fclose(outputDestination);
    return 0;
}
