#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearBufferInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

typedef struct Node {
    int quantity;
    char *carName;
    char *carType;

    struct Node *next;
    struct Node *prev;
} Node;

int quantityInput(void) {
    int quantity;
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    clearBufferInput();
    return quantity;
}

char *carName() {
    char name = (char *)malloc(sizeof(char) * 20);
    printf("Enter the car name: ");
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = '\0';
    return name;
}

char *carType() {
    char type = (char *)malloc(sizeof(char) * 20);
    printf("Enter the car name: ");
    fgets(type, 20, stdin);
    type[strcspn(type, "\n")] = '\0';
    return type;
}

Node *createNode(int quantity, char *name, char *type) {
    Node *createNode = (Node *)malloc(sizeof(Node));

    if (createNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    createNode->quantity = quantity;
    createNode->carName = name;
    createNode->carType = type;

    createNode->next = NULL;
    createNode->prev = NULL;

    return createNode;
}

void insertData(Node **head, Node **tail, int quantity, char *name, char *type) {
    Node *newNode = createNode(quantity, name, type);

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        newNode->prev = *tail;
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void addNode(Node **head, Node **tail) {
    int quantity = quantityInput();
    char *name = carName();
    char *type = carType();

    insertData(head, tail, quantity, name, type);
}

void deleteNode(Node **head, Node **tail) {
    Node *temp = *head;
    int position;
    if (*head == NULL) {
        printf("The list is empty\n");
        return;
    }
}

void switchcase(int userOption, Node **head, Node **tail) {
    switch (userOption) {
        case 1:
            addNode(head, tail);
            break;
        case 2:
            deleteNode(head, tail);
            break;
        case 3:
            printNode(head);
            break;
        case 4:
            printf("Exiting the program...\n");
            break;
        defualt:
            printf("Invalid option\n");
            break;
    }
}

int main(void) {
    int userOption;
    Node *head = NULL;
    Node *tail = NULL;

    do {
        printf("====================================\n");
        printf("1. Add a new node\n");
        printf("2. Delete a node\n");
        printf("3. Print the list\n");
        printf("4. Exit\n");
        printf("====================================\n");
        printf("Enter your option: ");
        scanf("%d", &userOption);

        switchcase(userOption, &head, &tail);
    }
}