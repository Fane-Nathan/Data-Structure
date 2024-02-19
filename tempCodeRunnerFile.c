#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push element.\n");
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop element.\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot peek element.\n");
        return -1;
    }
    return stack->data[stack->top];
}

int main() {
    push(Stack, 1);
    push(Stack, 2);
    push(Stack, 3);
    push(Stack, 4);
    Stack undoStack;
    Stack redoStack;
    initialize(&undoStack);
    initialize(&redoStack);

    int choice, value;

    while (1) {
        printf("1. Undo\n");
        printf("2. Redo\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!isEmpty(&undoStack)) {
                    value = pop(&undoStack);
                    push(&redoStack, value);
                    printf("Undo: %d\n", value);
                } else {
                    printf("Undo stack is empty.\n");
                }
                break;
            case 2:
                if (!isEmpty(&redoStack)) {
                    value = pop(&redoStack);
                    push(&undoStack, value);
                    printf("Redo: %d\n", value);
                } else {
                    printf("Redo stack is empty.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
