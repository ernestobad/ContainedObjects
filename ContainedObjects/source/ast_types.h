#pragma once

namespace COBJ
{
	class Type;
	typedef boost::shared_ptr<Type> TypePtr;
	//typedef boost::shared_ptr<const Type> ConstTypePtr;

	class PrimitiveType;
	typedef boost::shared_ptr<PrimitiveType> PrimitiveTypePtr;
	//typedef boost::shared_ptr<const PrimitiveType> ConstPrimitiveTypePtr;

	class ReferenceType;
	typedef boost::shared_ptr<ReferenceType> ReferenceTypePtr;
	//typedef boost::shared_ptr<const ReferenceType> ConstReferenceTypePtr;

	enum basic_type;

	class ArrayType;
	typedef boost::shared_ptr<ArrayType> ArrayTypePtr;
	//typedef boost::shared_ptr<const ArrayType> ConstArrayTypePtr;

	class ActualParamDef;
	typedef boost::shared_ptr<ActualParamDef> ActualParamDefPtr;
	//typedef boost::shared_ptr<const ActualParamDef> ConstActualParamDefPtr;

	class ArrayInitValueDef;
	typedef boost::shared_ptr<ArrayInitValueDef> ArrayInitValueDefPtr;
	//typedef boost::shared_ptr<const ArrayInitValueDef> ConstArrayInitValueDefPtr;

	class ASTNode;
	typedef boost::shared_ptr<ASTNode> ASTNodePtr;
	//typedef boost::shared_ptr<const ASTNode> ConstASTNodePtr;

	class ClassDefBase;
	typedef boost::shared_ptr<ClassDefBase> ClassDefBasePtr;

	class ClassDef;
	typedef boost::shared_ptr<ClassDef> ClassDefPtr;
	//typedef boost::shared_ptr<const ClassDef> ConstClassDefPtr;

	class InterfaceDef;
	typedef boost::shared_ptr<InterfaceDef> InterfaceDefPtr;
	//typedef boost::shared_ptr<const InterfaceDef> ConstInterfaceDefPtr;

	class FloatLiteralValueDef;
	typedef boost::shared_ptr<FloatLiteralValueDef> FloatLiteralValueDefPtr;
	//typedef boost::shared_ptr<const FloatLiteralValueDef> ConstFloatLiteralValueDefPtr;

	class FormalParamDef;
	typedef boost::shared_ptr<FormalParamDef> FormalParamDefPtr;
	//typedef boost::shared_ptr<const FormalParamDef> ConstFormalParamDefPtr;

	class IntegerLiteralValueDef;
	typedef boost::shared_ptr<IntegerLiteralValueDef> IntegerLiteralValueDefPtr;
	//typedef boost::shared_ptr<const IntegerLiteralValueDef> ConstIntegerLiteralValueDefPtr;

	class LiteralValueDef;
	typedef boost::shared_ptr<LiteralValueDef> LiteralValueDefPtr;
	//typedef boost::shared_ptr<const LiteralValueDef> ConstLiteralValueDefPtr;

	class ObjectInitValueDef;
	typedef boost::shared_ptr<ObjectInitValueDef> ObjectInitValueDefPtr;
	//typedef boost::shared_ptr<const ObjectInitValueDef> ConstObjectInitValueDefPtr;

	class ReferencePathValueDef;
	typedef boost::shared_ptr<ReferencePathValueDef> ReferencePathValueDefPtr;
	//typedef boost::shared_ptr<const ReferencePathValueDef> ConstReferencePathValueDefPtr;

	class StringLiteralValueDef;
	typedef boost::shared_ptr<StringLiteralValueDef> StringLiteralValueDefPtr;
	//typedef boost::shared_ptr<const StringLiteralValueDef> ConstStringLiteralValueDefPtr;

	class ValueDef;
	typedef boost::shared_ptr<ValueDef> ValueDefPtr;
	//typedef boost::shared_ptr<const ValueDef> ConstValueDefPtr;

	class VariableDeclDef;
	typedef boost::shared_ptr<VariableDeclDef> VariableDeclDefPtr;
	//typedef boost::shared_ptr<const VariableDeclDef> ConstVariableDeclDefPtr;
}