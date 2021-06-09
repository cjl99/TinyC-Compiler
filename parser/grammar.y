%{
#define MAX_LITERAL_LEN 256

#include "ast/Ast.h"
#include "visualize-ast/VisualizeAst.h"
#include "backend/ObjGen/ObjGen.h"
#include "backend/codeGen/CodeGen.h"
using namespace std;
#define DEBUG_PARSER

extern int yylex();
void yyerror(const char *str);
extern FILE* yyin;

void printExpr(string start){
	std::cout<<start;
	// for(int i = 0;i<strs.length();i++){
	// 	std::cout<<" "<<strs[i];
	// }
	std::cout<<endl;
}
char *key;

%}

%union {
	int token_type;
	char* str;

	AstFunDef* ast_func_def;
	AstProgram* ast_program;
	AstExternalExpr* ast_ext_expr;

	AstDeclaration* ast_declaration;
	AstSpec* ast_type_spec;
	AstInitDeclList* ast_init_decl_list;
	AstInitDeclarator* ast_init_declarator;
	AstInitializer* ast_init;
	AstInitList* ast_init_list;
	AstDeclarator* ast_declarator;
	AstDirectDeclarator* ast_direct_declarator;
	AstPointer* ast_pointer;
	AstParamList *ast_param_list;
	AstDeclarationList* ast_declaration_list;

	AstPrimaryExpr* ast_primary_expr;
	AstPostfixExpr* ast_post_expr;
	AstArgExprList* ast_arg_expr_list;
	AstUnaryExpr* ast_unary_expr;
	AstCastExpr* ast_cast_expr;
	AstBinaryExpr* ast_binary_expr;
	AstCondiExpr* ast_condi_expr;
	AstExpression* ast_expr;
	AstAssignOp* ast_assign_op;

	AstStructSpec* ast_struct_spec;
	AstStructDeclarationList *ast_struct_decl_list;
	AstIdList *ast_id_list;
	AstTypeName *ast_type_name;
	AstStmtList* ast_stmt_list;
	AstCompoundStmt* ast_compound_stmt;
	AstStmt* ast_stmt;
	AstExprStmt* ast_expr_stmt;
	AstSelectStmt* ast_select_stmt;
	AstIterStmt* ast_iter_stmt;
	AstJmpStmt* ast_jmp_stmt;

}
%token<str> IDENTIFIER CONSTANT STRING_LITERAL
%token<str> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token<str> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token<str> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token<str> XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token<str> CHAR SHORT INT LONG FLOAT DOUBLE VOID
%token<str> STRUCT
%token<str> IF ELSE WHILE DO FOR CONTINUE BREAK RETURN
%token<str> '&' '*' '+' '-' '!' '~'

%left OR_OP
%left AND_OP
%left '|'
%left '^'
%left '&'
%left EQ_OP NE_OP
%left '<' '>' LE_OP GE_OP
%left LEFT_OP RIGHT_OP
%left '+' '-'
%left '*' '/' '%'

%type<ast_program> program
%type<ast_ext_expr> external_declaration
%type<ast_func_def> function_definition
%type<ast_declaration> declaration
%type<ast_type_spec> type_specifier
%type<ast_init_decl_list> init_declarator_list
%type<ast_init_declarator> init_declarator
%type<ast_init> initializer
%type<ast_init_list> initializer_list
%type<ast_declarator> declarator
%type<ast_direct_declarator> direct_declarator
%type<ast_pointer> pointer
%type<ast_param_list> parameter_list
%type<ast_primary_expr> primary_expression
%type<ast_post_expr> postfix_expression
%type<ast_arg_expr_list> argument_expression_list
%type<ast_unary_expr> unary_expression
%type<str> unary_operator
%type<ast_cast_expr> cast_expression
%type<ast_binary_expr> binary_expression
%type<ast_condi_expr> conditional_expression
%type<ast_expr> expression
%type<ast_assign_op> assignment_operator
%type<ast_struct_spec> struct_specifier
%type<ast_struct_decl_list> struct_declaration_list
%type<ast_id_list> identifier_list
%type<ast_type_name> type_name
%type<ast_stmt_list> statement_list
%type<ast_declaration_list> declaration_list
%type<ast_compound_stmt> compound_statement
%type<ast_stmt> statement
%type<ast_expr_stmt> expression_statement
%type<ast_select_stmt> selection_statement
%type<ast_iter_stmt> iteration_statement
%type<ast_jmp_stmt> jump_statement


%start program

%%
program
	: external_declaration{
	    $$ = new AstProgram();
	    $$->addExternalExpr($1);
	    astRoot = $$;
	    printf("Program is parsed successfully!\n");
	}
	| program external_declaration {
	    $$ = $1;
	    $$->addExternalExpr($2);
	}
	;

external_declaration
	: function_definition{
	    $$ = new AstExternalExpr($1, nullptr);
	}
	| declaration{
	    $$ = new AstExternalExpr(nullptr, $1);
	}
	;

function_definition
	: type_specifier IDENTIFIER '(' parameter_list ')' compound_statement{
		$$ = new AstFunDef($1, nullptr, $2, $4, $6);
	}
	| type_specifier pointer IDENTIFIER '(' parameter_list ')' compound_statement{
		$$ = new AstFunDef($1, $2, $3, $5, $7);
	}
	;

declaration
	: type_specifier init_declarator_list ';' {
		$$ = new AstDeclaration($1, $2);
	}
	;
    
type_specifier
	: VOID{ $$ = new AstSpec($1); }
	| CHAR{ $$ = new AstSpec($1); }
	| SHORT{ $$ = new AstSpec($1); }
	| INT{ $$ = new AstSpec($1); }
	| LONG{ $$ = new AstSpec($1); }
	| FLOAT{ $$ = new AstSpec($1); }
	| DOUBLE{ $$ = new AstSpec($1); }
	| struct_specifier{ $$ = new AstSpec($1->getName()); }
	;

init_declarator_list
	: init_declarator {
		$$ = new AstInitDeclList();
		$$->addInitDeclarator($1);
	}
	| init_declarator_list ',' init_declarator {
		$1->addInitDeclarator($3);
		$$ = $1;
	}
	;

init_declarator
	: declarator {
		$$ = new AstInitDeclarator($1, nullptr);
	}
	| declarator '=' initializer {
		$$ = new AstInitDeclarator($1, $3);
	}
	;

initializer
	: expression {
		$$ = new AstInitializer($1, nullptr);
	}
	| '{' initializer_list '}' {
		$$ = new AstInitializer(nullptr, $2);
	}
	| '{' initializer_list ',' '}' {
		$$ = new AstInitializer(nullptr, $2);
	}
	;

initializer_list
	: initializer {
		$$ = new AstInitList();
		$$->addInitializer($1);
	}
	| initializer_list ',' initializer {
		$1->addInitializer($3);
		$$ = $1;
	}
	;

declarator
	: pointer direct_declarator {
		$$ = new AstDeclarator($1, $2);
	}
	| direct_declarator {
		$$ = new AstDeclarator(nullptr, $1);
	}
	;

direct_declarator
	: IDENTIFIER {
		$$ = new AstDirectDeclarator($1);
	}
	| direct_declarator '[' CONSTANT ']' {
		$1->addToDirectDecl(1, $3);
		$$ = $1;
	}
	| direct_declarator '[' ']' {
		$$->addToDirectDecl(2, nullptr);
		$$ = $1;
	}
	| direct_declarator '(' identifier_list ')' {
		$1->addToDirectDecl(3, $3);
		$$ = $1;
	}
	;

pointer
	: '*' {
		$$ = new AstPointer();
	}
	| '*' pointer {
		$2->addOneStar();
		$$ = $2;
	}
	;

parameter_list 
    : {
		$$ = new AstParamList(false);

	}
    | type_specifier declarator {
		$$ = new AstParamList(true);
		$$->addParam($1, $2);
	}
	| parameter_list ',' type_specifier declarator {
		$1->addParam($3, $4);
		$$  = $1;
	}
	;


primary_expression
	: IDENTIFIER {
        $$ = new AstPrimaryExpr(1, $1);
	}
	| CONSTANT {
        $$ = new AstPrimaryExpr(2, $1);
	}
	| STRING_LITERAL {
        $$ = new AstPrimaryExpr(3, $1);
	}
	| '(' expression ')' {
        $$ = new AstPrimaryExpr(4, $2);
	}
	;

postfix_expression
	: primary_expression {
	    $$ = new AstPostfixExpr(nullptr, "", $1);
	}
	| postfix_expression '[' expression ']' {
	    $$ = new AstPostfixExpr($1, "[]", $3);
	}
	| postfix_expression '(' ')' {
	    $$ = new AstPostfixExpr($1, "()");
	}
	| postfix_expression '(' argument_expression_list ')' {
	    $$ = new AstPostfixExpr($1, "()", $3);
	}
	| postfix_expression '.' IDENTIFIER {
	    $$ = new AstPostfixExpr($1, ".", $3);
	}
	| postfix_expression PTR_OP IDENTIFIER{
	    $$ = new AstPostfixExpr($1, $2, $3);
	}
	| postfix_expression INC_OP {
	    $$ = new AstPostfixExpr($1, $2);
	}
	| postfix_expression DEC_OP {
	    $$ = new AstPostfixExpr($1, $2);
	}
	;

argument_expression_list
	: expression {
	    $$ = new AstArgExprList();
	    $$->addExpression($1);
	}
	| argument_expression_list ',' expression {
	    $1->addExpression($3);
	    $$ = $1;
	}
	;

unary_expression
	: postfix_expression {
	    $$ = new AstUnaryExpr("", $1);
	}
	| INC_OP unary_expression {
	    $$ = new AstUnaryExpr($1, $2);
	}
	| DEC_OP unary_expression {
	    $$ = new AstUnaryExpr($1, $2);
	}
	| unary_operator cast_expression {
	    $$ = new AstUnaryExpr($1, $2);
	}
	;

unary_operator
	: '&' {
	    $$ = $1;
	}
	| '*' {
        $$ = $1;
	}
	| '+' {
	    $$ = $1;
	}
	| '-' {
	    $$ = $1;
	}
	| '~' {
	    $$ = $1;
	}
	| '!' {
	    $$ = $1;
	}
	;

cast_expression
	: unary_expression {
	    $$ = new AstCastExpr($1);
	}
	| '(' type_name ')' cast_expression {
	    $$ = new AstCastExpr($2, $4);
	}
	;

binary_expression
    : cast_expression {
        $$ = new AstBinaryExpr($1);
    }
    | binary_expression OR_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression AND_OP  binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression '|'     binary_expression {
        $$ = new AstBinaryExpr($1, "|", $3);
    }
    | binary_expression '^'     binary_expression {
        $$ = new AstBinaryExpr($1, "^", $3);
    }
    | binary_expression '&'     binary_expression {
        $$ = new AstBinaryExpr($1, "&", $3);
    }
    | binary_expression EQ_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression NE_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression '<'     binary_expression {
        $$ = new AstBinaryExpr($1, "<", $3);
    }
    | binary_expression '>'     binary_expression {
        $$ = new AstBinaryExpr($1, ">", $3);
    }
    | binary_expression LE_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression GE_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression LEFT_OP binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression RIGHT_OP   binary_expression {
        $$ = new AstBinaryExpr($1, $2, $3);
    }
    | binary_expression '+'     binary_expression {
        $$ = new AstBinaryExpr($1, "+", $3);
    }
    | binary_expression '-'     binary_expression {
        $$ = new AstBinaryExpr($1, "-", $3);
    }
    | binary_expression '*'     binary_expression {
        $$ = new AstBinaryExpr($1, "*", $3);
    }
    | binary_expression '/'     binary_expression {
        $$ = new AstBinaryExpr($1, "/", $3);
    }
    | binary_expression '%'     binary_expression {
        $$ = new AstBinaryExpr($1, "%", $3);
    }
    ;

conditional_expression
	: binary_expression {
	    $$ = new AstCondiExpr($1);
	}
	| binary_expression '?' expression ':' binary_expression {
	    $$ = new AstCondiExpr($1, $3, $5);
	}
	;

expression
	: conditional_expression {
	    printf("conditional_expression\n");
	    $$ = new AstExpression($1);
	}
	| unary_expression assignment_operator expression {
	    $$ = new AstExpression($1, $2, $3);
	    printf("unary_expression\n");
	}
	;

assignment_operator
	: '=' {
        $$ = new AstAssignOp("=");
	}
	| MUL_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| DIV_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| MOD_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| ADD_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| SUB_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| LEFT_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| RIGHT_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| AND_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| XOR_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	| OR_ASSIGN {
	    $$ = new AstAssignOp($1);
	}
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'{
		$$ = new AstStructSpec($2, $4);
	}
	| STRUCT '{' struct_declaration_list '}'{
		$$ = new AstStructSpec("", $3);
	}
	| STRUCT IDENTIFIER{
		$$ = new AstStructSpec($2, nullptr);
	}
	;

struct_declaration_list
	: type_specifier declarator ';'{
		$$ = new AstStructDeclarationList();
		$$->addMember($1, $2);
	}
	| struct_declaration_list type_specifier declarator ';'{
		$$ = $1;
		$$->addMember($2, $3);
	}
	;

identifier_list
	: IDENTIFIER{
		$$ = new AstIdList();
		$$->addId($1);
	}
	| identifier_list ',' IDENTIFIER{
		$$ = $1;
		$$->addId($3);
	}
	;

type_name
	: type_specifier{
		$$ = new AstTypeName($1, nullptr);
	}
	| type_specifier pointer{
		$$ = new AstTypeName($1, $2);
	}
	;

statement_list
	: statement{
		$$ = new AstStmtList();
		$$->addStmt($1);
	}
	| statement_list statement{
		$$ = $1;
		$$->addStmt($2);
	}
	;

declaration_list
	: declaration{
		$$ = new AstDeclarationList();
		$$->addDeclaration($1);
	}
	| declaration_list declaration{
		$1->addDeclaration($2);
		$$ = $1;
	}
	;


compound_statement
	: '{' '}'{
		$$ = new AstCompoundStmt(nullptr, nullptr);
	}
	| '{' statement_list '}'{
		$$ = new AstCompoundStmt(nullptr, $2);
	}
	| '{' declaration_list '}'{
		$$ = new AstCompoundStmt($2, nullptr);
	}
	| '{' declaration_list statement_list '}'{
		$$ = new AstCompoundStmt($2, $3);
	}
	;

statement
	: compound_statement{ $$ = new AstStmt(1, $1); }
	| expression_statement{ $$ = new AstStmt(2, $1); }
	| selection_statement{ $$ = new AstStmt(3, $1); }
	| iteration_statement{ $$ = new AstStmt(4, $1); }
	| jump_statement{ $$ = new AstStmt(5, $1); }
	;

expression_statement
	: ';' {$$ = nullptr;}
	| expression ';' {$$ = new AstExprStmt($1); }
	;

selection_statement
	: IF '(' expression ')' statement{
		$$ = new AstSelectStmt($3, $5);
	}
	| IF '(' expression ')' statement ELSE statement{
		$$ = new AstSelectStmt($3, $5, $7);
	}
	;

iteration_statement
	: WHILE '(' expression ')' statement{
		$$ = new AstIterStmt(1, nullptr, $3, nullptr, $5);
	}
	| FOR '(' expression_statement expression_statement ')' statement{
		$$ = new AstIterStmt(2, $3->getExpr(), $4->getExpr(), nullptr, $6);
	}
	| FOR '(' expression_statement expression_statement expression ')' statement{
		$$ = new AstIterStmt(2, $3->getExpr(), $4->getExpr(), $5, $7);
	}
	;

jump_statement
	: CONTINUE ';'{ $$ = new AstJmpStmt($1, nullptr);}
	| BREAK ';'   { $$ = new AstJmpStmt($1, nullptr);}
	| RETURN ';'  { $$ = new AstJmpStmt($1, nullptr);}
	| RETURN expression ';' { $$ = new AstJmpStmt($1, $2);}
	;

%%
#include <stdio.h>
#define DEBUG_PARSER

extern char yytext[];
extern int column;

#ifdef DEBUG_PARSER
int main(int argc,char* argv[]){
	// open file to parse
	yyin=fopen(argv[1],"r");
	printf("parse\n");
	yyparse();
	fclose(yyin);

	// visualize ast and save it to file
	VisualizeAst *graph = new VisualizeAst("AstGraph.dot");
	graph->generateGraph();
	graph->saveGraph();

	// IR generation
    CodeGen *CodeGenContext = new CodeGen(); // program
    //astRoot->codeGen(&CodeGenContext);

    CodeGenContext->generateCode((AstProgram *)astRoot);

    ObjGen(*CodeGenContext);

	return 0;
}
#endif