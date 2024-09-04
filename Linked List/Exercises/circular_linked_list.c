#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

void randomChar(char *str, int length) {
    int i;
    for (i = 0; i < length; i++) {
        str[i] = 'a' + rand() % 26;
    }
    str[i] = '\0';
}

void randomInt(int *data, int length) {
    int i;
    for (i = 0; i < length; i++) {
        data[i] = rand() % 100;
    }
}

typedef enum { INT, STRING } DataType;

typedef struct Node {
    DataType type;
    union data {
        int data;
        char *words;
    } data;
    struct Node *next;
} Node;

Node* createNode(DataType type, int data, char *words) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->type = type;
    if (type == INT) {
        newNode -> data.data = data;
    } else {
        newNode -> data.words = strdup(words);
    }

    return newNode;
}

void insert(DataType type, int data, char *words, int position, Node **head) {
    Node *insertNode = createNode(type, data, words);
    Node *temp = *head;

    if (position == 0) {
        if (*head == NULL) {
            // if the list is empty, make the only node point to itself
            insertNode->next = insertNode;
        } else {
            // insert at beginning and adjust the last node's next pointer
            while (temp->next != *head){
                temp = temp->next;
            }
            temp->next = insertNode;
            insertNode->next = *head;
        }
        *head = insertNode;
    } else {
        // insert at given position
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        insertNode->next = temp->next;
        temp->next = insertNode;
    }
}

void 

int main(void){
    Node *head = NULL;
    int userChoice;

    do {
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        switch (userChoice){
            case 1:
                printf("You chose 1\n");
                break;
            case 2:
                printf("You chose 2\n");
                break;
            case 3:
                printf("You chose 3\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (userChoice < 1 || userChoice > 4);

    return 0;
}