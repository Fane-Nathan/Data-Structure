#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// To initialize a linked list to be empty
Node* head = NULL;

// To add node we can use struct Node* newNode = (struct Node*) malloc (sizeof(struct Node));
void add(){
    Node* newNode = (Node*) malloc (sizeof(Node));
    printf("Enter the data: ");
    scanf("%d", &(newNode->data));
    newNode->next = head;
    head = newNode;
}

// To insert in certain place of the data
void insert(int data, int position){
    Node* insertNode = (Node*)malloc(sizeof(Node));
    insertNode->data = data;
    insertNode->next = NULL;

// ________________ I still do not understand at this part until the bottom _________________
    if (head == NULL || position == 0){
        insertNode->next = head;
        head = insertNode;
    } else {
        Node* current = head;
        for (int i = 0; i < position; i++){
            current = current->next;
        }

        if (current != NULL){
            insertNode->next = current->next;
            current->next = insertNode;
        } else {
            printf("Position out of range\n");
        }
    }
}

void delete(int data){
    if (head == NULL){
        printf("List is empty\n");
        return;
    }

    // If HEAD NODE itself holds the key/data to be deleted
    if (head->data == data){
        Node* temp = head;
        head = head->next;
        free(temp);
        return;
    }

    // search the key/data to be deleted
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL && current->data != data){
        prev = current;
        current = current->next;
    }

    // If key was not present in the linked list
    if(current == NULL){
        printf("Element not found\n");
        return;
    }

    // unlink the node from linked list
    prev->next = current->next;

    free(current);
}

// I understand this
int main(void){
    printf("This is a linked list data structure\n");
    printf("\nThere are 3 option currently I'm developing\n");
    printf("1. Add a data (must be an integer)\n");
    printf("2. Insert a data (also an int)\n");
    printf("3. Delete a data\n");
    printf("4. Exit\n");

    int userChoice;
    do {
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                add();
                break;
            case 2:
                printf("What number do you want to insert: ");
                int num1;
                scanf("%d", &num1);
                printf("At index: ");
                int index;
                scanf("%d", &index);
                insert(num1, index);
                break;
            case 3:
                printf("What number do you want to delete: ");
                int del;
                scanf("%d", &del);
                delete(del);
                break;
            case 4:
                printf("Exiting....\n");
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (userChoice != 4);
        
    return 0;
}