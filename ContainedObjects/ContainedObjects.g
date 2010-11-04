grammar ContainedObjects;

options
{
	output=AST;
	language=C;
}

tokens
{
	CLASS_KW		= 'class';
	INTERFACE_KW		= 'interface';
	
	IMPLEMENTS_KW		= 'implements';
	STATIC_KW		= 'static';
	
	// primitive types
	INTEGER_KW		= 'integer';
	FLOAT_KW		= 'float';
	STRING_KW		= 'string';

	// TOKENS used only in the AST
	
	N_CLASS_DECL;
	N_IFACE_DECL;
	
	N_FORMAL_CLASS_PARAMS;
	N_CLASS_BODY;
	N_IFACE_BODY;
	N_IMPLEMENTS_DECL;
	N_IMPLEMENTED_IFACE;
	N_FORMAL_CLASS_PARAM;
	N_VARDEF;
	N_VARDEF_ASSIGN;
	
	N_TYPE;
	N_REFERENCE_TYPE;
	N_ARRAY_TYPE;
	
	N_VALUE;
	N_ACTUAL_PARAMS;
	N_ACTUAL_PARAM;
	N_SIMPLE_TYPE;
	N_ARRAY_TYPE;
	N_ARRAY_VALUES;
	
	N_INTEGER_TYPE;
	N_FLOAT_TYPE;
	N_STRING_TYPE;
	
	N_OBJECT_INIT_VAL;
	N_ARRAY_INIT_VAL;
	N_LITERAL_VAL;
	N_REFERENCE_VAL;
	
	N_CLASS_NAME;
	N_IFACE_NAME;
	N_PARAM_CLASS;
	N_SCOPE;
	N_VAR_NAME;
	N_PARAM_NAME;
	N_TYPE_NAME;
	N_PROC_NAME;
	N_COMMAND_NAME;
	N_INT_LITERAL;
	N_FLOAT_LITERAL;
	N_STRING_LITERAL;
	N_REF_PATH;
}

/*------------------------------------------------------------------
 * PARSER RULES
 *------------------------------------------------------------------*/

init 	:	classDecl	-> ^(N_CLASS_DECL classDecl)
	|	interfaceDecl	-> ^(N_IFACE_DECL interfaceDecl)
	;

// Interface
	
interfaceDecl
	:	INTERFACE_KW ID '(' formalClassParamList ')' '{' interfaceBody '}' EOF
		-> ^(N_IFACE_NAME ID) ^(N_FORMAL_CLASS_PARAMS formalClassParamList) ^(N_IFACE_BODY interfaceBody)
	;
	
interfaceBody
	:	varDef*
		-> ^(N_VARDEF varDef)*
	;
	
varDef
	:	STATIC_KW? type ID ';'
		-> ^(N_SCOPE STATIC_KW?) ^(N_TYPE type) ^(N_VAR_NAME ID)
	;

// Class

classDecl 
	:	CLASS_KW ID '(' formalClassParamList ')' implementsDecl '{' classBody '}' EOF
		-> ^(N_CLASS_NAME ID) ^(N_FORMAL_CLASS_PARAMS formalClassParamList) ^(N_IMPLEMENTS_DECL implementsDecl) ^(N_CLASS_BODY classBody)
	;

formalClassParamList 
	:	(formalClassParam (',' formalClassParam)*)?
		-> ^(N_FORMAL_CLASS_PARAM formalClassParam)*
	;

formalClassParam : type ID
		-> ^(N_TYPE type) ^(N_VAR_NAME ID) 
	;

implementsDecl 
	:	(IMPLEMENTS_KW ID (',' ID)*)?
		-> ^(N_IMPLEMENTED_IFACE ID)*
	;

classBody
	:	varDefAssign*
		-> ^(N_VARDEF_ASSIGN varDefAssign)*
	;

varDefAssign
	:	STATIC_KW? type ID '=' value ';'
		-> ^(N_SCOPE STATIC_KW?) ^(N_TYPE type) ^(N_VAR_NAME ID) ^(N_VALUE value)
	;

actualParamList
	:	(actualParam (',' actualParam)*)?
		-> ^(N_ACTUAL_PARAM actualParam)*
	;

actualParam
	:	ID '=' value
		-> ^(N_PARAM_NAME ID) ^(N_VALUE value)
	;

value	:	objectInit	-> ^(N_OBJECT_INIT_VAL objectInit)
	|	arrayInit	-> ^(N_ARRAY_INIT_VAL arrayInit)
	|	literal		-> ^(N_LITERAL_VAL literal)
	| 	reference	-> ^(N_REFERENCE_VAL reference)
	;

reference
	:	ID ('.' ID)*
		-> ID+
	;

literal	:	INTL	-> ^(N_INT_LITERAL INTL)
	|	FLOATL  -> ^(N_FLOAT_LITERAL FLOATL)
	| 	STRINGL	-> ^(N_STRING_LITERAL STRINGL)
	;

arrayInit
	:	simpleType '[' ']' '{' (value (',' value)*)? '}'
		-> ^(N_ARRAY_TYPE simpleType) ^(N_ARRAY_VALUES value*)
	;

objectInit
	:	ID '(' actualParamList ')'
		-> ^(N_CLASS_NAME ID) ^(N_ACTUAL_PARAMS actualParamList)
	;

type	:	arrayType	-> ^(N_ARRAY_TYPE arrayType)
	|	simpleType	-> ^(N_SIMPLE_TYPE simpleType)
	;

arrayType
	:	simpleType '[' ']'
		-> ^(N_SIMPLE_TYPE simpleType)
	;

simpleType
 	:	INTEGER_KW	-> N_INTEGER_TYPE
	|	FLOAT_KW	-> N_FLOAT_TYPE
	|	STRING_KW	-> N_STRING_TYPE
	|	ID		-> ^(N_REFERENCE_TYPE ID)
	;

 /*------------------------------------------------------------------
 * LEXER RULES
 *------------------------------------------------------------------*/

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INTL :	'0'..'9'+
    ;

FLOATL
    :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '.' ('0'..'9')+ EXPONENT?
    |   ('0'..'9')+ EXPONENT
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

STRINGL
    :  '"' ( ESC_SEQ | ~('\\'|'"') )* '"'
    ;

// CHARL
//	:  '\'' ( ESC_SEQ | ~('\''|'\\') ) '\''	
//	;

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
   :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
   ;


SPACE  : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+
              {
                 $channel = HIDDEN;
              }
            ;
