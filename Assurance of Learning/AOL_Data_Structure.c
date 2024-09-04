#include <cstdio>
#include <cstring>
#include <cstdlib>


#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

TrieNode *createNode() {
    TrieNode *newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(TrieNode *root, const char *key) {
    TrieNode *node = root;
    for (int i = 0; i < strlen(key); i++){
        int index = key[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = createNode();
            node = node->children[index];
        }
    }
    node->isEndOfWord = 1;
}

int search(TrieNode *root, const char *key){
    int index;
    TrieNode *node = root;
    for (int i = 0; i < strlen(key); i++){
        index = key[i] - 'a';
        if (!node->children[index]){
            return 0;
        }
        node = node->children[index];
    }
    return (node != NULL && node->isEndOfWord);
}

int isEmpty(TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i]){
            return 0;
        }
    }
    return 1;
}

TrieNode *delete(TrieNode *root, const char *key, int depth) {
    if (!root) return NULL;
    if (depth == strlen(key)){
        if(root->isEndOfWord){
            root->isEndOfWord = 0;
        }
        if (isEmpty(root)){
            free(root);
            root = NULL;
        }
        return root;
    }
    int index = key[depth] - 'a';

    root->children[index] = delete(root->children[index], key, depth + 1);
    if (isEmpty(root)){
        free(root);
        root = NULL;
    }
    return root;
}

void printWords(TrieNode *root, char str[], int level, bool isLastWord){
    if (root == NULL) return;

    if (root->isEndOfWord){
        str[level] = '\0';
        printf("%s ", str);
    }
    
    int printed = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i]) {
            if (printed == 0 && root->isEndOfWord && !isLastWord) {
                printf(" -> ");
                printed = 1;
            }
            str[level] = i + 'a';
            printWords(root->children[i], str, level + 1, i == ALPHABET_SIZE - 1);
        }
    }
    if (root->isEndOfWord && printed == 1) {
        printf("\n");
    }
}

void printPrefix(TrieNode *root, char str[], int level){
    if (root == NULL) return;

    if (root->isEndOfWord){
        str[level] = '\0';
        printf("%s\n", str);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (root->children[i]){
            str[level] = i + 'a';
            printPrefix(root->children[i], str, level + 1);
        }
    }
}

void printMenu(void) 
{
    printf("1. Insert word\n");
    printf("2. Seach word\n");
    printf("3. Delete word\n");
    printf("4. Print all words\n");
    printf("5. View prefix\n");
    printf("6. Exit\n");
    printf("\n");
}

int main(void) {
    TrieNode *root = createNode();
    char str[100];
    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter word to insert: ");
                scanf("%s", str);
                insert(root, str);
                break;
            case 2:
                printf("Enter word to search: ");
                scanf("%s", str);
                printf(search(root, str) ? "Word found.\n" : "Word not found.\n");
                break;
            case 3:
                printf("Enter word to delete: ");
                scanf("%s", str);
                delete(root, str, 0);
                if (search(root, str))
                    printf("Word not deleted.\n");
                else
                    printf("Word deleted.\n");
                break;
            case 4:
                printf("Words in Trie are: ");
                printWords(root, str, 0, false);
                printf("\n");
                break;
            case 5:
                printf("Enter prefix: ");
                scanf("%s", str);
                printf("Words with prefix %s are:\n", str);
                printPrefix(root, str, 0);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);
    return 0;
}