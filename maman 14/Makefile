CXX       := gcc -c
CXX_FLAGS := -Wall -ansi -std=c90 -pedantic

SRC     := src
BIN     := bin
INCLUDE := include

PROGRAM_NAME  := main



all: init input.o data.o operands.o handleFiles.o symbol.o commands.o macro.o main.o main clean

# This process will make sure that directory named bin exists
init: 
	mkdir -p bin

input.o: $(SRC)/input.c
	$(CXX) $(SRC)/input.c -o $(BIN)/input.o $(CXX_FLAGS) -I $(INCLUDE)
data.o: $(SRC)/data.c
	$(CXX) $(SRC)/data.c -o $(BIN)/data.o $(CXX_FLAGS) -I $(INCLUDE)
operands.o: $(SRC)/operands.c
	$(CXX) $(SRC)/operands.c -o $(BIN)/operands.o $(CXX_FLAGS) -I $(INCLUDE)
commands.o: $(SRC)/commands.c
	$(CXX) $(SRC)/commands.c -o $(BIN)/commands.o $(CXX_FLAGS) -I $(INCLUDE)
macro.o: $(SRC)/macro.c
	$(CXX) $(SRC)/macro.c -o $(BIN)/macro.o $(CXX_FLAGS) -I $(INCLUDE)
symbol.o: $(SRC)/symbol.c
	$(CXX) $(SRC)/symbol.c -o $(BIN)/symbol.o $(CXX_FLAGS) -I $(INCLUDE)
handleFiles.o: $(SRC)/handleFiles.c
	$(CXX) $(SRC)/handleFiles.c -o $(BIN)/handleFiles.o $(CXX_FLAGS) -I $(INCLUDE)
main.o: $(SRC)/main.c
	$(CXX) $(SRC)/main.c -o $(BIN)/main.o $(CXX_FLAGS) -I $(INCLUDE)
main: $(BIN)/main.o $(BIN)/input.o
	gcc $(BIN)/input.o $(BIN)/symbol.o $(BIN)/operands.o $(BIN)/handleFiles.o $(BIN)/commands.o $(BIN)/macro.o $(BIN)/data.o $(BIN)/main.o -o $(PROGRAM_NAME) $(CXX_FLAGS)

clean:
	rm $(BIN)/*.o
	@echo "Done ...\n"