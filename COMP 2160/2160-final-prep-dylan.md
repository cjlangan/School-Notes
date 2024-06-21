## Practice Questions

Write a queue that takes an array of numbers from a .txt file as input.
Write a stack that takes an array of numbers from a .txt file as input.

### Question 1: Stack Implementation

**Question:**
Implement a stack data structure in C. You need to provide the following functions:
1. void initStack(Stack* stack, int capacity);
2. void push(Stack* stack, int value);
3. int pop(Stack* stack);
4. int peek(const Stack* stack);
5. int isEmpty(const Stack* stack);
6. int isFull(const Stack* stack);
7. void freeStack(Stack* stack);

**Requirements:**
- Use dynamic memory allocation for the stack.
- Include defensive programming (e.g., NULL checks, boundary checks).
- Design by contract: Pre-conditions and post-conditions should be checked using assertions.

**Answer Key:**
```c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

// Function to initialize the stack
void initStack(Stack* stack, int capacity) {

    assert(stack != NULL && capacity > 0); // Pre-condition
    stack->data = (int*)malloc(sizeof(int) * capacity);
    assert(stack->data != NULL); // Defensive check - Memory allocation

    stack->top = -1;
    stack->capacity = capacity;

    assert(stack->capacity == capacity && stack->top == -1); // Post-condition
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {

    assert(stack != NULL && stack->data != NULL && stack->top < stack->capacity - 1); // Pre-conditions

    stack->data[++stack->top] = value;

    assert(stack->data[stack->top] == value && stack->top >= 0); // Post-condition
}
  
// Function to pop an element from the stack
int pop(Stack* stack) {
    assert(stack != NULL && stack->data != NULL && stack->top >= 0); // Pre-conditions

    int value = stack->data[stack->top--];

    return value;
}

// Function to peek the top element of the stack
int peek(const Stack* stack) {

    assert(stack != NULL && stack->data != NULL && stack->top >= 0); // Pre-conditions

    return stack->data[stack->top];
}

// Function to check if the stack is empty
int isEmpty(const Stack* stack) {

    assert(stack != NULL); // Pre-condition

    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(const Stack* stack) {

    assert(stack != NULL); // Pre-condition

    return stack->top == stack->capacity - 1;

}

// Function to free the resources allocated by the stack
void freeStack(Stack* stack) {

    assert(stack != NULL); // Pre-condition

    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;

    assert(stack->data == NULL && stack->top == -1); // Post-condition
}

```
---
### Question 2: Queue Implementation

**Question:**
Implement a queue data structure in C. You need to provide the following functions:
1. void initQueue(Queue* queue, int capacity);
2. void enqueue(Queue* queue, int value);
3. int dequeue(Queue* queue);
4. int isEmpty(const Queue* queue);
5. int isFull(const Queue* queue);
6. void freeQueue(Queue* queue);
**Requirements:**
- Use dynamic memory allocation for the queue.
- Include defensive programming (e.g., NULL checks, boundary checks).
- Design by contract: Pre-conditions and post-conditions should be checked using assertions.

**Answer Key:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;
  
// Function to initialize the queue
void initQueue(Queue* queue, int capacity) {

    assert(queue != NULL && capacity > 0); // Pre-condition
    queue->data = (int*)malloc(sizeof(int) * capacity);
    assert(queue->data != NULL); // Defensive check - Memory allocation

    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;

    assert(queue->capacity == capacity && queue->size == 0); // Post-condition
}

// Function to enqueue an element
void enqueue(Queue* queue, int value) {

    assert(queue != NULL && queue->data != NULL && queue->size < queue->capacity); // Pre-conditions

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;

	assert(queue->data[queue->rear] == value && queue->size > 0); // Post-condition
}

// Function to dequeue an element
int dequeue(Queue* queue) {

    assert(queue != NULL && queue->data != NULL && queue->size > 0); // Pre-conditions

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return value;
}

// Function to check if the queue is empty
int isEmpty(const Queue* queue) {

    assert(queue != NULL); // Pre-condition
    
    return queue->size == 0;
}

// Function to check if the queue is full
int isFull(const Queue* queue) {

    assert(queue != NULL); // Pre-condition

    return queue->size == queue->capacity;
}

// Function to free the resources allocated by the queue
void freeQueue(Queue* queue) {

    assert(queue != NULL); // Pre-condition

    free(queue->data);
    queue->data = NULL;
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = 0;
    queue->size = 0;

    assert(queue->data == NULL && queue->size == 0); // Post-condition
}
```
---
### Question 3: Dynamic Array Implementation
**Question:**
Implement a dynamic array data structure in C. You need to provide the following functions:
1. `void initArray(DynamicArray* array, int initialCapacity);`
2. `void insertArray(DynamicArray* array, int element);`
3. `int getElement(DynamicArray* array, int index);`
4. `int sizeArray(const DynamicArray* array);`
5. `void freeArray(DynamicArray* array);`

**Requirements:**
- Use dynamic memory allocation for the array.
- Include defensive programming (e.g., NULL checks, boundary checks).
- Design by contract: Pre-conditions and post-conditions should be checked using assertions.
  
**Answer Key:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

// Function to initialize the dynamic array
void initArray(DynamicArray* array, int initialCapacity) {

    assert(array != NULL && initialCapacity > 0); // Pre-condition
    array->data = (int*)malloc(sizeof(int) * initialCapacity);
    assert(array->data != NULL); // Defensive check - Memory allocation

    array->size = 0;
    array->capacity = initialCapacity;

    assert(array->capacity == initialCapacity && array->size == 0); // Post-condition
}

// Function to insert an element into the dynamic array
void insertArray(DynamicArray* array, int element) {

    assert(array != NULL && array->data != NULL); // Pre-conditions

    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = (int*)realloc(array->data, sizeof(int) * array->capacity);
        assert(array->data != NULL); // Defensive check - Memory reallocation
    }
  
    array->data[array->size++] = element;

    assert(array->data[array->size - 1] == element && array->size > 0); // Post-condition
}

// Function to get an element by index
int getElement(DynamicArray* array, int index) {

	memcpy(data, array->data[index], sizeof(DynamicArray));

	assert(index >= 0 && index< array->size) // defensive check 

	return array->data[index];

}

// Function to return the size of the dynamic array
int sizeArray(const DynamicArray* array) {

    assert(array != NULL); // Pre-condition

    return array->size;
}

// Function to free the resources allocated by the dynamic array
void freeArray(DynamicArray* array) {

    assert(array != NULL); // Pre-condition

    free(array->data);

    array->data = NULL;
    array->size = 0;
    array->capacity = 0;

    assert(array->data == NULL && array->size == 0); // Post-condition
}
```
---
### Question 4: Linked List Implementation

**Question:**
Implement a singly linked list in C, providing the following functions:
1. void initList(LinkedList* list);
2. void insertNode(LinkedList* list, int value);
3. int deleteNode(LinkedList* list, int value);
4. int searchNode(const LinkedList* list, int value);
5. void freeList(LinkedList* list);

**Requirements:**
- Use dynamic memory allocation for nodes.
- Include defensive programming (e.g., NULL checks, boundary checks).
- Design by contract: Pre-conditions and post-conditions should be checked using assertions.

**Answer Key:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

// Function to initialize the linked list
void initList(LinkedList* list) {

    assert(list != NULL); // Pre-condition

    list->head = NULL;

    assert(list->head == NULL); // Post-condition
}

// Function to insert a node into the linked list
void insertNode(LinkedList* list, int value) {

    assert(list != NULL); // Pre-condition

    Node* newNode = (Node*)malloc(sizeof(Node));

    assert(newNode != NULL); // Defensive check - Memory allocation

    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;

    assert(list->head == newNode && list->head->data == value); // Post-condition
}

// Function to delete a node by value from the linked list
int deleteNode(LinkedList* list, int value) {

    assert(list != NULL); // Pre-condition

    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return -1; // Value not found
    }
  
    if (prev == NULL) {

        list->head = temp->next;

    } else {

        prev->next = temp->next;

    }

    int deletedValue = temp->data;

    free(temp);

    return deletedValue;
}

// Function to search for a node by value in the linked list
int searchNode(const LinkedList* list, int value) {

    assert(list != NULL); // Pre-condition

    Node* current = list->head;

    while (current != NULL) {
        if (current->data == value) {
            return 1; // Value found
        }
        current = current->next;
    }

    return 0; // Value not found
}

// Function to free the resources allocated by the linked list
void freeList(LinkedList* list) {

    assert(list != NULL); // Pre-condition

    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;

    assert(list->head == NULL); // Post-condition
}
```
