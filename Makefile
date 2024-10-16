SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

HEADER_DIR = headers

OUTPUT = Pokemon.exe

CXXFLAGS= -I$(HEADER_DIR) -std=c++11

ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q
else
    RM = rm -f
endif

compile:
	g++ $(CXXFLAGS) $(SRC_FILES) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)

execute:
    ./$(OUTPUT)

.PHONY: compile clean execute
