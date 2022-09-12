#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct person {
	char *phoneNumber;
	char *name;  
	struct person *next;
} person;

person *s = NULL;

person *create(char *name, char *phoneNumber, person **start) {
	person *next = malloc(sizeof(person));

	next->name = name;
	next->phoneNumber = phoneNumber;	
	next->next = NULL;

	if (*start == NULL)	
		*start = next;	
	 else {
		person *i = *start; 
		for (; i->next != NULL; i = i->next);
		i->next = next;

	}
	
	return next;
}

void writeInfo(person *p) {
	FILE *file = fopen("info.txt", "a");
	fprintf(file, "[\n%s\n%s\n]\n", p->name, p->phoneNumber);
	fclose(file);
}

void readInfo() {
	FILE *file = fopen("info.txt", "r");
	char line[60]; 
	int collectingCount;
	char *name;
	
	while (fgets(line, 60, file)) {
		line[strlen(line) - 1] = '\0';
		if (collectingCount == 1) {
			name = strdup(line);
			collectingCount += 1;
		} else if (collectingCount == 2) {
			create(name, strdup(line), &s);
			collectingCount = 0;
		} if (line[0] == '[')  {
			collectingCount = 1;

		}
	}
	fclose(file);
}

void search(person *start, const char *name) {
	for (person *i = start; i != NULL; i = i->next) {
		if (!strcmp(name, i->name))
			printf("Name: %s\nPhone Number: %s\n\n", i->name, i->phoneNumber);
	}
}


int main(int argc, char **argv) {
	char ch; 
	char phoneNumber[60];	
	char name[60]; 
	while ((ch = getopt(argc, argv, "l:c:")) != EOF) {
		switch (ch) {
			case 'l':
				readInfo();
				search(s, optarg);
				break;
			case 'c': 
				printf("Please enter %s's phone number: ", optarg);
				scanf("%59s", phoneNumber);
				person *newPerson = create(optarg, phoneNumber, &s);
				writeInfo(newPerson);
		}
	}
	return 0;
}
