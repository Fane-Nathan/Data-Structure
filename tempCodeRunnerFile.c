#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

typedef struct Node {
    char *studentID;
    char *name;
    int age;
    char *address;

    struct Node *next;
    struct Node *prev;
} Node;

void clearBufferInput() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void MemoryAllocationFailed(Node* node) {
    if (stdin == NULL){
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

void userInput(char string[], int size) {
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        string[i++] = ch;
        if (i == size) {
            size *= 2;
            string = (char *)realloc(string, sizeof(char) * size);
            MemoryAllocationFailed(char *string);
        }
    }
    string[i] = '\0';
    clearBufferInput();
    return;
}

void ifNodeIsNullDisplay(Node **head, Node **tail) {
    if (*head == NULL) {
        printf("No data available\n");
        return;
    }
}

char *studentID() {
    char *studentID = (char *)malloc(sizeof(char) * 11);
    MemoryAllocationFailed(studentID);

    printf("Enter student ID [10 characters]: ");
    fgets(studentID, 11, stdin);
    studentID[strcspn(studentID, "\n")] = '\0';

    if (strlen(studentID) != 10) {
        printf("Student ID must be 10 characters long\n");
        free(studentID);
        return NULL;
    }

    return studentID;
}

char *name() {
    int size = 10;
    char *name = (char *)malloc(sizeof(char) * size);
    MemoryAllocationFailed(name);

    printf("Enter student's name: ");
    userInput(name, size);
    return name;
}

int age(){
    int age;
    printf("Enter student's age: ");
    scanf("%d", &age);
    clearBufferInput();
    return age;
}

char *address() {
    int size = 10;
    char *address = (char *)malloc(sizeof(char) * size);

    printf("Enter student's address: ");
    userInput(address, size);
    return address;
}

Node *createData(char studentID[], char name[], int age, char address[]) {
    Node *newData = (Node *)malloc(sizeof(Node));
    MemoryAllocationFailed(*newData);

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
    MemoryAllocationFailed(newStudent);
    
    newStudent->studentID = studentID();
    MemoryAllocationFailed(newStudent->studentID);
    newStudent->name = name();
    MemoryAllocationFailed(newStudent->name);
    newStudent->age = age();
    newStudent->address = address();
    MemoryAllocationFailed(newStudent->address);

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
    ifNodeIsNullDisplay(&head, &tail);
    Node *current = head;
    printf("%-15s | %-20s | %-5s | %-20s\n", "Student ID", "Name", "Age", "Address");
    while (current != NULL) {
        printf("%-15s | %-20s | %-5d | %-20s\n", current->studentID, current->name, current->age, current->address);
        current = current->next;
    }
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

int main(void){
    int userOpt;
    Node *head = NULL;
    Node *tail = NULL;

    do {
        dataDisplay(head, tail);
        printf("=== Student Management System ===\n");
        printf("1. Add student\n");
        printf("2. Search student\n");
        printf("3. Update student data\n");
        printf("4. Delete student data\n");
        printf("5. Exit\n");
        printf("=================================\n");
        printf("Option: ");
        scanf("%d", &userOpt);
        clearBufferInput();

        switchCase(&head, &tail, userOpt);
    } while (userOpt != 5);
    return 0;
}