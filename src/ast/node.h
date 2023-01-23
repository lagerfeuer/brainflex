#ifndef NODE_H
#define NODE_H

typedef struct node {
  int token;
  struct node* next;
  struct node* other; // to pair [ and ] in loops
} Node;

char convert(int token);
Node* mknode(int token);
Node* append(Node* list, Node* element);
void printTree(Node* tree);

#endif
