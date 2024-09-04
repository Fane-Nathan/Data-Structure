#include <cstdio>
#include <cstdlib>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *head = NULL;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void delete(int data) {
  Node *temp = head;
  if (temp == NULL) {
    printf("List is empty\n");
    return;
  }

  // If the head itself is the node to be deleted
  // checking if the data field of the node called temp pointing to is equal to
  // the value of data.
  if (temp->data == data) {
    head = temp->next;
    free(temp);
    return;
  }

  // If the node is not the head
  while (temp->next != NULL) {
    // to read the line below, read from right to left
    // if the data field of the node that is being pointed to by the next field
    // of the node called temp is equal to the value of data
    if (temp->next->data == data) {
      Node *temp2 = temp->next;
      temp->next = temp2->next;
      free(temp2);
      return;
    }
    temp = temp->next;
  }
  printf("Data not found/cannot be deleted\n");
}

void search(int data) {
  Node *search = head;
  while (search != NULL) {
    if (search->data == data) {
      printf("Data found\n");
      return;
    } else {
      search = search->next;
    }
  }
  printf("Data not found\n");
}

void display() {
  Node *display = head;
  while (display != NULL) {
    printf("%d", display->data);
    if (display->next != NULL) {
      printf(" -> ");
    }
    display = display->next;
  }
  printf("\n");
}

void insert(int data, int position) {
  Node *newNode = createNode(data);
  if (newNode == NULL) {
    return;
  }

  if (position == 1) {
    newNode->next = head;
    head = newNode;
    return;
  } else {
    Node *temp = head;
    for (int i = 0; i < position - 2; i++) {
      if (temp == NULL || temp->next == NULL) {
        printf("Position not found\n");
        return;
      }
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }
}

int main(void) {
  int userChoice;
  do {
    printf("1. Create a linked list\n");
    printf("2. Insert\n");
    printf("3. Delete\n");
    printf("4. Search\n");
    printf("5. Display\n");
    printf("6. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &userChoice);
    switch (userChoice) {
    case 1:
      printf("Creating....\n");
      int data;
      printf("Enter how many number do you want to create: ");
      scanf("%d", &data);
      printf("Do you want to be random generated or manually inputted?\n");
      printf("1. Random\n");
      printf("2. Manual\n");
      printf("3. Exit\n");

      int choice;
      scanf("%d", &choice);
      switch (choice) {
      case 1:
        for (int i = 0; i < data; i++) {
          int random = rand() % 100;
          insert(random, i + 1);
        }
        printf("Number generated\n\n");
        break;
      case 2:
        for (int i = 0; i < data; i++) {
          int input;
          printf("Enter data: ");
          scanf("%d", &input);
          insert(input, i + 1);
        }
        break;
      case 3:
        printf("Exiting....\n");
        break;
      default:
        break;
      }
      break;
    case 2:
      int data2, position;
      printf("Enter data: ");
      scanf("%d", &data2);
      printf("Enter position: ");
      scanf("%d", &position);
      insert(data2, position);
      break;
    case 3:
      int data3;
      printf("What data do you want to delete?\n");
      scanf("%d", &data3);
      delete (data3);
      break;
    case 4:
      int data4;
      printf("What data do you want to search?\n");
      scanf("%d", &data4);
      search(data4);
      break;
    case 5:
      display();
      break;
    default:
      break;
    }
  } while (userChoice != 6);
  return 0;
}