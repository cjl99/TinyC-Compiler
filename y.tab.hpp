/* A Bison parser, made by GNU Bison 3.6.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CONSTANT = 259,                /* CONSTANT  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    PTR_OP = 261,                  /* PTR_OP  */
    INC_OP = 262,                  /* INC_OP  */
    DEC_OP = 263,                  /* DEC_OP  */
    LEFT_OP = 264,                 /* LEFT_OP  */
    RIGHT_OP = 265,                /* RIGHT_OP  */
    LE_OP = 266,                   /* LE_OP  */
    GE_OP = 267,                   /* GE_OP  */
    EQ_OP = 268,                   /* EQ_OP  */
    NE_OP = 269,                   /* NE_OP  */
    AND_OP = 270,                  /* AND_OP  */
    OR_OP = 271,                   /* OR_OP  */
    MUL_ASSIGN = 272,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 273,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 274,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 275,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 276,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 277,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 278,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 279,              /* AND_ASSIGN  */
    XOR_ASSIGN = 280,              /* XOR_ASSIGN  */
    OR_ASSIGN = 281,               /* OR_ASSIGN  */
    TYPE_NAME = 282,               /* TYPE_NAME  */
    CHAR = 283,                    /* CHAR  */
    SHORT = 284,                   /* SHORT  */
    INT = 285,                     /* INT  */
    LONG = 286,                    /* LONG  */
    FLOAT = 287,                   /* FLOAT  */
    DOUBLE = 288,                  /* DOUBLE  */
    VOID = 289,                    /* VOID  */
    STRUCT = 290,                  /* STRUCT  */
    IF = 291,                      /* IF  */
    ELSE = 292,                    /* ELSE  */
    WHILE = 293,                   /* WHILE  */
    DO = 294,                      /* DO  */
    FOR = 295,                     /* FOR  */
    CONTINUE = 296,                /* CONTINUE  */
    BREAK = 297,                   /* BREAK  */
    RETURN = 298                   /* RETURN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define PTR_OP 261
#define INC_OP 262
#define DEC_OP 263
#define LEFT_OP 264
#define RIGHT_OP 265
#define LE_OP 266
#define GE_OP 267
#define EQ_OP 268
#define NE_OP 269
#define AND_OP 270
#define OR_OP 271
#define MUL_ASSIGN 272
#define DIV_ASSIGN 273
#define MOD_ASSIGN 274
#define ADD_ASSIGN 275
#define SUB_ASSIGN 276
#define LEFT_ASSIGN 277
#define RIGHT_ASSIGN 278
#define AND_ASSIGN 279
#define XOR_ASSIGN 280
#define OR_ASSIGN 281
#define TYPE_NAME 282
#define CHAR 283
#define SHORT 284
#define INT 285
#define LONG 286
#define FLOAT 287
#define DOUBLE 288
#define VOID 289
#define STRUCT 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define DO 294
#define FOR 295
#define CONTINUE 296
#define BREAK 297
#define RETURN 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "./parser/grammar.y"

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


#line 196 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
