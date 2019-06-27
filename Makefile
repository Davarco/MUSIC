CXX		= gcc
RMV 	= rm -rf
CFLAGS 	= 
LFLAGS 	= -I. -lm

SRC 	= src
BIN  	= bin

all: data main

data:
	$(CXX) $(CFLAGS) $(SRC)/data.c $(SRC)/config.h -o $(BIN)/data $(LFLAGS)

main:
	$(CXX) $(CFLAGS) $(SRC)/main.c -o $(BIN)/main $(LFLAGS)


