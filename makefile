objects = parser.o scanner.o symTab.o
CC = gcc
LEX = flex
YACC = bison

all: pl1c

pl1c: $(objects)
		$(CC) -o $@ $^

parser.c: parser.y
		$(YACC) -d $< -o parser.c
		$(YACC) -d $<

scanner.c: scanner.l
		$(LEX) -t $< > $@

scanner.o : parser.h symTab.h
parser.o : parser.h symTab.h
symTab.o : symTab.h