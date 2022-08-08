#include <stdio.h>
#include <string.h>
#include "passwordmanager.h"

char masterPassword[50];
int placeInArray = 0;
char usernames[50][50];
char passwords[50][50];

void create() {
    puts("Please enter the username of the account: ");
    scanf("%49s", usernames[placeInArray]);
    puts("Please enter the password of the account: ");
    scanf("%49s", passwords[placeInArray]);
    puts("User created!");
}

void ListUsers() {
    puts("List of users");
    for (int i = 0; i < placeInArray;  i++) 
        printf("\t%i) %s\n", i+1, usernames[i]);

}

int authenticate() {
    char enteredPassword[50];
    puts("Please enter your masterpassword: ");
    scanf("%s", enteredPassword);
    if (!strncmp(masterPassword, enteredPassword, sizeof(enteredPassword)))
        return 1;
    return 0;
}

void getUserData() {
    int userId;
    puts("Enter the number that corresponds with the user that you would like to see: ");
    scanf("%i", &userId);

    if (userId > placeInArray || userId <= 0)
        puts("That number does not correspond with any user.");
    
    else if (authenticate(masterPassword)) 
        printf("The password is: %s.\n", passwords[userId - 1]);
    else
        puts("Masterpassword incorrect!");
} 

void removeUser() {
	int userId;
	puts("Please enter the number that corresponds to the user that you would like to delete");
	scanf("%i", &userId);

	if (userId > placeInArray || userId < 1) 
		puts("That number does not correspond with any user.");
		return; 
    
	for (int index = userId - 1; index < placeInArray && index > 0; index++) {
	     strcpy(usernames[index - 1], usernames[index]);
	     strcpy(passwords[index - 1], passwords[index]);
	}

	placeInArray -= 1; 

	puts("Removal of user was successful!");

}

void setup(int NeedToAuthenticate) {
    if (NeedToAuthenticate) {
        if (!authenticate(masterPassword)) {
			puts("Invalid masterpassword.");
            return;
		}
    }
    puts("Please enter your new master password: ");
    scanf("%49s", masterPassword);
    
}
int main() {
    int command;
    setup(0);
    while (1) {
        puts("Please enter a command: "); 
        scanf("%i", &command); 

		switch (command) {
			case 0:
				puts("List of commands: ");
				puts("0\tOpens help menu");
				puts("1\tAllows you to reset your masterpassword");
				puts("2\tAllows you to create a username that will correspond with a password");
				puts("3\tList users");
				puts("4\tGet password from username"); 
				puts("5\tRemove a username");
				break;
			case 1: 
				setup(1);
				break;
			case 2: 
				create();
				placeInArray += 1; 
				break; 
			case 3:
				if (placeInArray > 0)  
					ListUsers();
				else 
					puts("You have not created any users.");
				break;
			case 4:
				if (placeInArray > 0) {
					ListUsers();
					getUserData();
				} else 
					puts("You have not created any users.");
				break;
			case 5: 
				if (placeInArray > 0) {
					ListUsers();
					removeUser();
				} else 
					puts("You have not created any users.");
				break;
			default: 
				puts("Looks like the command you entered doesn't match any of the available commands. Please type '0' for a list of commands.");

	}

    }
    return 0;
}
