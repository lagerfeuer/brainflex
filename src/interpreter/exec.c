#include "exec.h"
#include "../grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 64
#define CELLS_SIZE 256

void exec(Node* program) {
  Node* curr = program;

  int stack_mult = 1;
  int stack_ptr = 0;
  Node** stack = malloc(sizeof(Node*) * STACK_SIZE * stack_mult);

  int cells_mult = 1;
  int idx = CELLS_SIZE / 2;
  int* cells = malloc(sizeof(int) * CELLS_SIZE * cells_mult);

  while (curr != NULL) {
    switch (curr->token) {
      case PRINT:
        putchar(cells[idx]);
        break;
      case READ:
        cells[idx] = getchar();
        break;
      case LSHIFT:
        idx--; // TODO fix negative overflow
        break;
      case RSHIFT:
        idx++; // TODO fix overflow
        break;
      case INCR:
        cells[idx]++;
        break;
      case DECR:
        cells[idx]--;
        break;
      case LBRACKET:
        if (cells[idx] == 0) {
          curr = curr->other;
        } else {
          stack[stack_ptr++] = curr; // TODO fix overflow
        }
        break;
      case RBRACKET:
        curr = stack[--stack_ptr];
        continue;
    }
    curr = curr->next;
  }
}
