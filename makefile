CC = g++
FLAG = -c 
CXXFLAGS = -g

TARGET = numtest
OBJ = Function.o test.o FunctionSolver.o common/util.o
HEADER = common/util.h

all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -g 
.c.o:
	$(CC) $(FLAG) $< -g

test:
	make clean && make && ./numtest 

clean:
	rm -rf $(OBJ) $(TARGET)




