CC = g++
FLAG = -c 
CXXFLAGS = -g 

TARGET = numtest
OBJ = FunctionSolver/Function.o test.o FunctionSolver/FunctionSolver.o common/util.o LinearAlgebra/Vector.o LinearAlgebra/Matrix.o LinearAlgebra/LinearEquationSolver.o Approximating/Interpolation.o
HEADER = common/util.h

all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -g 
.c.o:
	$(CC) $(FLAG) $< -g

test:
	make clean && make && ./numtest 

clean:
	rm -rf $(OBJ) $(TARGET)




