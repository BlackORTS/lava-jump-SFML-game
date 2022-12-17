CC = g++
LINKERS = -lsfml-graphics -lsfml-window -lsfml-system 
FILE = src/main.cpp 
EX_NAME = executable 

all: compile

compile: $(FILE)
	$(CC) $(FILE) $(LINKERS) -o build/$(EX_NAME)

clean:
	rm $(EX_NAME)
