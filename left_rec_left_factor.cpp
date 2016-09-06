#include <bits/stdc++.h>
using namespace std;

/*
Given Grammar:
	S -> Aa | b
	A -> Ac | Sd | ^
*/

#define R 10
vector < string > prod_rules [R]; // stores grammar

map < char, int > rule_no;

int usedChar[26]; // characters already used
int num; // curr num of prod
 
bool isTerminal(char a)
{
	if(a >= 65 && a <= 90)
		return false;
	return true;
}

bool isNonTerminal(char a)
{
	if(a >= 65 && a <= 90)
		return true;
	return false;
}

bool isNull(char a)
{
	if (a == '^')
		return true;
	return false;
}

void define_grammar()
{
	//S -> Aa | b
	fill(usedChar, usedChar+26, 0);

	rule_no['S'] = 0;
	prod_rules[0].push_back("S");
	prod_rules[0].push_back("Aa");
	prod_rules[0].push_back("b");

	// A -> Ac | Sd | ^
	rule_no['A'] = 1;
	prod_rules[1].push_back("A");
	prod_rules[1].push_back("Ac");
	prod_rules[1].push_back("Sd");
	prod_rules[1].push_back("^");

	num = 2;
	usedChar[65 - 'A'] = 1;
	usedChar[65 - 'S'] = 1;
}

/*
void define_grammar()
{
	//S -> Aa | b
	fill(usedChar, usedChar+26, 0);

	rule_no['E'] = 0;
	prod_rules[0].push_back("E");
	prod_rules[0].push_back("E+T");
	prod_rules[0].push_back("T");

	num = 1;
	usedChar[65 - 'E'] = 1;
}
*/
/*
bool ifTendsNull(int pn) // if production ultimately tends to null
{
	bool success = false;
	for(int j=1; j<prod_rules[pn].size(); j++)
	{
		string pr = prod_rules[pn][j];
		
		if(isNull(pr[0]))
		{
			success = true;
			break;
		}

		if (isNonTerminal(pr[0]) && ifTendsNull(rule_no[pr[0]]) == false)
		{	
			success = false;
			break;
		}
		else
			continue;
	}
	return success;
}
*/

void directRec()
{
	vector <string> alpha;
	vector <string> beta;
	int numrules = num;
	for(int i=0; i<numrules; i++)
	{
		char a = prod_rules[i][0][0];

		for(int j = 1; j <  prod_rules[i].size(); j++)
		{
			char b = prod_rules[i][j][0];

			if(a == b)
			{
				alpha.push_back(prod_rules[i][j].substr(1)); 
			}
			else
			{
				beta.push_back(prod_rules[i][j]);
			}
		}

		if(alpha.size() > 0)
		{
			cout << "alpha" << endl;
			for(int k=0 ;k<alpha.size(); k++)
				cout << alpha[k] << " ";
			cout << endl << "beta" << endl;
			for(int k=0 ;k<beta.size(); k++)
				cout << beta[k] << " ";
			cout << endl;
			char p; // next character to be used

			for(int k=0; k<26; k++)
				if(usedChar[k] == 0)
				{
					p = k + 65;
					break;
				}

			string newrule(1, p);
			
			prod_rules[num].push_back(newrule);

			string rule = prod_rules[i][0];
			prod_rules[i].clear();
			prod_rules[i].push_back(rule);

			if(beta.size() == 0)
			{
				prod_rules[i].push_back(newrule);
			}
			else
			{
				for(int k=0; k<beta.size();k++)
				{
					if(isNull(beta[k][0]))
						prod_rules[i].push_back("^");
					else
						prod_rules[i].push_back(beta[k] + newrule);
				}
			}
			beta.clear();

			for(int k=0; k<alpha.size(); k++)
			{
				prod_rules[num].push_back(alpha[k]+newrule);
			}
			prod_rules[num].push_back("^");
			alpha.clear();
			rule_no[p] = num;
			num++;
		}
		beta.clear();
	}
}

void indirectRec()
{
	stack <string> temp;
	int numrules = 0;
	for(int i=1; i<num; i++)
	{

		char a = prod_rules[i][0][0];

		for(int j = 1; j <  prod_rules[i].size(); j++)
		{
			char b = prod_rules[i][j][0];

			if(isTerminal(b))
			{
				cout << "Inside Production " << a << "->" << b << endl;
				string alpha = prod_rules[i][j].substr(1);
				int rule = rule_no[b];
				if(rule < i)
				{
					for(int k=prod_rules[i].size()-1; k>i; k--)
					{
						temp.push(prod_rules[i][k]);
						cout << "pushing " << prod_rules[i][k] << endl;
					}
					int lim = prod_rules[i].size();
					for(int k=lim-1; k>=i; k--)
					{
						prod_rules[i].pop_back();
					}

					for(int k=0; k<prod_rules[rule].size(); k++)
					{
						prod_rules[i].push_back(prod_rules[rule][k] + alpha);
					}
					while(!temp.empty())
					{
						prod_rules[i].push_back(temp.top());
						temp.pop();
					}
				}
			}
		}
	}
}

void printGrammar()
{
	for(int i=0; i<num; i++)
	{
		for(int j=0; j<prod_rules[i].size(); j++)
			cout << prod_rules[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void debug()
{

}

int main()
{
	define_grammar();
	//debug();
	indirectRec();
	printGrammar();

	return 0;
}