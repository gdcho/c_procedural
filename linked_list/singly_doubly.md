## Singly Linked List

A singly linked list is a data structure that contains a sequence of elements such that each element points to the next element in the sequence. Each element in a singly linked list is called a node.

### Structure for a Node:
```c
struct Node {
    int data;           // Data to be stored in the node
    struct Node* next;  // Pointer to the next node in the list
};
```

### Operations on a Singly Linked List:
1. Insertion
    - Insertion at the beginning
    - Insertion at the end
    - Insertion at a given position
2. Deletion
    - Deletion at the beginning
    - Deletion at the end
    - Deletion at a given position
3. Traversal
    - Traversing the list
4. Searching

## Doubly Linked List
A doubly linked list is similar to a singly linked list, but each node points to both its next node and its previous node.

### Structure for a Node:
```c
struct Node {
    int data;           // Data to be stored in the node
    struct Node* next;  // Pointer to the next node in the list
    struct Node* prev;  // Pointer to the previous node in the list
};
```

### Operations on a Doubly Linked List:
1. Insertion
    - Insertion at the beginning
    - Insertion at the end
    - Insertion at a given position
2. Deletion
    - Deletion at the beginning
    - Deletion at the end
    - Deletion at a given position
3. Traversal
    - Traversing the list
4. Searching

## Comparison between Singly and Doubly Linked Lists
| Singly Linked List | Doubly Linked List |
|--------------------|--------------------|
| Each node has a pointer to the next node | Each node has a pointer to the next node and the previous node |
| Insertion and deletion at the beginning of the list is efficient | Insertion and deletion at the beginning of the list is efficient |
| Insertion and deletion at the end of the list is inefficient | Insertion and deletion at the end of the list is efficient |
| Searching is inefficient | Searching is efficient |

