
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define TABLE_SIZE 20

// Hash Table Component and Linked List Component
typedef struct Node {
    char *rubiksName;
    char *rubiksType;
    int quantity;
    char *price;
    char *rubiksID;

    struct Node *next;
    struct Node *prev;
} Node;

Node *hashTable[TABLE_SIZE];

unsigned int hashFunction(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

void insertRubiks(Node *hashTable[], char *rubiksID, Node *rubiks) {
    unsigned int index = hashFunction(rubiks->rubiksID);
    rubiks->next = hashTable[index];
    hashTable[index] = rubiks;

    Node *current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->rubiksID, rubiksID) == 0) {
            printf("Duplicate entry: %s\n", rubiks->rubiksID);
            return;
        }
        current = current->next;
    }

    // If no duplicate is found, insert the rubiks into the hash table
    rubiks->next = hashTable[index];
    hashTable[index] = rubiks;
}

void clearBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Rubiks Component
char *randomIDgen(Node **head) {
    srand(time(NULL));
    char *id = (char *)malloc(sizeof(char) * 7);
    if (id == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char number[] = "0123456789";
    Node *temp;

    do {
        id[0] = 'R';
        id[1] = 'B';
        id[2] = '-';

        for (int i = 3; i < 6; i++) {
            id[i] = number[rand() % 10];
        }

        id[6] = '\0';

        temp = *head;
        while (temp != NULL) {
            if (strcmp(temp->rubiksID, id) == 0) {
                break;
            }
            temp = temp->next;
        }
    } while (temp != NULL);

    return id;
}

char *name() {
    char *name = NULL;
    char tempChar;
    int len = 0;

    printf("Please input rubik's name [No limits!] (ENTER HOW LONG YOU WANT THIS IS JUST A TEST FOR MY PROGRAM): ");

    while ((tempChar = getchar()) != '\n' && tempChar != EOF) {
        name = realloc(name, len + 2);
        name[len] = tempChar;
        len++;
    }

    if (name != NULL) {
        name[len] = '\0';
    }

    free(name);
    return name;
}

char *getInput(char *message, int size) {
    char *input = (char *)malloc(sizeof(char) * size);
    printf("%s", message);
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';
    return input;
}

int validatePrice(char *price, int min, int max) {
    if (atoi(price) < min || atoi(price) > max) {
        printf("\nInvalid price. Price must be between Rp. %d and Rp. %d\n\n", min, max);
        return 0;
    }
    return price != NULL && atoi(price) >= min && atoi(price) <= max;
}

int quantity() {
    int quantity;
    do {
        printf("Please input rubik's quantity [1 - 50]: ");
        scanf("%d", &quantity);
        clearBufferInput();

        if (quantity < 1 || quantity > 50) {
            printf("\nInvalid quantity. Quantity must be between 1 and 50\n\n");
        }

    } while (quantity < 1 || quantity > 50);
    return quantity;
}

char *magnetic() {
    char *price;
    do {
        price = getInput("Please input Rubik price [Rp. 200,000 - Rp. 300,000]: ", 20);
        if (!validatePrice(price, 200000, 300000)) {
            free(price);
            price = NULL;
        }
    } while (price == NULL);
    return price;
}

char *nonMagnetic() {
    char *price;
    do {
        price = getInput("Please input Rubik price [Rp. 50,000 - Rp. 150,000]: ", 20);
        if (!validatePrice(price, 50000, 150000)) {
            free(price);
            price = NULL;
        }
    } while (price == NULL);
    return price;
}

bool isInvalidType(char *type, char *magneticType, char *nonMagneticType);
char *processType(char *type, char *magneticType, char *nonMagneticType);

char *getRubiksType() {
    char *magneticType = "Magnetic";
    char *nonMagneticType = "Non-Magnetic";
    char *type = NULL;

    do {
        type = getInput("Please input rubik's type [Magnetic / Non-Magnetic] [Case sensitive]: ", 20);

        if (isInvalidType(type, magneticType, nonMagneticType)) {
            printf("\nInvalid type. Type must be either Magnetic or Non-Magnetic\n\n");
            continue;
        }

    } while (type == NULL || isInvalidType(type, magneticType, nonMagneticType));

    return type;
}

bool isInvalidType(char *type, char *magneticType, char *nonMagneticType) {
    return strcmp(type, magneticType) != 0 && strcmp(type, nonMagneticType) != 0;
}

char *processType(char *type, char *magneticType, char *nonMagneticType) {
    if (strcmp(type, magneticType) == 0) {
        return magnetic();
    } else {
        return nonMagnetic();
    }
}

// Linked List Component to add rubiks data
Node *addRubiks(Node **head, Node **tail, Node *hashTable[]) {
    Node *addRubik = (Node *)malloc(sizeof(Node));

    addRubik->rubiksName = name();
    addRubik->rubiksType = getRubiksType();
    addRubik->quantity = quantity();
    addRubik->price = processType(addRubik->rubiksType, "Magnetic", "Non-Magnetic");
    addRubik->rubiksID = randomIDgen(head);
    addRubik->next = NULL;

    if (*head == NULL) {
        *head = addRubik;
        *tail = addRubik;
    } else {
        (*tail)->next = addRubik;
        addRubik->prev = *tail;
        *tail = addRubik;
    }

    insertRubiks(hashTable, addRubik->rubiksID, addRubik);

    return addRubik;
}

// Delete function
Node *deleteRubiks(Node *hashTable[], char *rubiksId) {
    unsigned int index = hashFunction(rubiksId);
    Node *temp = hashTable[index];
    Node *prev = NULL;

    // search for the key in the hashTable
    while (temp != NULL && strcmp(temp->rubiksID, rubiksId) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If the key was not found
    if (temp == NULL) {
        printf("No Rubik's Cube found with ID: %s\n", rubiksId);
        return NULL;
    }

    // If the key was found
    if (prev == NULL) {
        // The node to be deleted is the first node
        hashTable[index] = temp->next;
    } else {
        // The node to be deleted is the middle or last node
        prev->next = temp->next;
    }

    // Update the next and prev pointers to remove the node from the linked list
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("Rubik's Cube with ID: %s has been deleted\n", rubiksId);
    Node *deletedNode = temp;
    free(temp);
    return deletedNode;
}

// Display function using hash table
char *formatPrice(char *price) {
    int length = strlen(price);
    int newLength = length + length / 3 + (length % 3 == 0 ? -1 : 0) + 1;
    char *formattedPrice = (char *)malloc(sizeof(char) * newLength);
    int j = newLength - 2;
    for (int i = length - 1, k = 0; i >= 0; i--, k++) {
        if (k != 0 && k % 3 == 0) {
            formattedPrice[j--] = '.';
        }
        formattedPrice[j--] = price[i];
    }
    formattedPrice[newLength - 1] = '\0';
    return formattedPrice;
}

void viewRubiks(Node *hashTable[], int size) {
    for (int i = 0; i < size; i++) {
        Node *temp = hashTable[i];
        if (temp != NULL) {
            printf("\n---------------------\n");
            printf("Slot %d:\n", i + 1);
            printf("---------------------\n");
        }
        while (temp != NULL) {
            printf("\nRubik's Cube Details:\n");
            printf("---------------------\n");
            printf("ID: %s\n", temp->rubiksID);
            printf("Name: %s\n", temp->rubiksName);
            printf("Type: %s\n", temp->rubiksType);
            printf("Quantity: %d\n", temp->quantity);
            char *formattedPrice = formatPrice(temp->price);
            printf("Price: Rp. %s\n", formattedPrice);
            printf("---------------------\n");
            temp = temp->next;
        }
    }
}

void checkSuccess(Node *addRubiks) {
    if (addRubiks != NULL) {
        printf("Rubik's data has been added successfully\n");
        printf("========================================\n");
        printf("Rubik's ID: %s\n", addRubiks->rubiksID);
        printf("\nPress enter to continue...");
        clearBufferInput();
    } else {
        printf("Failed to add rubik's data\n");
    }
}

bool isHashEmpty(Node *hashTable[], int size) {
    for (int i = 0; i < size; i++) {
        if (hashTable[i] != NULL) {
            return false;
        }
    }
    return true;
}

void switchCase(int userChoice, Node **head, Node **tail, Node *hashTable[], int size) {
    switch (userChoice) {
        case 1: {
            Node *newNode = addRubiks(head, tail, hashTable);
            checkSuccess(newNode);
            break;
        }
        case 2:
            viewRubiks(hashTable, size);
            break;
        case 3: {
            if (isHashEmpty(hashTable, size)) {
                printf("No rubik's data found\n");
                printf("\nPress enter to continue...");
                clearBufferInput();
                break;
            }
            Node *deletedRubiks = deleteRubiks(hashTable, getInput("Please input rubik's ID to delete: ", 20));
            if (deletedRubiks != NULL) {
                printf("\nPress enter to continue...");
                clearBufferInput();
            }
            break;
        }
        case 4:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

int main(void) {
    int userChoice;
    Node *head = NULL;
    Node *tail = NULL;

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    do {
        printf("\n GR Rubiks Cube Store\n");
        printf("==========================\n");
        printf("|  1. Add a new rubiks   |\n");
        printf("|  2. View rubiks        |\n");
        printf("|  3. Delete rubiks      |\n");
        printf("|  4. Exit               |\n");
        printf("==========================\n");
        printf("Option: ");
        scanf("%d", &userChoice);
        clearBufferInput();

        switchCase(userChoice, &head, &tail, hashTable, TABLE_SIZE);

    } while (userChoice != 4);

    return 0;
}