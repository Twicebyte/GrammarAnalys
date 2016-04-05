#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#pragma region Grammar Classes
class Symbol
{
public:
	Symbol() {};
	Symbol(string V) { Value = V; };
	string Value = "";
	bool operator==(Symbol S)
	{
		return Value == S.Value;
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
	Symbol* exist(Symbol* link, int k)
	{
		if ((*((Value))).Value == (*link).Value) return Value;
		else
			if (k == 0) return link; else return (*Next).exist(link, k - 1);
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
	void Report(int k)
	{
		cout << (*Value).Value <<' ';
		if (k > 0) (*Next).Report(k-1);
	}
	Litera* getNext()
	{
		return Next;
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
	void Skip()
	{
		First = (*First).getNext();
		Count--;
	}
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
	void Switch(Symbol* link)
	{
		(*Last).setValue(link);
	}
	Symbol* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First)[a];
		else
			return (*Last)[0];
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
	void Report()
	{
		if (Count>0) (*First).Report(Count - 1);
	}
};

class Alphabet
{
private:
	Litera* First;
	Litera* Last;
	Symbol* exist(Symbol* link)
	{
		if (Count > 0) return (*First).exist(link, Count - 1); else return link;
	}
public:
	Alphabet() {};
	int Count = 0;
	Symbol* add(Symbol* link)
	{
		Symbol* r = exist(link);
		if (r!=link)
			return r;
		else
		{
			if (Count > 0)
			{
				Litera* p = new Litera();
				(*p).setValue((link));
				(*Last).setNext(p);
				Last = p;
				Count++;
			}
			else
			{
				Litera* p = new Litera();
				(*p).setValue((link));
				Last = p; First = p;
				Count++;
			}
			return link;
		}
	}
	Symbol* operator[](int a)
	{
		if ((a<Count)&(a>-1))
		return (*First)[a];
		else
			return (*Last)[0];
	}
	void Report()
	{
		if (Count>0) (*First).Report(Count-1);
	}
};

class Rule
{
public:
	Rule() {};
	Rule(Symbol* F) { From = F; };
	Rule(Symbol* F, Symbol* T) { From = F; To.add(T); };
	Rule(Symbol* F, Plural T) { From = F; To = T; };
	Symbol* From;
	Plural To;
	void Add(Symbol* S) { To.add(S); }
	void Switch(Symbol* S) { To.Switch(S); }
	void Report()
	{
		cout << (*From).Value << " -> ";
		To.Report();
		cout << endl;
	}
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
		if (((*Value).From == (*link).From)&((*Value).To == (*link).To)) return true;
		else
			if (k == 0) return false; else return (*Next).exist(link, k - 1);
	}
	void Report(int k)
	{
		(*Value).Report();
		if (k > 0) (*Next).Report(k-1);
	}
};

class Codex
{
private:
	RuleNode* First;
	RuleNode* Last;
	bool exist(Rule* link)
	{
		if (Count > 0) return (*First).exist(link, Count - 1); else return false;
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
	void Report()
	{
		if (Count>0) (*First).Report(Count-1);
	}
};
#pragma endregion

#pragma region Partition Classes
class Situation
{
public:
	Situation() {};
	Situation(Symbol* F, Plural TA, Plural TB, int P) { From = F; ToA = TA; ToB = TB; Position = P; };
	Symbol* From;
	Plural ToA;
	Plural ToB;
	int Position;
};

class SituationNode
{
public:
	SituationNode() {};
	SituationNode(Situation* S) { Value = S; };
	Situation* Value;
	SituationNode* Next;
	void setValue(Situation* link)
	{
		Value = link;
	}
	void setNext(SituationNode* link)
	{
		Next = link;
	}
	Situation* operator[](int a)
	{
		if (a == 0) return Value;
		else
			return (*Next)[a - 1];
	}
};


class Partition
{
public:
	Partition() {};
	SituationNode* First;
	SituationNode* Last;
	int Count=0;
	Partition* Next;
	void add(Situation* link)
	{
		if (Count > 0)
		{
			SituationNode* p = new SituationNode();
			(*p).setValue(link);
			(*Last).setNext(p);
			Last = p;
			Count++;
		}
		else
		{
			SituationNode* p = new SituationNode();
			(*p).setValue(link);
			Last = p; First = p;
			Count++;
		}
	}
	Situation* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First)[a];
		else
			return (*Last)[0];
	}
	Partition* Get(int a)
	{
		if (a == 0) return this;
		else
			return (*Next).Get(a - 1);
	}
	void setNext(Partition* link)
	{
		Next = link;
	}
};

class Deconstruction
{
public:
	Deconstruction() {};
	Partition* First;
	Partition* Last;
	int Count=0;
	void add()
	{
		if (Count > 0)
		{
			Partition* p = new Partition();
			(*Last).setNext(p);
			Last = p;
			Count++;
		}
		else
		{
			Partition* p = new Partition();
			Last = p; First = p;
			Count++;
		}
	}
	Partition* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First).Get(a);
		else
			return (*Last).Get(0);
	}
};
#pragma endregion

class Grammar
{
private:
	Alphabet AAlphabet;
	Alphabet BAlphabet;
	Alphabet RAlphabet;
	Alphabet TAlphabet;
	Codex Rules;
public:
	Grammar() {};

	void AltReading(string s,unsigned int& k, Symbol* ParentBrackets)
	{		
	//Create references
		Symbol* A = new Symbol("A"+to_string(AAlphabet.Count));
		AAlphabet.add(A);
		Rule* R0 = new Rule(ParentBrackets, A);
		Rules.add(R0);
		Rule* R = new Rule(A);
	//Start reading
		bool stay_in = true;
		while ((k < s.length())&stay_in)
		{
			if (s[k] != '\\')
			{
				Symbol* T = new Symbol(s.substr(k,1));
				T = TAlphabet.add(T);
				(*R).Add(T);
				k++;
			}
			else
			{
				if (s[k+1] == '\\')
				{
					Symbol* T = new Symbol(s.substr(k+1, 1));
					T = TAlphabet.add(T);
					(*R).Add(T);
					k++; k++;
				}
				else if (s[k + 1] == ')')
				{
					k++; k++;
					stay_in = false;
				}
				else if (s[k + 1] == '(')
				{
					k++; k++;
					Symbol* B = new Symbol("B" + to_string(BAlphabet.Count));
					BAlphabet.add(B);
					(*R).Add(B);
					AltReading(s, k, B);
				}
				else if (s[k + 1] == '*')
				{
					k++; k++;
					Symbol* Rep = new Symbol("R" + to_string(RAlphabet.Count));
					RAlphabet.add(Rep);
					Rule* R1 = new Rule(Rep,(*R).To[(*R).To.Count-1]);
					(*R1).Add(Rep);
					Rules.add(R1);
					(*R).Switch(Rep);
				}
				else if (s[k + 1] == '|')
				{
					k++; k++; stay_in = false;
					AltReading(s, k, ParentBrackets);
				}
				else
				{
					k++; int c = 0;
					while (((int)s[k] < 58) & ((int)s[k]>47))
					{
						c += c * 9 + (int)(s[k]) - 48; 
						k++;
					}
					if (s[k] == ' ') k++;
					(*R).Add(BAlphabet[c]);
				}
			}
		}
		Rules.add(R);
	}
	Grammar(string s) //Combine grammar
	{
		/*
init: Create B0 +
0 Create A1 +
1 B0 -> A1 +
2 Ai -> Reading +
2.1 If Brackets open then +
	2.1.1 Create B last_b +
	2.1.2 Ai -> ...B last_b +
	2.1.3 Create A last_a +
	2.1.4 B last_b -> A last_a +
	2.1.5 Go to 2 (last_a) +
2.2 If Alternative then +
	2.2.1 Create A last_a +
	2.2.1 ParentBrackets(Ai) -> A last_a +
	2.2.2 Go to 2 (last_a) +
2.3 If Brackets close (EOL) then +
	2.3.1 Drop back to ParentBrackets +
	2.3.2 Drop back to ParentAlternative (Finish process of reading!) +
	2.3.3 Go to 2 (ParentAlternative(ParentBrackets(Ai))) +
2.4 If Link then +
	2.4.1 Ai -> ...B link +
	2.4.2 Go to 2 (i) +
2.5 If Replicator then +
	2.5.1 Create R last_r +
	2.5.2 Ai -> ...R last_r +
	2.5.3 R last_r -> prev_Symbol +
	2.5.4 R last_r -> ...R last_r +
	2.5.5 Go to 2 (i) +
2.6 Else +
	2.6.1 Create (if not exists) Symbol T last_t (Tk) +
	2.6.2 Ai -> ...T last_t (Ai -> ...Tk) +
	2.6.3 Go to 2 (i) +
3 Create S +
4 S -> B0 +
*/
		unsigned int k = 0;
		Symbol* S = new Symbol("S");
		AAlphabet.add(S);
		Symbol* B0 = new Symbol("B0");
		BAlphabet.add(B0);
		Rule* R = new Rule(S, B0);
		Rules.add(R);
		AltReading(s, k, B0);
	};
	void Report()
	{
		cout << "Symbols Alphabet:" << endl;
		TAlphabet.Report(); cout << endl;

		cout << "Symbols Alphabet:" << endl;
		AAlphabet.Report();
		BAlphabet.Report();
		RAlphabet.Report(); cout << endl;

		cout << "Rules list:" << endl;
		Rules.Report(); cout << endl;
	};

	void Scan(Deconstruction* D, int j, string s)
	{
		if (j == 0) return;
		else
		{
			for (int i = 0; i < (*((*D)[j - 1])).Count; i++)
			{
				if ((*(*(*(*D)[j - 1])[i]).ToB[0]) == Symbol(s.substr(j - 1, 1)))
				{
					
					(*(*D)[j]).add((*(*D)[j - 1])[i]);
				}
			}
		}
	}

	void Complete(Deconstruction* D, int j, string s)
	{
		for (int i = 0; i < (*((*D)[j])).Count; i++)
		{
			if ((*(*(*D)[j])[i]).ToB.Count==0)
			{
				int k = (*(*(*D)[j])[i]).Position;
				for (int r = 0; r < (*((*D)[k])).Count; r++)
				{
					if ((*(*(*(*D)[k])[r]).ToB[0]) == (*(*(*(*D)[j])[i]).From))
					{
						Situation T = *(*(*D)[k])[r];
						T.ToA.add(T.ToB[0]);
						T.ToB.Skip();
						Situation* S = new Situation(T.From,T.ToA,T.ToB,T.Position);
						(*(*D)[j]).add(S);
					}
				}
			}
		}
	}

	void Predict(Deconstruction* D, int j, string s)
	{
		for (int i = 0; i < (*((*D)[j])).Count; i++)
		{
			if ((*(*(*(*D)[j])[i]).ToB[0]).Value.length()>1)
			{
				for (int r = 0; r < Rules.Count; r++)
				{
					if ((*((*Rules[r]).From)) == ((*(*(*(*D)[j])[i]).ToB[0])))
					{
						Plural* P = new Plural();
						Situation* S = new Situation((*Rules[r]).From, *P, (*Rules[r]).To, j);
						(*(*D)[j]).add(S);
					}
				}
			}
		}
	}

	bool CheckLine(string s) //Proceed algorithm
	{

	};
};

int main()
{
	Grammar G = Grammar("\\(\\|(\\1)\\1\\)");
	G.Report();

	cout << endl;
}