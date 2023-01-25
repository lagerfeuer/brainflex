%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "ast/node.h"

  extern FILE* yyin;
  extern int yylex(void);
  extern int yyparse(void);
  void yyerror(const char *s);

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


void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
