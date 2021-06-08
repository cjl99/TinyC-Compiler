FLAG_C_VERSION = -std=c++11
LLVM_COMPILE_FLAGS = `llvm-config --cxxflags`

all: gen gen_decl gen_prog gen_stmt gen_expr

gen:
	g++ -c CodeGen.cpp -o CodeGen.o $(FLAG_C_VERSION) $(LLVM_COMPILE_FLAGS)
gen_decl:
	g++ -c CodeGenDecl.cpp -o CodeGenDecl.o $(FLAG_C_VERSION)  $(LLVM_COMPILE_FLAGS)
gen_prog:
	g++ -c CodeGenProg.cpp -o CodeGenProg.o $(FLAG_C_VERSION)  $(LLVM_COMPILE_FLAGS)
gen_stmt:
	g++ -c CodeGenStmt.cpp -o CodeGenStmt.o $(FLAG_C_VERSION)  $(LLVM_COMPILE_FLAGS)
gen_expr:
	g++ -c CodeGenExpr.cpp -o CodeGenExpr.o $(FLAG_C_VERSION)  $(LLVM_COMPILE_FLAGS)

clean:
	rm -rf *.o