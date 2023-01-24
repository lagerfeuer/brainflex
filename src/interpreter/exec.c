#include "exec.h"
#include "../grammar.tab.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 64
#define CELLS_SIZE 256

int exec(Node* program) {
  Node* curr = program;

  unsigned char stack_ptr = 0;
  Node** stack = malloc(sizeof(Node*) * STACK_SIZE);
  if (!stack)
    return ERR_OUT_OF_MEMORY;

  unsigned short length = CELLS_SIZE;
  unsigned short idx = CELLS_SIZE / 2;
  unsigned short* cells = calloc(length, sizeof(unsigned short));
  if (!cells)
    return ERR_OUT_OF_MEMORY;

  while (curr != NULL) {
    switch (curr->token) {
      case PRINT:
        putchar(cells[idx]);
        break;
      case READ:
        cells[idx] = getchar();
        break;
      case LSHIFT:
        if (idx == 0) {
          length *= 2;
          unsigned short* tmp = calloc(length, sizeof(unsigned short));
          if (!tmp)
            return ERR_OUT_OF_MEMORY;
          memcpy(tmp + (length / 2), cells, length / 2);
          cells = tmp;
        }
        idx--;
        break;
      case RSHIFT:
        if (idx == length - 1) {
          length *= 2;
          unsigned short* tmp = calloc(length, sizeof(unsigned short));
          if (!tmp)
            return ERR_OUT_OF_MEMORY;
          memcpy(tmp, cells, length / 2);
        }
        idx++;
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
          if (stack_ptr >= STACK_SIZE) {
            return ERR_STACK_OVERFLOW;
          }
          stack[stack_ptr++] = curr;
        }
        break;
      case RBRACKET:
        curr = stack[--stack_ptr];
        continue;
    }
    curr = curr->next;
  }
  return 0;
}
