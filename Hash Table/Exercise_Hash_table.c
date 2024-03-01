#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

/**
 * @struct Node
 * @brief A struct representing a node in a hash table.
 * 
 * The Node struct contains a key-value pair, where the key is a string and the value is an integer.
 * It also contains a pointer to the next node in the hash table.
 */
typedef struct Node {
//  char* key;          /**< The key of the node */
    void* key;          /**< For every data type input, the key will be void */
    int value;          /**< The value of the node */
    struct Node* next;  /**< Pointer to the next node */
} Node;

// To make it more readable (basically), so it become more modular
typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; i < strlen(key); i++) {
        hashValue = hashValue * 31 + key[i];
    }
    return hashValue % TABLE_SIZE;
}

Node* createNode(const char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insert(HashTable* ht, const char* key, int value) {
    unsigned int index = hash(key);
    Node* newNode = createNode(key, value);

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        Node* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int search(HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1;
}

void delete(HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    Node* current = ht->table[index];
    Node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                ht->table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* current = ht->table[i];
        while (current != NULL) {
            printf("(%s, %d) ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    insert(&ht, "apple", 5);
    insert(&ht, "banana", 10);
    insert(&ht, "cherry", 15);

    printf("Value for key 'apple': %d\n", search(&ht, "apple"));
    printf("Value for key 'banana': %d\n", search(&ht, "banana"));
    printf("Value for key 'cherry': %d\n", search(&ht, "cherry"));

    delete(&ht, "banana");

    printf("Value for key 'banana' after deletion: %d\n", search(&ht, "banana"));

    printHashTable(&ht);

    return 0;
}

