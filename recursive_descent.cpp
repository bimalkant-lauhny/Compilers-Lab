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

vector <string> prod_rules[R];

string inpString;
int readPointer;

map < char, int > rule_no;

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
	prod_rules[3].push_back("*FT");
	prod_rules[3].push_back("^");

	//F  ->  (E) | d
	rule_no['F'] = 4;
	prod_rules[4].push_back("F");
	prod_rules[4].push_back("(E)");
	prod_rules[4].push_back("d");
	//prod_rules[4].push_back("^");		

}
//d+d*d;
bool parseRecDescent(int rule)
{
	bool status = false;
	int prevPointer = readPointer;
	for(int i=1; i<prod_rules[rule].size(); i++)
	{
		prevPointer = readPointer;
		for(int j=0; j<prod_rules[rule][i].size(); j++)
		{
			char currChar =  prod_rules[rule][i][j];
			if(isNull(currChar))
				status = true;
			else if(isNonTerminal(currChar))
				status = parseRecDescent(rule_no[currChar]);
			else if(inpString[readPointer] == currChar)
			{
				readPointer++;
				status = true;
			}
			else
			{
				status = false;
			}
			if(!status)
			{
				readPointer = prevPointer;
				break;
			}
			else
			{
				if(readPointer == inpString.size())
					return true;
			}
		}
	}

	return status;
}

int main()
{
	define_grammar();
	cin >> inpString;
	readPointer = 0;

	bool success = parseRecDescent(rule_no['E']);
	if(success == true)
		cout << "String Successfully Parsed..\n";
	else
		cout << "String could not be Parsed..\n";

	return 0;
}