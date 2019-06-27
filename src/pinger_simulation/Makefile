EXEC 	= simulation

CC  	= gcc
RMV 	= rm -rf
CFLAGS 	= -ggdb -std=c++11 -Wall -Iinclude
LFLAGS 	= -Wall -I. -lm

SRC 	= src
OBJ  	= obj
BIN  	= bin

SOURCES  	= $(wildcard $(SRC)/*.c)
INCLUDES 	= $(wildcard $(SRC)/*.h)
OBJECTS 	= $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
DEPENDS		= $(OBJECTS:%.o=%.d) 

$(BIN)/$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@	

-include $(DEPENDS)

$(OBJECTS): $(OBJ)/%.o : $(SRC)/%.c
	$(CXX) $(CFLAGS) -c -MMD $< -o $@

clean:	
	$(RMV) $(OBJ)/*
	$(RMV) $(BIN)/*
