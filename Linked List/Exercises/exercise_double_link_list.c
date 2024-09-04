#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

void clearBufferInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

typedef struct Node {
  char brand[20];
  char serial[15];
  char type[15];
  char id[9];
  int price;

  struct Node *next;
  struct Node *prev;
} Node;

char *brand() {
  char *brand = (char *)malloc(sizeof(char) * 21);
  if (brand == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  while (1) {
    printf("Please input brand [3 - 20 characters]: ");
    fgets(brand, 21, stdin);
    brand[strcspn(brand, "\n")] = '\0';
    if (strlen(brand) >= 3 || strlen(brand) <= 20) {
      break;
    }
    printf("Invalid input. Brand must be between 3 and 20 characters\n");
  }

  return brand;
}

char *serial() {
  char *serial = (char *)malloc(sizeof(char) * 16);
  if (serial == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  while (1) {
    printf("Please input serial [10 - 15 characters]: ");
    fgets(serial, 16, stdin);
    serial[strcspn(serial, "\n")] = '\0';
    if (strlen(serial) >= 10 || strlen(serial) <= 15) {
      break;
    }
    printf("Invalid input. Serial must be between 10 and 15 characters\n");
  }

  return serial;
}

char *type() {
  char *type = (char *)malloc(sizeof(char) * 16);
  if (type == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  while (1) {
    printf("Please input type [3 - 15 characters]: ");
    fgets(type, 16, stdin);
    type[strcspn(type, "\n")] = '\0';
    if (strlen(type) >= 3 || strlen(type) <= 15) {
      break;
    }
    printf("Invalid input. Type must be between 3 and 15 characters\n");
  }

  return type;
}

char *mobileIdGenerator() {
  srand(time(NULL));
  char *id = (char *)malloc(sizeof(char) * 10);
  if (id == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  id[0] = 'S';
  id[1] = 'M';
  id[2] = '-';

  for (int i = 3; i < 9; i++) {
    id[i] = (rand() % 10) + '0';
  }
  id[9] = '\0';

  return id;
}

int price() {
  int price;
  printf("Price value: ");
  scanf("%d", &price);
  clearBufferInput();
  return price;
}

Node *createNode(char M_brand[], char M_serial[], char M_type[], int M_price) {
  Node *newNode = (Node *)malloc(sizeof(Node));

  strcpy(newNode->brand, M_brand);
  strcpy(newNode->serial, M_serial);
  strcpy(newNode->type, M_type);
  strcpy(newNode->id, mobileIdGenerator());
  newNode->price = M_price;

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

void addValue(Node **tail, Node **head) {
  char *M_brand = strdup(brand());
  char *M_serial = strdup(serial());
  char *M_type = strdup(type());
  int M_price = price();
  Node *newNode = createNode(M_brand, M_serial, M_type, M_price);
  (insert(head, tail, newNode) ? printf("Mobile data has been added\n")
                               : printf("Failed to add mobile data\n"));
  printf("======================\n");
  printf("Phone ID: %s\n", newNode->id);

  printf("Press enter to continue...\n");
  clearBufferInput();

  free(M_brand);
  free(M_serial);
  free(M_type);
}

void mainDisplay(Node **head) {
  if (*head != NULL) {
    Node *temp = *head;
    while (temp != NULL) {
      printf("\n");
      printf("============================================\n");
      printf("|                                          |\n");
      printf("|    Brand             : %-15s   |\n", temp->brand);
      printf("|    Serial            : %-15s   |\n", temp->serial);
      printf("|    Type              : %-15s   |\n", temp->type);
      printf("|    Mobile ID         : %-15s   |\n", temp->id);
      printf("|    Price             : %-15d   |\n", temp->price);
      printf("|                                          |\n");
      printf("============================================\n");
      printf("\n");
      printf("--------------------------------------------\n");
      temp = temp->next;
    }
  } else {
    printf("No mobile available\n");
  }
}

void printList(Node **head) {
  if (*head == NULL) {
    printf("No mobile available\n");
  } else {
    mainDisplay(head);
  }
}

void IDtrue(Node *temp, Node **tail, Node **head) {
  if (temp->prev == NULL) {
    *head = temp->next;
    if (*head != NULL) {
      (*head)->prev = NULL;
    } else {
      *tail = NULL;
    }
  } else if (temp->next == NULL) {
    *tail = temp->prev;
    (*tail)->next = NULL;
  } else {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
  }
  free(temp);
}

void removeID(char *id, Node **head, Node **tail) {
  Node *temp = *head;
  Node *nextNode;
  while (temp != NULL) {
    nextNode = temp->next;
    if (strcmp(temp->id, id) == 0) {
      IDtrue(temp, tail, head);
      printf("Mobile has been removed\n");
      return;
    }
    temp = temp->next;
  }
  printf("Mobile not found\n");
}

void removeValue(Node **head, Node **tail) {
  if (*head == NULL) {
    printf("No mobile available\n");
  } else {
    printf("Which mobile ID do you want to remove? ");
    char *id = (char *)malloc(sizeof(char) * 10);
    if (id == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    removeID(id, head, tail);
    free(id);
  }
}

void reverseList(Node **head, Node **tail) {
  Node *temp = *head;
  Node *nextNode;
  while (temp != NULL) {
    nextNode = temp->next;
    temp->next = temp->prev;
    temp->prev = nextNode;
    temp = nextNode;
  }
  temp = *head;
  *head = *tail;
  *tail = temp;
}

void switchCase(int userChoice, Node **head, Node **tail) {
  switch (userChoice) {
  case 1:
    addValue(head, tail);
    break;
  case 2:
    removeValue(head, tail);
    break;
  case 3:
    printList(head);
    break;
  case 4:
    reverseList(head, tail);
    break;
  case 5:
    break;
  default:
    printf("Invalid choice\n");
    break;
  }
}

int main(void) {
  Node *head = NULL;
  Node *tail = NULL;
  int userChoice;
  do {
    printf("Some random menu below\n");
    printf("====================================\n");
    printf("1. Add a value to the list\n");
    printf("2. Remove a value from the list\n");
    printf("3. Print the list\n");
    printf("4. Reverse the list\n");
    printf("5. Quit\n");
    printf("====================================\n");
    printf("Enter your choice: ");
    scanf("%d", &userChoice);
    clearBufferInput();

    switchCase(userChoice, &head, &tail);

  } while (userChoice != 5);
  return 0;
}