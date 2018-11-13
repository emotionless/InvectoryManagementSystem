#include<stdio.h>

void check_id(char *p, int size)
{
	int i=0;
	char ch;

	do
	{
		ch=getch();

		if( (ch>='0' && ch<='9') && (i<size-1) )
		{
			 *p=ch;
			 p++;
			 i++;
			 cout<<"%c",ch;
		}
		else
		if(ch==8 && i>0)
		{
			cout<<"%c%c%c",8,32,8;
			i--;
			p--;
			}

	}while(ch!=13 || i<size-1);

	*p='\0';

}

void check_name(char *p, int size)
{
	int j=0;
	char x[40],cj;

	do
	{

		cj=toupper(getch());

		if(((cj>='a' && cj<='z')||(cj>='A' && cj<='Z')||(cj==' ')) && (j<size-1))
		{
			*p++=cj;
			j++;
			cout<<"%c",cj;
		}

		else

		if(cj==8 && j>0)
		{
			cout<<"%c%c%c",8,32,8;
			j--; p--;
		}

	}while(cj!=13);

	x[j]='\0';
	*p='\0';
}