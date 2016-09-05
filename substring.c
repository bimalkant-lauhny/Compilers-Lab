#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *s1, *s2;
	size_t size = 100;
	int index, flag = -1, len1, len2;

	puts("Enter a sentence:");	
 	//scanf("%[^\t\n]s", &s1);
	s1 = (char *) malloc (size + 1);
  	len1 = getline (&s1, &size, stdin);
	if(len1 == -1)
	{
		puts("ERROR!!");
		return 0;
	}
	//puts(s1);
	puts("Enter a substring to be searched:");
	s2 = (char *) malloc (size + 1);
  	len2 = getline (&s2, &size, stdin);
	if(len2 == -1)
	{
		puts("ERROR!!");
		return 0;
	}
	//puts(s2);
	//printf("%d %d", len1, len2);
	len1 --;
	len2 --;

	for(int i=0; i < len1; i++)
	{
		if(s2[0] == s1[i])
		{
			//printf("%c\n", s1[i]);
			for(int j=1; j < len2; j++)
			{
				if(i+j >= len1 || s2[j] != s1[i+j])
				{
					flag = 0;	
					break;
				}
				flag = 1;
			} 	
			if(flag == 1)
			{
				index = i;
				break;
			}	
		}
	}
	if(flag == 1)
		printf("Found substring at index %d at location %p.\n", index, s1+index);
	else
		printf("Substring not found!!!\n");
	return 0;
}
