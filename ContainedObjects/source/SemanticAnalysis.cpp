#include "platform.h"
#include "SemanticAnalysis.h"
#include "Context.h"
#include "StaticContextEntry.h"
#include "SemanticCheck.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include "ValueDef.h"
#include "VariableDeclDef.h"
#include "ObjectInitValueDef.h"
#include "ArrayInitValueDef.h"
#include "LiteralValueDef.h"
#include "ActualParamDef.h"
#include "ReferencePathValueDef.h"
#include "Type.h"
#include "PrimitiveType.h"
#include "ReferenceType.h"

namespace COBJ
{
	SemanticAnalysis::SemanticAnalysis(void)
	{
	}

	SemanticAnalysis::~SemanticAnalysis(void)
	{
	}

	void SemanticAnalysis::addCheck(const boost::shared_ptr<SemanticCheck>& pSemanticCheck)
	{

	}

	void SemanticAnalysis::analyze(
			std::list<boost::shared_ptr<ClassDef>> classes,
			std::list<boost::shared_ptr<InterfaceDef>> interfaces)
	{
		Context<StaticContextEntry> rootCtx;

		std::list<boost::shared_ptr<ClassDef>>::iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			boost::shared_ptr<StaticContextEntry> entry(new StaticContextEntry(*cit));
			rootCtx.addEntry(entry);
		}

		std::list<boost::shared_ptr<InterfaceDef>>::iterator iit;

		for (iit = interfaces.begin(); iit != interfaces.end(); iit++)
		{
			boost::shared_ptr<StaticContextEntry> entry(new StaticContextEntry(*iit));
			rootCtx.addEntry(entry);
		}


	}

	void SemanticAnalysis::inferTypes(
			std::list<boost::shared_ptr<ClassDef>>& classes,
			const Context<StaticContextEntry>& rootCtx)
	{
		std::list<boost::shared_ptr<ClassDef>>::iterator cit;

		for (cit = classes.begin(); cit != classes.end(); cit++)
		{
			boost::shared_ptr<ClassDef>& pClassDef = *cit;

			Context<StaticContextEntry> classCtx(rootCtx);

			initClassContext(classCtx, pClassDef);

			const std::list<boost::shared_ptr<VariableDeclDef>>& variables = pClassDef->getVariableDecls();

			std::list<boost::shared_ptr<VariableDeclDef>>::const_iterator vit;

			for (vit = variables.begin(); vit != variables.end(); vit++)
			{
				const boost::shared_ptr<VariableDeclDef>& pVariable = *vit;
				const boost::shared_ptr<ValueDef>& pValueDef = pVariable->getValue();

				inferTypes(pValueDef, classCtx);
			}
		}
	}

	void SemanticAnalysis::inferTypes(
		const boost::shared_ptr<ValueDef>& pValueDef,
		const Context<StaticContextEntry>& classCtx)
	{
		switch (pValueDef->getValueType())
		{
		case OBJECT_INIT:
			{
				boost::shared_ptr<ObjectInitValueDef>& pObjectInitDef = 
					boost::static_pointer_cast<ObjectInitValueDef, ValueDef>(pValueDef);

				boost::shared_ptr<Type> pType = boost::shared_ptr<Type>(
					new ReferenceType(OBJECT_REF_TYPE, pObjectInitDef->getClassName()));

				pValueDef->setInferredType(pType);

				const std::list<boost::shared_ptr<ActualParamDef>>& actualParams = pObjectInitDef->getActualParams();

				std::list<boost::shared_ptr<ActualParamDef>>::const_iterator it;

				for (it = actualParams.begin(); it != actualParams.end(); it++)
				{
					const boost::shared_ptr<ActualParamDef>& pActualParamDef = *it;
					const boost::shared_ptr<ValueDef>& pParamValueDef = pActualParamDef->getValue();

					inferTypes(pParamValueDef, classCtx);
				}
			}
			break;
		case ARRAY_INIT:
			{
				boost::shared_ptr<ArrayInitValueDef>& pArrayInitDef = 
					boost::static_pointer_cast<ArrayInitValueDef, ValueDef>(pValueDef);

				pValueDef->setInferredType(pArrayInitDef->getDeclaredType());

				const std::list<boost::shared_ptr<ValueDef>>& arrayValues = pArrayInitDef->getValues();

				std::list<boost::shared_ptr<ValueDef>>::const_iterator it;

				for (it = arrayValues.begin(); it != arrayValues.end(); it++)
				{
					const boost::shared_ptr<ValueDef>& pArrayValue = *it;

					inferTypes(pArrayValue, classCtx);
				}
			}
			break;
		case LITERAL:
			{
				boost::shared_ptr<LiteralValueDef>& pLiteralInitDef = 
					boost::static_pointer_cast<LiteralValueDef, ValueDef>(pValueDef);

				switch (pLiteralInitDef->getLiteralType())
				{
				case INTEGER_LITERAL:
					pValueDef->setInferredType(P_INTEGER_TYPE);
					break;
				case FLOAT_LITERAL:
					pValueDef->setInferredType(P_FLOAT_TYPE);
					break;
				case STRING_LITERAL:
					pValueDef->setInferredType(P_STRING_TYPE);
					break;
				default:
					assert(false);
					break;
				}
			}
			break;
		case REFERENCE_PATH:
			{
				boost::shared_ptr<ReferencePathValueDef>& pReferencePathDef = 
					boost::static_pointer_cast<ReferencePathValueDef, ValueDef>(pValueDef);

				const std::list<std::wstring>& path = pReferencePathDef->getReferencePath();

				boost::shared_ptr<StaticContextEntry> pEntry;

				std::list<std::wstring>::const_iterator it;

				for (it = path.begin(); it != path.end(); it++)
				{
					const std::wstring& pathElement = *it;


				}
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	bool SemanticAnalysis::followPath(
			const boost::shared_ptr<Type>& pCurrentType,
			const 
			const std::wstring& pathElement,
			boost::shared_ptr<Type>& pNextType)
	{
		return false;
	}

	void SemanticAnalysis::initClassContext(
		Context<StaticContextEntry>& ctx,
		const boost::shared_ptr<ClassDef> pClassDef)
	{
		const std::list<boost::shared_ptr<FormalParamDef>>& formalParams = pClassDef->getFormalParameters();

		std::list<boost::shared_ptr<FormalParamDef>>::const_iterator fpit;

		for (fpit = formalParams.begin(); fpit != formalParams.end(); fpit++)
		{
			boost::shared_ptr<StaticContextEntry> entry(new StaticContextEntry(*fpit));
			ctx.addEntry(entry);
		}

		const std::list<boost::shared_ptr<VariableDeclDef>>& variables = pClassDef->getVariableDecls();

		std::list<boost::shared_ptr<VariableDeclDef>>::const_iterator vit;

		for (vit = variables.begin(); vit != variables.end(); vit++)
		{
			boost::shared_ptr<StaticContextEntry> entry(new StaticContextEntry(*vit));
			ctx.addEntry(entry);
		}
	}
}