#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

#pragma region Symbols determination
class Symbol
{
public:
	Symbol() {}
};
class Terminal :Symbol
{
public:
	char value;
};
class Nonterminal :Symbol {public:	Nonterminal() :Symbol() {}}; // "BARs" - Brackets, Alternatives, Replicators 
class Alternative :Nonterminal 
{public:	Alternative() :Nonterminal() {}
};
class Bracket : Nonterminal 
{public:	Bracket() :Nonterminal() {}
};
class Replicator : Nonterminal 
{public:	Replicator() :Nonterminal() {}
};
#pragma endregion

#pragma region List determination
template <class T>
class ListItem
{
public:
	ListItem* next;
	ListItem* prev;
	T* S;
	SymbolTypeListItem(T* Sym) { S = Sym; }
};
template <class T>
class List
{
private:
	ListItem* first;
	ListItem* last;
public:
	int Count = 0;
	List()
	{
		Count = 0;
	}
	void add(T* S)
	{
		ListItem* I;
		I = new ListItem(S);
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
		ListItem* current = first;
		while (a > 1) { current = (*current).next; a--; }
		return (*current).S;
	}
};
#pragma endregion

#pragma region General classes
class Alphabet
{
private:
	List <Symbol> T; //Terminals
	List <Symbol> B; //Brackets
	List <Symbol> A; //Alternatives
	List <Symbol> R; //Replicators
public:
	Alphabet()
	{
		T = List <Symbol>();
		B = List <Symbol>();
		A = List <Symbol>();
		R = List <Symbol>();
	}
	void reset()
	{
		T = List <Symbol>();
		B = List <Symbol>();
		A = List <Symbol>();
		R = List <Symbol>();
	}
};
class GrammarRule
{
private:
	Nonterminal* Seed;
	Symbol* Value;
public:
	GrammarRule(Nonterminal* S)
	{
		Seed = S;
	}
};
class GrammarBook
{
private:
	List <GrammarRule> Rules; //Terminals
public:
	GrammarBook()
	{
		Rules = List <GrammarRule>();
	}
	GrammarRule* reset(Nonterminal* G)
	{
		Rules = List <GrammarRule>();
		GrammarRule* A = new GrammarRule(G);
	}
};
class Grammar
{
	Nonterminal GeneralSeed;
	GrammarBook Rules;
	Alphabet Symbols;
	Grammar()
	{
		GeneralSeed = Nonterminal();
	}
	void resetGrammar(string prop)
	{
		Symbols.reset();
		GrammarRule* Current = Rules.reset(&GeneralSeed);
		//The place to parse the proposition
	}
};
#pragma endregion


int main()
{

}