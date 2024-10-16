SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

HEADER_DIR = headers

OUTPUT = Pokemon.exe

CXXFLAGS= -I$(HEADER_DIR) -std=c++11

ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q
    EXEC=$(OUTPUT)
else
    RM = rm -f
    EXEC=./$(OUTPUT)
endif

compile:
	g++ $(CXXFLAGS) $(SRC_FILES) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)

execute:
	$(EXEC)

.PHONY: compile clean execute