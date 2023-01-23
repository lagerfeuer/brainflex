TARGET := ../brainflex

CC ?= gcc
CFLAGS := -O2 -Werror -Wall
CLIBS := -ll

LEX := flex

YACC := bison
YFLAGS := -v -d

SRCS := ast/node.c interpreter/exec.c

all: $(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: $(TARGET)

$(TARGET): lex.yy.c grammar.tab.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

lex.yy.c: lexer.l grammar.tab.h
	$(LEX) $<

grammar.tab.c grammar.tab.h: grammar.y
	$(YACC) $(YFLAGS) $<

