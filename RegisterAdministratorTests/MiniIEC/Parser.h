

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include <iostream>
#include <string>
#include "AtgHelpers.h"
#include "SymbolTable.h"
#include "SymbolFactory.h"
#include "BaseType.h"
#include "TACGenerator.h"


#include "Scanner.h"

namespace MIEC {


class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_ident=1,
		_number=2,
		_Integer=3,
		_semicolon=4,
		_colon=5,
		_lpar=6,
		_rpar=7
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

SymbolTable _symTab;
	SymbolFactory _symFactory;
	TACGenerator _tacGenerator;
	size_t offset = 0;



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void MIEC();
	void VarDecl();
	void Statements();
	void SingleVarDecl(size_t& offset);
	void Ident(std::string& name);
	void Stat();
	void Expr(Symbol* exprResultSymbol);
	void Condition();
	void Term(Symbol* termResultSymbol);
	void Fact(Symbol* factResultSymbol);
	void Number(Symbol* numberSymbol);
	void Relop();

	void Parse();

}; // end Parser

} // namespace


#endif // !defined(COCO_PARSER_H__)

