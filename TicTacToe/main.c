#include <stdio.h>
#include "tictactoe.h"

void displayBoard(char board[]) {
    printf("%c|%c|%c\n", board[0], board[1], board[2]);
    printf("-----\n");
    printf("%c|%c|%c\n", board[3], board[4], board[5]);
    printf("-----\n");
    printf("%c|%c|%c\n", board[6], board[7], board[8]);

}

int checkWins(char board[], char playerTurn) {
	int wins[9][4] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}

	};

	for (int counter = 0; counter < 8; counter++) {
		if (board[wins[counter][0]] == playerTurn && board[wins[counter][1]] == playerTurn && board[wins[counter][2]] == playerTurn)
			return 1;
	}
	return 0;
}

int main() {
    puts("Welcome to this great TicTacToe game.");

    char board[10] = {
        ' ', ' ', ' ',
        ' ', ' ', ' ',
        ' ', ' ' , ' ',
        };

    int spotOfChoice = 0; 
    int validSpotEntered = 0;
    int playerTurn = 'X';

    for (int counter = 0; counter < 9; counter++) {
        displayBoard(board);
		if (playerTurn == 'X')
			puts("Player one, it's your turn");
		else 
			puts("Player two, it's your turn");
        validSpotEntered = 0;
        do {
            puts("Please Enter the spot that you would like to occupy: ");
            scanf("%i", &spotOfChoice);

            if (spotOfChoice < 1 || spotOfChoice > 9) {
                puts("Out of range.");
            } else {
                switch (board[spotOfChoice - 1]) {
                    case 'O':
                    case 'X':
                        puts("Invalid. That spot is already taken.");
                        break;
                    default:
                        validSpotEntered = 1;

                }
            }
        }  while (!validSpotEntered);

        board[spotOfChoice - 1] = playerTurn;
		if (checkWins(board, playerTurn)) {
			displayBoard(board);
			if (playerTurn == 'X')
				puts("Player one won!");
			else
				puts("Player two won!");
			break;
		} else
			if (counter == 8) {
				displayBoard(board);
				puts("Looks like it's a draw.");
			}

        // Change turns
        playerTurn = playerTurn == 'X' ? 'O' : 'X';

    }
    return 0;
}
