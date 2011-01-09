/** \file
 *  This C header file was generated by $ANTLR version 3.3 Nov 30, 2010 12:45:30
 *
 *     -  From the grammar source file : C:\\Users\\Ernesto\\Documents\\Visual Studio 2008\\Projects\\FeedViz\\ContainedObjects\\ContainedObjects.g
 *     -                            On : 2011-01-03 23:41:44
 *     -                 for the lexer : ContainedObjectsLexerLexer *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer ContainedObjectsLexer has the callable functions (rules) shown below,
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
 * a parser context typedef pContainedObjectsLexer, which is returned from a call to ContainedObjectsLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 * * The methods in pContainedObjectsLexer are  as follows:
 *
 *  -  void      pContainedObjectsLexer->CLASS_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->INTERFACE_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->IMPLEMENTS_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->STATIC_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->INTEGER_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->FLOAT_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->STRING_KW(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__58(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__59(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__60(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__61(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__62(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__63(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__64(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__65(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__66(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__67(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__68(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->T__69(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->UNICODE_CHAR(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->ID(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->INTL(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->FLOATL(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->COMMENT(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->STRINGL(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->EXPONENT(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->HEX_DIGIT(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->ESC_SEQ(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->SPACE(pContainedObjectsLexer)
 *  -  void      pContainedObjectsLexer->Tokens(pContainedObjectsLexer)
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

#ifndef	_ContainedObjectsLexer_H
#define _ContainedObjectsLexer_H
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
typedef struct ContainedObjectsLexer_Ctx_struct ContainedObjectsLexer, * pContainedObjectsLexer;



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

/** Context tracking structure for ContainedObjectsLexer
 */
struct ContainedObjectsLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;


     void (*mCLASS_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mINTERFACE_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mIMPLEMENTS_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mSTATIC_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mINTEGER_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mFLOAT_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mSTRING_KW)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__58)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__59)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__60)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__61)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__62)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__63)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__64)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__65)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__66)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__67)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__68)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mT__69)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mUNICODE_CHAR)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mID)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mINTL)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mFLOATL)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mCOMMENT)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mSTRINGL)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mEXPONENT)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mHEX_DIGIT)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mESC_SEQ)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mSPACE)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
     void (*mTokens)	(struct ContainedObjectsLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct ContainedObjectsLexer_Ctx_struct * ctx);
    void	    (*free)   (struct ContainedObjectsLexer_Ctx_struct * ctx);
        
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pContainedObjectsLexer ContainedObjectsLexerNew         (pANTLR3_INPUT_STREAM instream);
ANTLR3_API pContainedObjectsLexer ContainedObjectsLexerNewSSD      (pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the lexer will work with.
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
#define EOF      -1
#define T__58      58
#define T__59      59
#define T__60      60
#define T__61      61
#define T__62      62
#define T__63      63
#define T__64      64
#define T__65      65
#define T__66      66
#define T__67      67
#define T__68      68
#define T__69      69
#define CLASS_KW      4
#define INTERFACE_KW      5
#define IMPLEMENTS_KW      6
#define STATIC_KW      7
#define INTEGER_KW      8
#define FLOAT_KW      9
#define STRING_KW      10
#define N_CLASS_DECL      11
#define N_IFACE_DECL      12
#define N_FORMAL_CLASS_PARAMS      13
#define N_BODY      14
#define N_IMPLEMENTS_DECL      15
#define N_IMPLEMENTED_IFACE      16
#define N_FORMAL_CLASS_PARAM      17
#define N_VARDEF      18
#define N_TYPE      19
#define N_OBJECT_TYPE      20
#define N_CLASS_TYPE      21
#define N_ARRAY_TYPE      22
#define N_VALUE      23
#define N_ACTUAL_PARAMS      24
#define N_ACTUAL_PARAM      25
#define N_SIMPLE_TYPE      26
#define N_ARRAY_VALUES      27
#define N_INTEGER_TYPE      28
#define N_FLOAT_TYPE      29
#define N_STRING_TYPE      30
#define N_OBJECT_INIT_VAL      31
#define N_ARRAY_INIT_VAL      32
#define N_LITERAL_VAL      33
#define N_REFERENCE_VAL      34
#define N_CLASS_NAME      35
#define N_IFACE_NAME      36
#define N_PARAM_CLASS      37
#define N_SCOPE      38
#define N_VAR_NAME      39
#define N_PARAM_NAME      40
#define N_TYPE_NAME      41
#define N_PROC_NAME      42
#define N_COMMAND_NAME      43
#define N_INT_LITERAL      44
#define N_FLOAT_LITERAL      45
#define N_STRING_LITERAL      46
#define N_REF_PATH      47
#define ID      48
#define INTL      49
#define FLOATL      50
#define STRINGL      51
#define UNICODE_CHAR      52
#define EXPONENT      53
#define COMMENT      54
#define ESC_SEQ      55
#define HEX_DIGIT      56
#define SPACE      57
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for ContainedObjectsLexer
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
