#include "platform.h"
#include "Engine.h"
#include "exceptions.h"
#include "conversions.h"
#include "auto_resource.h"
#include "ClassDef.h"
#include "InterfaceDef.h"
#include <antlr3defs.h>
#include "antlr/ContainedObjectsLexer.h"
#include "antlr/ContainedObjectsParser.h"
#include "Log.h"
#include "ClassImpl.h"
#include "Context.h"
#include "RuntimeContextEntry.h"

namespace COBJ
{
	using namespace std;

	EnginePtr Engine::s_pInstance = EnginePtr();

	Engine::Engine(void)
		: m_pLog(new Log())
	{
	}

	Engine::~Engine(void)
	{
	}

	const wstring& Engine::getCurrentFile()
	{
		return m_CurrentFile;
	}

	void Engine::parseFiles(const list<const wstring>& filePaths)
	{
		list<const wstring>::const_iterator it;

		for (it = filePaths.begin(); it != filePaths.end(); it++)
		{
			parseFile(*it);
		}

		initClasses();
	}

	static void print(pANTLR3_BASE_TREE node, int level)
	{
			for (int i = 0; i < level; ++i)
				wprintf(L"   ");
			wprintf(L"%s %i\n", (const wchar_t*) node->getText(node)->chars, node->getType(node));
			for (int i = 0; i < (int)node->getChildCount(node); ++i)
			{
				pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)node->getChild(node, i);
				print(child, level+1);
			}
	} 

	void Engine::parseFile(const wstring& filePath)
	{
		m_CurrentFile = filePath;

		pANTLR3_UINT8 fName = NULL;
		cantlr3_auto_resource<ANTLR3_INPUT_STREAM>::Type input;
		fantlr3_auto_resource<ContainedObjectsLexer>::Type lxr;
		fantlr3_auto_resource<ANTLR3_COMMON_TOKEN_STREAM>::Type tstream;
		fantlr3_auto_resource<ContainedObjectsParser>::Type psr;
		ContainedObjectsParser_init_return langAST;
		//fantlr3_auto_resource<ANTLR3_COMMON_TREE_NODE_STREAM>::Type nodes;

		string filePathUtf8;
		convertUTF16ToUTF8(filePath, filePathUtf8);

		ifstream fileStream(filePathUtf8.c_str());
		string fileContentsUtf8((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
		
		wstring fileContentsUtf16;
		convertUTF8ToUTF16(fileContentsUtf8, fileContentsUtf16);

		input = antlr3NewUCS2StringInPlaceStream(
			(pANTLR3_UINT16) fileContentsUtf16.data(),
			(ANTLR3_UINT32) fileContentsUtf16.length(),
			NULL);

		//input = antlr3AsciiFileStreamNew((pANTLR3_UINT8) filePathUtf8.c_str());

		ofstream outFileStream("test.txt", ios::out | ios::binary);
		outFileStream.write((char*) input->data, input->sizeBuf);
		outFileStream.close();

		if (input.get() == NULL)
		{
			wstring msg(L"Unable to open file " + filePath);
			ParserException e(msg);
			throw e;
		}

		lxr = ContainedObjectsLexerNew(input.get());

		if (lxr == NULL)
		{
			wstring msg(L"Unable to create the lexer");
			ParserException e(msg);
            throw e;
		}

		tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr.get()));

		if (tstream == NULL)
		{
			wstring msg(L"Could not allocate token stream\n");
			ParserException e(msg);
			throw e;
		}

		psr = ContainedObjectsParserNew(tstream.get());
 
		if (psr == NULL)
		{
			wstring msg(L"Could not allocate parser\n");
			ParserException e(msg);
			throw e;
		}

		langAST = psr->init(psr.get());

		pANTLR3_BASE_RECOGNIZER lexerRec = lxr->pLexer->rec;
		pANTLR3_BASE_RECOGNIZER parserRec = psr->pParser->rec;

		if (lexerRec->getNumberOfSyntaxErrors(lexerRec) > 0)
		{
			wstring msg(L"The lexer returned errors\n");
			ParserException e(msg);
			throw e;
		}
		else if (parserRec->getNumberOfSyntaxErrors(parserRec) > 0)
		{
			wstring msg(L"The parser returned errors\n");
			ParserException e(msg);
			throw e;
		}
		else
		{
			// nodes = antlr3CommonTreeNodeStreamNewTree(langAST.tree, ANTLR3_SIZE_HINT); // sIZE HINT WILL SOON BE DEPRECATED!!
	 
			pANTLR3_BASE_TREE root = langAST.tree;

			if (root->getType(root) == N_CLASS_DECL)
			{
				ClassDefPtr pClassDef(new ClassDef(root));
				m_ClassDefMap[pClassDef->getClassName()] = pClassDef;
			}
			else if (root->getType(root) == N_IFACE_DECL)
			{
				InterfaceDefPtr pInterfaceDef(new InterfaceDef(root));
				m_ClassDefMap[pInterfaceDef->getClassName()] = pInterfaceDef;
			}
			else
			{
				assert(false);
			}

			print(root, 0);
		}
	}

	void Engine::initClasses()
	{
		map<const wstring, ClassDefBasePtr>::const_iterator it;

		for (it = m_ClassDefMap.begin(); it != m_ClassDefMap.end(); it++)
		{
			initClass(it->second);
		}
	}

	void Engine::initClass(const ClassDefBasePtr& pClassDefBase)
	{
		const wstring& className = pClassDefBase->getClassName();

		if (m_ClassesMap.find(className) != m_ClassesMap.end())
		{
			return;
		}

		m_ClassesMap[className] = IClassPtr();

		const set<const wstring>& deps = pClassDefBase->getStaticDependencies();

		map<const wstring, ClassDefBasePtr>::const_iterator mit;
		set<const wstring>::const_iterator it;

		for (it = deps.begin(); it != deps.end(); it++)
		{
			const wstring& name = *it;
			if ((mit = m_ClassDefMap.find(name)) != m_ClassDefMap.end())
			{
				initClass(mit->second);
			}
		}

		IClassPtr pClass = IClassPtr(new ClassImpl(pClassDefBase,  m_pRootCtx));

		RuntimeContextEntryPtr pEntry = RuntimeContextEntryPtr(new RuntimeContextEntry(pClass));
		m_pRootCtx->addEntry(pEntry);

		m_ClassesMap[className] = pClass;
	}

	bool Engine::getClass(const wstring& className, IClassPtr& pClass)
	{
		map<const wstring, IClassPtr>::const_iterator it;

		it = m_ClassesMap.find(className);

		if (it == m_ClassesMap.end())
		{
			return false;
		}

		pClass = it->second;

		return true;
	}

	const void CreateEngine(
		const vector<IClassPtr> nativeClasses,
		IEnginePtr& pEngine)
	{

	}
}
