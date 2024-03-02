#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearBufferInput(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

typedef struct Node {
    char *fruit;
    int quantity;

    struct Node *next;
    struct Node *prev;
} Node;

char *fruit(){
    char *fruitName = (char *)malloc(20 * sizeof(char));
    if (!fruitName) {
        return NULL;
    }
    printf("Input fruit name: ");
    fgets(fruitName, 20, stdin);
    fruitName[strcspn(fruitName, "\n")] = 0;
    return fruitName;
}

int quantity(){
    int quantity;
    printf("Input quantity: ");
    scanf("%d", &quantity);
    clearBufferInput();
    return quantity;
}

Node *createNode(char *fruit, int quantity){
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    
    newNode->fruit = malloc(strlen(fruit) + 1);
    if (!newNode->fruit) {
        free(newNode);
        return NULL;
    }
    strcpy(newNode->fruit, fruit);

    newNode->quantity = quantity;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void addData(Node **head, Node **tail){
    char *fruitName = fruit();
    int fruitQuantity = quantity();
    Node *newNode = createNode(fruitName, fruitQuantity);

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }

    free(fruitName);
}

void mainDisplay(Node **head, Node **tail){    
    printf("\033[1;36m");
    printf("     Dictionary        ||       Quantity\n");
    printf("====================   ||  =================\n");
    printf(" English | Indonesia   ||\n");
    printf("--------------------   ||\n");
    if (*head != NULL){
        Node *current = *head;
        while (current != NULL){
            printf("  %-20s | %10d\n", current->fruit, current->quantity);
            current = current->next;
        }
    } else {
        printf("No data is available\n");
    }
    printf("\033[0m");
}

void switchCase(int userOption, Node **head, Node **tail){
    switch (userOption) {
        case 1:
            addData(head, tail);
            break;
        case 2:
            // deleteData(head, tail);
            break;
        case 3:
            printf("Thank you for using this program\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

int main(void){
    int userOption;
    Node *head = NULL;
    Node *tail = NULL;

    do {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

        mainDisplay(&head, &tail);
        printf("\n\n");
        printf("=== Menu ===\n");
        printf(" 1. Add\n");
        printf(" 2. Delete\n");
        printf(" 3. Exit\n");
        printf("============\n");
        printf("Choose: ");
        scanf("%d", &userOption);
        clearBufferInput();

        switchCase(userOption, &head, &tail);

    } while (userOption != 3);

    return 0;
}