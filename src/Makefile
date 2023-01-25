TARGET := ../brainflex

CC ?= gcc
CFLAGS := -O2 -Wall -Wextra -Wpedantic
CLIBS := -lfl

LEX := flex
LFLAGS :=

YACC := bison
YFLAGS := -v -d

SRCS := main.c ast/node.c interpreter/exec.c

all: $(TARGET)

debug: CFLAGS += -DDEBUG -g
debug: LFLAGS += --debug
debug: YFLAGS += --debug
debug: $(TARGET)

$(TARGET): lex.yy.c grammar.tab.c $(SRCS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(CLIBS)

lex.yy.c lex.yy.h: lexer.l grammar.tab.h
	$(LEX) $(LFLAGS) $<

grammar.tab.c grammar.tab.h: grammar.y
	$(YACC) $(YFLAGS) $<

clean:
	rm -rf grammar.tab.c grammar.tab.h lex.yy.c $(TARGET)
.PHONY: clean
