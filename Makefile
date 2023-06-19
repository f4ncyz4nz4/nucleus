CXX=g++
CXXFLAGS=-Wall -g -O0 -fpermissive
LDFLAGS=-lcapstone -lbfd-multiarch

SRC=$(wildcard src/*.cc)
OBJ=$(patsubst src/%.cc, obj/%.o, $(SRC))
BIN=nucleus

.PHONY: all clean setup

all: $(BIN)

$(OBJ): | obj

obj:
	@mkdir -p $@

obj/%.o: src/%.cc src/%.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

setup:
	sudo apt install binutils-multiarch-dev libcapstone-dev

clean:
	rm -f $(OBJ)
	rm -Rf obj
	rm -f $(BIN)

