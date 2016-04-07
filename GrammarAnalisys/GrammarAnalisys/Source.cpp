#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

ofstream ofs("OUTPUT.txt");
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
	void setValue(Symbol* link,int k)
	{
		if (k > 0) (*Next).setValue(link, k - 1); else Value = link;
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
	Litera* getNext()
	{
		return Next;
	}
	void add(Litera* p, int k)
	{
		if (k > 0) (*Next).add(p, k - 1);
		else
		Next = p;
	}
};

class Plural
{
private:
	Litera* First;
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
			(*First).add(p,Count-1);
			Count++;
		}
		else
		{
			Litera* p = new Litera();
			(*p).setValue(link);
			First = p;
			Count++;
		}
	}
	void Switch(Symbol* link)
	{
		(*First).setValue(link,Count-1);
	}
	Symbol* operator[](int a)
	{
		if ((a<Count)&(a>-1))
			return (*First)[a];
		else
			return (*First)[0];
	}
	bool operator== (Plural p)
	{
		bool b = true;
		if (Count != p.Count) b = false;
		else
		{
			if (Count == 0) return true;
			else
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
	bool operator==(Situation S)
	{
		return((*From == *S.From)&(ToA == S.ToA)&(ToB == S.ToB)&(Position == S.Position));
	}
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
	bool Exists(Situation* link, int k)
	{
		if ((*Value) == (*link))
			return true;
		else
			if (k == 0) return false;
			else
				return (*Next).Exists(link, k - 1);
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
	int add(Situation* link)
	{
		if (Count > 0)
		{
			if (!(*First).Exists(link, Count - 1))
			{
				SituationNode* p = new SituationNode();
				(*p).setValue(link);
				(*Last).setNext(p);
				Last = p;
				Count++;
				return 1;
			}
			else
				return 0;
		}
		else
		{

			SituationNode* p = new SituationNode();
			(*p).setValue(link);
			Last = p; First = p;
			Count++;
			return 1;

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
		unsigned int k = 0;
		Symbol* S = new Symbol("S");
		AAlphabet.add(S);
		Symbol* B0 = new Symbol("B0");
		BAlphabet.add(B0);
		Rule* R = new Rule(S, B0);
		Rules.add(R);
		AltReading(s, k, B0);
	};

	void Scan(Deconstruction* D, int j, string s)
	{
		if (j == 0) return;
		else
		{
			for (int i = 0; i < (*((*D)[j - 1])).Count; i++)
			{
				if (((*(*(*D)[j-1])[i]).ToB.Count)>0)
				{
					if ((*(*(*(*D)[j - 1])[i]).ToB[0]) == Symbol(s.substr(j - 1, 1)))
					{
						Situation T = *(*(*D)[j-1])[i];
						T.ToA.add(T.ToB[0]);
						T.ToB.Skip();
						Situation* S = new Situation(T.From, T.ToA, T.ToB, T.Position);
						(*(*D)[j]).add(S);
					}
				}
			}
		}
	}

	int Complete(Deconstruction* D, int j, string s)
	{
		int o = 0;
		for (int i = 0; i < (*((*D)[j])).Count; i++)
		{
			if ((*(*(*D)[j])[i]).ToB.Count==0)
			{
				int k = (*(*(*D)[j])[i]).Position;
				for (int r = 0; r < (*((*D)[k])).Count; r++)
				{
					if ((*(*(*D)[k])[r]).ToB.Count > 0)
					{
						if ((*(*(*(*D)[k])[r]).ToB[0]) == (*(*(*(*D)[j])[i]).From))
						{
							Situation T = *(*(*D)[k])[r];
							T.ToA.add(T.ToB[0]);
							T.ToB.Skip();
							Situation* S = new Situation(T.From, T.ToA, T.ToB, T.Position);
							o += (*(*D)[j]).add(S);

						}
					}
				}
			}
		}
		return o;
	}

	int Predict(Deconstruction* D, int j, string s)
	{
		int o = 0;
		for (int i = 0; i < (*((*D)[j])).Count; i++)
		{
			if (((*(*(*D)[j])[i]).ToB.Count)>0)
			{
				if ((*(*(*(*D)[j])[i]).ToB[0]).Value.length() > 1)
				{
					for (int r = 0; r < Rules.Count; r++)
					{
						if ((*((*Rules[r]).From)) == ((*(*(*(*D)[j])[i]).ToB[0])))
						{
							Plural* P = new Plural();
							Situation* S = new Situation((*Rules[r]).From, *P, (*Rules[r]).To, j);
							o += (*(*D)[j]).add(S);

						}
					}
				}
			}
		}
		return o;
	}

	bool CheckLine(string s) //Proceed algorithm
	{
		//Initialization
		Deconstruction D = Deconstruction();
		D.add();
		Plural* P = new Plural;
		Situation* S = new Situation((*Rules[0]).From, *P, (*Rules[0]).To, 0);
		(*D[0]).add(S);
		int y = 1;
		while (y != 0)
		{
			y = Complete(&D, 0, s) + Predict(&D, 0, s);
		}

		for (int i = 1; i <= s.length(); i++)
		{
			D.add();
		}

		//Calculating
		for (int i = 1; i <= s.length(); i++)
		{
			Scan(&D, i, s);
			int y = 1;
			while (y != 0)
			{
				y = Complete(&D, i, s) + Predict(&D, i, s);
			}
		}

		//Resulting
		bool b = false;
		for (int i = 0; i < (*(D[s.length()])).Count; i++)
		{
			if (*((*(*(D[s.length()]))[i]).From) == *((*Rules[0]).From))
			{
				if (((*(*(D[s.length()]))[i]).ToA) == ((*Rules[0]).To))
				{
					if (((*(*(D[s.length()]))[i]).ToB.Count) == 0)
					{
						b = true;
					}
				}
			}
		}
		return b;
	};
};


int main()
{

	ifstream ifs("INPUT.txt");
	string s;

	getline(ifs, s);
	ofs << s << endl;
	Grammar G = Grammar(s);
	ofs << endl;

	while (!ifs.eof())
	{
		getline(ifs, s);
		ofs <<"Control line:"<<endl<< s << endl;
		if (G.CheckLine(s))
		{
			ofs <<"Result:"<<endl<< "Success" << endl; // SOME KIND OF FUUUUUUCK!!!
		}
		else
		{
			ofs << "Result:" << endl << "Fail" << endl;
		}
		ofs << endl;
	};

	ifs.close();	
	ofs.close();
}