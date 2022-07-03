#include <stdio.h>

int main() {

	int age;
	char name[50];
	float num; 
    char operatingSystem[8];
	float num2;
	char animal[20];

	puts("Welcome to the madlibs calculator! Enter the following inputs and the program will output a beautifully crafted story.");

	puts("\nPlease enter your age: ");
	scanf("%i", &age);

	switch(age) {
		case 100:
			puts("\nWow. Good job staying alive for so long!");
			break;
		case 1:
			puts("\ndid you even read my question, or did you just guess?");
			break;
		default:
			puts("\nYou are so old!");

	}

	puts("\nPlease enter a name: ");
	scanf("%49s", name);

	puts("\nPlease enter a random floating point number: ");
	scanf("%f", &num);
	printf("%f", num);

	puts("\nPlease enter your favourite operating system: ");
	scanf("%7s", operatingSystem);

	puts("\nPlease enter a random animal: ");
	scanf("%s", animal);
	
	num2 = (age + 1)*num;
	num2++;
	
	printf("You woke up one morning %i hours late. This didn't matter though because %s had consumed the town's supply of oreos and everybody was too angry to go to work. You thought about the state of the world and it made you feel %.2f times as %s-like as you did yesterday. You dragged yourself out of your bedroom and into your office. You sat down at your computer. It was running %s and you had spent %f dollars on it.", age, name, num, animal, operatingSystem, num2);

	return 0;
}

