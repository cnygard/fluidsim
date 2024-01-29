CC       := gcc
CXX      := g++
CFLAGS   := -Wall -Wextra -std=c11 -g -pedantic -I./include
CXXFLAGS := -Wall -Wextra -std=c++17 -g -pedantic -I./include

ifeq ($(UNAME), Linux)
	CXXFLAGS += -lopengl32 -lglfw3 -lassimp

	PROG     := fs.exe
endif

SRC_DIR     := src
INCLUDE_DIR := include
CSRC        := $(wildcard $(SRC_DIR)/*.c)
CPPSRC      := $(wildcard $(SRC_DIR)/*.cpp)
CHDR        := $(wildcard $(INCLUDE_DIR)/*.h)
CPPHDR      := $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJ         := $(CSRC:.c=.o) $(CPPSRC:.cpp=.o)

PROG := fs

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.c $(CHDR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.o: %.cpp $(CPPHDR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ): $(CHDR) $(CPPHDR)

clean:
	rm $(OBJ) $(PROG)
