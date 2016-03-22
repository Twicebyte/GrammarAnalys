#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

/*
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
class Nonterminal :Symbol 
{
public:
	Nonterminal() :Symbol() {}
}; // "BARs" - Brackets, Alternatives, Replicators 
class Alternative :Nonterminal 
{
public:
	Alternative() :Nonterminal() {}
};
class Bracket : Nonterminal 
{
public:
	Bracket() :Nonterminal() {}
};
class Replicator : Nonterminal 
{
public:
	Replicator() :Nonterminal() {}
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
*/

class Symbol
{
public:
	Symbol() {};
};

class Nonterminal : Symbol
{
public:
	Nonterminal(): Symbol() {};
};

class Terminal : Symbol
{
public:
	Terminal() : Symbol() {};
	char Value;
};

class Plural
{
private:
	Litera* First;
	Litera* Last;
public:
	Plural() {};
	int Count = 0;
	void add(Symbol* link)
	{
		if (Count > 0)
		{
			Litera* p = new Litera();
			(*p).setValue(link);
			(*Last).setNext(p);
			Last = p;
			Count++;
		}
		else
		{
			Litera* p = new Litera();
			(*p).setValue(link);
			Last = p; First = p;
			Count++;
		}
	}
	Symbol* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First)[a];
	}
};

class Litera
{
private:
	Symbol* Value;
	Litera* Next;
public:
	Litera() {};
	Symbol* operator[](int a)
	{
		if (a == 0) return Value;
		else
			return (*Next)[a - 1];
	}
	void setValue(Symbol* link)
	{
		Value = link;
	}
	void setNext(Litera* link)
	{
		Next = link;
	}
	bool exist(Symbol* link, int k)
	{
		if (Value == link) return true;
		else
			if (k = 0) return false; else return (*Next).exist(link, k - 1);
	}
};

class Alphabet
{
private:
	Litera* First;
	Litera* Last;
	bool exist(Symbol* link)
	{
		return (*First).exist(link,Count-1);
	}
public:
	Alphabet() {};
	int Count = 0;
	bool add(Symbol* link)
	{
		if (exist(link))
			return false;
		else
		{
			if (Count > 0)
			{
				Litera* p = new Litera();
				(*p).setValue(link);
				(*Last).setNext(p);
				Last = p;
				Count++;
			}
			else
			{
				Litera* p = new Litera();
				(*p).setValue(link);
				Last = p; First = p;
				Count++;
			}
			return true;
		}
	}
	Symbol* operator[](int a)
	{
		if ((a<Count)&(a>-1))
		return (*First)[a];
	}
};

class Rule
{
private:
	Nonterminal From;
	Plural To;
public:
	Rule() {};
};

class RuleNode
{
private:
	Rule* Value;
	RuleNode* Next;
public:
	RuleNode() {};
	Rule* operator[](int a)
	{
		if (a == 0) return Value;
		else
			return (*Next)[a - 1];
	}
	void setValue(Rule* link)
	{
		Value = link;
	}
	void setNext(RuleNode* link)
	{
		Next = link;
	}
	bool exist(Rule* link, int k)
	{
		if (Value == link) return true; //REPAIR!!!
		else
			if (k = 0) return false; else return (*Next).exist(link, k - 1);
	}
};

class Codex
{
private:
	RuleNode* First;
	RuleNode* Last;
	bool exist(Rule* link)
	{
		return (*First).exist(link, Count - 1);
	}
public:
	Codex() {};
	int Count = 0;
	bool add(Rule* link)
	{
		if (exist(link))
			return false;
		else
		{
			if (Count > 0)
			{
				RuleNode* p = new RuleNode();
				(*p).setValue(link);
				(*Last).setNext(p);
				Last = p;
				Count++;
			}
			else
			{
				RuleNode* p = new RuleNode();
				(*p).setValue(link);
				Last = p; First = p;
				Count++;
			}
			return true;
		}
	}
	Rule* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First)[a];
	}
};

class Grammar
{
private:
	Alphabet NTAlphabet;
	Alphabet TAlphabet;
	Codex Rules;
public:
	Grammar() {};
	bool CheckLine(string s)
	{

	}
};


int main()
{

}