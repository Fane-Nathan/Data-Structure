#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char rubiksName;
    char 
}

void switchCase(int userChoice, Node **head, Node **tail) {
    switch (userChoice) {
        case 1:
            addRubiks(head, tail);
            break;
        case 2:
            viewRubiks(head);
            break;
        case 3:
            deleteRubiks(head, tail);
            break;
        case 4:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

int main(void) {
    int userChoice;
    Node *head = NULL;
    Node *tail = NULL;
    printf("\nGR Rubiks Cube Store\n");

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        printf("==========================\n");
        printf("|  1. Add a new rubiks   |\n");
        printf("|  2. View rubiks        |\n");
        printf("|  3. Delete rubiks      |\n");
        printf("|  4. Exit               |\n");
        printf("==========================\n");
        printf("Option: ");
        scanf("%d", &userChoice);

        switchCase(userChoice, &head, &tail);

    } while (userChoice != 4);
}