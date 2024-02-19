#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char rubiksName[50];
    char rubiksID[7];
    char type[20];
    int quantity;
    int price;
    struct Node *next;
    struct Node *prev;
} Node;

// Clear the input buffer at the end of each input
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

char* rubiksName(){
    char *rubiksName = (char *)malloc(50 * sizeof(char));
    if (rubiksName == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    do {
        printf("Please input rubik's name [5 - 20 characters]: ");
        fgets(rubiksName, 50, stdin);
        rubiksName[strcspn(rubiksName, "\n")] = '\0';
        if (strlen(rubiksName) < 5 || strlen(rubiksName) > 20) {
            printf("\nInvalid name. Name must be between 5 and 20 characters\n\n");
        }
    } while (strlen(rubiksName) < 5 || strlen(rubiksName) > 20);
    return rubiksName;
}

char* rubiksType() {
    char *rubiksType = (char *)malloc(20 * sizeof(char));
    do {
        printf("Please input rubik's type [Magnetic / Non-Magnetic] [Case sensitive]: ");
        fgets(rubiksType, 20, stdin);
        rubiksType[strcspn(rubiksType, "\n")] = '\0';
        if (strcmp(rubiksType, "Magnetic") != 0 && strcmp(rubiksType, "Non-Magnetic")){
            printf("\nInvalid type. Type must be either Magnetic or Non-Magnetic\n\n");
        }
    } while (strcmp(rubiksType, "Magnetic") != 0 && strcmp(rubiksType, "Non-Magnetic") != 0);
    return rubiksType;
}

int rubiksQuantity(){
    int rubiksQuantity;
    do {
        printf("Please input rubik's quantity [1 - 10]: ");
        scanf("%d", &rubiksQuantity);
        if (rubiksQuantity < 1 || rubiksQuantity > 10) {
            printf("\nInvalid quantity. Quantity must be between 1 and 10\n\n");
        }
    } while (rubiksQuantity < 1 || rubiksQuantity > 10);
    return rubiksQuantity;
}

int rubiksPrice(){
    int rubiksPrice;
    do {
        printf("Please input rubik's price [200000 - 300000]: ");
        scanf("%d", &rubiksPrice);
        if (rubiksPrice < 200000 || rubiksPrice > 300000) {
            printf("\nInvalid price. Price must be between 200000 and 300000\n\n");
        }
    } while (rubiksPrice < 200000 || rubiksPrice > 300000);
    return rubiksPrice;
}

int rubiksPriceNonMagnet(){
    int rubiksPriceNonMagnet;
    do {
        printf("Please input rubik's price [50000 - 150000]: ");
        scanf("%d", &rubiksPriceNonMagnet);
        if (rubiksPriceNonMagnet < 50000 || rubiksPriceNonMagnet > 150000){
            printf("\nInvalid price. Price must be between 50000 and 150000\n\n");
        }
    } while (rubiksPriceNonMagnet < 50000 || rubiksPriceNonMagnet > 150000);
    return rubiksPriceNonMagnet;
}

char *rubiksIdGenerator(){
    char *rubiksID = (char *)malloc(6 * sizeof(char));
    if (rubiksID == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    srand(time(NULL));
    rubiksID[0] = 'R';
    rubiksID[1] = 'B';
    for (int i = 2; i < 5; i++){
        rubiksID[i] = (rand() % 10) + '0';
    }
    rubiksID[5] = '\0';
    return rubiksID;
}

Node *createNode(char *Name, char *rubiksType, char *rubiksID, int rubiksQuantity, int rubiksPrice) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    strcpy(newNode -> rubiksName, Name);
    strcpy(newNode->type, rubiksType);
    strcpy(newNode->rubiksID, rubiksID);
    newNode->quantity = rubiksQuantity;
    newNode->price = rubiksPrice;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

int insert(Node **head, Node **tail, Node *newNode) {
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
        return 1;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        return 1;
    }
    return 0;
}

void displayUI(Node *node){
    printf("\n");
    printf("============================================\n");
    printf("|                                          |\n");
    printf("|    Rubik's ID        : %-15s   |\n", node->rubiksID);
    printf("|    Rubik's Name      : %-15s   |\n", node->rubiksName);
    printf("|    Rubik's Type      : %-15s   |\n", node->type);
    printf("|    Rubik's Quantity  : %-15d   |\n", node->quantity);
    printf("|    Rubik's Price     : %-15d   |\n", node->price);
    printf("|                                          |\n");
    printf("============================================\n");
    printf("\n");
    printf("--------------------------------------------\n");
}

void mainDisplay(Node **head){
    if(*head != NULL){
        Node *temp = *head;
        while (temp != NULL){
            displayUI(temp);
            temp = temp->next;
        }
    } else {
        printf("No rubik's available\n");
    }
}

void inputData(Node **head, Node **tail){
    char* name = strdup(rubiksName());
    char* type = strdup(rubiksType());
    int quantity = rubiksQuantity();
    int price = (strcmp(type, "Magnetic") == 0) ? rubiksPrice() : rubiksPriceNonMagnet();
    char *rubiksID = strdup(rubiksIdGenerator());
    Node *newNode = createNode(name, type, rubiksID, quantity, price);
    (insert(head, tail, newNode) == 1) ? printf("Rubik's has been added\n") : printf("\nFailed to add rubik's\n");
    printf("========================\n");
    printf("Rubiks ID: %s\n", rubiksID);
    
    printf("\nPress Enter to continue...\n");
    getchar();
    clearInputBuffer();
}

void delete(Node **head, Node **tail){
    if (*head == NULL){
        printf("No rubiks available\n");
    } else {
        Node *delete = *head;
        *head = (*head)->next;
        if (*head != NULL){
            (*head)->prev = NULL;
        } else {
            *tail = NULL;
        }
        free(delete);
    }
}


void switchCase(int userChoice, Node **head, Node **tail){
    switch (userChoice){
        case 1:
            inputData(head, tail);
            break;    
        case 2:
            mainDisplay(head);
            break;
        case 3:
            // deleteRubik();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

int main(void){
    Node *head = NULL;
    Node *tail = NULL;
    int userChoice;
    
    // #ifdef _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif

    do {
        printf("\n");
        printf("============================================\n");
        printf("|                                          |\n");
        printf("|              RUBIK'S MENU                |\n");
        printf("|                                          |\n");
        printf("|    1. Add new rubik's                    |\n");
        printf("|    2. View rubik's                       |\n");
        printf("|    3. Delete rubik's                     |\n");
        printf("|    4. Exit                               |\n");
        printf("|                                          |\n");
        printf("============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        clearInputBuffer();
        
        switchCase(userChoice, &head, &tail);

    } while (userChoice != 4);

    return 0;
}