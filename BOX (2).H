void box(int a, int b, int c, int d)
{
	
	for(int i = a; i < c; i++)
	{
		gotoxy(i,b);	cout<<"\xcd";
		gotoxy(i,d);	cout<<"\xcd";
	}
	
	for(int j = b; j < d; j++)
	{
		gotoxy(a,j);	cout<<"\xba";
		gotoxy(c,j);	cout<<"\xba";
	}
	
	gotoxy(a,b);	cout<<"\xc9";
	gotoxy(c,b);	cout<<"\xbb";
	gotoxy(a,d);	cout<<"\xc8";
	gotoxy(c,d);	cout<<"\xbc";
	
}