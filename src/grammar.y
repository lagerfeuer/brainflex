%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <unistd.h>
  #include <stdbool.h>

  #include "ast/node.h"
  #include "interpreter/exec.h"

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
  }
  else
    exec(prog);
}

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
