FLAG_C_VERSION = -std=c++11
LLVM_COMPILE_FLAGS = `llvm-config --cxxflags`

all:
	g++ -c TypeSystem.cpp -o TypeSystem.o $(FLAG_C_VERSION) $(LLVM_COMPILE_FLAGS)

clean:
	rm -rf *.o