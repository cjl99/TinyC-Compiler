%token IDENTIFIER CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token CHAR SHORT INT LONG FLOAT DOUBLE VOID
%token STRUCT
%token IF ELSE WHILE DO FOR CONTINUE BREAK RETURN

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

%start program

%%
program
	: external_declaration{
	    $$ = new AstProgram();
	    $$->addExternalExpr($1);
	    astRoot = $$
	}
	| program external_declaration {
	    $$ = $1;
	    $$->addExternalExpr($1);
	}
	;

external_declaration
	: function_definition
	| declaration
	;

declaration
	: type_specifier init_declarator_list ';' {
		$$ = new AstDeclaration($1, $2);
	}
	;
    
type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| struct_specifier
	;

init_declarator_list
	: init_declarator {
		$$ = new AstInitDeclList();
		$$->addInitDecl($1);
	}
	| init_declarator_list ',' init_declarator {
		$1->addInitDecl($3);
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
		$$ = new AstDeclarator(nullptr, $2);
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
		$1->addToDirectDecl(1, $3);
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

function_definition
	: type_specifier IDENTIFIER '(' parameter_list ')' compound_statement
	| type_specifier pointer IDENTIFIER '(' parameter_list ')' compound_statement
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
		$1->addParam($2, $3);
		$$  = $1;
	}
	;


primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: expression
	| argument_expression_list ',' expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

binary_expression
    : cast_expression
    | binary_expression OR_OP   binary_expression
    | binary_expression AND_OP  binary_expression
    | binary_expression '|'     binary_expression
    | binary_expression '^'     binary_expression
    | binary_expression '&'     binary_expression
    | binary_expression EQ_OP   binary_expression
    | binary_expression NE_OP   binary_expression
    | binary_expression '<'     binary_expression
    | binary_expression '>'     binary_expression
    | binary_expression LE_OP   binary_expression
    | binary_expression GE_OP   binary_expression  
    | binary_expression LEFT_OP binary_expression
    | binary_expression RIGHT_OP   binary_expression  
    | binary_expression '+'     binary_expression
    | binary_expression '-'     binary_expression 
    | binary_expression '*'     binary_expression
    | binary_expression '/'     binary_expression 
    | binary_expression '%'     binary_expression 


conditional_expression
	: binary_expression
	| binary_expression '?' expression ':' binary_expression
	;

expression
	: conditional_expression
	| unary_expression assignment_operator expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

constant_expression
	: conditional_expression
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: type_specifier declarator ';'
	| struct_declaration_list type_specifier declarator ';'
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: type_specifier
	| type_specifier pointer
	;


compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

statement
	: compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}