#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
	time_t t;
	srand((unsigned) time(&t));
	
	int randomNumber = rand() % 21;
	int guess;
	int guesses = 5;

	puts("Try to guess a number between 1 and 20!");
	
	while (guesses > 0) {
		puts("\n\nOk, please enter your guess: ");
		scanf("%i", &guess);

		if (guess == randomNumber) {
			puts("You guessed correctly!");
			break; 
		} else if (guess > 20 || guess < 0) {
			puts("Your guess is out of range. You are to guess a number between 1 and 20.");
			continue;
		} else if (guess > randomNumber)
			printf("%i is too high... The number is less than that", guess);

		else if (guess < randomNumber)
			printf("%i is too low... The number is greater than that", guess);
		
		guesses--;	
	} if (guesses == 0) {
		printf("\nYou're out of guesses... The number that I was thinking of is %i\n", randomNumber);

	    }
	
	return 0;
}
