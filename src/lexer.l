%option header-file="lex.yy.h"
%option noinput nounput noyywrap

%{
  #include "grammar.tab.h"
  #define TOKEN(t) yylval.token = (t)
%}

%%

[ \t\n]+    { ; }
"."         { return TOKEN(PRINT); }
","         { return TOKEN(READ); }
">"         { return TOKEN(RSHIFT); }
"<"         { return TOKEN(LSHIFT); }
"+"         { return TOKEN(INCR); }
"-"         { return TOKEN(DECR); }
"["         { return TOKEN(LBRACKET); }
"]"         { return TOKEN(RBRACKET); }
.           { ; }

%%
