CXX=g++
CXXFLAGS=-Wall -g -O0 -fpermissive
LDFLAGS=-lcapstone -lbfd-multiarch

SRC=$(wildcard *.cc)
OBJ=$(patsubst %.cc, obj/%.o, $(SRC))
BIN=nucleus

.PHONY: all clean setup

all: $(BIN)

$(OBJ): | obj

obj:
	@mkdir -p $@

obj/%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

setup:
	sudo apt install binutils-multiarch-dev libcapstone-dev

clean:
	rm -f $(OBJ)
	rm -Rf obj
	rm -f $(BIN)

