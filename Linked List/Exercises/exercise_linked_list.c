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

// Function to handle memory allocation failure for strings
void StrMemoryAllocationFailed(char *string) {
    if (string == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to handle memory allocation failure for Node structure
void NodeMemoryAllocationFailed(Node *node) {
    if (node->studentID == NULL || node->name == NULL || node->address == NULL) {
        printf("Memory allocation failed\n");
        free(node->studentID);
        free(node->name);
        free(node->address);
    }
    return;
}

// Function to handle memory allocation failure for Node structure (alternative)
void Node2MemoryAllocationFailed(Node *node) {
    if (stdin == NULL) {  // node == NULL
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Function to get user input for strings
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

// Function to display a message if the Node is null
void ifNodeIsNullDisplay(Node **head, Node **tail) {
    if (*head == NULL) {
        printf("|\033[1;31m                         NO DATA AVAILABLE                          \033[0m|\n");
        return;
    }
}

// Function to get student ID from user input
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

// Function to get student name from user input
char *name() {
    int size = 100;
    char *name = (char *)malloc(sizeof(char) * size);
    StrMemoryAllocationFailed(name);

    printf("Enter student's name: ");
    clearBufferInput();
    userInput(name, size);
    return name;
}

// Function to get student age from user input
int age() {
    int age;
    printf("Enter student's age: ");
    scanf("%d", &age);
    clearBufferInput();
    return age;
}

// Function to get student address from user input
char *address() {
    int size = 50;
    char *address = (char *)malloc(sizeof(char) * size);

    printf("Enter student's address: ");
    userInput(address, size);
    return address;
}

// Function to create a new Node with provided data
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

// Function to add a new student to the linked list
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

// Function to search for a student by student ID
// However, this function is not working properly
// It crashes the program when the user tries to search for a student ID
// and when inserting a new student data, the program crashes as well
void searchStudent(Node **head, Node **tail) {
    Node *current = *head;
    char studentID[11];
    printf("Enter student ID to search: ");
    fgets(studentID, 11, stdin);
    studentID[strcspn(studentID, "\n")] = '\0';
    clearBufferInput();

    ifNodeIsNullDisplay(head, tail);
    while(current != NULL) {
        if (strcmp(current->studentID, studentID) == 0) {
            printf("Student ID: %s\n", current->studentID);
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Address: %s\n", current->address);
            return;
        }
    }
    printf("Student ID not found\n");
}

// Function to display all student data
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

// Function to handle different user options
void switchCase(Node **head, Node **tail, int userOpt) {
    switch (userOpt) {
        case 1:
            addStudent(head, tail);
            break;
        case 2:
            searchStudent(head, tail);
            break;
        case 3:
            // updateStudent(head, tail);
            break;
        case 4:
            // deleteStudent(head, tail);
            break;
        case 5:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

// Main function
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
