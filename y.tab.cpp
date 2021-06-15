/* A Bison parser, made by GNU Bison 3.6.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./parser/grammar.y"

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


#line 96 "y.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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


#line 278 "y.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_PTR_OP = 6,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 7,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 8,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 9,                    /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 10,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 11,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 12,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 13,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 14,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 15,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 16,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 17,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 18,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 19,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 20,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 21,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 22,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 23,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 24,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 25,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 26,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 27,                 /* TYPE_NAME  */
  YYSYMBOL_CHAR = 28,                      /* CHAR  */
  YYSYMBOL_SHORT = 29,                     /* SHORT  */
  YYSYMBOL_INT = 30,                       /* INT  */
  YYSYMBOL_LONG = 31,                      /* LONG  */
  YYSYMBOL_FLOAT = 32,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 33,                    /* DOUBLE  */
  YYSYMBOL_VOID = 34,                      /* VOID  */
  YYSYMBOL_STRUCT = 35,                    /* STRUCT  */
  YYSYMBOL_IF = 36,                        /* IF  */
  YYSYMBOL_ELSE = 37,                      /* ELSE  */
  YYSYMBOL_WHILE = 38,                     /* WHILE  */
  YYSYMBOL_DO = 39,                        /* DO  */
  YYSYMBOL_FOR = 40,                       /* FOR  */
  YYSYMBOL_CONTINUE = 41,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 42,                     /* BREAK  */
  YYSYMBOL_RETURN = 43,                    /* RETURN  */
  YYSYMBOL_44_ = 44,                       /* '&'  */
  YYSYMBOL_45_ = 45,                       /* '*'  */
  YYSYMBOL_46_ = 46,                       /* '+'  */
  YYSYMBOL_47_ = 47,                       /* '-'  */
  YYSYMBOL_48_ = 48,                       /* '!'  */
  YYSYMBOL_49_ = 49,                       /* '~'  */
  YYSYMBOL_50_ = 50,                       /* '|'  */
  YYSYMBOL_51_ = 51,                       /* '^'  */
  YYSYMBOL_52_ = 52,                       /* '<'  */
  YYSYMBOL_53_ = 53,                       /* '>'  */
  YYSYMBOL_54_ = 54,                       /* '/'  */
  YYSYMBOL_55_ = 55,                       /* '%'  */
  YYSYMBOL_56_ = 56,                       /* '('  */
  YYSYMBOL_57_ = 57,                       /* ')'  */
  YYSYMBOL_58_ = 58,                       /* ';'  */
  YYSYMBOL_59_ = 59,                       /* ','  */
  YYSYMBOL_60_ = 60,                       /* '='  */
  YYSYMBOL_61_ = 61,                       /* '{'  */
  YYSYMBOL_62_ = 62,                       /* '}'  */
  YYSYMBOL_63_ = 63,                       /* '['  */
  YYSYMBOL_64_ = 64,                       /* ']'  */
  YYSYMBOL_65_ = 65,                       /* '.'  */
  YYSYMBOL_66_ = 66,                       /* '?'  */
  YYSYMBOL_67_ = 67,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 68,                  /* $accept  */
  YYSYMBOL_program = 69,                   /* program  */
  YYSYMBOL_external_declaration = 70,      /* external_declaration  */
  YYSYMBOL_function_definition = 71,       /* function_definition  */
  YYSYMBOL_declaration = 72,               /* declaration  */
  YYSYMBOL_type_specifier = 73,            /* type_specifier  */
  YYSYMBOL_init_declarator_list = 74,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 75,           /* init_declarator  */
  YYSYMBOL_initializer = 76,               /* initializer  */
  YYSYMBOL_initializer_list = 77,          /* initializer_list  */
  YYSYMBOL_declarator = 78,                /* declarator  */
  YYSYMBOL_direct_declarator = 79,         /* direct_declarator  */
  YYSYMBOL_pointer = 80,                   /* pointer  */
  YYSYMBOL_parameter_list = 81,            /* parameter_list  */
  YYSYMBOL_primary_expression = 82,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 83,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 84,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 85,          /* unary_expression  */
  YYSYMBOL_unary_operator = 86,            /* unary_operator  */
  YYSYMBOL_cast_expression = 87,           /* cast_expression  */
  YYSYMBOL_binary_expression = 88,         /* binary_expression  */
  YYSYMBOL_conditional_expression = 89,    /* conditional_expression  */
  YYSYMBOL_expression = 90,                /* expression  */
  YYSYMBOL_assignment_operator = 91,       /* assignment_operator  */
  YYSYMBOL_struct_specifier = 92,          /* struct_specifier  */
  YYSYMBOL_struct_declaration_list = 93,   /* struct_declaration_list  */
  YYSYMBOL_identifier_list = 94,           /* identifier_list  */
  YYSYMBOL_type_name = 95,                 /* type_name  */
  YYSYMBOL_statement_list = 96,            /* statement_list  */
  YYSYMBOL_declaration_list = 97,          /* declaration_list  */
  YYSYMBOL_compound_statement = 98,        /* compound_statement  */
  YYSYMBOL_statement = 99,                 /* statement  */
  YYSYMBOL_expression_statement = 100,     /* expression_statement  */
  YYSYMBOL_selection_statement = 101,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 102,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 103            /* jump_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   730

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,     2,     2,    55,    44,     2,
      56,    57,    45,    46,    59,    47,    65,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    58,
      52,    60,    53,    66,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    64,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,    50,    62,    49,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   137,   144,   147,   153,   156,   162,   168,
     169,   170,   171,   172,   173,   174,   175,   179,   183,   190,
     193,   199,   202,   205,   211,   215,   222,   225,   231,   234,
     238,   242,   249,   252,   259,   263,   267,   275,   278,   281,
     284,   290,   293,   296,   299,   302,   305,   308,   311,   317,
     321,   328,   331,   334,   337,   343,   346,   349,   352,   355,
     358,   364,   367,   373,   376,   379,   382,   385,   388,   391,
     394,   397,   400,   403,   406,   409,   412,   415,   418,   421,
     424,   427,   433,   436,   442,   446,   453,   456,   459,   462,
     465,   468,   471,   474,   477,   480,   483,   489,   492,   495,
     501,   505,   512,   516,   523,   526,   532,   536,   543,   547,
     555,   558,   561,   564,   570,   571,   572,   573,   574,   578,
     579,   583,   586,   592,   595,   598,   604,   605,   606,   607
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "CHAR", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "VOID",
  "STRUCT", "IF", "ELSE", "WHILE", "DO", "FOR", "CONTINUE", "BREAK",
  "RETURN", "'&'", "'*'", "'+'", "'-'", "'!'", "'~'", "'|'", "'^'", "'<'",
  "'>'", "'/'", "'%'", "'('", "')'", "';'", "','", "'='", "'{'", "'}'",
  "'['", "']'", "'.'", "'?'", "':'", "$accept", "program",
  "external_declaration", "function_definition", "declaration",
  "type_specifier", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", "declarator", "direct_declarator",
  "pointer", "parameter_list", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "binary_expression", "conditional_expression",
  "expression", "assignment_operator", "struct_specifier",
  "struct_declaration_list", "identifier_list", "type_name",
  "statement_list", "declaration_list", "compound_statement", "statement",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    38,    42,    43,    45,    33,   126,
     124,    94,    60,    62,    47,    37,    40,    41,    59,    44,
      61,   123,   125,    91,    93,    46,    63,    58
};
#endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     211,  -137,  -137,  -137,  -137,  -137,  -137,  -137,     5,   282,
    -137,  -137,  -137,    10,  -137,   -38,   211,  -137,  -137,   -41,
      19,    15,  -137,     0,   -46,    76,   211,    11,   414,   211,
    -137,  -137,    11,   339,    85,     3,    33,   -46,   661,  -137,
      39,    96,  -137,    11,    11,   -35,  -137,  -137,  -137,  -137,
     528,   528,  -137,  -137,  -137,  -137,  -137,  -137,   515,   339,
    -137,  -137,    45,   238,   534,  -137,   419,  -137,  -137,  -137,
      21,    49,  -137,   211,  -137,  -137,    51,  -137,    58,   211,
     534,  -137,  -137,    19,    63,    64,  -137,     6,   120,  -137,
    -137,   454,   534,   124,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,  -137,  -137,  -137,   534,  -137,  -137,   534,   534,
     534,   534,   534,   534,   534,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   534,  -137,   135,  -137,
      25,  -137,   176,  -137,    11,  -137,  -137,   534,    99,  -137,
    -137,  -137,    55,  -137,    60,  -137,  -137,    71,    71,    40,
      40,   675,   675,   594,   582,   664,  -137,    16,    16,   606,
     653,    40,    40,  -137,  -137,    72,  -137,    58,    93,    94,
      95,    83,    98,   433,  -137,  -137,  -137,    11,   100,   292,
     245,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,   534,  -137,   534,  -137,   534,   534,   448,  -137,
    -137,  -137,   104,  -137,  -137,  -137,  -137,  -137,   319,  -137,
     121,    97,   112,   448,  -137,  -137,   366,   366,   509,   115,
    -137,   366,   125,   366,  -137,   366,  -137,  -137
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,    11,    12,    13,    14,    15,     9,     0,     0,
       2,     4,     5,     0,    16,    99,     0,     1,     3,    28,
      32,     0,    17,    19,    27,     0,     0,     0,     0,    34,
      33,     8,     0,     0,     0,     0,    28,    26,     0,    28,
       0,     0,    98,     0,     0,     0,    18,    37,    38,    39,
       0,     0,    55,    56,    57,    58,    60,    59,     0,     0,
      20,    41,    51,    61,     0,    63,    82,    84,    21,   102,
       0,     0,    30,    34,    97,   100,     0,    35,     0,     0,
       0,    52,    53,   104,     0,     0,    24,     0,     0,    47,
      48,     0,     0,     0,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    86,     0,    61,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,    29,
       0,   101,     0,     6,     0,   105,    40,     0,     0,    22,
      46,    43,     0,    49,     0,    45,    85,    75,    76,    73,
      74,    69,    70,    65,    64,    68,    79,    77,    78,    66,
      67,    71,    72,    80,    81,     0,   103,     0,     0,     0,
       0,     0,     0,     0,   119,   110,   108,     0,     0,     0,
       0,   114,   106,   115,   116,   117,   118,    36,    62,    23,
      25,    44,     0,    42,     0,     7,     0,     0,     0,   126,
     127,   128,     0,   120,   111,   107,   112,   109,     0,    50,
      83,     0,     0,     0,   129,   113,     0,     0,     0,   121,
     123,     0,     0,     0,   124,     0,   122,   125
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,   144,  -137,  -123,   -10,  -137,   145,   -57,  -137,
     -23,   -14,    -8,    84,  -137,  -137,  -137,    78,  -137,   -61,
     -79,  -137,   -33,  -137,  -137,   152,  -137,  -137,    46,  -137,
     -77,  -125,  -136,  -137,  -137,  -137
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    21,    22,    60,    87,
      23,    24,    41,    45,    61,    62,   142,    63,    64,    65,
      66,    67,   178,   105,    14,    28,    70,    85,   179,   180,
     181,   182,   183,   184,   185,   186
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      68,   133,    86,   107,    40,    25,    27,    71,    15,   176,
      34,    37,    30,    19,    39,    29,    27,    35,    43,    44,
      76,    77,    78,    26,    79,    84,    68,    37,    43,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,    84,    83,   108,
     109,    88,    89,    90,   205,    20,    20,   207,   143,   144,
      33,   117,   213,    44,    20,   138,    16,    72,   139,   134,
     124,   125,   146,    31,    32,   135,   188,   218,   127,    36,
     128,   190,   167,   205,    79,   117,   118,   119,    69,    73,
     195,   219,   220,   165,   124,   125,   224,    75,   226,    39,
     227,    91,    47,    48,    49,    68,    50,    51,    92,   131,
      93,   187,   191,   129,   192,   210,   117,   118,   119,   132,
     136,   137,   177,   140,   193,   124,   125,   145,    81,    82,
     108,   109,   110,   111,   112,   113,   114,   115,   166,   194,
     202,   199,   106,    52,    53,    54,    55,    56,    57,   196,
     197,   198,   223,    18,   216,    58,   200,   130,   203,   209,
      59,   189,   214,   211,   212,   116,   117,   118,   119,   217,
     177,   120,   121,   122,   123,   124,   125,    46,    38,    47,
      48,    49,   225,    50,    51,   222,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,     1,     2,     3,     4,     5,     6,
       7,     8,   168,     0,   169,   106,   170,   171,   172,   173,
      52,    53,    54,    55,    56,    57,   208,     0,     0,     0,
       0,     0,    58,     0,   174,     0,     0,   132,   175,     1,
       2,     3,     4,     5,     6,     7,     8,     0,    47,    48,
      49,     0,    50,    51,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,   106,     1,     2,     3,     4,     5,     6,     7,
       8,   168,    17,   169,     0,   170,   171,   172,   173,    52,
      53,    54,    55,    56,    57,    47,    48,    49,   104,    50,
      51,    58,     0,   174,     0,     0,   132,   206,     0,     0,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     0,
       0,     0,    47,    48,    49,     0,    50,    51,   168,     0,
     169,     0,   170,   171,   172,   173,    52,    53,    54,    55,
      56,    57,    47,    48,    49,     0,    50,    51,    58,     0,
     174,     0,     0,   132,   204,   168,     0,   169,     0,   170,
     171,   172,   173,    52,    53,    54,    55,    56,    57,    47,
      48,    49,     0,    50,    51,    58,     0,   174,     0,     0,
     132,   215,     0,    52,    53,    54,    55,    56,    57,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
      59,     0,   168,     0,   169,     0,   170,   171,   172,   173,
      52,    53,    54,    55,    56,    57,     0,     0,     0,     0,
       0,     0,    58,     0,   174,     0,     0,   132,   108,   109,
     110,   111,   112,   113,   114,   115,    47,    48,    49,     0,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     8,
       0,    47,    48,    49,     0,    50,    51,    47,    48,    49,
       0,    50,    51,   116,   117,   118,   119,     0,     0,   120,
     121,   122,   123,   124,   125,     0,    42,    52,    53,    54,
      55,    56,    57,     0,     0,   126,     0,     0,     0,    58,
       0,   201,    52,    53,    54,    55,    56,    57,    52,    53,
      54,    55,    56,    57,    58,     0,   174,     0,     0,     0,
      58,   141,    47,    48,    49,     0,    50,    51,    47,    48,
      49,     0,    50,    51,     0,     0,     0,     0,     0,     0,
       0,    47,    48,    49,     0,    50,    51,    47,    48,    49,
       0,    50,    51,     1,     2,     3,     4,     5,     6,     7,
       8,     0,     0,    52,    53,    54,    55,    56,    57,    52,
      53,    54,    55,    56,    57,    58,   221,     0,     0,     0,
       0,    58,    52,    53,    54,    55,    56,    57,    52,    53,
      54,    55,    56,    57,    80,     0,     0,     0,     0,     0,
      58,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
     113,     0,     0,     0,     0,     0,   116,   117,   118,   119,
       0,     0,   120,   121,   122,   123,   124,   125,   116,   117,
     118,   119,     0,     0,   120,   121,   122,   123,   124,   125,
     116,   117,   118,   119,     0,     0,     0,   121,   122,   123,
     124,   125,   108,   109,   110,   111,   112,   113,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,     0,   108,   109,   110,   111,     0,     1,
       2,     3,     4,     5,     6,     7,     8,   116,   117,   118,
     119,     0,     0,     0,     0,   122,   123,   124,   125,   117,
     118,   119,     0,     0,     0,     0,   122,   123,   124,   125,
     117,   118,   119,    74,     0,     0,     0,   122,   123,   124,
     125
};

static const yytype_int16 yycheck[] =
{
      33,    78,    59,    64,    27,    13,    16,     4,     3,   132,
      56,    25,    20,     3,     3,    56,    26,    63,    28,    29,
      43,    44,    57,    61,    59,    58,    59,    41,    38,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    80,    58,     9,
      10,     6,     7,     8,   179,    45,    45,   180,    91,    92,
      60,    45,   198,    73,    45,    59,    61,    64,    62,    79,
      54,    55,   105,    58,    59,    83,   137,   213,    57,     3,
      59,   138,    57,   208,    59,    45,    46,    47,     3,    56,
     167,   216,   217,   126,    54,    55,   221,    58,   223,     3,
     225,    56,     3,     4,     5,   138,     7,     8,    63,    58,
      65,   134,    57,    64,    59,   194,    45,    46,    47,    61,
      57,    57,   132,     3,    64,    54,    55,     3,    50,    51,
       9,    10,    11,    12,    13,    14,    15,    16,     3,    67,
     173,    58,    64,    44,    45,    46,    47,    48,    49,    56,
      56,    56,    37,     9,    57,    56,    58,    73,    58,   192,
      61,    62,    58,   196,   197,    44,    45,    46,    47,    57,
     180,    50,    51,    52,    53,    54,    55,    32,    26,     3,
       4,     5,    57,     7,     8,   218,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,   137,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,   180,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    -1,    -1,    61,    62,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,     3,     4,
       5,    -1,     7,     8,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   194,    28,    29,    30,    31,    32,    33,    34,
      35,    36,     0,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     3,     4,     5,    60,     7,
       8,    56,    -1,    58,    -1,    -1,    61,    62,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,     8,    36,    -1,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,     3,     4,     5,    -1,     7,     8,    56,    -1,
      58,    -1,    -1,    61,    62,    36,    -1,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,     3,
       4,     5,    -1,     7,     8,    56,    -1,    58,    -1,    -1,
      61,    62,    -1,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      61,    -1,    36,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,    -1,    -1,    61,     9,    10,
      11,    12,    13,    14,    15,    16,     3,     4,     5,    -1,
       7,     8,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,     3,     4,     5,    -1,     7,     8,     3,     4,     5,
      -1,     7,     8,    44,    45,    46,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    -1,    62,    44,    45,    46,
      47,    48,    49,    -1,    -1,    66,    -1,    -1,    -1,    56,
      -1,    58,    44,    45,    46,    47,    48,    49,    44,    45,
      46,    47,    48,    49,    56,    -1,    58,    -1,    -1,    -1,
      56,    57,     3,     4,     5,    -1,     7,     8,     3,     4,
       5,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,     8,     3,     4,     5,
      -1,     7,     8,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    44,    45,    46,    47,    48,    49,    44,
      45,    46,    47,    48,    49,    56,    57,    -1,    -1,    -1,
      -1,    56,    44,    45,    46,    47,    48,    49,    44,    45,
      46,    47,    48,    49,    56,    -1,    -1,    -1,    -1,    -1,
      56,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    50,    51,    52,    53,    54,    55,    44,    45,
      46,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      44,    45,    46,    47,    -1,    -1,    -1,    51,    52,    53,
      54,    55,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      45,    46,    47,    62,    -1,    -1,    -1,    52,    53,    54,
      55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    69,
      70,    71,    72,    73,    92,     3,    61,     0,    70,     3,
      45,    74,    75,    78,    79,    80,    61,    73,    93,    56,
      80,    58,    59,    60,    56,    63,     3,    79,    93,     3,
      78,    80,    62,    73,    73,    81,    75,     3,     4,     5,
       7,     8,    44,    45,    46,    47,    48,    49,    56,    61,
      76,    82,    83,    85,    86,    87,    88,    89,    90,     3,
      94,     4,    64,    56,    62,    58,    78,    78,    57,    59,
      56,    85,    85,    73,    90,    95,    76,    77,     6,     7,
       8,    56,    63,    65,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    60,    91,    85,    87,     9,    10,
      11,    12,    13,    14,    15,    16,    44,    45,    46,    47,
      50,    51,    52,    53,    54,    55,    66,    57,    59,    64,
      81,    58,    61,    98,    73,    80,    57,    57,    59,    62,
       3,    57,    84,    90,    90,     3,    90,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    90,     3,    57,    36,    38,
      40,    41,    42,    43,    58,    62,    72,    73,    90,    96,
      97,    98,    99,   100,   101,   102,   103,    78,    87,    62,
      76,    57,    59,    64,    67,    98,    56,    56,    56,    58,
      58,    58,    90,    58,    62,    99,    62,    72,    96,    90,
      88,    90,    90,   100,    58,    62,    57,    57,   100,    99,
      99,    57,    90,    37,    99,    57,    99,    99
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    71,    71,    72,    73,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    76,    76,    77,    77,    78,    78,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      84,    85,    85,    85,    85,    86,    86,    86,    86,    86,
      86,    87,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    89,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      93,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     100,   101,   101,   102,   102,   102,   103,   103,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     6,     7,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     4,     1,     3,     2,     1,     1,     4,
       3,     4,     1,     2,     0,     2,     4,     1,     1,     1,
       3,     1,     4,     3,     4,     3,     3,     2,     2,     1,
       3,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     2,
       3,     4,     1,     3,     1,     2,     1,     2,     1,     2,
       2,     3,     3,     4,     1,     1,     1,     1,     1,     1,
       2,     5,     7,     5,     6,     7,     2,     2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 131 "./parser/grammar.y"
                              {
	    (yyval.ast_program) = new AstProgram();
	    (yyval.ast_program)->addExternalExpr((yyvsp[0].ast_ext_expr));
	    astRoot = (yyval.ast_program);
	    printf("Program is parsed successfully!\n");
	}
#line 1639 "y.tab.cpp"
    break;

  case 3:
#line 137 "./parser/grammar.y"
                                       {
	    (yyval.ast_program) = (yyvsp[-1].ast_program);
	    (yyval.ast_program)->addExternalExpr((yyvsp[0].ast_ext_expr));
	}
#line 1648 "y.tab.cpp"
    break;

  case 4:
#line 144 "./parser/grammar.y"
                             {
	    (yyval.ast_ext_expr) = new AstExternalExpr((yyvsp[0].ast_func_def), nullptr);
	}
#line 1656 "y.tab.cpp"
    break;

  case 5:
#line 147 "./parser/grammar.y"
                     {
	    (yyval.ast_ext_expr) = new AstExternalExpr(nullptr, (yyvsp[0].ast_declaration));
	}
#line 1664 "y.tab.cpp"
    break;

  case 6:
#line 153 "./parser/grammar.y"
                                                                             {
		(yyval.ast_func_def) = new AstFunDef((yyvsp[-5].ast_type_spec), nullptr, (yyvsp[-4].str), (yyvsp[-2].ast_param_list), (yyvsp[0].ast_compound_stmt));
	}
#line 1672 "y.tab.cpp"
    break;

  case 7:
#line 156 "./parser/grammar.y"
                                                                                     {
		(yyval.ast_func_def) = new AstFunDef((yyvsp[-6].ast_type_spec), (yyvsp[-5].ast_pointer), (yyvsp[-4].str), (yyvsp[-2].ast_param_list), (yyvsp[0].ast_compound_stmt));
	}
#line 1680 "y.tab.cpp"
    break;

  case 8:
#line 162 "./parser/grammar.y"
                                                  {
		(yyval.ast_declaration) = new AstDeclaration((yyvsp[-2].ast_type_spec), (yyvsp[-1].ast_init_decl_list));
	}
#line 1688 "y.tab.cpp"
    break;

  case 9:
#line 168 "./parser/grammar.y"
              { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1694 "y.tab.cpp"
    break;

  case 10:
#line 169 "./parser/grammar.y"
              { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1700 "y.tab.cpp"
    break;

  case 11:
#line 170 "./parser/grammar.y"
               { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1706 "y.tab.cpp"
    break;

  case 12:
#line 171 "./parser/grammar.y"
             { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1712 "y.tab.cpp"
    break;

  case 13:
#line 172 "./parser/grammar.y"
              { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1718 "y.tab.cpp"
    break;

  case 14:
#line 173 "./parser/grammar.y"
               { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1724 "y.tab.cpp"
    break;

  case 15:
#line 174 "./parser/grammar.y"
                { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].str)); }
#line 1730 "y.tab.cpp"
    break;

  case 16:
#line 175 "./parser/grammar.y"
                          { (yyval.ast_type_spec) = new AstSpec((yyvsp[0].ast_struct_spec)->getName()); }
#line 1736 "y.tab.cpp"
    break;

  case 17:
#line 179 "./parser/grammar.y"
                          {
		(yyval.ast_init_decl_list) = new AstInitDeclList();
		(yyval.ast_init_decl_list)->addInitDeclarator((yyvsp[0].ast_init_declarator));
	}
#line 1745 "y.tab.cpp"
    break;

  case 18:
#line 183 "./parser/grammar.y"
                                                   {
		(yyvsp[-2].ast_init_decl_list)->addInitDeclarator((yyvsp[0].ast_init_declarator));
		(yyval.ast_init_decl_list) = (yyvsp[-2].ast_init_decl_list);
	}
#line 1754 "y.tab.cpp"
    break;

  case 19:
#line 190 "./parser/grammar.y"
                     {
		(yyval.ast_init_declarator) = new AstInitDeclarator((yyvsp[0].ast_declarator), nullptr);
	}
#line 1762 "y.tab.cpp"
    break;

  case 20:
#line 193 "./parser/grammar.y"
                                     {
		(yyval.ast_init_declarator) = new AstInitDeclarator((yyvsp[-2].ast_declarator), (yyvsp[0].ast_init));
	}
#line 1770 "y.tab.cpp"
    break;

  case 21:
#line 199 "./parser/grammar.y"
                     {
		(yyval.ast_init) = new AstInitializer((yyvsp[0].ast_expr), nullptr);
	}
#line 1778 "y.tab.cpp"
    break;

  case 22:
#line 202 "./parser/grammar.y"
                                   {
		(yyval.ast_init) = new AstInitializer(nullptr, (yyvsp[-1].ast_init_list));
	}
#line 1786 "y.tab.cpp"
    break;

  case 23:
#line 205 "./parser/grammar.y"
                                       {
		(yyval.ast_init) = new AstInitializer(nullptr, (yyvsp[-2].ast_init_list));
	}
#line 1794 "y.tab.cpp"
    break;

  case 24:
#line 211 "./parser/grammar.y"
                      {
		(yyval.ast_init_list) = new AstInitList();
		(yyval.ast_init_list)->addInitializer((yyvsp[0].ast_init));
	}
#line 1803 "y.tab.cpp"
    break;

  case 25:
#line 215 "./parser/grammar.y"
                                           {
		(yyvsp[-2].ast_init_list)->addInitializer((yyvsp[0].ast_init));
		(yyval.ast_init_list) = (yyvsp[-2].ast_init_list);
	}
#line 1812 "y.tab.cpp"
    break;

  case 26:
#line 222 "./parser/grammar.y"
                                    {
		(yyval.ast_declarator) = new AstDeclarator((yyvsp[-1].ast_pointer), (yyvsp[0].ast_direct_declarator));
	}
#line 1820 "y.tab.cpp"
    break;

  case 27:
#line 225 "./parser/grammar.y"
                            {
		(yyval.ast_declarator) = new AstDeclarator(nullptr, (yyvsp[0].ast_direct_declarator));
	}
#line 1828 "y.tab.cpp"
    break;

  case 28:
#line 231 "./parser/grammar.y"
                     {
		(yyval.ast_direct_declarator) = new AstDirectDeclarator((yyvsp[0].str));
	}
#line 1836 "y.tab.cpp"
    break;

  case 29:
#line 234 "./parser/grammar.y"
                                             {
		(yyvsp[-3].ast_direct_declarator)->addToDirectDecl(1, (yyvsp[-1].str));
		(yyval.ast_direct_declarator) = (yyvsp[-3].ast_direct_declarator);
	}
#line 1845 "y.tab.cpp"
    break;

  case 30:
#line 238 "./parser/grammar.y"
                                    {
		(yyval.ast_direct_declarator)->addToDirectDecl(2, nullptr);
		(yyval.ast_direct_declarator) = (yyvsp[-2].ast_direct_declarator);
	}
#line 1854 "y.tab.cpp"
    break;

  case 31:
#line 242 "./parser/grammar.y"
                                                    {
		(yyvsp[-3].ast_direct_declarator)->addToDirectDecl(3, (yyvsp[-1].ast_id_list));
		(yyval.ast_direct_declarator) = (yyvsp[-3].ast_direct_declarator);
	}
#line 1863 "y.tab.cpp"
    break;

  case 32:
#line 249 "./parser/grammar.y"
              {
		(yyval.ast_pointer) = new AstPointer();
	}
#line 1871 "y.tab.cpp"
    break;

  case 33:
#line 252 "./parser/grammar.y"
                      {
		(yyvsp[0].ast_pointer)->addOneStar();
		(yyval.ast_pointer) = (yyvsp[0].ast_pointer);
	}
#line 1880 "y.tab.cpp"
    break;

  case 34:
#line 259 "./parser/grammar.y"
      {
		(yyval.ast_param_list) = new AstParamList(false);

	}
#line 1889 "y.tab.cpp"
    break;

  case 35:
#line 263 "./parser/grammar.y"
                                {
		(yyval.ast_param_list) = new AstParamList(true);
		(yyval.ast_param_list)->addParam((yyvsp[-1].ast_type_spec), (yyvsp[0].ast_declarator));
	}
#line 1898 "y.tab.cpp"
    break;

  case 36:
#line 267 "./parser/grammar.y"
                                                       {
		(yyvsp[-3].ast_param_list)->addParam((yyvsp[-1].ast_type_spec), (yyvsp[0].ast_declarator));
		(yyval.ast_param_list)  = (yyvsp[-3].ast_param_list);
	}
#line 1907 "y.tab.cpp"
    break;

  case 37:
#line 275 "./parser/grammar.y"
                     {
        (yyval.ast_primary_expr) = new AstPrimaryExpr(1, (yyvsp[0].str));
	}
#line 1915 "y.tab.cpp"
    break;

  case 38:
#line 278 "./parser/grammar.y"
                   {
        (yyval.ast_primary_expr) = new AstPrimaryExpr(2, (yyvsp[0].str));
	}
#line 1923 "y.tab.cpp"
    break;

  case 39:
#line 281 "./parser/grammar.y"
                         {
        (yyval.ast_primary_expr) = new AstPrimaryExpr(3, (yyvsp[0].str));
	}
#line 1931 "y.tab.cpp"
    break;

  case 40:
#line 284 "./parser/grammar.y"
                             {
        (yyval.ast_primary_expr) = new AstPrimaryExpr(4, (yyvsp[-1].ast_expr));
	}
#line 1939 "y.tab.cpp"
    break;

  case 41:
#line 290 "./parser/grammar.y"
                             {
	    (yyval.ast_post_expr) = new AstPostfixExpr(nullptr, "", (yyvsp[0].ast_primary_expr));
	}
#line 1947 "y.tab.cpp"
    break;

  case 42:
#line 293 "./parser/grammar.y"
                                                {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-3].ast_post_expr), "[]", (yyvsp[-1].ast_expr));
	}
#line 1955 "y.tab.cpp"
    break;

  case 43:
#line 296 "./parser/grammar.y"
                                     {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-2].ast_post_expr), "()");
	}
#line 1963 "y.tab.cpp"
    break;

  case 44:
#line 299 "./parser/grammar.y"
                                                              {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-3].ast_post_expr), "()", (yyvsp[-1].ast_arg_expr_list));
	}
#line 1971 "y.tab.cpp"
    break;

  case 45:
#line 302 "./parser/grammar.y"
                                            {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-2].ast_post_expr), ".", (yyvsp[0].str));
	}
#line 1979 "y.tab.cpp"
    break;

  case 46:
#line 305 "./parser/grammar.y"
                                              {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-2].ast_post_expr), (yyvsp[-1].str), (yyvsp[0].str));
	}
#line 1987 "y.tab.cpp"
    break;

  case 47:
#line 308 "./parser/grammar.y"
                                    {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-1].ast_post_expr), (yyvsp[0].str));
	}
#line 1995 "y.tab.cpp"
    break;

  case 48:
#line 311 "./parser/grammar.y"
                                    {
	    (yyval.ast_post_expr) = new AstPostfixExpr((yyvsp[-1].ast_post_expr), (yyvsp[0].str));
	}
#line 2003 "y.tab.cpp"
    break;

  case 49:
#line 317 "./parser/grammar.y"
                     {
	    (yyval.ast_arg_expr_list) = new AstArgExprList();
	    (yyval.ast_arg_expr_list)->addExpression((yyvsp[0].ast_expr));
	}
#line 2012 "y.tab.cpp"
    break;

  case 50:
#line 321 "./parser/grammar.y"
                                                  {
	    (yyvsp[-2].ast_arg_expr_list)->addExpression((yyvsp[0].ast_expr));
	    (yyval.ast_arg_expr_list) = (yyvsp[-2].ast_arg_expr_list);
	}
#line 2021 "y.tab.cpp"
    break;

  case 51:
#line 328 "./parser/grammar.y"
                             {
	    (yyval.ast_unary_expr) = new AstUnaryExpr("", (yyvsp[0].ast_post_expr));
	}
#line 2029 "y.tab.cpp"
    break;

  case 52:
#line 331 "./parser/grammar.y"
                                  {
	    (yyval.ast_unary_expr) = new AstUnaryExpr((yyvsp[-1].str), (yyvsp[0].ast_unary_expr));
	}
#line 2037 "y.tab.cpp"
    break;

  case 53:
#line 334 "./parser/grammar.y"
                                  {
	    (yyval.ast_unary_expr) = new AstUnaryExpr((yyvsp[-1].str), (yyvsp[0].ast_unary_expr));
	}
#line 2045 "y.tab.cpp"
    break;

  case 54:
#line 337 "./parser/grammar.y"
                                         {
	    (yyval.ast_unary_expr) = new AstUnaryExpr((yyvsp[-1].str), (yyvsp[0].ast_cast_expr));
	}
#line 2053 "y.tab.cpp"
    break;

  case 55:
#line 343 "./parser/grammar.y"
              {
	    (yyval.str) = (yyvsp[0].str);
	}
#line 2061 "y.tab.cpp"
    break;

  case 56:
#line 346 "./parser/grammar.y"
              {
        (yyval.str) = (yyvsp[0].str);
	}
#line 2069 "y.tab.cpp"
    break;

  case 57:
#line 349 "./parser/grammar.y"
              {
	    (yyval.str) = (yyvsp[0].str);
	}
#line 2077 "y.tab.cpp"
    break;

  case 58:
#line 352 "./parser/grammar.y"
              {
	    (yyval.str) = (yyvsp[0].str);
	}
#line 2085 "y.tab.cpp"
    break;

  case 59:
#line 355 "./parser/grammar.y"
              {
	    (yyval.str) = (yyvsp[0].str);
	}
#line 2093 "y.tab.cpp"
    break;

  case 60:
#line 358 "./parser/grammar.y"
              {
	    (yyval.str) = (yyvsp[0].str);
	}
#line 2101 "y.tab.cpp"
    break;

  case 61:
#line 364 "./parser/grammar.y"
                           {
	    (yyval.ast_cast_expr) = new AstCastExpr((yyvsp[0].ast_unary_expr));
	}
#line 2109 "y.tab.cpp"
    break;

  case 62:
#line 367 "./parser/grammar.y"
                                            {
	    (yyval.ast_cast_expr) = new AstCastExpr((yyvsp[-2].ast_type_name), (yyvsp[0].ast_cast_expr));
	}
#line 2117 "y.tab.cpp"
    break;

  case 63:
#line 373 "./parser/grammar.y"
                      {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[0].ast_cast_expr));
    }
#line 2125 "y.tab.cpp"
    break;

  case 64:
#line 376 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2133 "y.tab.cpp"
    break;

  case 65:
#line 379 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2141 "y.tab.cpp"
    break;

  case 66:
#line 382 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "|", (yyvsp[0].ast_binary_expr));
    }
#line 2149 "y.tab.cpp"
    break;

  case 67:
#line 385 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "^", (yyvsp[0].ast_binary_expr));
    }
#line 2157 "y.tab.cpp"
    break;

  case 68:
#line 388 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "&", (yyvsp[0].ast_binary_expr));
    }
#line 2165 "y.tab.cpp"
    break;

  case 69:
#line 391 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2173 "y.tab.cpp"
    break;

  case 70:
#line 394 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2181 "y.tab.cpp"
    break;

  case 71:
#line 397 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "<", (yyvsp[0].ast_binary_expr));
    }
#line 2189 "y.tab.cpp"
    break;

  case 72:
#line 400 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), ">", (yyvsp[0].ast_binary_expr));
    }
#line 2197 "y.tab.cpp"
    break;

  case 73:
#line 403 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2205 "y.tab.cpp"
    break;

  case 74:
#line 406 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2213 "y.tab.cpp"
    break;

  case 75:
#line 409 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2221 "y.tab.cpp"
    break;

  case 76:
#line 412 "./parser/grammar.y"
                                                     {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), (yyvsp[-1].str), (yyvsp[0].ast_binary_expr));
    }
#line 2229 "y.tab.cpp"
    break;

  case 77:
#line 415 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "+", (yyvsp[0].ast_binary_expr));
    }
#line 2237 "y.tab.cpp"
    break;

  case 78:
#line 418 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "-", (yyvsp[0].ast_binary_expr));
    }
#line 2245 "y.tab.cpp"
    break;

  case 79:
#line 421 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "*", (yyvsp[0].ast_binary_expr));
    }
#line 2253 "y.tab.cpp"
    break;

  case 80:
#line 424 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "/", (yyvsp[0].ast_binary_expr));
    }
#line 2261 "y.tab.cpp"
    break;

  case 81:
#line 427 "./parser/grammar.y"
                                                  {
        (yyval.ast_binary_expr) = new AstBinaryExpr((yyvsp[-2].ast_binary_expr), "%", (yyvsp[0].ast_binary_expr));
    }
#line 2269 "y.tab.cpp"
    break;

  case 82:
#line 433 "./parser/grammar.y"
                            {
	    (yyval.ast_condi_expr) = new AstCondiExpr((yyvsp[0].ast_binary_expr));
	}
#line 2277 "y.tab.cpp"
    break;

  case 83:
#line 436 "./parser/grammar.y"
                                                                 {
	    (yyval.ast_condi_expr) = new AstCondiExpr((yyvsp[-4].ast_binary_expr), (yyvsp[-2].ast_expr), (yyvsp[0].ast_binary_expr));
	}
#line 2285 "y.tab.cpp"
    break;

  case 84:
#line 442 "./parser/grammar.y"
                                 {
	    printf("conditional_expression\n");
	    (yyval.ast_expr) = new AstExpression((yyvsp[0].ast_condi_expr));
	}
#line 2294 "y.tab.cpp"
    break;

  case 85:
#line 446 "./parser/grammar.y"
                                                          {
	    (yyval.ast_expr) = new AstExpression((yyvsp[-2].ast_unary_expr), (yyvsp[-1].ast_assign_op), (yyvsp[0].ast_expr));
	    printf("unary_expression\n");
	}
#line 2303 "y.tab.cpp"
    break;

  case 86:
#line 453 "./parser/grammar.y"
              {
        (yyval.ast_assign_op) = new AstAssignOp("=");
	}
#line 2311 "y.tab.cpp"
    break;

  case 87:
#line 456 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2319 "y.tab.cpp"
    break;

  case 88:
#line 459 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2327 "y.tab.cpp"
    break;

  case 89:
#line 462 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2335 "y.tab.cpp"
    break;

  case 90:
#line 465 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2343 "y.tab.cpp"
    break;

  case 91:
#line 468 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2351 "y.tab.cpp"
    break;

  case 92:
#line 471 "./parser/grammar.y"
                      {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2359 "y.tab.cpp"
    break;

  case 93:
#line 474 "./parser/grammar.y"
                       {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2367 "y.tab.cpp"
    break;

  case 94:
#line 477 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2375 "y.tab.cpp"
    break;

  case 95:
#line 480 "./parser/grammar.y"
                     {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2383 "y.tab.cpp"
    break;

  case 96:
#line 483 "./parser/grammar.y"
                    {
	    (yyval.ast_assign_op) = new AstAssignOp((yyvsp[0].str));
	}
#line 2391 "y.tab.cpp"
    break;

  case 97:
#line 489 "./parser/grammar.y"
                                                           {
		(yyval.ast_struct_spec) = new AstStructSpec((yyvsp[-3].str), (yyvsp[-1].ast_struct_decl_list));
	}
#line 2399 "y.tab.cpp"
    break;

  case 98:
#line 492 "./parser/grammar.y"
                                                {
		(yyval.ast_struct_spec) = new AstStructSpec("", (yyvsp[-1].ast_struct_decl_list));
	}
#line 2407 "y.tab.cpp"
    break;

  case 99:
#line 495 "./parser/grammar.y"
                           {
		(yyval.ast_struct_spec) = new AstStructSpec((yyvsp[0].str), nullptr);
	}
#line 2415 "y.tab.cpp"
    break;

  case 100:
#line 501 "./parser/grammar.y"
                                       {
		(yyval.ast_struct_decl_list) = new AstStructDeclarationList();
		(yyval.ast_struct_decl_list)->addMember((yyvsp[-2].ast_type_spec), (yyvsp[-1].ast_declarator));
	}
#line 2424 "y.tab.cpp"
    break;

  case 101:
#line 505 "./parser/grammar.y"
                                                               {
		(yyval.ast_struct_decl_list) = (yyvsp[-3].ast_struct_decl_list);
		(yyval.ast_struct_decl_list)->addMember((yyvsp[-2].ast_type_spec), (yyvsp[-1].ast_declarator));
	}
#line 2433 "y.tab.cpp"
    break;

  case 102:
#line 512 "./parser/grammar.y"
                    {
		(yyval.ast_id_list) = new AstIdList();
		(yyval.ast_id_list)->addId((yyvsp[0].str));
	}
#line 2442 "y.tab.cpp"
    break;

  case 103:
#line 516 "./parser/grammar.y"
                                        {
		(yyval.ast_id_list) = (yyvsp[-2].ast_id_list);
		(yyval.ast_id_list)->addId((yyvsp[0].str));
	}
#line 2451 "y.tab.cpp"
    break;

  case 104:
#line 523 "./parser/grammar.y"
                        {
		(yyval.ast_type_name) = new AstTypeName((yyvsp[0].ast_type_spec), nullptr);
	}
#line 2459 "y.tab.cpp"
    break;

  case 105:
#line 526 "./parser/grammar.y"
                                {
		(yyval.ast_type_name) = new AstTypeName((yyvsp[-1].ast_type_spec), (yyvsp[0].ast_pointer));
	}
#line 2467 "y.tab.cpp"
    break;

  case 106:
#line 532 "./parser/grammar.y"
                   {
		(yyval.ast_stmt_list) = new AstStmtList();
		(yyval.ast_stmt_list)->addStmt((yyvsp[0].ast_stmt));
	}
#line 2476 "y.tab.cpp"
    break;

  case 107:
#line 536 "./parser/grammar.y"
                                  {
		(yyval.ast_stmt_list) = (yyvsp[-1].ast_stmt_list);
		(yyval.ast_stmt_list)->addStmt((yyvsp[0].ast_stmt));
	}
#line 2485 "y.tab.cpp"
    break;

  case 108:
#line 543 "./parser/grammar.y"
                     {
		(yyval.ast_declaration_list) = new AstDeclarationList();
		(yyval.ast_declaration_list)->addDeclaration((yyvsp[0].ast_declaration));
	}
#line 2494 "y.tab.cpp"
    break;

  case 109:
#line 547 "./parser/grammar.y"
                                      {
		(yyvsp[-1].ast_declaration_list)->addDeclaration((yyvsp[0].ast_declaration));
		(yyval.ast_declaration_list) = (yyvsp[-1].ast_declaration_list);
	}
#line 2503 "y.tab.cpp"
    break;

  case 110:
#line 555 "./parser/grammar.y"
                 {
		(yyval.ast_compound_stmt) = new AstCompoundStmt(nullptr, nullptr);
	}
#line 2511 "y.tab.cpp"
    break;

  case 111:
#line 558 "./parser/grammar.y"
                                {
		(yyval.ast_compound_stmt) = new AstCompoundStmt(nullptr, (yyvsp[-1].ast_stmt_list));
	}
#line 2519 "y.tab.cpp"
    break;

  case 112:
#line 561 "./parser/grammar.y"
                                  {
		(yyval.ast_compound_stmt) = new AstCompoundStmt((yyvsp[-1].ast_declaration_list), nullptr);
	}
#line 2527 "y.tab.cpp"
    break;

  case 113:
#line 564 "./parser/grammar.y"
                                                 {
		(yyval.ast_compound_stmt) = new AstCompoundStmt((yyvsp[-2].ast_declaration_list), (yyvsp[-1].ast_stmt_list));
	}
#line 2535 "y.tab.cpp"
    break;

  case 114:
#line 570 "./parser/grammar.y"
                            { (yyval.ast_stmt) = new AstStmt(1, (yyvsp[0].ast_compound_stmt)); }
#line 2541 "y.tab.cpp"
    break;

  case 115:
#line 571 "./parser/grammar.y"
                              { (yyval.ast_stmt) = new AstStmt(2, (yyvsp[0].ast_expr_stmt)); }
#line 2547 "y.tab.cpp"
    break;

  case 116:
#line 572 "./parser/grammar.y"
                             { (yyval.ast_stmt) = new AstStmt(3, (yyvsp[0].ast_select_stmt)); }
#line 2553 "y.tab.cpp"
    break;

  case 117:
#line 573 "./parser/grammar.y"
                             { (yyval.ast_stmt) = new AstStmt(4, (yyvsp[0].ast_iter_stmt)); }
#line 2559 "y.tab.cpp"
    break;

  case 118:
#line 574 "./parser/grammar.y"
                        { (yyval.ast_stmt) = new AstStmt(5, (yyvsp[0].ast_jmp_stmt)); }
#line 2565 "y.tab.cpp"
    break;

  case 119:
#line 578 "./parser/grammar.y"
              {(yyval.ast_expr_stmt) = nullptr;}
#line 2571 "y.tab.cpp"
    break;

  case 120:
#line 579 "./parser/grammar.y"
                         {(yyval.ast_expr_stmt) = new AstExprStmt((yyvsp[-1].ast_expr)); }
#line 2577 "y.tab.cpp"
    break;

  case 121:
#line 583 "./parser/grammar.y"
                                         {
		(yyval.ast_select_stmt) = new AstSelectStmt((yyvsp[-2].ast_expr), (yyvsp[0].ast_stmt));
	}
#line 2585 "y.tab.cpp"
    break;

  case 122:
#line 586 "./parser/grammar.y"
                                                        {
		(yyval.ast_select_stmt) = new AstSelectStmt((yyvsp[-4].ast_expr), (yyvsp[-2].ast_stmt), (yyvsp[0].ast_stmt));
	}
#line 2593 "y.tab.cpp"
    break;

  case 123:
#line 592 "./parser/grammar.y"
                                            {
		(yyval.ast_iter_stmt) = new AstIterStmt(1, nullptr, (yyvsp[-2].ast_expr), nullptr, (yyvsp[0].ast_stmt));
	}
#line 2601 "y.tab.cpp"
    break;

  case 124:
#line 595 "./parser/grammar.y"
                                                                         {
		(yyval.ast_iter_stmt) = new AstIterStmt(2, (yyvsp[-3].ast_expr_stmt)->getExpr(), (yyvsp[-2].ast_expr_stmt)->getExpr(), nullptr, (yyvsp[0].ast_stmt));
	}
#line 2609 "y.tab.cpp"
    break;

  case 125:
#line 598 "./parser/grammar.y"
                                                                                    {
		(yyval.ast_iter_stmt) = new AstIterStmt(2, (yyvsp[-4].ast_expr_stmt)->getExpr(), (yyvsp[-3].ast_expr_stmt)->getExpr(), (yyvsp[-2].ast_expr), (yyvsp[0].ast_stmt));
	}
#line 2617 "y.tab.cpp"
    break;

  case 126:
#line 604 "./parser/grammar.y"
                      { (yyval.ast_jmp_stmt) = new AstJmpStmt((yyvsp[-1].str), nullptr);}
#line 2623 "y.tab.cpp"
    break;

  case 127:
#line 605 "./parser/grammar.y"
                      { (yyval.ast_jmp_stmt) = new AstJmpStmt((yyvsp[-1].str), nullptr);}
#line 2629 "y.tab.cpp"
    break;

  case 128:
#line 606 "./parser/grammar.y"
                      { (yyval.ast_jmp_stmt) = new AstJmpStmt((yyvsp[-1].str), nullptr);}
#line 2635 "y.tab.cpp"
    break;

  case 129:
#line 607 "./parser/grammar.y"
                                { (yyval.ast_jmp_stmt) = new AstJmpStmt((yyvsp[-2].str), (yyvsp[-1].ast_expr));}
#line 2641 "y.tab.cpp"
    break;


#line 2645 "y.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 610 "./parser/grammar.y"

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
