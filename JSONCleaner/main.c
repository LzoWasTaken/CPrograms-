#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char line[100];
	while (fgets(line, sizeof(line), stdin)) {
		line[strlen(line) - 1] = '\0';
		if (strchr(line, '{')) {
			char *val = strchr(line, ']');
			if (val) 
				line[val - line] = '\0';
			puts(line); 

			}
	}
	return 0;
}
