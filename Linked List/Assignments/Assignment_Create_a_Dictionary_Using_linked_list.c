#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

void clearBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

typedef struct Node {
    char *engFruit;
    char *indFruit;
    int quantity;

    struct Node *next;
    struct Node *prev;
} Node;

void mainDisplay(Node **head, Node **tail);

char *engFruit() {
    char *fruitName = (char *)malloc(20 * sizeof(char));
    if (!fruitName) {
        return NULL;
    }
    printf("Input fruit name [English]: ");
    fgets(fruitName, 20, stdin);
    fruitName[strcspn(fruitName, "\n")] = 0;
    return fruitName;
}

char *indFruit() {
    char *fruitName = (char *)malloc(sizeof(char) * 20);
    if (!fruitName) {
        return NULL;
    }
    printf("Input fruit name [Indonesia]: ");
    fgets(fruitName, 20, stdin);
    fruitName[strcspn(fruitName, "\n")] = '\0';
    return fruitName;
}

int quantity() {
    int quantity;
    printf("Input quantity: ");
    scanf("%d", &quantity);
    clearBufferInput();
    return quantity;
}

Node *createNode(char *engFruit, char *indFruit, int quantity) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }

    newNode->engFruit = malloc(strlen(engFruit) + 1);
    newNode->indFruit = malloc(strlen(indFruit) + 1);
    if (!newNode->engFruit || !newNode->indFruit) {
        free(newNode);
        return NULL;
    }
    strcpy(newNode->engFruit, engFruit);
    strcpy(newNode->indFruit, indFruit);
    newNode->quantity = quantity;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void freeList(Node **head) {
    Node *current = *head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current->engFruit);
        free(current->indFruit);
        free(current);
        current = next;
    }

    *head = NULL;
}

void addData(Node **head, Node **tail) {
    char *fruitNameEng = engFruit();
    char *fruitNameInd = indFruit();
    int fruitQuantity = quantity();
    Node *newNode = createNode(fruitNameEng, fruitNameInd, fruitQuantity);

    if (fruitNameEng == NULL || fruitNameInd == NULL) {
        printf("Failed to allocated memory\n");
        return;
    }

    if (newNode == NULL) {
        printf("Failed to allocated memory\n");
        return;
    }

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

void deleteData(Node **head, Node **tail) {
    if (*head == NULL) {
        printf("No data is available\n");
    } else {
        char *fruitNameEng = engFruit();
        char *fruitNameInd = indFruit();
        Node *current = *head;
        int count = 0;
        printf("Before deletion:\n");
        mainDisplay(head, tail);
        while (current != NULL) {
            printf("Iteration %d: current fruit [English & Indonesia]= %s | %s\n", count, current->engFruit, current->indFruit);
            if (strcmp(current->engFruit, fruitNameEng) == 0 || strcmp(current->indFruit, fruitNameInd) == 0) {
                // Found the data
                printf("Found matching fruit at iteration %d\n", count);
                // Check if the node has a previous node.
                if (current->prev != NULL) {
                    // If it is not empty then the active node is not the head.
                    // Select the previous node pointer that pointing to our active node.
                    // Then change the pointer to the node after the active node.
                    current->prev->next = current->next;
                } else {
                    // Select the head node
                    *head = current->next;
                }
                // Check if the node has a next node
                if (current->next != NULL) {
                    // If it is not empty then the current node is not the tail.
                    // Select the next node pointer that pointing to our active node.
                    // Then change it to pointing the node before the active node.
                    current->next->prev = current->prev;
                } else {
                    // Select the tail node
                    *tail = current->prev;
                }
                free(current->engFruit);
                free(current->indFruit);
                free(current);
                break;
            }
            current = current->next;
            count++;
        }
        printf("After deletion:\n");
        mainDisplay(head, tail);
        free(fruitNameEng);
        free(fruitNameInd);
    }
}

void mainDisplay(Node **head, Node **tail) {
    printf("\033[1;36m"); // Just adding color hehe
    printf("        Dictionary           ||       Quantity\n");
    printf("===========================  ||  =================\n");
    printf(" No. | English | Indonesia   ||\n");
    printf("---------------------------  ||\n");
    if (*head != NULL) {
        Node *current = *head;
        int counter = 1;
        while (current != NULL) {
            printf(" %-2d. | %-6s  |  %-10s ||          %d\n", counter, current->engFruit, current->indFruit, current->quantity);
            current = current->next;
        }
    } else {
        printf("   No data is available\n");
    }
    printf("\033[1;31m"); // Just adding color hehe
}

void switchCase(int userOption, Node **head, Node **tail) {
    switch (userOption) {
        case 1:
            addData(head, tail);
            break;
        case 2:
            deleteData(head, tail);
            break;
        case 3:
            printf("Thank you for using this program\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

int main(void) {
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

    freeList(&head);

    return 0;
}