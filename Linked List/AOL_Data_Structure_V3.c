#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void randomCharGeneration(char *word, int length) {
    for (int i = 0; i < length; i++) {
        word[i] = (rand() % 26) + 97;
    }
    word[length] = '\0';
}

void randomIntGeneration(int *number, int total) {
    for (int i = 0; i < total; i++) {
        number[i] = (rand() % 100) + 1;
    }
}

typedef enum {INT, STRING} DataType;

typedef struct Node {
    DataType dataType;
    union {
        char *words;
        int number;
    } data;
    struct Node *next;
    struct Node *prev;
} Node;

Node* createNode(DataType dataType, char *words, int number) {
    Node *createNode = (Node *)malloc(sizeof(Node));
    createNode->dataType = dataType;
    if (dataType == INT) {
        createNode->data.number = number;
    } else {
        createNode -> data.words = strdup(words);
    }
    createNode->next = NULL;    
    createNode->prev = NULL;

    return createNode;
}

void insertAtBeginning(DataType dataType, char* words, int number, Node **head){
    Node *newNode = createNode(dataType, words, number);
    newNode->next = *head;
    *head = newNode;
}

void insertNode(DataType dataType, char* words, int number, Node **head, int position){
    Node *insertNode = createNode(dataType, words, number);
    if (*head == NULL || position == 1) {
        insertNode->next = *head;
        *head = insertNode;
    } else {
        Node *temp = *head;
        int count = 1;
        while (temp->next != NULL && count < position - 1) {
            temp = temp->next;
            count++;
        }
        if (count == position - 1) {
            insertNode->next = temp->next;
            temp->next = insertNode;
        } else {
            printf ("Position out of range\n");
        }
    }
}

void display(Node *head){
    Node *temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("%d. ", count);
        if (temp->dataType == INT) {
            printf("%d\n", temp->data.number);
        } else {
            printf("%s\n", temp->data.words);
        }
        temp = temp->next;
        count++;
    }
}

void displayASCII(Node *head){
    Node *temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("%d. ", count);
        if (temp->dataType == STRING) {
            for (int i = 0; i < strlen(temp->data.words); i++) {
                printf("%d", temp->data.words[i]);
                if (temp->data.words[i + 1] != '\0') {
                    printf(" - ");
                }
            }
            printf("\n");
        } else {
            if (temp->data.number < 32 || temp->data.number > 126){
                printf("Non-printable ASCII character\n");
                printf("Do you want to display it either way?\n");
                printf("1. Yes\n2. No\n");
                printf("Option: ");
                int option;
                if (scanf("%d", &option) != 1) {
                    printf("Invalid input. Skipping this character.\n");
                    temp = temp->next;
                    count++;
                    continue;
                }
                if (option == 1){
                    printf("%d", temp->data.number);
                } else {
                    temp = temp->next;
                    count++;
                    continue;
                }
            } else {
                printf("%d", temp->data.number);
            }
        }
        temp = temp->next;
        count++;
    }
}

void delete(DataType dataType, int number, char *words, Node **head) {
    Node *temp = *head;
    Node *prev = NULL;

    while (temp != NULL) {
        if (temp->dataType == dataType){
            if ((dataType == INT && temp->data.number) || (dataType == STRING && strcmp(temp->data.words, words) == 0)) {
                // Found the node to delete
                if (prev == NULL) {
                    // Node to delete is the head
                    *head = temp->next;
                } else {
                    // Node to delete is not the head
                    prev->next = temp->next;
                }
                if (temp->next != NULL) {
                    // Node to delete is not the tail
                    temp->next->prev = prev;
                }
                if (dataType == STRING) {
                    // Free the duplicated string
                    free(temp->data.words);
                }
                free(temp);
                return;
            }
        }
        prev = temp;
        temp = temp->next;
    }
}

int search(Node *head, DataType dataType, char* words, int number) {
    Node *current = head;
    int position = 1;

    while (current != NULL) {
        if (current->dataType == dataType) {
            if (dataType == INT && current->data.number == number) {
                return position;
            } else if (dataType == STRING && strcmp(current->data.words, words) == 0) {
                return position;
            }
        }
        current = current->next;
        position++;
    }

    return -1;
}

int main(void) {
    Node *head = NULL;
    int userChoice;

    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Mac and Linux
        system("clear");
    #endif
    
    printf("\nThis is a program to store a data from a user either integer or word.\n");
    do {
        printf("\n==============================\n");
        printf(" 1. Create a list\n");
        printf(" 2. Insert a data\n");
        printf(" 3. Display\n");
        printf(" 4. Delete\n");
        printf(" 5. Search\n");
        printf(" 6. Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        clearInputBuffer();
        
        switch (userChoice) {
            case 1:
                int choice;
                do {
                    printf("\n\nDo you want a random generated number or word?");
                    printf("\n1. Number\n2. Word\n3. Back\n");
                    printf("Option: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            int number;
                            printf("How many: ");
                            scanf("%d", &number);
                            int *randomNumber = (int *)malloc(sizeof(int) * number);
                            for (int i = 0; i < number; i++) {
                                randomIntGeneration(&randomNumber[i], 1);
                                insertAtBeginning(INT, NULL, randomNumber[i], &head);
                            }
                            free(randomNumber);
                            break;
                        case 2:
                            int word;
                            printf("How many: ");
                            scanf("%d", &word);
                            for (int i = 0; i < word; i++){
                                char *randomWord = (char*) malloc (sizeof(char) * 11);
                                randomCharGeneration(randomWord, 11);
                                insertAtBeginning(STRING, randomWord, 0, &head);
                                free(randomWord);
                            }
                            break;
                    }
                } while (choice != 3);
                break;
            case 2:
                int option2;
                printf("Do you want to insert a number or word? (1/2)\n");
                printf("Option: ");
                scanf("%d", &option2);
                switch (option2) {
                    case 1:
                        int answer;
                        int location;
                        printf("INT: ");
                        scanf("%d", &answer);
                        printf("At what position? ");
                        scanf("%d", &location);
                        insertNode(INT, NULL, answer, &head, location);
                        break;
                    case 2:
                        char words[256];
                        printf("STRING: ");
                        fgets(words, 256, stdin);
                        clearInputBuffer();
                        int position;
                        printf("At what position? ");
                        scanf("%d", &position);
                        insertNode(STRING, words, 0, &head, position);
                        break;
                }
                break;
            case 3:
                int option;
                printf("1. Display as words\n2. Display as ASCII\n3. Back\n");
                printf("\nOption: ");
                scanf("%d", &option);
                switch (option) {
                    case 1:
                        printf("\n--------------------\n");
                        display(head);
                        printf("--------------------\n");
                        break;
                    case 2:
                        printf("\n--------------------\n");
                        displayASCII(head);
                        printf("--------------------\n");
                        break;
                    case 3:
                        printf("Invalid option, please enter 1, 2, or 3\n");
                }
                break;
            case 4:
                int option4;
                printf("Do you want to delete a number or word? (1/2)\n");
                printf("Option: ");
                scanf("%d", &option4);
                switch (option4) {
                    case 1:
                        int numToDelete;
                        printf("Enter the number to delete: ");
                        scanf("%d", &numToDelete);
                        delete(INT, numToDelete, NULL, &head);
                        break;
                    case 2:
                        char wordToDelete[100];
                        printf("Enter the word to delete: ");
                        scanf("%s", wordToDelete);
                        delete(STRING, 0, wordToDelete, &head);
                        break;
                    default:
                        printf("Invalid option, please enter 1 or 2\n");
                }
                break;
            case 5:
                printf("Do you want to search for a number or word? (1/2)\n");
                printf("Option: ");
                int option5;
                scanf("%d", &option5);
                switch (option5) {
                    case 1:
                        int numToSearch;
                        printf("Enter the number to search: ");
                        scanf("%d", &numToSearch);
                        int positionNum = search(head, INT, NULL, numToSearch);
                        if (positionNum != -1) {
                            printf("Number '%d' found at position %d\n", numToSearch, positionNum);
                        } else {
                            printf("Number '%d' is not found\n", numToSearch);
                        }
                        break;
                    case 2:
                        char wordToSearch[100];
                        printf("Enter the word to search: ");
                        scanf("%s", wordToSearch);
                        int positionWord = search(head, STRING, wordToSearch, 0);
                        if (positionWord != -1) {
                            printf("Word '%s' found at position %d\n", wordToSearch, positionWord);
                        } else {
                            printf("Word '%s' not found\n", wordToSearch);
                        }
                        break;
                    default:
                        printf("Invalid option, please enter 1 or 2\n");
                }
                break;
            case 6:
                printf("Thank you, have a nice day!\n");
        }
    } while (userChoice != 6);
    return 0;
}