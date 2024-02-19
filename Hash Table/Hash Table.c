#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int key;
    int value;
    struct Node* next;
};

struct Node* hashTable[SIZE];

// Function to create a new node
struct Node* createNode(int key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value; 
    newNode->next = NULL;
    return newNode;
}

// Function to insert a key-value pair into the hash table
void insert(int key, int value) {
    int index = key % SIZE;
    struct Node* newNode = createNode(key, value);

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to search for a value based on the key
int search(int key) {
    int index = key % SIZE;
    struct Node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }

    return -1; // Key not found
}

// Function to display the hash table
void display() {
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        struct Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("(%d, %d) ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    // Initialize hash table
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    // Insert key-value pairs into the hash table
    insert(1, 10);
    insert(2, 20);
    insert(3, 30);
    insert(4, 40);
    insert(5, 50);

    // Display the hash table
    display();

    // Search for a value based on the key
    int key = 3;
    int value = search(key);
    if (value != -1) {
        printf("Value for key %d: %d\n", key, value);
    } else {
        printf("Key not found\n");
    }

    return 0;
}
