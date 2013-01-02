SRC = $(shell ls *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = glModel

CC = gcc
CXX = g++
CFLAGS = -ggdb #-Wall 
CXXFLAG := $(CFLAGS)
LD = -lGL


.PHONY: all clean compile
all:main


compile: $(SRC)
	@echo "Compiling ..."
	@for go in $(SRC:.cpp=);\
		do\
		$(CXX) $(CXXFLAG) -c $$go.cpp -o $$go.o;\
		echo "compile $$go.cpp to $$go.o";\
		done;

main: compile
	@echo "Linking ...";
	$(CXX) $(CXXFLAG) $(OBJ) -o $(EXE) $(LD)

clean:
	rm -rf $(EXE) $(OBJ)
