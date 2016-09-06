//Program for identifying integers and floating point numbers
/*
Grammar rules ->
S -> PD | PD.D | PDXPD | PD.DXPD
D -> 0 | 1 | ..... | 9
P -> + | - | NULL
X -> e | 'E'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int usedExp = 0;

int isDigit(char a)
{
	int i, num = a - 48;
	for(i=0; i<=9; i++)
		if( num == i)
			return 1;
	return 0;
}

int isSign(char a)
{
	if (a == '+' || a == '-')
		return 1;
	return 0;
}

int isExpo(char a)
{
	if ( a == 'e' || a == 'E')
		return 1;
	return 0;
}

int checkBefPt(char *str, int j)
{
	printf("before point string %c\n", str[j]);
	int isValid = 1, i=0;

	if(isSign(str[i]))
		++i;

	if(isDigit(str[i]))
		while(isDigit(str[i])) ++i;
	else
		isValid = 0;

	if(i < j && isExpo(str[i]) && isValid)
	{
		usedExp = 1;
		++i;
		if(isSign(str[i]))
			++i;

		if(isDigit(str[i]))
			while(isDigit(str[i])) ++i;
		else
			isValid = 0;
	}

	return isValid;
}

int checkAftPt(char *str, int j)
{
	printf("after point string %c\n", str[j]);
	int isValid = 1, i=j;
	int sLen = strlen(str);

	if(isDigit(str[i]))
		while(isDigit(str[i])) ++i;
	else
		isValid = 0;	
	
	if(i < sLen && isValid && isExpo(str[i]))
	{
		if(usedExp)
			isValid = 0;
		++i;
		if(isSign(str[i]))
			++i;

		if(isDigit(str[i]))
			while(isDigit(str[i])) ++i;
		else
			isValid = 0;
	}

	//last character must be a digit
	//if(isDigit(str[sLen-1]) == 0)
	//	isValid = 0;

	return isValid;
}

int checkValidity( char *str)
{	
	int sLen = strlen(str);
	int i = 0, isValid = 1;
	
	while(i < sLen && !isExpo(str[i]) && str[i] != '.')
		i++;

	if(!checkBefPt(str, i))
		isValid = 0;
	
	//printf("before point=%d\n",checkBefPt(str, i));

	if(i < sLen && isValid)
	{
		if(usedExp)
			isValid = 0;
		i++;
		if(isValid && !checkAftPt(str, i))
			isValid = 0;
		//printf("after point=%d\n",checkAftPt(str, i));
	}

	return isValid;
}

int main(void)
{
	puts("This program checks whether a string belongs to set {integers, floats, exponentials}.");
	puts("Enter any string to check (0 < size < 100):");

	char *str;
	size_t size = 100;
	int index, flag = -1, len;

	str = (char *) malloc (size + 1);
  	len = getline (&str, &size, stdin);
	if(len == -1)
	{
		puts("ERROR!!");
		return 0;
	}
	
	if(checkValidity(str) == 1)
		puts("String entered belongs to the set {integers, floats, exponentials}.");
	else
		puts("String entered does NOT belong to the set {integers, floats, exponentials}.");
	return 0;
}