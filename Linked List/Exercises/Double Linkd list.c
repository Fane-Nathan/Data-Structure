#include <cstdio>
#include <cstdlib>
#include <cstring>


typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
} Node;

void insert(struct node** head, struct node** tail, int data){

}

void delete(){

}

void search(){

}

void display(){
    printf("1. Display all data\n");
    prtinf("2. Insert data\n");
    printf("3. Delete data\n");
    printf("4. Search data\n");
    printf("5. Exit\n");
}

int main(void){
    struct node* head = NULL;
    struct node* tail = NULL;

    display();
    int choice;
    int option = 0;
    int option2 = 0;
    scanf("%d", &choice);
    while(choice != 5){
        switch (choice) {
            case 1:
                printf("Display all data\n");
                break;
            case 2:
                printf("Insert data\n");
                printf("1. Insert at the beginning\n");
                printf("2. Insert at the end\n");
                printf("3. Insert at a specific position\n");
                scanf("%d", &option);
                if (option == 1){
                    printf("Enter the data to be inserted: ");
                    int data;
                    scanf("%d", &data);
                    insert(&head, &tail, data);
                }
                else if (option == 2){
                    printf("Enter the data to be inserted: ");
                    int data;
                    scanf("%d", &data);
                    insert(&head, &tail, data);
                }
                else if (option == 3){
                    printf("Enter the data to be inserted: ");
                    int data;
                    scanf("%d", &data);
                    printf("Enter the position: ");
                    int pos;
                    scanf("%d", &pos);
                    insert(&head, &tail, data);
                }
                else{
                    printf("Invalid option\n");
                }
                break;
            case 3:
                printf("Delete data\n");
                printf("1. Delete from the beginning\n");
                printf("2. Delete from the end\n");
                printf("3. Delete from a specific position\n");
                scanf("%d", &option2);
                if (option2 == 1){
                    delete();
                }
                else if (option2 == 2){
                    delete();
                }
                else if (option2 == 3){
                    delete();
                }
                else{
                    printf("Invalid option\n");
                }
                break;
            case 4:
                printf("Search data\n");
                search();
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }

}