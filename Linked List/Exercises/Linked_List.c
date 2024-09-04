#include <cstdio>
#include <cstdlib>

typedef struct {
  void *next;
  int data;
} Node;

Node *head = NULL;

// Add a node to the list
Node *addNode(int data) {
  Node *new = (Node *)malloc(sizeof(Node));
  if (new == NULL) {
    return NULL;
  }
  new->data = data;
  new->next = head;
  head = new;
}

// remove a node form the list
int removeNode(int data) {
  Node *current = head;
  Node *prev = NULL;
  while (current != NULL) {
    if (current->data == data) {
      // if the current is = head
      if (current == head) {
        head = current->next;
      } else {
        prev->next = current->next;
      }
      return 1;
    }
    prev = current;
    current = current->next;
  }
  return 0;
}

// insert a mode into a position in the list
Node *insertNode(int data, int position) {
  Node *current = head;
  while (current != NULL && position > 0) {
    position--;
  }

  if (position != 0) {
    printf("The list is not long enough to insert at the given position\n");
    return NULL;
  }

  Node *new = malloc(sizeof(Node));
  if (new == NULL)
    return NULL;
  new->data = data;
  new->next = current->next;
  current->next = new;

  return new;
}

// print operation
void printList() {
  Node *current = head;
  while (current != NULL) {
    printf("%d", current->data);
    if (current->next != NULL) {
      printf(" -> ");
    } else {
      printf("\n");
    }
    current = current->next;
  }
}

void printMenu() {
  printf("\nYou have the following options:\n");
  printf("1. Add a node to the list\n");
  printf("2. Remove a node from the list\n");
  printf("3. Insert a node into a position in the list\n");
  printf("4. Print the list.\n");
  printf("5. Quit.\n");
}

int main(void) {
  int option = 1;
  int answer = 0;
  int answer2 = 0;
  while (option != 5) {
    printMenu();
    int num_recevied = scanf("%d", &option);
    if (num_recevied == 1 && option > 0 && option <= 5) {
      switch (option) {
      case 1:
        // add operation
        printf("Enter the number you want to add to the list: ");
        scanf("%d", &answer);
        Node *new = addNode(answer);
        break;
      case 2:
        // remove operation
        printf("Enter the number you want to remove from the list: ");
        scanf("%d", &answer);
        int success = removeNode(answer);
        if (success == 0)
          printf("The number was not found in the list\n");
        break;
      case 3:
        // insert operation
        printf("Enter the number you want to insert into the list: ");
        scanf("%d", &answer);
        printf("Enter the position you want to insert the number into: ");
        scanf("%d", &answer2);
        Node *insert = insertNode(answer, answer2);
        if (new == NULL)
          printf("The number was not inserted into the list\n");
        break;
      case 4:
        // print the list
        printList();
        break;
      case 5:
        // quit
        break;
      default:
        printf("Invalid option\n");
      }
    }
  }
  return 0;
}