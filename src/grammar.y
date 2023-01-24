%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <unistd.h>
  #include <stdbool.h>

  #include "ast/node.h"
  #include "interpreter/exec.h"
  #include "utils.h"

  void yyerror(const char *s);
  extern int yylex();

  struct node* prog;
%}

%union {
  struct node* node;
  int token;
}

%token <token> PRINT READ LSHIFT RSHIFT INCR DECR
%token <token> LBRACKET RBRACKET

%type <node> program stmts stmt loop
%type <token> op

%start program

%%

program
  : stmts { prog = $$; }
;

stmts
  : stmt        { $$ = $1; }
  | stmts stmt  { append($$ = $1, $2); }
;

stmt
  : loop { $$ = $1; }
  | op   { $$ = mknode($1); }
;

loop
  : LBRACKET stmts RBRACKET {
      $$ = mknode($1);
      $$->next = $2;
      $$->other = mknode($3);
      append($$->next, $$->other);
      $$->other->other = $$;
    }
;

op
  : PRINT
  | READ
  | LSHIFT
  | RSHIFT
  | INCR
  | DECR
;

%%

int main(int argc, char** argv) {
  bool printAst = false;
  int c;

  while((c = getopt(argc, argv, "p")) != -1) {
    switch(c) {
      case 'p':
        printAst = true;
        break;
      default:
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        abort();
    }
  }

  yyparse();

  if (printAst) {
    printf("Got -p, print AST and exit...\n\n");
    printTree(prog);
    exit(0);
  }
  int result = exec(prog);
  switch(result) {
    case ERR_STACK_OVERFLOW:
      fprintf(stderr, "Stack Overflow, exiting...\n");
      exit(ERR_STACK_OVERFLOW);
    case ERR_OUT_OF_MEMORY:
      fprintf(stderr, "Out of memory, exiting...\n");
      exit(ERR_STACK_OVERFLOW);
  }
  return 0;
}

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
