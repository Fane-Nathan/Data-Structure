#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *randomGeneratedWord(int length){
    char *word = (char *)malloc(sizeof(char) * (length + 1));
    for (int i = 0; i < length; i++){
        word[i] = 'a' + rand() % 26;
    }
    word[length] = '\0';
    return word;
}

typedef struct Node {
    char *word;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

Node *createNode(char *word) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->word = word;
    newNode->next = NULL;
    newNode -> prev = NULL;
    return newNode;
}

void insert(char *word, int position){
    Node *newNode = createNode(word);
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        if (position == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            Node *temp = head;
            for (int i = 0; i < position - 1; i++) {
                if (temp->next == NULL) {
                    break;
                }
                temp = temp->next;
            }
            newNode->next = temp->next;
            if (temp-> next != NULL) {
                temp->next->prev = newNode;
            } else {
                tail = newNode;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
}

int deleteWord(char *word){
    Node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            // If node to be deleted is head node
            if (temp == head) {
                head = temp -> next;
            }
            // change next only if node to be deleted is NOT the last node
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            // change prev only if node to be deleted is NOT the first node
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp == tail) {
                tail = temp->prev;
            }
            free(temp->word);
            free(temp);
            return 1;
        }
        temp = temp->next;
    }
    printf("The word is not in the list\n");
    return 0;
}

int deleteFromTop(){
    if (head == NULL) {
        return 0;
    } 
    Node *temp = head;
    head = head->next;
    if (head != NULL) {
        head -> prev = NULL;
    }
    if (temp == tail) {
        tail = NULL;
    }
    printf("The word '%s' has been deleted\n", temp->word);
    free(temp->word);
    free(temp);
    return 1;
}

int bulkDelete(int numberOfWordsToDelete){
    int total = 0;
    for (int i = 0; i < numberOfWordsToDelete; i++) {
        int result = deleteFromTop();
        total += result;
    }
    return total;
}

void createList(char *word)
{
    // Create a new node
    Node *newNode = createNode(word);
    // if the head is NULL, then assign a new one for the head.
    if (head == NULL) {
        head = newNode;
    // If the head is not NULL, then traverse the list to the end and add the new node.
    } else {
        Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Add the new node to the end of the list.
        temp->next = newNode;
    }
}

void printList(){
    Node *temp = head;
    int counter = 1;
    printf("\n");
    while (temp != NULL) {
        printf("%d. %s\n", counter++, temp->word);
        temp = temp->next;
    }
}

void printASCII(){
    Node *temp = head;
    int counter = 1;
    while (temp != NULL) {
        printf("%d. ", counter++);
        for (int i = 0; temp->word[i] != '\0'; i++){
            printf("%d", (int)temp->word[i]);
            if (temp->word[i + 1] != '\0'){
                printf("-");
            }
        }
        printf("\n");
        temp = temp->next;
    }
}

void search(char *word){
    Node *temp = head;
    int counter = 1;
    while (temp != NULL){
        if (strcmp (temp->word, word) == 0) {
            printf("The word '%s' is found at position %d\n", word, counter);
            return;
        } else {
            temp = temp->next;
            counter++;
        }
    }
    printf("The word '%s' is not found\n", word);
}

void searchByASCII(int ASCIIsum) {
    Node *temp = head;
    int counter = 1;
    while (temp != NULL) {
        int currentSum = 0;
        for (int i = 0; temp->word[i] != '\0'; i++) {
            currentSum += (int)temp->word[i];
        }
        if (currentSum == ASCIIsum) {
            printf("The word '%s' with ASCII sum %d is found at position %d\n", temp->word, ASCIIsum, counter);
            return;
        }
        temp = temp->next;
        counter++;
    }
    printf("The word with ASCII sum %d is not found\n", ASCIIsum);
}

int mathASCII(const char *word){
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++){
        sum += (int)word[i];
    }
    return sum;
}

int main(void){
    int userChoice;
    printf("\nThis is a double linked list program, hope you are happy with it");
    do {
        printf("\n==============================\n");
        printf(" 1. Create a list\n");
        printf(" 2. Insert a word\n");
        printf(" 3. Delete a word\n");
        printf(" 4. Print the list\n");
        printf(" 5. Search\n");
        printf(" 6. Search the ASCII values\n");
        printf(" 7. Exit\n");
        printf("==============================\n");

        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf("Do you want to create a list with random words? (y/n) ");
                char answer[4];
                scanf("%s", &answer);
                if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0 || strcmp(answer, "yes") == 0 || strcmp(answer, "YES") == 0 || strcmp(answer, "Yes") == 0) {
                    srand(time(0));
                    for (int i = 0; i < 7; i++) {
                        char *word = randomGeneratedWord(5);
                        createList(word);
                    }
                } else {
                    printf("How many words would you like to add? ");
                    int numberOfWords;
                    scanf("%d", &numberOfWords);
                    for (int i = 0; i < numberOfWords; i++) {
                        printf("Please type the word: ");
                        char word[100];
                        scanf("%s", word);
                        char *newWord = (char *)malloc(sizeof(char) * (strlen(word) + 1));
                        strcpy(newWord, word);
                        createList(newWord);
                    }
                }
                printf("Creating.....\n");
                break;
            case 2:
                printf("\nPlease type the word: ");
                char word[100];
                scanf("%s", word);
                printf("Where would you like to insert the word? ");
                int position;
                scanf("%d", &position);
                insert(word, position - 1);
                break;
            case 3:
                printf("Do you want to delete a word or multiple words? (y/n) ");
                char answer2[4];
                scanf("%s", &answer2);
                if (strcmp(answer2, "Y") == 0 || strcmp(answer2, "y") == 0 || strcmp(answer2, "yes") == 0 || strcmp(answer2, "YES") == 0 || strcmp(answer2, "Yes") == 0) {
                    printf("How many words would you like to delete? ");
                    int numberOfWordsToDelete;
                    scanf("%d", numberOfWordsToDelete);
                    bulkDelete(numberOfWordsToDelete);
                } else {
                    printf("\nWhat word would you like to delete? ");
                    char wordToDelete[100];
                    scanf("%s", wordToDelete);
                    int result = deleteWord(wordToDelete);
                    if (result == 0) {
                        printf("Please check again\n");
                    } else {
                        printf("The word '%s' has been deleted\n", wordToDelete);
                    }
                }
                break;
            case 4:
                printf("\n------------------------\n");
                printf("The list: ");
                printList();
                printf("------------------------\n");
                printf("Do you want to print the words in ASCII? (y/n) ");
                char answer3[4];
                scanf("%s", &answer3);
                if (strcmp(answer3, "Y") == 0 || strcmp(answer3, "y") == 0 || strcmp(answer3, "yes") == 0 || strcmp(answer3, "YES") == 0 || strcmp(answer3, "Yes") == 0) {
                    printASCII();
                } else {
                    printf("Alright\n");
                }
                break;
            case 5:
                printf("Word to search: ");
                char wordToSearch[100];
                scanf("%s", wordToSearch);
                search(wordToSearch);
                break;
            case 6:
                do {
                    printf("\nEnter the ASCII sum: "); // Look it is easier for me to find the ASCII sum so deal with it
                    printf("(For example, the ASCII sum of 'abc' is 294)\n");
                    printf("(Why I do this because it easier to code so deal with it)\n");
                    printf("Do you want a calculator?");
                    char answer4[4];
                    scanf("%s", &answer4);
                    if (strcmp(answer4, "Y") == 0 || strcmp(answer4, "y") == 0 || strcmp(answer4, "yes") == 0 || strcmp(answer4, "YES") == 0 || strcmp(answer4, "Yes") == 0) {
                        printf("You lazy person, here is the calculator\n");
                        printf("Enter the word: ");
                        char word[100];
                        scanf("%s", word);
                        printf("The ASCII sum of the word '%s' is %d\n", word, mathASCII(word));
                    }
                    int ASCIIsum;
                    scanf("%d", &ASCIIsum);
                    searchByASCII(ASCIIsum);
                    break;
                } while (1);
                break;
            case 7:
                printf("Alright, Thank you and goodbye!\n");
                break;
        }
    } while (userChoice != 7);

    return 0;
}