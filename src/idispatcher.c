/*
Brayden Klemens
March 2019
*/

#include "idispatcher.h"


int main(){

    //variables
    char buffer[2000];
    char *token = NULL;
    Input array[2000];
    int arrayIndex = 0;

    //make lists
    List *resourceOne = NULL;
    List *resourceTwo = NULL;
    List *resourceThree = NULL;
    List *resourceFour = NULL;
    List *resourceFive = NULL;
    List *completeprocess = NULL;

    //read in the strings and dump nodes into queue
    while(fgets(buffer, 100, stdin) != NULL){

        //remove newline
        if(buffer[strlen(buffer) - 1] == '\n'){
            buffer[strlen(buffer) - 1] = 0;
        }

        if(strcmp(buffer, "") == 0){
            break;
        }

        //intit
        Input input;
        input.time = -1;
        strcpy(input.event, "");
        input.process = -1;
        input.resource = -1;

        //store inpout in stucts and fill array with input
        token = strtok(buffer, " ");
        if(token != NULL){input.time = atoi(token);}
        token = strtok(NULL, " ");
        if(token != NULL){strcpy(input.event, token);}

        if(strcmp(token, "C") == 0 || strcmp(token, "E") == 0){
            token = strtok(NULL, " ");
            if(token != NULL){input.process = atoi(token);}
            array[arrayIndex] = input;
            arrayIndex++;
        }else if(strcmp(token, "R") == 0 || strcmp(token, "I") == 0){
            token = strtok(NULL, " ");
            if(token != NULL){input.resource = atoi(token);}
            token = strtok(NULL, " ");
            if(token != NULL){input.process = atoi(token);}
            array[arrayIndex] = input;
            arrayIndex++;
        }else{
            array[arrayIndex] = input;
            arrayIndex++;
        }
    }

    for(int i = 0; i < arrayIndex; i++){

    }

    Node *idle = malloc(sizeof(Node));
    idle->process = 0;
    idle->running = 0;
    Queue *queue = createQueue(2000);

    //takes care of all cases and updates the 3 time variables
    for(int i = 0; i < arrayIndex; i++){

        if(strcmp(array[i].event, "C") == 0){

            int timePassed = 0;
            if(i == 0){
                timePassed = array[i].time;
            }else{
                timePassed = (array[i].time) - (array[i - 1].time);
            }
            updateQueue(queue, idle, timePassed);
            updateAllLists(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, timePassed);

            Node node = initNode();
            node.process = array[i].process;
            enqueue(queue, node);

        }else if(strcmp(array[i].event, "R") == 0){

            int timePassed = 0;
            if(i == 0){
                timePassed = array[i].time;
            }else{
                timePassed = (array[i].time) - (array[i - 1].time);
            }

            updateQueue(queue, idle, timePassed);
            updateAllLists(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, timePassed);

            if(array[i].process == queue->data[queue->front].process && isEmpty(queue) != 0){
                Node node = dequeue(queue);
                insertToList(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, node, array[i].resource);
            }

        }else if(strcmp(array[i].event, "I") == 0){

            int timePassed = 0;
            if(i == 0){
                timePassed = array[i].time;
            }else{
                timePassed = (array[i].time) - (array[i - 1].time);
            }
        
            updateQueue(queue, idle, timePassed);
            updateAllLists(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, timePassed);

            Node node = removeFromList(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, array[i].process, array[i].resource);
            enqueue(queue, node);

        }else if(strcmp(array[i].event, "T") == 0){

            int timePassed = 0;
            if(i == 0){
                timePassed = array[i].time;
            }else{
                timePassed = (array[i].time) - (array[i - 1].time);
            }

            updateQueue(queue, idle, timePassed);
            updateAllLists(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, timePassed);

            if(isEmpty(queue) != 0){
                Node node = dequeue(queue);
                enqueue(queue, node);
            }

        }else if(strcmp(array[i].event, "E") == 0){

            int timePassed = 0;
            if(i == 0){
                timePassed = array[i].time;
            }else{
                timePassed = (array[i].time) - (array[i - 1].time);
            }

            updateQueue(queue, idle, timePassed);
            updateAllLists(&resourceOne, &resourceTwo, &resourceThree, &resourceFour, &resourceFive, timePassed);

            //printf("array: %d queuefront: %d\n",array[i].process, queue->data[queue->front].process);
            if(array[i].process == queue->data[queue->front].process){
                Node node = dequeue(queue);
                insertNode(&completeprocess, node);
            }

        }else{
            printf("Incorrect file Input\n");
            exit(0);
        }
    }

    printLinkedList(&completeprocess, idle);

    //free memory
    freeQueue(queue);
    free(idle);
    freeList(&completeprocess);

    freeList(&resourceOne);
    freeList(&resourceTwo);
    freeList(&resourceThree);
    freeList(&resourceFour);
    freeList(&resourceFive);
    
    return 0;
}


//Time calculation Questions

//Scheduling functions **********************************************************************************************

Node removeFromList(List **list1, List **list2, List **list3, List **list4, List **list5, int process, int resource){

    List list;

    if(resource == 1){
        list = removeNode(list1, process);
    }else if(resource == 2){	
        list = removeNode(list2, process);
    }else if(resource == 3){
        list = removeNode(list3, process);
    }else if(resource == 4){
        list = removeNode(list4, process);
    }else if(resource == 5){
        list = removeNode(list5, process);
    }else{
        printf("Invalid resource!\n");
        exit(0);
    }

    return list.data;
}		

void insertToList(List **list1, List **list2, List **list3, List **list4, List **list5, Node node, int resource){
    if(resource == 1){
        insertNode(list1, node);
    }else if(resource == 2){	
        insertNode(list2, node);
    }else if(resource == 3){
        insertNode(list3, node);
    }else if(resource == 4){
        insertNode(list4, node);
    }else if(resource == 5){
        insertNode(list5, node);
    }else{
        printf("Invalid resource!\n");
        exit(0);
    }
}

void updateAllLists(List **list1, List **list2, List **list3, List **list4, List **list5, int timePassed){
    updateList(list1, timePassed);
    updateList(list2, timePassed);
    updateList(list3, timePassed);
    updateList(list4, timePassed);
    updateList(list5, timePassed);
}

void updateList(List **list, int timePassed){

    List *current;
    current = *list;

    if(*list == NULL){
        return;
    }

    while(current != NULL){
        current->data.blocked += timePassed;
        current = current->next;
    }
}

void updateQueue(Queue *queue, Node *idle, int timePassed){

    if(isEmpty(queue) == 0){
        idle->running += timePassed;
    }else{
        int front = queue->front + 1;
        queue->data[queue->front].running += timePassed;

        while(front <= queue->rear){
            queue->data[front].ready += timePassed;
            front++;
        }		
    }
}

//Queue functions *******************************************************************

//inititailizes a queue and mallocates memory for the queue
Queue *createQueue(int capacity){

    Queue *queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = queue->capacity - 1;
    queue->data = malloc(sizeof(Node) * queue->capacity);
    return queue;
}

//checks if queue is full
int isFull(Queue* queue){
    if(queue->size == queue->capacity){
        return 0;
    }
    return 1;
} 

//checks if queue is empty
int isEmpty(Queue* queue){
    if(queue->size == 0){
        return 0;
    }
    return 1;
} 

//adds an element to the rear of the queue
void enqueue(Queue *queue, Node temp){

    if(isFull(queue) == 0){return;}

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = temp;
    queue->size = queue->size + 1;
}

//returns the first front of the queue and declares a new fron of queue
Node dequeue(Queue *queue){

    Node temp = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return temp;
}

//initialiizes a node
Node initNode(){
    Node temp;
    temp.process = -1;
    temp.running = 0;
    temp.ready = 0;
    temp.blocked = 0;
    return temp;
}

//List functions *******************************************************************

/* Adds a node to the front of a list*/
void insertNode(List **head, Node toAdd) {

    /*initialize temp node*/
    List *temp = malloc(sizeof(List));
    temp->data = toAdd;
    temp->next = NULL;

    List *curr = NULL, *prev = NULL;
    curr = *head;

    while(curr != NULL && toAdd.process > curr->data.process){
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL){
        temp->next = *head;
        *head = temp;
    }else{
        prev->next = temp;
        temp->next = curr;
    }
}

/*delete a node a re link the list */
List removeNode(List **head, int process){

    /*Variables*/
    List *old, *curr;
    List def;
    def.data = initNode();
    def.next = NULL;
    curr = *head; 

    /*return default if list doesnt exist*/
    if(*head == NULL){
        return def;
    }

    /*if the first node is the node were searching for remove it*/
    if(curr->data.process == process){
        old = curr;
        curr = (*head)->next;
        *head = curr;
        List ret = *old;
        free(old);
        return ret;
    } 

    /*loop through the list at next locations until finding the node with the correct plate number */
    while (curr->next != NULL && curr->next->data.process != process){ 
        curr = curr->next;
    }

    if (curr->next != NULL){
        old = curr->next;
        curr->next = curr->next->next;
        List ret = *old;
        free(old);
        return ret;
    }else{
        return def;
    }
}

/* Prints out the data at each node of he Linked list*/
void printLinkedList(List **head, Node *idle) {

    List *current;
    current = *head;

    if(*head == NULL){
        return;
    }else{
        printf("%d %d\n", idle->process, idle->running);
        while(current != NULL){
            printf("%d %d %d %d\n", current->data.process, current->data.running, current->data.ready, current->data.blocked);
            current = current->next;
        }
    }
}

void freeQueue(Queue *queue){

    free(queue->data);
    free(queue);
}

void freeList(List **list){

    List *temp;

    if(*list == NULL){
        return;
    }else{
        while(*list != NULL){
            temp = *list;
            *list = (*list)->next;
            free(temp);
        }
    }
}


