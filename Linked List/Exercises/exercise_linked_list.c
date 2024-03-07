#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Students data management system
typedef struct Node {
    char *studentID;
    char *name;
    int age;
    char *address;

    struct Node *next;
    struct Node *prev;
} Node;

// Clear the buffer input
void clearBufferInput() {
    // fflush(stdin);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void StrMemoryAllocationFailed(char *string) {
    if (string == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void NodeMemoryAllocationFailed(Node *node) {
    if (node->studentID == NULL || node->name == NULL || node->address == NULL) {
        printf("Memory allocation failed\n");
        free(node->studentID);
        free(node->name);
        free(node->address);
    }
    return;
}

void Node2MemoryAllocationFailed(Node *node) {
    if (stdin == NULL) {  // node == NULL
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void userInput(char string[], int size) {
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        string[i++] = ch;
        if (i == size) {
            size *= 2;
            string = (char *)realloc(string, sizeof(char) * size);
            StrMemoryAllocationFailed(string);
        }
    }
    string[i] = '\0';
    return;
}

void ifNodeIsNullDisplay(Node **head, Node **tail) {
    if (*head == NULL) {
        printf("|\033[1;31m                         NO DATA AVAILABLE                          \033[0m|\n");
        return;
    }
}

char *studentID() {
    char *studentID = (char *)malloc(sizeof(char) * 11);
    StrMemoryAllocationFailed(studentID);

    do {
        printf("Enter student ID [10 characters]: ");
        fgets(studentID, 11, stdin);
        studentID[strcspn(studentID, "\n")] = '\0';

        clearBufferInput();
        
        if (strlen(studentID) != 10) {
            printf("Student ID must be 10 characters long\n");
        }
    } while (strlen(studentID) != 10);
    return studentID;
}

char *name() {
    int size = 100;
    char *name = (char *)malloc(sizeof(char) * size);
    StrMemoryAllocationFailed(name);

    printf("Enter student's name: ");
    clearBufferInput();
    userInput(name, size);
    return name;
}

int age() {
    int age;
    printf("Enter student's age: ");
    scanf("%d", &age);
    clearBufferInput();
    return age;
}

char *address() {
    int size = 50;
    char *address = (char *)malloc(sizeof(char) * size);

    printf("Enter student's address: ");
    userInput(address, size);
    return address;
}

Node *createData(char studentID[], char name[], int age, char address[]) {
    Node *newData = (Node *)malloc(sizeof(Node));
    NodeMemoryAllocationFailed(newData);

    newData->studentID = studentID;
    newData->name = name;
    newData->age = age;
    newData->address = address;

    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

void addStudent(Node **head, Node **tail) {
    Node *newStudent = (Node *)malloc(sizeof(Node));
    Node2MemoryAllocationFailed(newStudent);

    newStudent->studentID = studentID();
    StrMemoryAllocationFailed(newStudent->studentID);
    newStudent->name = name();
    StrMemoryAllocationFailed(newStudent->name);
    newStudent->age = age();
    newStudent->address = address();
    StrMemoryAllocationFailed(newStudent->address);
    printf("\n=== Student data added successfully ===\n\n");
    printf("Press enter to continue...\n");
    getchar();

    if (*head == NULL) {
        *head = newStudent;
        *tail = newStudent;
    } else {
        (*tail)->next = newStudent;
        newStudent->prev = *tail;
        *tail = newStudent;
    }
    return;
}

void dataDisplay(Node *head, Node *tail) {
    Node *current = head;
    printf("----------------------------------------------------------------------\n");
    printf("| %-15s | %-17s | %-5s | %-20s |\n", "Student ID", "Name", "Age", "Address");
    printf("----------------------------------------------------------------------\n");
    ifNodeIsNullDisplay(&head, &tail);
    while (current != NULL) {
        printf("| %-15s | %-17s | %-5d | %-20s |\n", current->studentID, current->name, current->age, current->address);
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n");
    return;
}

void switchCase(Node **head, Node **tail, int userOpt) {
    switch (userOpt) {
        case 1:
            addStudent(head, tail);
            break;
        case 2:
    }
}

int main(void) {
    int userOpt;
    Node *head = NULL;
    Node *tail = NULL;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        dataDisplay(head, tail);
        printf("\n==== Student Management System ====\n");
        printf("  1. Add student\n");
        printf("  2. Search student\n");
        printf("  3. Update student data\n");
        printf("  4. Delete student data\n");
        printf("  5. Exit\n");
        printf("===================================\n");
        printf("Option: ");
        scanf("%d", &userOpt);
        clearBufferInput();

        switchCase(&head, &tail, userOpt);
    } while (userOpt != 5);
    return 0;
}