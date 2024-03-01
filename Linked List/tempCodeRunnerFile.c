void viewRubiks(Node *hashTable[], int size) {
    for (int i = 1; i <= size; i++) {
        Node *temp = hashTable[i];
        if (temp != NULL) {
            printf("\n---------------------\n");
            printf("Slot %d:\n", i);
            printf("---------------------\n");
        }
        while (temp != NULL) {
            printf("\nRubik's Cube Details:\n");
            printf("---------------------\n");
            printf("ID: %s\n", temp->rubiksID);
            printf("Name: %s\n", temp->rubiksName);
            printf("Type: %s\n", temp->rubiksType);
            printf("Quantity: %d\n", temp->quantity);
            char *formattedPrice = formatPrice(temp->price);
            printf("Price: Rp. %s\n", formattedPrice);
            printf("---------------------\n");
            temp = temp->next;
        }
    }
}