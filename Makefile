SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

HEADER_DIR = headers

OUTPUT = Pokemon.exe

CXXFLAGS= -I$(HEADER_DIR) -std=c++11

compile:
	g++ $(CXXFLAGS) $(SRC_FILES) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

execute:
	./$(OUTPUT)

.PHONY: compile clean execute
