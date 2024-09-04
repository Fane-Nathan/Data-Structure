#include <cstdio>
#include <cstdlib>


typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct
{
    node *head;
    node *tail;
    int size;
} Queue;

Queue *createQueue(void);
int size(Queue *queue);
bool isEmpty(Queue *queue);
int peek(Queue *queue, bool *status);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue, bool *status);
void destroyQueue(Queue *queue);

int main(void)
{
    Queue *queue = createQueue();

    if(isEmpty(queue)) printf("Queue is empty.\n");

    enqueue(queue, 2);

    if(!isEmpty(queue)) printf("Queue is not empty.\n");

    enqueue(queue, 4);
    enqueue(queue, 6);

    printf("Queue size: %d\n", size(queue));

    bool status;
    int value = 0;

    value = peek(queue, &status);
    if (status) printf("Peek first value: %d\n", value);

    value = dequeue(queue, &status);
    if(status) printf("Dequeue first value: %d\n", value);
    
    // To see the next value
    value = peek(queue, &status);
    if (status) printf("Peek first value: %d\n", value);

    value = dequeue(queue, &status);
    if(status) printf("Dequeue first value: %d\n", value);

    value = peek(queue, &status);
    if (status) printf("Peek first value: %d\n", value);

    value = dequeue(queue, &status);
    if(status) printf("Dequeue first value: %d\n", value);

    // To see if false
    value = peek(queue, &status);
    if (!status) printf("Peek has not value.\n");

    value = dequeue(queue, &status);
    if(!status) printf("Dequeue is unsuccesful.\n");

    destroyQueue(queue);

    return 0;
}

Queue *createQueue(void)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;

    return queue;
}

int size(Queue *queue)
{
    return queue->size;
}

bool isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

int peek(Queue *queue, bool *status)
{
    if (isEmpty(queue))
    {
        *status = false;
        return -1;
    }

    *status = true;
    return queue->head->value;
}

void enqueue(Queue *queue, int value)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = NULL;

    if (isEmpty(queue)){
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

int dequeue(Queue *queue, bool *status)
{
    if(isEmpty(queue)){
        *status = false;
        return -1;
    }

    *status = true;

    int value = queue->head->value;

    node *oldHead = queue->head;
    if (queue->size == 1){
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    free(oldHead);

    queue->size--;

    return value;
}

void destroyQueue(Queue *queue)
{
    node *currentNode = queue->head;

    while (currentNode != NULL)
    {
        node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }

    free(queue);
}