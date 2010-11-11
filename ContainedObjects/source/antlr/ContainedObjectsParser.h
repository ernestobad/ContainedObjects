/** \file
 *  This C header file was generated by $ANTLR version 3.2 Sep 23, 2009 12:02:23
 *
 *     -  From the grammar source file : C:\\Users\\Ernesto\\Documents\\Visual Studio 2008\\Projects\\FeedViz\\ContainedObjects\\ContainedObjects.g
 *     -                            On : 2010-11-06 21:26:27
 *     -                for the parser : ContainedObjectsParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser ContainedObjectsParser has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pContainedObjectsParser, which is returned from a call to ContainedObjectsParserNew().
 *
 * The methods in pContainedObjectsParser are  as follows:
 *
 *  - ContainedObjectsParser_init_return      pContainedObjectsParser->init(pContainedObjectsParser)
 *  - ContainedObjectsParser_interfaceDecl_return      pContainedObjectsParser->interfaceDecl(pContainedObjectsParser)
 *  - ContainedObjectsParser_classDecl_return      pContainedObjectsParser->classDecl(pContainedObjectsParser)
 *  - ContainedObjectsParser_formalClassParamList_return      pContainedObjectsParser->formalClassParamList(pContainedObjectsParser)
 *  - ContainedObjectsParser_formalClassParam_return      pContainedObjectsParser->formalClassParam(pContainedObjectsParser)
 *  - ContainedObjectsParser_implementsDecl_return      pContainedObjectsParser->implementsDecl(pContainedObjectsParser)
 *  - ContainedObjectsParser_body_return      pContainedObjectsParser->body(pContainedObjectsParser)
 *  - ContainedObjectsParser_varDef_return      pContainedObjectsParser->varDef(pContainedObjectsParser)
 *  - ContainedObjectsParser_actualParamList_return      pContainedObjectsParser->actualParamList(pContainedObjectsParser)
 *  - ContainedObjectsParser_actualParam_return      pContainedObjectsParser->actualParam(pContainedObjectsParser)
 *  - ContainedObjectsParser_value_return      pContainedObjectsParser->value(pContainedObjectsParser)
 *  - ContainedObjectsParser_reference_return      pContainedObjectsParser->reference(pContainedObjectsParser)
 *  - ContainedObjectsParser_literal_return      pContainedObjectsParser->literal(pContainedObjectsParser)
 *  - ContainedObjectsParser_arrayInit_return      pContainedObjectsParser->arrayInit(pContainedObjectsParser)
 *  - ContainedObjectsParser_objectInit_return      pContainedObjectsParser->objectInit(pContainedObjectsParser)
 *  - ContainedObjectsParser_type_return      pContainedObjectsParser->type(pContainedObjectsParser)
 *  - ContainedObjectsParser_arrayType_return      pContainedObjectsParser->arrayType(pContainedObjectsParser)
 *  - ContainedObjectsParser_simpleType_return      pContainedObjectsParser->simpleType(pContainedObjectsParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_ContainedObjectsParser_H
#define _ContainedObjectsParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct ContainedObjectsParser_Ctx_struct ContainedObjectsParser, * pContainedObjectsParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
typedef struct ContainedObjectsParser_init_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_init_return;

typedef struct ContainedObjectsParser_interfaceDecl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_interfaceDecl_return;

typedef struct ContainedObjectsParser_classDecl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_classDecl_return;

typedef struct ContainedObjectsParser_formalClassParamList_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_formalClassParamList_return;

typedef struct ContainedObjectsParser_formalClassParam_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_formalClassParam_return;

typedef struct ContainedObjectsParser_implementsDecl_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_implementsDecl_return;

typedef struct ContainedObjectsParser_body_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_body_return;

typedef struct ContainedObjectsParser_varDef_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_varDef_return;

typedef struct ContainedObjectsParser_actualParamList_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_actualParamList_return;

typedef struct ContainedObjectsParser_actualParam_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_actualParam_return;

typedef struct ContainedObjectsParser_value_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_value_return;

typedef struct ContainedObjectsParser_reference_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_reference_return;

typedef struct ContainedObjectsParser_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_literal_return;

typedef struct ContainedObjectsParser_arrayInit_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_arrayInit_return;

typedef struct ContainedObjectsParser_objectInit_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_objectInit_return;

typedef struct ContainedObjectsParser_type_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_type_return;

typedef struct ContainedObjectsParser_arrayType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_arrayType_return;

typedef struct ContainedObjectsParser_simpleType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    ContainedObjectsParser_simpleType_return;



/** Context tracking structure for ContainedObjectsParser
 */
struct ContainedObjectsParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;


     ContainedObjectsParser_init_return (*init)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_interfaceDecl_return (*interfaceDecl)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_classDecl_return (*classDecl)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_formalClassParamList_return (*formalClassParamList)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_formalClassParam_return (*formalClassParam)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_implementsDecl_return (*implementsDecl)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_body_return (*body)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_varDef_return (*varDef)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_actualParamList_return (*actualParamList)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_actualParam_return (*actualParam)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_value_return (*value)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_reference_return (*reference)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_literal_return (*literal)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_arrayInit_return (*arrayInit)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_objectInit_return (*objectInit)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_type_return (*type)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_arrayType_return (*arrayType)	(struct ContainedObjectsParser_Ctx_struct * ctx);
     ContainedObjectsParser_simpleType_return (*simpleType)	(struct ContainedObjectsParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct ContainedObjectsParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pContainedObjectsParser ContainedObjectsParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API pContainedObjectsParser ContainedObjectsParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define T__68      68
#define T__69      69
#define N_SIMPLE_TYPE      27
#define T__66      66
#define EXPONENT      53
#define T__67      67
#define T__64      64
#define INTL      50
#define T__65      65
#define T__62      62
#define T__63      63
#define N_PARAM_NAME      41
#define N_VARDEF_ASSIGN      19
#define N_FORMAL_CLASS_PARAM      17
#define N_STRING_TYPE      31
#define ID      49
#define T__61      61
#define SPACE      57
#define EOF      -1
#define T__60      60
#define N_PARAM_CLASS      38
#define STRING_KW      10
#define N_ACTUAL_PARAMS      25
#define CLASS_KW      4
#define N_FLOAT_TYPE      30
#define T__58      58
#define ESC_SEQ      55
#define N_REFERENCE_VAL      35
#define N_REF_PATH      48
#define N_IFACE_NAME      37
#define T__59      59
#define N_CLASS_TYPE      22
#define N_INTEGER_TYPE      29
#define STRINGL      52
#define STATIC_KW      7
#define N_PROC_NAME      43
#define N_ARRAY_TYPE      23
#define N_BODY      14
#define COMMENT      54
#define N_LITERAL_VAL      34
#define N_VARDEF      18
#define N_TYPE      20
#define N_CLASS_DECL      11
#define INTERFACE_KW      5
#define HEX_DIGIT      56
#define INTEGER_KW      8
#define N_SCOPE      39
#define N_CLASS_NAME      36
#define N_IMPLEMENTED_IFACE      16
#define N_INT_LITERAL      45
#define N_TYPE_NAME      42
#define N_OBJECT_INIT_VAL      32
#define N_IMPLEMENTS_DECL      15
#define N_FORMAL_CLASS_PARAMS      13
#define N_COMMAND_NAME      44
#define IMPLEMENTS_KW      6
#define N_VAR_NAME      40
#define N_OBJECT_TYPE      21
#define N_ACTUAL_PARAM      26
#define N_ARRAY_INIT_VAL      33
#define FLOATL      51
#define N_VALUE      24
#define FLOAT_KW      9
#define N_IFACE_DECL      12
#define N_ARRAY_VALUES      28
#define N_FLOAT_LITERAL      46
#define N_STRING_LITERAL      47
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for ContainedObjectsParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
