#include <stdio.h>
#include <string.h>
// Enter current masterpassword before resetting it
// Option to remove a user
// Cleanup

void setup(char *password, int NeedToAuthenticate, char *masterPassword) {
    if (NeedToAuthenticate) {
        if (!authenticate(masterPassword))
            return;
    }
    puts("Please enter your new master password: ");
    scanf("%49s", password);
    
}

void create(char usernames[][50], char passwords[][50], int arrayPlace) {
    puts("Please enter the username of the account: ");
    scanf("%49s", usernames[arrayPlace]);
    puts("Please enter the password of the account: ");
    scanf("%49s", passwords[arrayPlace]);
    puts("User created!");
}

void ListUsers(char usernames[][50], int arrayPlace) {
    // Make arrayPlace loop variable.
    puts("List of users");
    for (int i = 0; i < arrayPlace && arrayPlace > 0;  i++) {
        printf("\t%i) %s\n", i+1, usernames[i]);
    }
}

int authenticate(char masterpassword[]) {
    char enteredPassword[50];
    puts("Please enter your masterpassword: ");
    scanf("%s", enteredPassword);
    if (!strncmp(masterpassword, enteredPassword, sizeof(enteredPassword)))
        return 1;
    return 0;
}

void getUserData(char passwords[][50], char masterpassword[], int arrayPlace) {
    int userId;
    puts("Enter the number that corresponds with the user that you would like to see: ");
    scanf("%i", &userId);

    if (userId > arrayPlace || userId <= 0)
        puts("That number does not correspond with any user.");
    
    else if (authenticate(masterpassword)) 
        printf("The password is: %s.\n", passwords[userId - 1]);
    else
        puts("Masterpassword incorrect!");
}

int main() {
    int command;
    char masterPassword[50];
    int placeInArray = 0;
    char users[50][50];
    char passwords[50][50];

    setup(masterPassword);
    while (1) {
        puts("Please enter a command: "); 
        scanf("%i", &command); 
        if (command == 0) {
            puts("List of commands: ");
            puts("0\tOpens help menu");
            puts("1\tAllows you to reset your masterpassword");
            puts("2\tAllows you to create a username that will correspond with a password");
            puts("3\tList users");
            puts("4\tGet password from username"); 

        } else if (command == 1) {
            setup(masterPassword, 1, masterPassword);
        } else if (command == 2) {
            create(users, passwords, placeInArray);
            placeInArray += 1; 
        } else if (command == 3) {
           ListUsers(users, placeInArray);
        } else if (command == 4) {
            if (placeInArray > 0) {
                ListUsers(users, placeInArray); 
                getUserData(passwords, masterPassword, placeInArray);
            } else
                puts("You have not created any users.");
        } else
            puts("Looks like the command you entered doesn't match any of the available commands. Please type '0' for a list of commands.");
    }
    return 0;
}
