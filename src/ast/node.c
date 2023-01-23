#include "node.h"
#include "../grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>

char convert(int token) {
  switch (token) {
    case PRINT:
      return '.';
    case READ:
      return ',';
    case LSHIFT:
      return '<';
    case RSHIFT:
      return '>';
    case INCR:
      return '+';
    case DECR:
      return '-';
    case LBRACKET:
      return '[';
    case RBRACKET:
      return ']';
  }
  return '?';
}

Node* mknode(int token) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->token = token;
  node->next = NULL;
  node->other = NULL;
  return node;
}

Node* append(Node* list, Node* element) {
  Node* curr = list;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = element;
  return list;
}

void printTree(Node* tree) {
  Node* it = tree;
  int indent = 0;
  while (it) {
    if (it->token == RBRACKET)
      indent--;
    printf("%*s%c\n", indent * 2, "", convert(it->token));
    if (it->token == LBRACKET)
      indent++;
    it = it->next;
  }
}
