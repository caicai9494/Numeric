CC = g++
FLAG = -c 
CXXFLAGS = -g -Wall -std=c++11

TARGET = numtest
OBJ = FunctionSolver/Function.o test.o FunctionSolver/FunctionSolver.o common/util.o LinearAlgebra/Vector.o LinearAlgebra/Matrix.o LinearAlgebra/LinearEquationSolver.o Approximating/Interpolation.o common/Timer.o
LOBJ = FunctionSolver/Function.cc test.cc FunctionSolver/FunctionSolver.cc common/util.cc LinearAlgebra/Vector.cc LinearAlgebra/Matrix.cc LinearAlgebra/LinearEquationSolver.cc Approximating/Interpolation.cc common/Timer.cc
HEADER = common/util.h

link:
	$(CC) $(LOBJ) -fPIC -shared -o libnumeric.so

all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -g 
.c.o:
	$(CC) $(FLAG) $< -g

test:
	make clean && make && ./numtest 

clean:
	rm -rf $(OBJ) $(TARGET)




