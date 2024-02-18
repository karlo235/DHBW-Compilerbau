.DEFAULT_GOAL := help

objects = parser.o scanner.o symTab.o synTree.o optimizer.o
CC = gcc
LEX = flex
YACC = bison

all: pl1c # Build the compiler.

pl1c: $(objects)
		$(CC) -o $@ $^

parser.c: parser.y
		$(YACC) -d $< -o parser.c
		$(YACC) -d $<

scanner.c: scanner.l
		$(LEX) -t $< > $@

scanner.o : parser.h symTab.h
parser.o : parser.h symTab.h optimizer.h
symTab.o : symTab.h
synTree.o : synTree.h symTab.h
optimizer.o : synTree.h

files = parser.c parser.o parser.h parser.tab.c parser.tab.h pl1c scanner.c scanner.o symTab.o synTree.o optimizer.o outputs

.SILENT: clean

clean: # Remove build and output files.
		rm -r -f $(files)
		echo "Files are removed"

OUTPUT_FILES := $(patsubst ./examples/%_in.pl1,./outputs/%_out.pl1,$(wildcard ./examples/*_in.pl1))

test: # Compile test files.
	mkdir -p outputs $(OUTPUT_FILES)

./outputs/%_out.pl1: ./examples/%_in.pl1
	-./pl1c $< $@ > $(@:_out.pl1=_log.pl1)

help: # Show help for each of the Makefile commands.
	@printf "\nUsage: make <command> \n\nThe following commands are available : \n\n"
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  makefile | sort | while read -r l; do printf "\t\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "$(RESET)\n"