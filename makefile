FLAG = `llvm-config --cxxflags --ldflags --libs --system-libs`
LLVM_LINK_FLAGS = `llvm-config --ldflags --libs --system-libs`
LLVM_COMPILE_FLAGS = `llvm-config --cxxflags`
FLAG_C_VERSION = -std=c++11

.PHONY: test
SOURCE = $(wildcard ./ast/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCE))
SOURCE2 = $(wildcard ./visualize-ast/*.cpp)
OBJS2 = $(patsubst %.cpp,%.o,$(SOURCE2))

SOURCE_CODEGEN = $(wildcard ./backend/codeGen/*.cpp)
OBJS_CODEGEN = $(patsubst %.cpp,%.o,$(SOURCE_CODEGEN))

SOURCE_OBJGEN = $(wildcard ./backend/ObjGen/*.cpp)
OBJS_OBJGEN = $(patsubst %.cpp,%.o,$(SOURCE_OBJGEN))

SOURCE_TYPESYS = $(wildcard ./backend/TypeSystem/*.cpp)
OBJS_TYPESYS = $(patsubst %.cpp,%.o,$(SOURCE_TYPESYS))

all: res

res: $(OBJS) $(OBJS2) $(OBJS_CODEGEN) $(OBJS_TYPESYS) $(OBJS_OBJGEN) y.tab.o lex.yy.o
	g++ y.tab.o lex.yy.o $(OBJS) $(OBJS2) $(OBJS_TYPESYS) $(OBJS_CODEGEN) $(OBJS_OBJGEN) -o res $(FLAG)

y.tab.o: y.tab.cpp
	g++ -c y.tab.cpp -std=c++11 $(LLVM_COMPILE_FLAGS)

y.tab.cpp: ./parser/grammar.y
	yacc -d -o y.tab.cpp ./parser/grammar.y

y.tab.hpp: y.tab.cpp
	echo "y.tab.h was created at the same time as y.tab.c"
	
lex.yy.o: lex.yy.cpp y.tab.hpp $(OBJS) 
	g++ -c lex.yy.cpp -std=g++17 $(LLVM_COMPILE_FLAGS)

lex.yy.cpp: 
	lex -o lex.yy.cpp ./lexer/c.l

$(OBJS): $(SOURCE) 
	g++ -c ast/Ast.cpp -o ast/Ast.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstBase.cpp -o ast/AstBase.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstType.cpp -o ast/AstType.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstDecl.cpp -o ast/AstDecl.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstExpr.cpp -o ast/AstExpr.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstProg.cpp -o ast/AstProg.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstStmt.cpp -o ast/AstStmt.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	g++ -c ast/AstStruct.cpp -o ast/AstStruct.o -std=c++11 $(LLVM_COMPILE_FLAGS)
	
$(OBJS2): $(SOURCE2)
	g++ -c ./visualize-ast/VisualizeAst.cpp -o ./visualize-ast/VisualizeAst.o -std=c++11 $(LLVM_COMPILE_FLAGS)

$(OBJS_CODEGEN): $(SOURCE_CODEGEN)
	make -C ./backend/codeGen

$(OBJS_TYPESYS) : $(SOURCE_TYPESYS)
	make -C ./backend/TypeSystem

$(OBJS_OBJGEN) : $(SOURCE_OBJGEN)
	make -C ./backend/ObjGen

test: ./test/quicksort.c
	./res test/quicksort.c
	g++ output.o -o test1
	./test1

graph:
	./res test/quicksort.c
	dot AstGraph.dot -T jpg -o graph.jpg

clean:
	make clean -C lexer
	make clean -C parser
	make clean -C ast
	make clean -C visualize-ast
	make clean -C backend/ObjGen
	make clean -C backend/codeGen
	make clean -C backend/TypeSystem

	rm -rf y.tab.cpp y.tab.hpp lex.yy.cpp
	rm -rf *.dot *.jpg
	rm -rf *.o *.out
	rm -rf res
	rm -rf test1

