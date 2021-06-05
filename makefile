.PHONY:all
SOURCE = $(wildcard ./ast/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCE))
SOURCE2 = $(wildcard ./visualizeAST/*.cpp)
OBJS2 = $(patsubst %.cpp,%.o,$(SOURCE2))

all: res

res: $(OBJS) y.tab.o lex.yy.o
	g++ y.tab.o lex.yy.o $(OBJS) -o res

y.tab.o: y.tab.cpp
	g++ -c y.tab.cpp -std=c++11

y.tab.cpp: ./parser/grammar.y
	yacc -d -o y.tab.cpp ./parser/grammar.y

y.tab.hpp: y.tab.cpp
	echo "y.tab.h was created at the same time as y.tab.c"
	
lex.yy.o: lex.yy.cpp y.tab.hpp $(OBJS) 
	g++ -c lex.yy.cpp -std=c++11

lex.yy.cpp: 
	lex -o lex.yy.cpp ./lexer/c.l

$(OBJS): $(SOURCE) 
	g++ -c ast/Ast.cpp -o ast/Ast.o -std=c++11
	g++ -c ast/AstBase.cpp -o ast/AstBase.o -std=c++11
	g++ -c ast/AstType.cpp -o ast/AstType.o -std=c++11
	g++ -c ast/AstDecl.cpp -o ast/AstDecl.o -std=c++11
	g++ -c ast/AstExpr.cpp -o ast/AstExpr.o -std=c++11
	g++ -c ast/AstProg.cpp -o ast/AstProg.o -std=c++11
	g++ -c ast/AstStmt.cpp -o ast/AstStmt.o -std=c++11
	g++ -c ast/AstStruct.cpp -o ast/AstStruct.o -std=c++11
	
$(OBJS2): $(SOURCE2)
	g++ -c ./visualizeAST/astGenerator.cpp -o ./visualizeAST/astGenerator.o -std=c++11

graph:
	./res test/quicksort.c
	dot AstGraph.dot -T jpg -o graph.jpg

clean:
	make clean -C lexer
	make clean -C parser
	make clean -C ast
	rm -rf *.o
	rm -r y.tab.cpp y.tab.hpp lex.yy.cpp
	rm -r res
	
