#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void randomChar(){
    char str[10];
    for (int i = 0; i < 10; i++){
        str[i] = 'a' + rand() % 26;
    }
    for (int i = 0; i < 10; i++){
        printf("%c", str[i]);
    }
}

void randomInt() {
    int arr[7];
    for (int i = 0; i < 7; i++){
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < 7; i++){
        printf("%d", arr[i]);
        if (i != 6){
            printf(" ");
        }
    }
}

typedef enum {STRING, INT} data_type;

typedef struct Node {
    data_type type;
    union {
        char brand[50];
        char model[20];
        char series[20];
        int year;
        int price;
        int dateOfPurchase;
    } data;

    struct Node *next;
    struct Node *prev;
} Node;

Node *createNode(data_type type, char *word, int number, Node **head, Node **tail){
    Node *createNode = (Node *)malloc(sizeof(Node));
    if (createNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    if (*head == NULL){
        *head = createNode;
        *tail = createNode;
    } else {
        (*tail)->next = createNode;
        createNode->prev = *tail;
        *tail = createNode;
    }
    createNode->type = type;
    if (type == STRING) {
        strcpy_s(createNode->data.word, word);
    } else {
        createNode->data.number = number;
    }
    createNode->next = NULL;
    return createNode;
}

void insertData(Node **head, Node **tail, data_type type, char *word, int number){
    Node *insertNode = createNode(type, word, number, head, tail);
    if (*head == NULL){
        *head = insertNode;
        *tail = insertNode;
    } else {
        (*tail)->next = insertNode;
        insertNode->prev = *tail;
        *tail = insertNode;
    }
}

void deleteData(Node **head, Node **tail, data_type type, char *word, int number){
    if (*head == NULL){
        printf("List is empty\n");
        return;
    }

    Node *temp = *head;
    while (temp != NULL){
        if ((temp->type == type) && ((type == STRING && strcmp(temp->data.word, word) == 0) || (type == INT && temp->data.number == number))){
            // Node to delete is at the head of the node
            if (temp == *head){
                *head = (*head)->next;
                if (*head != NULL) {
                    (*head)->prev = NULL;
                }
            } else if (temp == *tail) {
                *tail = (*tail)->prev;
                if (*tail != NULL){
                    (*tail)->next = NULL;
                }
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Data deleted!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Data not found/availeble!\n");
}

void display(Node *head, Node *tail){
    Node *temp = head;
    if (temp == NULL){
        printf("List is empty\n");
        return;
    }

    int count = 1;
    while (temp != NULL){
        if (temp->type == STRING){
            printf("%d. %s\n", count++, temp->data.word);
        } else {
            printf("%d. %d\n", count++, temp->data.number);
        }
        temp = temp->next;
    }
}

void insertOption(Node **head, Node **tail){
    char brand[50];
    char model[20];
    char series[20];
    int year;
    int price;
    int dateOfPurchase;
    int price;
    
    printf("Laptop brand: ");
    scanf("%s", brand);
    printf("Laptop model: ");
    scanf("%s", model);
    printf("Laptop series: ");
    scanf("%s", series);
    printf("When did you buy (Date & Year): ");
    fgets(dateOfPurchase, 20, stdin);
    clearBuffer();
    fgets(year, 20, stdin);
    clearBuffer();
    printf("Price: ");
    scanf("%d", &price);

    
}

void switchCase(int userChoice){
    switch (userChoice){
            case 1:
                char word[15];
                break;
            case 2:
                int number;
                printf("Enter an integer: ");
                scanf("%d", &number);
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                printf("Invalid choice\n");
        }
}

int main(){
    Node *head = NULL;
    Node *tail = NULL;
    clearScreen();
    srand(time(NULL));
    int userChoice;

    printf("  _                    _                  _____          _           _       _       _   \n");
    printf(" | |                  | |                |  __ \\        | |         | |     (_)     | |  \n");
    printf(" | |      __ _  _ __  | |_  ___   _ __   | |  | |  __ _ | |_  __ _  | |      _  ___ | |_ \n");
    printf(" | |     / _` || '_ \\ | __|/ _ \\ | '_ \\  | |  | | / _` || __|/ _` | | |     | |/ __|| __|\n");
    printf(" | |____| (_| || |_) || |_| (_) || |_) | | |__| || (_| || |_| (_| | | |____ | |\\__ \\| |_ \n");
    printf(" |______|\\__,_|| .__/  \\__|\\___/ | .__/  |_____/  \\__,_| \\__|\\__,_| |______||_||___/ \\__|\n");
    printf("               | |               | |                                                      \n");
    printf("               |_|               |_|                                                      \n");

    do {
        printf("\n");
        printf("                        ************************************\n");
        printf("                        *                                  *\n");
        printf("                        *    1. Create a template          *\n");
        printf("                        *    2. Insert data                *\n");
        printf("                        *    3. Print the list             *\n");
        printf("                        *    4. Exit                       *\n");
        printf("                        *                                  *\n");
        printf("                        ************************************\n");
        printf("                        Enter your choice: ");
        scanf("%d", &userChoice);
        switchCase(userChoice);
        
    } while (userChoice != 4);
    
    randomChar();
    printf("\n");
    randomInt();
    return 0;
}
