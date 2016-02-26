#include <cstdlib>
#include <fstream>

using namespace std;

#pragma region Symbols determination
class Symbol { };
Symbol U = Symbol(); //Universal
class Terminal :Symbol
{
public:
	char value;
};
class Nonterminal :Symbol {}; // "BARs" - Brackets, Alternatives, Replicators 
class Alternative : Nonterminal {};
class Bracket : Nonterminal {};
class Replicator : Nonterminal {};
#pragma endregion

#pragma region List determination
class SymbolTypeListItem
{
public:
	SymbolTypeListItem* next;
	SymbolTypeListItem* prev;
	Symbol* S;
	SymbolTypeListItem(Symbol* Sym) { S = Sym; }
};
class SymbolTypeList
{
private:
	SymbolTypeListItem* first;
	SymbolTypeListItem* last;
public:
	int Count = 0;
	void add(Symbol* S)
	{
		SymbolTypeListItem* I;
		I = new SymbolTypeListItem(S);
		if (Count > 0)
		{
			(*I).prev = last;
			(*last).next = I;
			last = I;
		}
		else
		{
			first = I;
			last = I;
		}
	}
	Symbol* operator[](int a)
	{
		if ((a > Count) | (a<1)) return &U;
		SymbolTypeListItem* current = first;
		while (a > 1) { current = (*current).next; a--; }
		return (*current).S;
	}
};
#pragma endregion

#pragma region General classes
class Alphabet
{
	SymbolTypeList T; //Terminals
	SymbolTypeList B; //Brackets
	SymbolTypeList A; //Alternatives
	SymbolTypeList R; //Replicators
};
class GrammarRule
{
	Nonterminal Seed;
	Symbol* Value;
};
class Grammar
{
	Nonterminal GeneralSeed;
	GrammarRule* Rules;
	Alphabet Symbols;
};
#pragma endregion


int main()
{

}