#include <bits/stdc++.h>
using namespace std;

/*
Given Grammar:
	E  ->  TA
	A ->  +TA | ^
	T  ->  FP
	P ->  *FT | ^
	F  ->  (E) | d
*/

#define R 5
vector < string > prod_rules [R]; // stores grammar

map < char, int > rule_no;

set < char > FIRST[R]; // stores FIRST set
set < char > FOLLOW[R]; // stores FOLLOW set

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
	// E -> TA
	rule_no['E'] = 0;
	prod_rules[0].push_back("E");
	prod_rules[0].push_back("TA");

	// A -> +TA | ^
	rule_no['A'] = 1;
	prod_rules[1].push_back("A");
	prod_rules[1].push_back("+TA");
	prod_rules[1].push_back("^");

	// T -> FP
	rule_no['T'] = 2;
	prod_rules[2].push_back("T");
	prod_rules[2].push_back("FP");

	//P ->  *FT | ^
	rule_no['P'] = 3;
	prod_rules[3].push_back("P");
	prod_rules[3].push_back("*FP");
	prod_rules[3].push_back("^");

	//F  ->  (E) | d
	rule_no['F'] = 4;
	prod_rules[4].push_back("F");
	prod_rules[4].push_back("(E)");
	prod_rules[4].push_back("d");	

}

/*
void define_grammar()
{
	// E -> TA
	rule_no['S'] = 0;
	prod_rules[0].push_back("S");
	prod_rules[0].push_back("aBDh");

	// A -> +TA | ^
	rule_no['B'] = 1;
	prod_rules[1].push_back("B");
	prod_rules[1].push_back("cC");

	// T -> FP
	rule_no['C'] = 2;
	prod_rules[2].push_back("C");
	prod_rules[2].push_back("bC");
	prod_rules[2].push_back("^");

	//P ->  *FT | ^
	rule_no['D'] = 3;
	prod_rules[3].push_back("D");
	prod_rules[3].push_back("EF");

	//F  ->  (E) | d
	rule_no['E'] = 4;
	prod_rules[4].push_back("E");
	prod_rules[4].push_back("g");
	prod_rules[4].push_back("^");	

	rule_no['F'] = 5;
	prod_rules[5].push_back("F");
	prod_rules[5].push_back("f");
	prod_rules[5].push_back("^");
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
void unionFirst(int i, int r)
{
	set<char>::iterator it;
		for( it=FIRST[r].begin(); it!=FIRST[r].end(); it++)
			FIRST[i].insert(*it);
}

void unionFollowFirst(int i, int r)
{
	set<char>::iterator it;
		for( it=FIRST[r].begin(); it!=FIRST[r].end(); it++)
			if(!isNull(*it))
				FOLLOW[i].insert(*it);
}

void unionFollow(int i, int r)
{
	set<char>::iterator it;
		for( it=FOLLOW[r].begin(); it!=FOLLOW[r].end(); it++)
			FOLLOW[i].insert(*it);
}

void find_first(int i)
{
	for(int j=1; j<prod_rules[i].size(); j++)
	{
		string pr = prod_rules[i][j];
		int k = 0;
		
		if (isTerminal(pr[k]) || isNull(pr[k]))
			FIRST[i].insert(pr[k]);

		else
		{
			/*
			while(k < pr.size())
			{
				if(ifTendsNull(pr[k]))
				{
						k++; continue;
				} 
				
				find_first(rule_no[pr[k]]);
				unionFirst(i, rule_no[pr[k]]);
				break;
			
				if(FIRST[rule_no[pr[k]]].size() == 0)
					find_first(rule_no[pr[k]]);
				unionFirst(i, rule_no[pr[k]]);
			}
			*/
			while(k < pr.size())
			{
				int rule = rule_no[pr[k]];
				
				if(FIRST[rule].size() == 0)
					find_first(rule);
				
				unionFirst(i, rule);
				
				bool flag = false;
				for(set<char>::iterator it = FIRST[rule].begin(); it != FIRST[rule].end(); it++)
					if(*it == '^')
					{	flag = true; 
						k++;
						break; 
					}
				if(flag == false)
					break;
			}
		}
	}
}

void findFollow(int k)
{
	char prodChar = prod_rules[k][0][0];
	for(int i=0; i<R; i++)
	{
		for(int j=1; j<prod_rules[i].size(); j++)
		{
			string pr = prod_rules[i][j];
			int index = -1;
			
			for(int s=0; s<pr.size(); s++)
				if(pr[s] == prodChar)
				{	index = s; break; }

			if(index == -1)
				continue;
			
			if(index == pr.size() - 1)
			{
				if(FOLLOW[i].size() == 0)
					findFollow(i);

				unionFollow(k, i);
				continue;
			}

			int rule;
			
			if((index) < pr.size() - 1)
			{
				char ch = pr[index+1];
				
				if(isTerminal(ch))
					FOLLOW[k].insert(ch);

				else if(isNonTerminal(ch))
				{
					rule = rule_no[ch];

					unionFollowFirst(k, rule);

					bool flag = false;
					for(set<char>::iterator it = FIRST[rule].begin(); it != FIRST[rule].end(); it++)
						if(*it == '^')
						{	flag = true; break; }
					
					
					if(flag)
					{
						if(FOLLOW[rule].size() == 0)
							findFollow(rule);
						unionFollow(k, rule);
					}
				}
			}

		}
	}
}

void printFirst()
{
	set<char>::iterator it;
	for(int i=0; i<R; i++)
	{
		cout << "FIRST " << "(" << prod_rules[i][0] << ")" << " -> ";
		cout << "{ ";
		for(it = FIRST[i].begin(); it!=FIRST[i].end(); it++)
			cout << *it << ", ";
		cout << "\b\b }"<<endl;
	}
	cout << endl;
}

void printFollow()
{
	set<char>::iterator it;
	for(int i=0; i<R; i++)
	{
		cout << "FOLLOW " << "(" << prod_rules[i][0] << ")" << " -> ";
		cout << "{ ";
		for(it = FOLLOW[i].begin(); it!=FOLLOW[i].end(); it++)
			cout << *it << ", ";
		cout << "\b\b }"<<endl;
	}

	cout << endl;
}

void debug()
{
	for(int i=0; i<R; i++)
	{
		for(int j=0; j<prod_rules[i].size();j++)
			cout << prod_rules[i][j] << " ";
		cout  << endl;
	}

		cout << rule_no['S'] << endl;
		cout << rule_no['B'] << endl;
		cout << rule_no['C'] << endl;
		cout << rule_no['D'] << endl;
		cout << rule_no['E'] << endl;
		cout << rule_no['F'] << endl;
}

int main()
{
	define_grammar();
	//debug();
	for(int i=0; i<R; i++)
		if(FIRST[i].size() == 0)
			find_first(i);

	printFirst();

	FOLLOW[0].insert('$');
	findFollow(0);
	for(int i=1; i<R; i++)
		if(FOLLOW[i].size() == 0)
			findFollow(i);

	printFollow();

	return 0;
}