#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10

typedef struct Node {
    char *rubiksName;
    char *rubiksType;
    int quantity;
    char *price;
    char *rubiksID;

    struct Node *next;
    struct Node *prev;
} Node;

Node *hashTable[TABLE_SIZE];

unsigned int hashFunction(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

void clearBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

char *randomIDgen() {
    srand(time(NULL));
    char *id = (char *)malloc(sizeof(char) * 7);
    char number[] = "0123456789";

    id[0] = 'R';
    id[1] = 'B';

    for (int i = 2; i < 6; i++) {
        id[i] = number[rand() % 10];
    }

    id[6] = '\0';
    return id;
}

char *name() {
    char *name = NULL;
    char tempChar;
    int len = 0;

    printf("Please input rubik's name [No limits!] (ENTER HOW LONG YOU WANT THIS IS JUST A TEST FOR MY PROGRAM): ");

    while ((tempChar = getchar()) != '\n' && tempChar != EOF) {
        name = realloc(name, len + 2);
        name[len] = tempChar;
        len++;
    }

    if (name != NULL) {
        name[len] = '\0';
    }

    return name;
}

char *getInput(char *message, int size) {
    char *input = (char *)malloc(sizeof(char) * size);
    printf("%s", message);
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';
    return input;
}

void validatePrice(char *price, int min, int max) {
    if (atoi(price) < min || atoi(price) > max) {
        printf("\nInvalid price. Price must be between Rp. %d and Rp. %d\n\n", min, max);
    }
}

int quantity() {
    int quantity;
    do {
        printf("Please input rubik's quantity [1 - 50]: ");
        scanf("%d", &quantity);
        clearBufferInput();

        if (quantity < 1 || quantity > 50) {
            printf("\nInvalid quantity. Quantity must be between 1 and 50\n\n");
        }

    } while (quantity < 1 || quantity > 50);
    return quantity;
}

void magnetic() {
    char *price = getInput("Please input Rubik price [Rp. 200,000 - Rp. 300,000]: ", 20);
    validatePrice(price, 200000, 300000);
}

void nonMagnetic() {
    char *price = getInput("Please input Rubik price [Rp. 50,000 - Rp. 150,000]: ", 20);
    validatePrice(price, 50000, 150000);
}

bool isInvalidType(char *type, char *magneticType, char *nonMagneticType);
void processType(char *type, char *magneticType, char *nonMagneticType);

char *getRubiksType() {
    char *magneticType = "Magnetic";
    char *nonMagneticType = "Non-Magnetic";
    char *type = NULL;

    do {
        type = getInput("Please input rubik's type [Magnetic / Non-Magnetic] [Case sensitive]: ", 20);
        quantity();

        if (isInvalidType(type, magneticType, nonMagneticType)) {
            printf("\nInvalid type. Type must be either Magnetic or Non-Magnetic\n\n");
            continue;
        }

        processType(type, magneticType, nonMagneticType);
    } while (type == NULL || isInvalidType(type, magneticType, nonMagneticType));

    return type;
}

bool isInvalidType(char *type, char *magneticType, char *nonMagneticType) {
    return strcmp(type, magneticType) != 0 && strcmp(type, nonMagneticType) != 0;
}

void processType(char *type, char *magneticType, char *nonMagneticType) {
    if (strcmp(type, magneticType) == 0) {
        magnetic();
    } else {
        nonMagnetic();
    }
}

Node *addRubiks(Node **head, Node **tail) {
    Node *addRubik = (Node *)malloc(sizeof(Node));

    addRubik->rubiksName = name();
    addRubik->rubiksType = getRubiksType();
    addRubik->quantity = quantity();
    addRubik->rubiksID = randomIDgen();
    addRubik->next = NULL;

    if (*head == NULL) {
        *head = addRubik;
        *tail = addRubik;
    } else {
        (*tail)->next = addRubik;
        addRubik->prev = *tail;
        *tail = addRubik;
    }

    return addRubik;
}

void viewRubiks(Node *head) {
    if (head == NULL) {
        printf("No rubik's data available\n");
    } else {
        Node *temp = head;
        while (temp != NULL) {
            printf("");
        }
    }
}

void checkSuccess(Node *addRubiks) {
    if (addRubiks != NULL) {
        printf("Rubik's data has been added successfully\n");
        printf("========================================\n");
        printf("Rubik's ID: %s\n", addRubiks->rubiksID);
        clearBufferInput();
        printf("\nPress enter to continue...");
    } else {
        printf("Failed to add rubik's data\n");
    }
}

void switchCase(int userChoice, Node **head, Node **tail) {
    switch (userChoice) {
        case 1:
            Node *newNode = addRubiks(head, tail);
            checkSuccess(newNode);
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
        clearBufferInput();

        switchCase(userChoice, &head, &tail);

    } while (userChoice != 4);

    return 0;
}