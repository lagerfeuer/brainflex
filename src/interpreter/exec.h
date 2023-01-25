#ifndef EXEC_H
#define EXEC_H

#include "../ast/node.h"

typedef unsigned int cell_t;

int exec(Node* program);

#endif
