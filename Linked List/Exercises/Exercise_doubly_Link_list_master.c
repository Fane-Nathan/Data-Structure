#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

void clearBufferInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

typedef struct Node
{
    int sum;
    char *cake;
    char *price;
    char *cakeID;

    struct Node *next;
    struct Node *prev;
} Node;

char *randCharGen()
{
    char *cakeId = (char *)malloc(sizeof(char) * 6);

    cakeId[0] = 'C';
    cakeId[1] = 'K';

    for (int i = 2; i < 5; i++)
    {
        cakeId[i] = (rand() % 10 + '0');
    }
    cakeId[5] = '\0';

    return cakeId;
}

int sum()
{
    int sum;
    do
    {
        printf("How many cake you want to show: ");
        scanf("%d", &sum);
        clearBufferInput();
        if (sum < 0)
        {
            printf("The number of cake must be positive\n");
        }
    } while (sum < 0);

    return sum;
}

char *price()
{
    int price;
    char *priceStr = (char *)malloc(sizeof(char) * 20);

    do
    {
        printf("Enter the cake price: ");
        scanf("%d", &price);
        clearBufferInput();

        if (price >= 1000000000){
            sprintf(priceStr, "Rp. %d.%03d.%03d.%03d", price / 1000000000, (price / 1000000) % 1000, (price / 1000) % 1000, price % 1000);
        }
        else if (price >= 1000000){
            sprintf(priceStr, "Rp. %d.%03d.%03d", price / 1000000, (price / 1000) % 1000, price % 1000);
        }
        else {
            sprintf(priceStr, "Rp. %d.%03d", price / 1000, price % 1000);
        }

    } while (price < 400);

    return priceStr;
}

char *cakeName()
{
    char *name = (char *)malloc(sizeof(char) * 15);
    do
    {
        printf("Enter the cake name: ");
        fgets(name, 15, stdin);
        name[strcspn(name, "\n")] == 0;
        if (strlen(name) > 15)
        {
            printf("The name is too long\n");
            return NULL;
        }
        else if (strlen(name) < 2)
        {
            printf("The name is too short\n");
            return NULL;
        }
    } while (strlen(name) > 15 || strlen(name) < 2);

    return name;
}

Node *createCake(char *cake, char *price, char *cakeID, int sum)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->cake = strdup(cake);
    newNode->price = strdup(price);
    newNode->cakeID = strdup(cakeID);
    newNode->sum = sum;

    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

int insertCake(Node **head, Node **tail, Node *newCake)
{
    if (*head == NULL)
    {
        *head = newCake;
        *tail = newCake;
        return 1;
    }
    else
    {
        (*tail)->next = newCake;
        newCake->prev = *tail;
        *tail = newCake;
        return 1;
    }

    return 0;
}

void addCake(Node **tail, Node **head)
{
    char *cakeNameVar = cakeName();
    char *cakePrice = price();
    char *cakeID = randCharGen();
    int sumCake = sum();
    Node *newCake = createCake(cakeNameVar, cakePrice, cakeID, sumCake);
    (insertCake(head, tail, newCake) == 1) ? printf("The cake has been added\n") : printf("The cake has not been added\n");
    printf("Press enter to continue...\n");
    clearBufferInput();

    free(cakeNameVar);
    free(cakePrice);
    free(cakeID);
}

void sortCake(Node **head, Node **tail)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *current, *index;
    int tempSum;
    char *tempCake, *tempPrice, *tempCakeID;

    for (current = *head; current != NULL; current = current->next)
    {
        for (index = current->next; index != NULL; index = index->next)
        {
            if (current->sum > index->sum)
            {
                tempSum = current->sum;
                current->sum = index->sum;
                index->sum = tempSum;

                tempCake = current->cake;
                current->cake = index->cake;
                index->cake = tempCake;

                tempPrice = current->price;
                current->price = index->price;
                index->price = tempPrice;

                tempCakeID = current->cakeID;
                current->cakeID = index->cakeID;
                index->cakeID = tempCakeID;
            }
        }
    }
}

void deleteCake(Node **head, Node **tail)
{
    Node *temp = *head;
    char *cakeID = (char *)malloc(sizeof(char) * 6);
    printf("Enter the cake code want to retrieve: ");
    fgets(cakeID, 6, stdin);
    cakeID[strcspn(cakeID, "\n")] = '\0';
    if (strlen(cakeID) != 5)
    {
        printf("The cake code is not valid\n");
        return;
    }

    temp = *head;
    Node *prev = NULL;
    while (temp != NULL && strcmp(temp->cakeID, cakeID) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("The cake code is not found\n");
        return;
    }

    if (prev == NULL)
    {
        *head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = prev;
    }
    else
    {
        *tail = prev;
    }

    free(temp->cake);
    free(temp->price);
    free(temp->cakeID);
    free(temp);
    printf("The cake has been deleted\n");
}

void searchCake(Node **head, Node **tail)
{
    Node *temp = *head;
    char *cakeID = (char*)malloc(sizeof(char) * 6);
    printf("Enter the cake code want to search: ");
    fgets(cakeID, 6, stdin);
    cakeID[strcspn(cakeID, "\n")] = '\0';
    if (strlen(cakeID) != 5)
    {
        printf("The cake code is not valid\n");
        return;
    }

    if (temp != NULL)
    {
        while (temp != NULL && strcmp(temp->cakeID, cakeID) != 0)
        {
            temp = temp -> next;
        }
        if (temp == NULL)
        {
            printf("The cake code is not found\n");
        }
        else
        {
            printf("C CAKE CASHIER\n");
            printf("===============\n\n");
            printf("%-7s | %-10s| %-10s| %-10s| %-10s\n", "No.", "Cake Code", "Cake Name", "Available", "Price");
            printf("-----------------------------------------------------------------------------------\n");
            printf("%-7s| %-10s| %-10s| %-10d| %-10s\n", "1", temp->cakeID, temp->cake, temp->sum, temp->price);
            printf("-----------------------------------------------------------------------------------\n");
        }
    }
}

void mainDisplay(Node **head, Node **tail)
{
    Node *currentNode = *head;
    int counter = 1;

    printf("C CAKE CASHIER\n");
    printf("===============\n\n");
    printf("%-7s | %-10s| %-10s| %-10s| %-10s\n", "No.", "Cake Code", "Cake Name", "Available", "Price");
    printf("-----------------------------------------------------------------------------------\n");

    if (currentNode != NULL)
    {
        while (currentNode != NULL)
        {
            printf("%-7d| %-10s| %-10s| %-10d| %-10s\n", counter++, currentNode->cakeID, currentNode->cake, currentNode->sum, currentNode->price);
            printf("-----------------------------------------------------------------------------------\n");
            currentNode = currentNode->next;
        }
    }
    else
    {
        printf("                           THE CAKE IS NOT YET SHOWN\n");
        printf("-----------------------------------------------------------------------------------\n");
    }
}

void option(int userChoice, Node **head, Node **tail)
{
    switch (userChoice)
    {
    case 1:
        addCake(head, tail);
        break;
    case 2:
        mainDisplay(head, tail);
        break;
    case 3:
        sortCake(head, tail);
        break;
    case 4:
        deleteCake(head, tail);
        break;
    case 5:
        searchCake(head, tail);
        break;
    case 6:
        printf("Thank you for using this program\n");
        break;
    default:
        printf("Invalid option\n");
        break;
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;

    int userChoice;
    do
    {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        printf("\n\n\n\n\n");
        mainDisplay(&head, &tail);
        printf("\n==================== CAKE SHOP MENU ====================\n");
        printf("    1. Add a new cake to the list\n");
        printf("    2. Display all cakes in the list\n");
        printf("    3. Sort all cakes by price\n");
        printf("    4. Delete a cake from the list\n");
        printf("    5. Search for a specific cake in the list\n");
        printf("    6. Exit the program\n");
        printf("==========================================================\n");
        printf("Option: ");
        scanf("%d", &userChoice);
        clearBufferInput();
        option(userChoice, &head, &tail);

    } while (userChoice != 6);
}