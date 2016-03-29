#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

/* Previous code
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
	char Value = 0;
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
	bool exist(Terminal* link, int k)
	{
		if ((*((Terminal*)(Value))).Value == (*link).Value) return true;
		else
			if (k = 0) return false; else return (*Next).exist(link, k - 1);
	}
	bool compare(Litera p, int k)
	{
		if (k == 0) return p.Value == Value;
		else
			return (p.Value == Value) & (*Next).compare(*(p.Next), k - 1);
	}
	bool operator== (Litera p)
	{
		return p.Value == Value;
	}
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
	bool operator== (Plural p)
	{
		bool b = true;
		if (Count != p.Count) b = false;
		else
		{
			b = (*First).compare(*(p.First), Count-1);
		}
		return b;
		
	}
};

class Alphabet
{
private:
	Litera* First;
	Litera* Last;
	bool exist(Terminal* link)
	{
		return (*First).exist(link,Count-1);
	}
public:
	Alphabet() {};
	int Count = 0;
	bool add(Terminal* link)
	{
		if (exist(link))
			return false;
		else
		{
			if (Count > 0)
			{
				Litera* p = new Litera();
				(*p).setValue(((Symbol*)link));
				(*Last).setNext(p);
				Last = p;
				Count++;
			}
			else
			{
				Litera* p = new Litera();
				(*p).setValue(((Symbol*)link));
				Last = p; First = p;
				Count++;
			}
			return true;
		}
	}
	bool add(Nonterminal* link)
	{
		if (Count > 0)
			{
				Litera* p = new Litera();
				(*p).setValue(((Symbol*)link));
				(*Last).setNext(p);
				Last = p;
				Count++;
			}
			else
			{
				Litera* p = new Litera();
				(*p).setValue(((Symbol*)link));
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

class Rule
{
public:
	Rule() {};
	Nonterminal* From;
	Plural To;

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
		if (((*Value).From == (*link).From)&((*Value).To == (*link).To)) return true; //REPAIR!!! Make adequate equality check.
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
	Grammar(string s) //Combine grammar
	{
/*
init: Create B0
0 Create A1
1 B0 -> A1
2 Ai -> Reading
2.1 If Brackets open then
	2.1.1 Create B last_b
	2.1.2 Ai -> ...B last_b
	2.1.3 Create A last_a
	2.1.4 B last_b -> A last_a
	2.1.5 Go to 2 (last_a)
2.2 If Alternative then
	2.2.1 Create A last_a
	2.2.1 ParentBrackets(Ai) -> A last_a
	2.2.2 Go to 2 (last_a)
2.3 If Brackets close (EOL) then
	2.3.1 Drop back to ParentBrackets
	2.3.2 Drop back to ParentAlternative (Finish process of reading!)
	2.3.3 Go to 2 (ParentAlternative(ParentBrackets(Ai)))
2.4 If Link then
	2.4.1 Ai -> ...B link
	2.4.2 Go to 2 (i)
2.5 If Replicator then
	2.5.1 Create R last_r 
	2.5.2 Ai -> ...R last_r
	2.5.3 R last_r -> prev_Symbol
	2.5.4 R last_r -> ...R last_r
	2.5.5 Go to 2 (i)
2.6 Else
	2.6.1 Create (if not exists) Terminal T last_t (Tk)
	2.6.2 Ai -> ...T last_t (Ai -> ...Tk)
	2.6.3 Go to 2 (i)
3 Create S
4 S -> B0
*/
	};
	bool CheckLine(string s) //Proceed algorithm
	{

	};
};


int main()
{

}