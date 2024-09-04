#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearBufferInput() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

typedef struct Node {
  char name[15];
  int total;
  //	char *year[5];
  char price[100];
  char id[6];

  struct Node *next;
  struct Node *prev;
} Node;

char *randomGeneratorId() {
  srand(time(NULL));
  char *id = (char *)malloc(sizeof(char) * 6);
  if (id == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  id[0] = 'C';
  id[1] = 'K';
  id[2] = '0';

  for (int i = 3; i < 6; i++) {
    id[i] = (rand() % 10) + '0';
  }

  id[5] = '\0';

  return id;
}

char *name() {
  char *name = (char *)malloc(sizeof(char) * 15);
  if (name == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  while (true) {
    printf("Input Cake Code [5 chars] : ");
    fgets(name, 15, stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) >= 5) {
      break;
    }
    printf("Invalid input. Name must be 5 characters at least!\n");
  }
  return name;
}

// char *year(){
//	char *year = (char *)malloc(sizeof(char) * 15);
//	if (name == NULL){
//		printf("Memory allocation failed\n");
//		exit(1);
//	}
//	while (1){
//		printf("Input Cake Code [5 chars]");
//		fgets(name, 15, stdin);
//		name[strcspn(name, "\n")] == '\0';
//		if (strlen(name) >= 5){
//			break;
//		}
//		printf("Invalid input. Name must be 5 characters at least!\n");
//	}
//	return name;
// }

int total() {
  int total;
  printf("How many cake you want to put?\n");
  scanf("%d", &total);
  if (total <= 0)
    printf("Invalid input. Name must be 5 characters at least!\n");
  return total;
}

char *price() {
  char *price = (char *)malloc(sizeof(char) * 15);
  if (price == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  do {
    printf("Input Cake Price: ");
    fgets(price, 15, stdin);
    price[strcspn(price, "\n")] = '\0';
    if (strlen(price) <= 0) {
      printf(
          "Your cake price is too small, you might want to check it again.\n");
    } else if (strlen(price) >= 8) {
      printf("You set the price too expensive! You have to make it worth it");
    }
  } while (strlen(price) <= 3);
  return price;
}

Node *createCake(char name[], int total, char id[], char price[]) {
  Node *createCake = (Node *)malloc(sizeof(Node));
  if (createCake == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  strcpy(createCake->name, name);
  strcpy(createCake->price, price);
  strcpy(createCake->id, id);
  createCake->total = total;

  createCake->next = NULL;
  createCake->prev = NULL;

  return createCake;
}

int insertPrice(Node **head, Node **tail, Node *createCake) {
  if (*head == NULL) {
    *head = createCake;
    *tail = createCake;
    return 1;
  } else {
    createCake->next = *head;
    (*head)->prev = createCake;
    *head = createCake;
    return 1;
  }
  return 0;
}

void addValue(Node **tail, Node **head) {
  char *cakeName = strdup(name());
  char *cakeId = strdup(randomGeneratorId());
  char *cakePrice = strdup(price());
  int cakeTotal = total();
  Node *newNode = createCake(cakeName, cakeTotal, cakeId, cakePrice);
  (insertPrice(head, tail, newNode) != 0
       ? printf("--- Cake has been added! ---\n")
       : printf("--- Failed to add cake :( ---\n)"));
  printf("Press enter to continue...\n");
  clearBufferInput();

  free(cakeName);
  free(cakeId);
  free(cakePrice);
}

void listCake(Node **head) {
  if (*head != NULL) {
    Node *temp = *head;
    int total = 1;
    while (temp != NULL) {
      printf("%-2d | %-10s| %-10s| %-10d| %-10s\n", total++, temp->id,
             temp->name, temp->total, temp->price);
      temp = temp->next;
    }
  } else {
    printf("Not selling currently!\n");
  }
}

void mainUI(Node **head, Node **tail) {
  printf("BAKE CAKE SHOP CASHIER\n");
  printf("======================\n\n");
  printf("%-7s | %-10s| %-10s| %-10s| %-10s\n", "No.", "Cake Code", "Cake Name",
         "Available", "Price");
  printf("---------------------------------------------------------------------"
         "--------------\n");
  listCake(head);
  printf("---------------------------------------------------------------------"
         "--------------\n");
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
      printf("Cake has been shown\n");
      return;
    }
    temp = nextNode;
  }
  printf("Cake is not shown\n");
}

void sellCake(Node **head, Node **tail) {
  if (*head == NULL) {
    printf("No particular cake that you want to delete\n");
  } else {
    printf("Which cake do you want to sell? ");
    char *id = (char *)malloc(sizeof(char) * 6);
    if (id == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    fgets(id, 6, stdin);
    id[strcspn(id, "\n")] = '\0';
    removeID(id, head, tail);
    free(id);
  }
}

void switchCase(int userChoice, Node **head, Node **tail) {
  switch (userChoice) {
  case 1:
    sellCake(head, tail);
    break;
  case 2:
    addValue(head, tail);
    break;
  case 3:
    mainUI(head, tail);
    break;
  case 4:
    break;
  }
}

int main() {
  Node *head = NULL;
  Node *tail = NULL;
  int userChoice;
  do {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mainUI(&head, &tail);
    printf("Menu :\n");
    printf("1. Sell cake\n");
    printf("2. Add cake\n");
    printf("3. Update the list\n");
    printf("4. exit\n");
    printf("========================\n");
    printf("Choose: ");
    scanf("%d", &userChoice);
    clearBufferInput();

    switchCase(userChoice, &head, &tail);
  } while (userChoice != 4);
  return 0;
}
