#include "ast/node.h"
#include "grammar.tab.h"
#include "interpreter/exec.h"
#include "lex.yy.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern Node* prog;
// extern FILE* yyin;

int main(int argc, char** argv) {
  bool printAst = false;
  char* filename = NULL;
  int c;

  while ((c = getopt(argc, argv, "pf:")) != -1) {
    switch (c) {
      case 'p':
        printAst = true;
        break;
      case 'f':
        filename = optarg;
        break;
      case '?':
        if (optopt == 'f')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        exit(ERR_USAGE);
      default:
        abort();
    }
  }

  if (filename == NULL) {
    fprintf(stderr, "Did not get a file, please provide one with -f.\n");
    exit(ERR_USAGE);
  }

  yyin = fopen(filename, "r");
  if (!yyin) {
    perror("Could not open file");
    exit(ERR_FILE);
  }
  yyparse();
  fclose(yyin);
  yyin = NULL;

  if (printAst) {
    printf("Got -p, print AST and exit...\n\n");
    printTree(prog);
    exit(0);
  }

#ifdef DEBUG
  fprintf(stderr, "Using cell size of %lu byte.\n\n", sizeof(cell_t));
#endif

  int result = exec(prog);
  switch (result) {
    case ERR_STACK_OVERFLOW:
      fprintf(stderr, "Stack Overflow, exiting...\n");
      break;
    case ERR_OUT_OF_MEMORY:
      fprintf(stderr, "Out of memory, exiting...\n");
      break;
  }
  return result;
}
