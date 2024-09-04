#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *head = NULL;

Node *createNode(char *data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = (char*)malloc(sizeof(char));
    if (newNode->data == NULL){
        printf("Unable to allocate memory for data\n");
        free(newNode);
        exit(1);
    }

    strcpy(newNode->data, data);
    newNode->next = NULL;

    return newNode;
}

void displayCharacters(){
    Node *current = head;
    int numberOfWords = 1;
    printf("\n-----------------------------");
    printf("\nAll the words in the list:\n");
    while (current != NULL){
        printf("%d. %s\n", numberOfWords++, current->data);
        current = current->next;
    }
    printf("-----------------------------\n");
}

void displayASCII(){
    Node *temp = head;
    int counter = 1;
    while (temp != NULL) {
        printf("%d. ", counter++);
        for (int i = 0; temp->data[i] != '\0'; i++){
            printf("%d", (int)temp->data[i]);
            if (temp->data[i + 1] != '\0'){
                printf("-");
            }
        }
        printf("\n");
        temp = temp->next;
    }
}

void insert(char *data){
    Node *newNode = createNode(data);
    if (head == NULL){
        head = newNode;
    } else {
        Node *current = head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

int delete(char *data){
    Node *current = head;
    Node *previous = NULL;
    int deleted = 0;
    while (current != NULL){
        if (strcmp(current->data, data) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            Node *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
            printf("Data deleted\n");
            deleted = 1;
            break;
        } else {
            previous = current;
            current = current->next;
        }
    }
    if (deleted == 0){
        printf("Data is not available\n");
    }
    return 0;
}

int search(char *data){
    Node *current = head;
    int index = 0; // To keep track of the index of the data
    while (current != NULL){
        printf("\n-----------------------------\n");
        printf("%d. %s\n", index, current->data);
        if (strcmp(current->data, data) == 0) {
            printf("\nData found\n");
            return index;
        } else {
            current = current->next;
            index++; // Increment the index
        }
    }
    printf("Data not found\n\n");
    return -1; // Return -1 if the data is not found
}

int main(void){
    int userChoice;
    char buffer[100000];
    printf("\nMenu for AOL Data Structure:\n");
    do {
        printf("===============================\n");
        printf(" 1. Display the characters\n");
        printf(" 2. Display the ASCII values\n");
        printf(" 3. Insert word\n");
        printf(" 4. Delete word\n");
        printf(" 5. Search for a word\n");
        printf(" 6. Exit\n");
        printf("===============================\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                displayCharacters();
                printf("\n");
                break;
            case 2:
                displayACII();
                printf("\n");
                break;
            case 3:
                printf("\nEnter the word: ");
                scanf("%s", buffer);
                char *word = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                strcpy(word, buffer);
                insert(word);
                break;
            case 4:
                printf("\nEnter the word to delete: ");
                scanf("%s", buffer);
                char *wordToDelete = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                strcpy(wordToDelete, buffer);
                delete(wordToDelete);
                break;
            case 5:
                printf("Enter the word to search: ");
                scanf("%s", buffer);
                char *wordToSearch = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                strcpy(wordToSearch, buffer);
                int index = search(wordToSearch);
                if (index != -1){
                    printf("The word is found at index %d\n", index);
                    printf("-----------------------------\n");
                }
                break;
            case 6:
                printf("Goodbye!\n");
                break;
        }
    } while (userChoice != 6);

    return 0;
}