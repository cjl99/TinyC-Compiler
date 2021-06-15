%option yylineno 
%{
#include <stdio.h>
#include "ast/Ast.h"
#include "y.tab.hpp"

extern void yyerror(const char *);  /* prints grammar violation message */
extern int sym_type(const char *);  /* returns type from symbol table */

// #define DEBUG_LEXER
#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */
#define YYSTYPE char*

#ifdef DEBUG_LEXER
#define RETURN_TOKEN(X) printf(#X); printf("\n"); return(X);
#else
#define RETURN_TOKEN(X) return(X);
#endif

void count();
static void comment(void);
static int check_type(void);
%}
O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
WS  [ \t\v\n\f]

%%
^"/*"[^*]*|[*]*"*/"    { /* DO NOTHING */ }
"//".*                  { /* consume //-comment */ }
"break"					{ yylval.str = strdup(yytext); RETURN_TOKEN(BREAK); }
"char"					{ yylval.str = strdup(yytext);RETURN_TOKEN(CHAR); }
"continue"				{ yylval.str = strdup(yytext);RETURN_TOKEN(CONTINUE); }
"double"				{ yylval.str = strdup(yytext);RETURN_TOKEN(DOUBLE); }
"else"					{ yylval.str = strdup(yytext);RETURN_TOKEN(ELSE); }
"extern"					{ yylval.str = strdup(yytext);RETURN_TOKEN(EXTERN); }
"float"					{ yylval.str = strdup(yytext);RETURN_TOKEN(FLOAT); }
"for"					{ yylval.str = strdup(yytext); RETURN_TOKEN(FOR); }
"if"					{ yylval.str = strdup(yytext);RETURN_TOKEN(IF); }
"int"					{ yylval.str = strdup(yytext);RETURN_TOKEN(INT); }
"long"					{ yylval.str = strdup(yytext);RETURN_TOKEN(LONG); }
"return"				{ yylval.str = strdup(yytext);RETURN_TOKEN(RETURN); }
"short"					{ yylval.str = strdup(yytext);RETURN_TOKEN(SHORT); }
"struct"				{ yylval.str = strdup(yytext);RETURN_TOKEN(STRUCT); }
"void"					{ yylval.str = strdup(yytext);RETURN_TOKEN(VOID); }
"while"					{ yylval.str = strdup(yytext);RETURN_TOKEN(WHILE); }

{L}{A}*					{ yylval.str = strdup(yytext); RETURN_TOKEN(IDENTIFIER); }
{HP}{H}+{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
{NZ}{D}*{IS}?			{yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
"0"{O}*{IS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
{CP}?"'"(\\.|[^\\'])+"'"		{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }

{D}+{E}{FS}?				{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
{D}*"."{D}+{E}?{FS}?		{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }
{D}+"."{E}?{FS}?			{ yylval.str = strdup(yytext); RETURN_TOKEN(CONSTANT); }

{SP}?\"(\\.|[^\\"])*\"     { yylval.str = strdup(yytext); RETURN_TOKEN(STRING_LITERAL); }

">>="					{ yylval.str = strdup(yytext); RETURN_TOKEN(RIGHT_ASSIGN); }
"<<="					{ yylval.str = strdup(yytext); RETURN_TOKEN(LEFT_ASSIGN); }
"+="					{ yylval.str = strdup(yytext); RETURN_TOKEN(ADD_ASSIGN); }
"-="					{ yylval.str = strdup(yytext); RETURN_TOKEN(SUB_ASSIGN); }
"*="					{ yylval.str = strdup(yytext); RETURN_TOKEN(MUL_ASSIGN); }
"/="					{ yylval.str = strdup(yytext); RETURN_TOKEN(DIV_ASSIGN); }
"%="					{ yylval.str = strdup(yytext); RETURN_TOKEN(MOD_ASSIGN); }
"&="					{ yylval.str = strdup(yytext); RETURN_TOKEN(AND_ASSIGN); }
"^="					{ yylval.str = strdup(yytext); RETURN_TOKEN(XOR_ASSIGN); }
"|="					{ yylval.str = strdup(yytext); RETURN_TOKEN(OR_ASSIGN); }

">>"					{ yylval.str = strdup(yytext); RETURN_TOKEN(RIGHT_OP); }
"<<"					{ yylval.str = strdup(yytext); RETURN_TOKEN(LEFT_OP); }
"++"					{ yylval.str = strdup(yytext); RETURN_TOKEN(INC_OP); }
"--"					{ yylval.str = strdup(yytext); RETURN_TOKEN(DEC_OP); }
"->"					{ yylval.str = strdup(yytext); RETURN_TOKEN(PTR_OP); }
"&&"					{ yylval.str = strdup(yytext); RETURN_TOKEN(AND_OP); }
"||"					{ yylval.str = strdup(yytext); RETURN_TOKEN(OR_OP); }
"<="					{ yylval.str = strdup(yytext);RETURN_TOKEN(LE_OP); }
">="				    { yylval.str = strdup(yytext);RETURN_TOKEN(GE_OP); }
"=="				    { yylval.str = strdup(yytext);RETURN_TOKEN(EQ_OP); }
"!="				    { yylval.str = strdup(yytext);RETURN_TOKEN(NE_OP); }

";"					{ yylval.str = strdup(yytext);RETURN_TOKEN(';'); }
("{"|"<%")			{ yylval.str = strdup(yytext);RETURN_TOKEN('{'); }
("}"|"%>")			{ yylval.str = strdup(yytext);RETURN_TOKEN('}'); }
","					{ yylval.str = strdup(yytext);RETURN_TOKEN(','); }
":"					{ yylval.str = strdup(yytext);RETURN_TOKEN(':'); }
"="					{ yylval.str = strdup(yytext);RETURN_TOKEN('='); }
"("					{ yylval.str = strdup(yytext);RETURN_TOKEN('('); }
")"					{ yylval.str = strdup(yytext);RETURN_TOKEN(')'); }
("["|"<:")			{ yylval.str = strdup(yytext);RETURN_TOKEN('['); }
("]"|":>")			{ yylval.str = strdup(yytext);RETURN_TOKEN(']'); }
"."					{ yylval.str = strdup(yytext);RETURN_TOKEN('.'); }
"&"					{ yylval.str = strdup(yytext);RETURN_TOKEN('&'); }
"!"					{ yylval.str = strdup(yytext);RETURN_TOKEN('!'); }
"~"					{ yylval.str = strdup(yytext);RETURN_TOKEN('~'); }
"-"					{ yylval.str = strdup(yytext);RETURN_TOKEN('-'); }
"+"					{ yylval.str = strdup(yytext);RETURN_TOKEN('+'); }
"*"					{ yylval.str = strdup(yytext);RETURN_TOKEN('*'); }
"/"					{ yylval.str = strdup(yytext);RETURN_TOKEN('/'); }
"%"					{ yylval.str = strdup(yytext);RETURN_TOKEN('%'); }
"<"					{ yylval.str = strdup(yytext);RETURN_TOKEN('<'); }
">"					{ yylval.str = strdup(yytext);RETURN_TOKEN('>'); }
"^"					{ yylval.str = strdup(yytext);RETURN_TOKEN('^'); }
"|"					{ yylval.str = strdup(yytext);RETURN_TOKEN('|'); }
"?"					{ yylval.str = strdup(yytext);RETURN_TOKEN('?'); }
{WS}+				{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%
#ifdef DEBUG_LEXER
// int main(int argc, char** argv) {
//     if(argc==2){
//         FILE* file = fopen(argv[1], "r");
//         if(!file) {
//             fprintf(stderr, "Open failed!\n");
//             exit(1);
//         }
//         yyin = file;
//     }
//     yylex();
//     return 0;
// }
#endif

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}

void yyerror(const char *s) {
    fprintf(stderr, "Lex Error: %s\n", s);
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int column = 0;
void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}