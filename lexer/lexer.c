//LEXER for C, eliminates comments, extra white chareacters
#include <stdio.h>
#include <stdlib.h>

void comment_removal(FILE *fpr, FILE *fpw)
{
	char ch, save;
	//long int curr_pos;
	while((ch = fgetc(fpr)) != EOF )
	{
		if(ch == '/')
		{
			//curr_pos = ftell(fpr);
			save = ch;
			ch = fgetc(fpr);
			if(ch == '/')
			{
				while((ch = fgetc(fpr)) != '\n');
			}
			else if(ch == '*')
			{
				while(ch != '/')
				{
					while((ch = fgetc(fpr)) != '*');
					ch = fgetc(fpr);
					if(ch == '/')
						break;
				}
			}
			else
			{
			 	fputc(save, fpw);
			 	fputc(ch, fpw);
			}
		}
		else
			fputc(ch, fpw);
	}
}

int is_space(char ch)
{
	int res = 0;
	switch(ch)
	{
		case ' ':
		case '\t':
		case '\n':
			res = 1;
	}
	return res;
}

void ext_sp_removal(FILE *fpr, FILE *fpw)
{
	char ch, save;
	while((ch = fgetc(fpr)) != EOF )
	{
		if(is_space(ch) == 1)
		{
			save = ch;
			while((ch = fgetc(fpr)) != EOF)
			{
				if(is_space(ch) == 0)
					break;
			}
			fputc(save, fpw);
			fputc(ch, fpw);
		}
		else
			fputc(ch, fpw);
	}
}

int main(int argc, char** argv)
{
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "w+");
	FILE *temp = fopen("temp.txt", "w+");
	comment_removal(fp1, temp);
	fclose(fp1);
	fclose(temp);
	temp = fopen("temp.txt", "r");
	ext_sp_removal(temp, fp2);
	fclose(fp2);
	return 0;
}