typedef struct {
    int directoryCount;
    int fileCount;
    int symbolicLinkCount;
    const char *format;
    FILE *destination;
} output;

void formatJson(output o); 
void formatCsv(output o);
void formatDefault(output o); 

