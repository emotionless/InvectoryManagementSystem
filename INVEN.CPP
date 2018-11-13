#include <iostream.h>
#include       <io.h>
#include      <dos.h>
#include  <process.h>
#include   <stdlib.h>
#include    <conio.h>
#include    <stdio.h>
#include   <string.h>
#include    <ctype.h>

#include      "Box.h"
#include    "Valid.h"

#define MIN 2
#define NUM 5
#define MAX 20

struct inventory
{
    char id[NUM];
    char name[MAX];
    double pai, cos, bal;
    int day, month, year;
    int status;
} in;

void splash();

void password();

void check_id(char *,int);
void check_name(char *,int);
void menu();
void viewmenu();
void searchmenu();
void helpmenu();

void add(inventory *in);
void paid(inventory *in);
void cost(inventory *in);
void view(inventory *in);
void viewall(inventory *in);
void print(inventory *in);
void delet(inventory *in);
void searchid(inventory *in);
void searchname(inventory*in);
void searchcase(inventory*in);

void intro();
void usage();

void about();

void quit();


void main()
{
    splash();
}
void add(inventory *in)
{
    FILE *f;
    char ch;
    in->bal = 0;
    f = fopen("inventory.dat","ab");
    if (f != NULL)
    {
        do
        {
            clrscr();
            _setcursortype(_SOLIDCURSOR);
            box(12,3,69,5);
            gotoxy(31,4);
            cprintf("INVENTORY MANAGEMENT SYSTEM");
            box(16,7,65,20);
            gotoxy(29,7);
            cprintf(" ++ 1.ADD NEW PRODUCT ++ ");
            gotoxy(27,10);
            cprintf("SERIAL NO  : ");
            check_id(in->id, NUM);
            gotoxy(27,12);
            cprintf("ENTER PRODUCT NAME : ");
            check_name(in->name, MAX);

            {
                struct date d;

                getdate(&d);
                in->day   = d.da_day;
                in->month = d.da_mon;
                in->year  = d.da_year;
            }

            _setcursortype(_NOCURSOR);

            gotoxy(27,14);
            cputs("ADDING DATE : ");
            gotoxy(42,14);
            cout<<in->day<<"-"<<in->month<<"-"<<in->year;
            gotoxy(27,16);
            cprintf("BASE PRICE %.00lf",in->bal);
            gotoxy(19,19);
            cputs(in->id);
            gotoxy(28,19);
            cputs(in->name);
            gotoxy(48,19);
            cprintf("%d-%d-%d",in->day,in->month,in->year);
            gotoxy(62,19);
            cprintf("%.00lf",in->bal);

            fwrite(in, sizeof(struct inventory), 1, f);
            fclose(f);

            gotoxy(18,23);
            cprintf("DO YOU WANT TO ENTER ANOTHER RECORD? [Y]/[N] : ");

            ch = getche();

        }
        while(ch =='Y' || ch == 'y');
    }

    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    menu();
}
void view(inventory *in)
{
    FILE *f;
    char ch;

    f = fopen("inventory.dat","rb");
    if(f != NULL)
    {
        clrscr();
        while( fread(in, sizeof(struct inventory), 1, f))
            if(in->status == 0)
            {

                clrscr();
                box(12,3,69,5);
                gotoxy(31,4);
                cprintf("INVENTORY MANAGEMENT SYSTEM");
                box(16,7,65,20);
                gotoxy(29,7);
                cprintf("  2.VIEW ALL PRODUCTS  ");
                _setcursortype(_NOCURSOR);
                gotoxy(27,10);
                cprintf("SERIAL NO     : %s",in->id);
                gotoxy(27,12);
                cprintf("PRODUCT NAME %s",in->name);
                gotoxy(27,14);
                cprintf("ADDING DATE  : %d-%d-%d",in->day,in->month,in->year);
                gotoxy(27,16);
                cprintf("BASE PRICE %.00lf",in->bal);
                gotoxy(19,19);
                cputs(in->id);
                gotoxy(26,19);
                cputs(in->name);
                gotoxy(46,19);
                cprintf("%d-%d-%d",in->day,in->month,in->year);
                gotoxy(59,19);
                cprintf("%.00lf",in->bal);
                getch();
            }

        if(in->status == 1)
        {
            clrscr();
            box(26,12,55,14);
            _setcursortype(_NOCURSOR);
            gotoxy(28,13);
            cputs("***  RECORD NOT FOUND  ***");
            getch();
        }
        fclose(f);
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    viewmenu();
}

void viewall(inventory *in)
{
    FILE *f;
    int r = 11;
    double n;

    f = fopen("inventory.dat", "rb");
    if (f != NULL)
    {
        clrscr();
        box(12,2,69,4);
        _setcursortype(_NOCURSOR);
        gotoxy(31,3);
        cprintf("INVENTORY MANAGEMENT SYSTEM");
        box(8,7,73,24);
        gotoxy(25,7);
        cprintf(" ++ ALL RECORDS OF DATABASE ++ ");
        gotoxy(10,9);

        cprintf("SERIAL NO.      NAME                   ADDING DATE    TK.");

        n = filelength (fileno(f)) / sizeof(struct inventory);

        while ((fread(in, sizeof(struct inventory), 1, f) == 1))
        {
            if(in->status == 0)
            {
                if(r == 22)
                {
                    gotoxy(10,23);
                    cprintf("PRESS ANY KEY TO CONTINUE...");
                    getch();
                    clrscr();
                    box(12,2,69,4);
                    gotoxy(31,3);
                    cprintf("INVENTORY MANAGEMENT SYSTEM");
                    box(8,7,73,24);
                    gotoxy(25,7);
                    cprintf(" ++ ALL RECORDS OF DATABASE ++ ");
                    gotoxy(10,9);

                    cprintf("SERIAL NO.      NAME                   ADDING DATE    TK.");

                    r = 11;
                }
                else
                {
                    gotoxy(12,r);
                    cputs(in->id);
                    gotoxy(26,r);
                    cputs(in->name);
                    gotoxy(50,r);
                    cprintf("%d-%d-%d",in->day,in->month,in->year);
                    gotoxy(65,r);
                    cprintf("%.00lf",in->bal);
                    r++;
                }
            }
        }

        fclose(f);
        gotoxy(10,23);
        cputs("END OF RECORDS");
        gotoxy(54,23);
        cputs("TOTAL RECORDS : ");
        cout<<n;
        getch();
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    viewmenu();
}
void searchid(inventory *in)
{
    int i;
    char no[NUM];
    FILE *f;
    clrscr();

    _setcursortype(_SOLIDCURSOR);
    f = fopen("inventory.dat","rb");
    if (f != NULL)
    {
        box(12,3,69,5);
        gotoxy(31,4);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(16,7,65,22);
        gotoxy(30,7);
        cputs(" ++ 6.SEARCH PRODUCT ++ ");
        gotoxy(24,9);
        cputs("ENTER SERIAL NO. TO SEARCH : ");
        check_id(no, NUM);

        _setcursortype(_NOCURSOR);

        rewind(f);

        while(fread(in, sizeof(struct inventory), 1, f))
        {
            if (strcmp(no, in->id) == 0)
            {
                i++;
                gotoxy(27,12);
                cprintf("SERIAL NO     : %s",in->id);
                gotoxy(27,14);
                cprintf("PRODUCT NAME %s",in->name);
                gotoxy(27,16);
                cprintf("ADDING DATE  : %d-%d-%d",in->day,in->month,in->year);
                gotoxy(27,18);
                cprintf("BASE PRICE %.00lf",in->bal);
                gotoxy(19,21);
                cputs(in->id);
                gotoxy(26,21);
                cputs(in->name);
                gotoxy(46,21);
                cprintf("%d-%d-%d",in->day,in->month,in->year);
                gotoxy(59,21);
                cprintf("%.00lf",in->bal);

                fflush(stdin);
                getch();
            }
        }
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    fclose(f);
    searchmenu();
}

void searchname(inventory *in)
{
    int i;
    char nm[MAX];
    FILE *f;
    clrscr();

    _setcursortype(_SOLIDCURSOR);
    f = fopen("inventory.dat","rb");
    if (f != NULL)
    {
        box(12,3,69,5);
        gotoxy(31,4);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(16,7,65,22);
        gotoxy(30,7);
        cputs(" ++ 6.SEARCH PRODUCT ++ ");
        gotoxy(18,9);
        cputs("ENTER NAME TO SEARCH : ");
        check_name(nm, MAX);
        _setcursortype(_NOCURSOR);

        rewind(f);
        while(fread(in, sizeof(struct inventory), 1, f))
        {
            if (strcmp(nm, in->name) == 0)
            {
                i++;
                gotoxy(27,12);
                cprintf("SERIAL NO     : %s",in->id);
                gotoxy(27,14);
                cprintf("PRODUCT NAME %s",in->name);
                gotoxy(27,16);
                cprintf("ADDING DATE  : %d-%d-%d",in->day,in->month,in->year);
                gotoxy(27,18);
                cprintf("BASE PRICE %.00lf",in->bal);
                gotoxy(19,21);
                cputs(in->id);
                gotoxy(26,21);
                cputs(in->name);
                gotoxy(46,21);
                cprintf("%d-%d-%d",in->day,in->month,in->year);
                gotoxy(59,21);
                cprintf("%.00lf",in->bal);
                fflush(stdin);
                getch();
            }
        }
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    fclose(f);
    searchmenu();
}

void searchcase(inventory *in)
{
    char ch[MIN];
    int r = 12, m = 0;
    FILE *f;
    clrscr();

    _setcursortype(_SOLIDCURSOR);
    f = fopen("inventory.dat","rb");
    if (f != NULL)
    {
        box(12,2,69,4);
        gotoxy(31,3);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(8,8,73,24);
        gotoxy(27,8);
        cprintf(" ++ ALL MATCHING RESULTS ++ ");
        gotoxy(10,10);

        cprintf("SERIAL NO.      NAME                   ADDING DATE    TK.");

        gotoxy(22,6);
        cputs("ENTER 1st LETTER OF NAME TO SEARCH : ");
        check_name(ch, MIN);
        rewind(f);
        _setcursortype(_NOCURSOR);

        while (fread(in, sizeof(struct inventory), 1, f))
        {
            if(in->name[m] == ch[m])
            {
                if(r == 22)
                {
                    gotoxy(10,23);
                    cprintf("PRESS ANY KEY TO CONTINUE...");
                    getch();
                    clrscr();
                    box(12,2,69,4);
                    gotoxy(31,3);
                    cprintf("INVENTORY MANAGEMENT SYSTEM");
                    box(6,8,73,24);
                    gotoxy(25,8);
                    cprintf(" ++ ALL MATCHING RESULTS ++ ");
                    gotoxy(10,10);

                    cprintf("SERIAL NO.      NAME                   ADDING DATE    TK.");

                    r = 12;
                }
                else
                {
                    gotoxy(12,r);
                    cputs(in->id);
                    gotoxy(26,r);
                    cputs(in->name);
                    gotoxy(50,r);
                    cprintf("%d-%d-%d",in->day,in->month,in->year);
                    gotoxy(66,r);
                    cprintf("%.00lf",in->bal);
                    r++;
                }
            }
        }

        fclose(f);
        gotoxy(10,23);
        cputs("END OF RECORDS");
        getch();
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }

    searchmenu();
}

void delet(inventory *in)
{
    int i;
    char del[NUM];
    char ch;
    FILE *f, *fd;
    clrscr();

    _setcursortype(_SOLIDCURSOR);

    f = fopen("inventory.dat","rb");
    fd = fopen("Temp.dat","wb");
    if (f != NULL)
    {
        box(12,3,69,5);
        gotoxy(31,4);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(16,7,65,22);
        gotoxy(30,7);
        cputs(" ++ 5.DELETE PRODUCT ++ ");
        gotoxy(24,9);
        cputs("ENTER SERIAL NO. TO DELETE : ");
        check_id(del, NUM);
        _setcursortype(_NOCURSOR);

        while(fread(in, sizeof(struct inventory), 1, f))
        {
            if (strcmp(del, in->id)== 0)
            {

                i++;
                gotoxy(27,12);
                cprintf("SERIAL NO     : %s",in->id);
                gotoxy(27,14);
                cprintf("PRODUCT NAME %s",in->name);
                gotoxy(27,16);
                cprintf("ADDING DATE  : %d-%d-%d",in->day,in->month,in->year);
                gotoxy(27,18);
                cprintf("BASE PRICE %.00lf",in->bal);
                gotoxy(19,21);
                cputs(in->id);
                gotoxy(26,21);
                cputs(in->name);
                gotoxy(46,21);
                cprintf("%d-%d-%d",in->day,in->month,in->year);
                gotoxy(59,21);
                cprintf("%.00lf",in->bal);
                gotoxy(24,23);
                cputs("ARE U SURE U WANT TO DELETE ? :- ");
                ch = getche();
            }
        }
        if (ch == 'Y' || ch == 'y')
        {
            gotoxy(28,24);
            textcolor(YELLOW);
            cprintf("RECORD DELETED SUCCESSFULY");
            getch();
        }

        else if (ch == 'N'|| ch == 'n')
            menu();
        rewind(f);

        while(fread(in, sizeof(struct inventory), 1, f) == 1)
        {
            if (strcmp(del, in->id) != 0)
                fwrite(in, sizeof(struct inventory), 1, fd);
        }

        fclose(f);
        fclose(fd);
        remove("inventory.dat");
        rename("Temp.dat","inventory.dat");
        menu();
    }

    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }
    menu();
}
void paid(inventory *in)
{
    int i;
    char pa[NUM];
    FILE *f, *fm;
    clrscr();

    _setcursortype(_SOLIDCURSOR);
    f = fopen("inventory.dat","rb");
    fm = fopen("Temp.dat","wb");
    if (f != NULL)
    {
        box(12,3,69,5);
        gotoxy(31,4);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(16,7,65,22);
        gotoxy(30,7);
        cputs(" ++ 2.PAID MONEY ++ ");
        gotoxy(24,9);
        cputs("ENTER SERIAL NO. TO PAID : ");
        check_id(pa, NUM);
        rewind(f);

        while(fread(in, sizeof(struct inventory), 1, f))
        {
            if (strcmp(pa, in->id) == 0)
            {
                i++;
                gotoxy(27,12);
                cprintf("SERIAL NO   : %s",in->id);
                gotoxy(27,14);
                cprintf(" PRODUCT NAME: %s",in->name);
                gotoxy(27,16);
                cputs("2.PAID MONEY  : ");
                cin>>in->pai;

                in->bal = in->bal + in->pai;

                gotoxy(27,18);
                cprintf("MEMBER'S TK.: %.00lf",in->bal);
                _setcursortype(_NOCURSOR);
                gotoxy(19,21);
                cputs(in->id);
                gotoxy(26,21);
                cputs(in->name);
                gotoxy(46,21);
                cprintf("%.00lf",in->pai);
                gotoxy(59,21);
                cprintf("%.00lf",in->bal);
                fflush(stdin);
                getch();
            }
            fwrite(in, sizeof(struct inventory), 1,fm);
        }
        fclose(f);
        fclose(fm);
        remove("inventory.dat");
        rename("Temp.dat","inventory.dat");
    }
    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }
    menu();
}

void cost(inventory *in)
{
    int i;
    char co[NUM];
    FILE *f, *fm;
    clrscr();

    _setcursortype(_SOLIDCURSOR);
    f = fopen("inventory.dat","rb");
    fm = fopen("Temp.dat","wb");
    if (f != NULL)
    {
        box(12,3,69,5);
        gotoxy(31,4);
        cputs("INVENTORY MANAGEMENT SYSTEM");
        box(16,7,65,22);
        gotoxy(31,7);
        cputs(" ++ 3. PRODUCT COST ++ ");
        gotoxy(24,9);
        cputs("ENTER SERIAL NO. TO  PRODUCT COST : ");
        check_id(co, NUM);
        rewind(f);

        while(fread(in, sizeof(struct inventory), 1, f))
        {
            if (strcmp(co, in->id)== 0)
            {
                gotoxy(27,12);
                cprintf("SERIAL NO   : %s",in->id);
                gotoxy(27,14);
                cprintf(" PRODUCT NAME: %s",in->name);
                gotoxy(27,16);
                cputs("3. PRODUCT COST   : ");
                cin>>in->cos;

                if (in->cos > in->bal)
                {
                    menu();
                }
                else
                {
                    in->bal = in->bal - in->cos;
                    gotoxy(27,18);
                    cprintf("MEMBER'S TK.: %.00lf",in->bal);
                    _setcursortype(_NOCURSOR);
                    gotoxy(19,21);
                    cputs(in->id);
                    gotoxy(26,21);
                    cputs(in->name);
                    gotoxy(46,21);
                    cprintf("%.00lf",in->cos);
                    gotoxy(59,21);
                    cprintf("%.00lf",in->bal);
                }
                fflush(stdin);
                getch();
            }
            fwrite(in, sizeof(struct inventory), 1, fm);

        }
        fclose(f);
        fclose(fm);
        remove("inventory.dat");
        rename("Temp.dat","inventory.dat");
    }

    else
    {
        clrscr();
        box(26,12,55,14);
        _setcursortype(_NOCURSOR);
        gotoxy(28,13);
        cputs("*** ERROR OPENING FILE ***");
        getch();
    }
    menu();
}

void splash()
{



    clrscr();

    _setcursortype(_NOCURSOR);
    box(12,3,69,5);
    gotoxy(31,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(12,9,69,18);
    gotoxy(35,10);
    cprintf("* WELCOME *");
    gotoxy(24,13);
    cprintf("PROGRAMMED BY   :   ");
    gotoxy(16,16);
    cprintf("         INSTITUTE OF INFORMATION TECHNOLOGY");
    gotoxy(44,13);
    cprintf("ASAD,SOHEL,MILON,BISWAS,LIFAT,TAUHID");
    gotoxy(30,17);
    cprintf("JAHANGIRNAGAR UNIVERSITY");
    delay(3000);
    password();
}


void password()

{
    char pass[10] = {"gcbit"};
    char p[10];
    char ps;
    char ch;

    int i = 0, c = 45;
    clrscr();
    box(12,3,69,5);
    gotoxy(31,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(16,8,65,22);
    gotoxy(30,9);
    cprintf("**** WELCOME ****");
    box(16,11,65,13);
    gotoxy(38,12);
    cprintf("LOGIN");
    gotoxy(28,16);
    cprintf("ENTER PASSWORD : ");



    _setcursortype(_SOLIDCURSOR);
    while(i <= 9 || ps !='\r')
    {
        ps = getche();
        gotoxy(c,16);
        cprintf("*");
        if (ps == '\r')
            break;
        else
        {
            p[i] = ps;
            c++;
            i++;
        }
        if (i > 12)	break;
    }
    p[i] = '\0';

    _setcursortype(_NOCURSOR); // To disable the cursor.

    if(strcmp(p,pass) == 0)
    {
        gotoxy(28,18);
        cprintf("YOU ARE SUCCESSFULY LOGIN...     ");
        delay(2000);
        menu();
    }

    else
    {
        gotoxy(27,18);
        cprintf("SORRY! ACCESS DENIED..... ");
        gotoxy(27,20);
        cprintf("LET'S TRY AGAIN [Y]/[N] : ");
        ch = getche();
    }

    if (ch == 'Y'|| ch == 'y')
        password();

    else if (ch == 'N'|| ch == 'n')
        exit(0);

}
void menu()
{
    char *ch[] = {"1.ADD NEW PRODUCT","2.PAID MONEY","3.PRODUCT COST",
                  "4.VIEW PRODUCTS","5.DELETE PRODUCT","6.SEARCH PRODUCT",
                  "7.HELP","8.EXIT"
                 };
    int a;
    int d = 1;
    char choice;
    clrscr();
    box(26,3,55,5);
    gotoxy(28,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(26,6,55,8);
    gotoxy(33,7);
    cprintf("***** MENU *****");
    box(26,9,55,20);

    for(int i=0; i<8; i++)
    {
        gotoxy(35,11+i);
        cprintf("  %s   ",ch[i]);
    }

    _setcursortype(_NOCURSOR);
    gotoxy(25,22);
    cputs("================================");
    gotoxy(25,24);
    cputs("================================");

    while(1)
    {

kee:
        for(a = 1; a <= 8; ++a)
        {
            if(a == d)
            {

                if (d == 1)
                {
                    gotoxy(37,11);
                    cprintf("1.ADD NEW PRODUCT");
                    gotoxy(34,11);
                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO ADD NEW RECORD");
                }

                else if (d == 2)
                {

                    gotoxy(37,12);
                    cprintf("2.PAID MONEY");
                    gotoxy(34,12);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO 2.PAID MONEY");
                }

                else if (d == 3)
                {

                    gotoxy(37,13);
                    cprintf("3.PRODUCT COST");
                    gotoxy(34,13);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO FIX 3. PRODUCT COST");
                }

                else if (d == 4)
                {

                    gotoxy(37,14);
                    cprintf("4.VIEW PRODUCTS");
                    gotoxy(34,14);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO VIEW RECORDS");
                }

                else if (d == 5)
                {

                    gotoxy(37,15);
                    cprintf("5.DELETE PRODUCT");
                    gotoxy(34,15);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO DELETE RECORD");
                }

                else if (d == 6)
                {

                    gotoxy(37,16);
                    cprintf("6.SEARCH PRODUCT");
                    gotoxy(34,16);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO SEARCH RECORD");
                }

                else if (d == 7)
                {

                    gotoxy(37,17);
                    cprintf("7.HELP");
                    gotoxy(34,17);

                    cputs("¯¯>");
                    gotoxy(28,23);
                    cputs("PRESS ENTER TO VIEW 7.HELP");
                }

                else if (d == 8)
                {

                    gotoxy(37,18);
                    cprintf("8.EXIT");
                    gotoxy(34,18);

                    cputs("¯¯>");
                    gotoxy(27,23);
                    cputs("PRESS ENTER TO 8.EXIT PROGRAM");
                }
            }

            else
            {

                if (a == 1)
                {

                    gotoxy(37,11);
                    cprintf("1.ADD NEW PRODUCT");

                    gotoxy(34,11);
                    cputs("   ");
                    gotoxy(27,23);
                    clreol();
                }

                else if (a == 2)
                {

                    gotoxy(37,12);
                    cprintf("2.PAID MONEY");
                    gotoxy(34,12);
                    cputs("   ");
                }

                else if (a == 3)
                {

                    gotoxy(37,13);
                    cprintf("3.PRODUCT COST");
                    gotoxy(34,13);
                    cputs("   ");
                }

                else if (a == 4)
                {

                    gotoxy(37,14);
                    cprintf("4.VIEW PRODUCTS");
                    gotoxy(34,14);
                    cputs("   ");
                }

                else if (a == 5)
                {

                    gotoxy(37,15);
                    cprintf("5.DELETE PRODUCT");
                    gotoxy(34,15);
                    cputs("   ");
                }

                else if (a == 6)
                {

                    gotoxy(37,16);
                    cprintf("6.SEARCH PRODUCT");
                    gotoxy(34,16);
                    cputs("   ");
                }

                else if (a == 7)
                {

                    gotoxy(37,17);
                    cprintf("7.HELP");
                    gotoxy(34,17);
                    cputs("   ");
                }

                else if (a == 8)
                {

                    gotoxy(37,18);
                    cprintf("8.EXIT");
                    gotoxy(34,18);
                    cputs("   ");
                }
            }
        }

        choice = getch();

        if (choice == 13)
        {
            if (d == 1)	add(&in);

            if (d == 2)	paid(&in);

            if (d == 3)	cost(&in);

            if (d == 4)	viewmenu();

            if (d == 5)	delet(&in);

            if (d == 6)	searchmenu();

            if (d == 7)	helpmenu();

            if (d == 8)	quit();
        }

        if (choice == 0)
        {
            choice = getch();

            if (choice == 80)
            {
                d++;
                if (d > 8) d = 1;
                goto kee;
            }

            if (choice == 72)
            {
                d--;
                if (d < 1) d = 8;
                goto kee;
            }
        }
    }

}

void viewmenu()
{

    char *ch[] = {"1.ONE BY ONE","2.VIEW ALL","3.BACK","----------"};
    int a;
    int d = 1;
    char choice;

    clrscr();

    box(26,3,55,5);
    gotoxy(28,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(31,8,50,10);
    gotoxy(33,9);
    cprintf("** VIEW MENU **");
    box(26,12,55,19);
    for(int i = 0; i < 4; i++)
    {
        gotoxy(35,14+i);
        cprintf("  %s   ",ch[i]);
    }

    _setcursortype(_NOCURSOR);

    gotoxy(25,22);
    cputs("================================");
    gotoxy(25,24);
    cputs("================================");
    while(1)
    {
kee:
        for(a = 1; a <= 4; ++a)
        {

            if(a == d)
            {

                if (d == 1)
                {
                    gotoxy(37,14);
                    cprintf("1.ONE BY ONE");
                    gotoxy(34,14);
                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO VIEW 1.ONE BY ONE");
                }

                else if (d == 2)
                {
                    gotoxy(37,15);

                    cprintf("2.VIEW ALL");
                    gotoxy(34,15);

                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO 2.VIEW ALL RECORD");
                }

                else if (d == 3)
                {
                    gotoxy(37,16);
                    cprintf("3.BACK");
                    gotoxy(34,16);
                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO GO 3.BACK TO MAIN");
                }
            }

            else
            {

                if (a == 1)
                {
                    gotoxy(37,14);
                    cprintf("1.ONE BY ONE");
                    gotoxy(34,14);
                    cputs("   ");
                    gotoxy(27,23);
                    clreol();
                }

                else if (a == 2)
                {
                    gotoxy(37,15);
                    cprintf("2.VIEW ALL");
                    gotoxy(34,15);
                    cputs("   ");
                }

                else if (a == 3)
                {
                    gotoxy(37,16);
                    cprintf("3.BACK");
                    gotoxy(34,16);
                    cputs("   ");
                }

            }

        }

        choice = getch();
        if (choice == 13)
        {
            if (d == 1)	view(&in);

            if (d == 2)	viewall(&in);

            if (d == 3)	menu();
        }

        if (choice == 0)
        {
            choice = getch();
            if (choice == 80)
            {
                d++;
                if (d > 4) d = 1;
                goto kee;
            }
            if (choice == 72)
            {
                d--;
                if (d < 1) d = 4;
                goto kee;
            }
        }
    }

}

void searchmenu()
{
    char *ch[] = {"1.SEARCH SERIAL","2.SEARCH PRUDUCT NAME","3.SEARCH CASE","3.BACK"};
    int a;
    int d = 1;
    char choice;
    clrscr();

    box(26,3,55,5);
    gotoxy(28,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(31,8,50,10);
    gotoxy(33,9);
    cprintf("* SEARCH MENU *");
    box(26,12,55,19);

    for(int i = 0; i < 4; i++)
    {
        gotoxy(35,14+i);
        cprintf("  %s   ",ch[i]);
    }

    _setcursortype(_NOCURSOR);
    gotoxy(25,22);
    cputs("================================");
    gotoxy(25,24);
    cputs("================================");

    while(1)
    {

kee:
        for(a = 1; a <= 4; ++a)
        {

            if(a == d)
            {

                if (d == 1)
                {
                    gotoxy(37,14);
                    cprintf("1.SEARCH SERIAL");
                    gotoxy(34,14);
                    cputs("¯¯>");
                    gotoxy(25,23);
                    cputs("PRESS ENTER TO SEARCH BY SERIAL NO.");
                }

                else if (d == 2)
                {
                    gotoxy(37,15);
                    cprintf("2.SEARCH PRUDUCT NAME");
                    gotoxy(34,15);
                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO SEARCH BY PRUDUCT NAME");
                }

                else if (d == 3)
                {
                    gotoxy(37,16);
                    cprintf("3.SEARCH CASE");
                    gotoxy(34,16);
                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO SEARCH BY CASE");
                }

                else if (d == 4)
                {
                    gotoxy(37,17);
                    cprintf("3.BACK");
                    gotoxy(34,17);
                    cputs("¯¯>");
                    gotoxy(26,23);
                    cputs("PRESS ENTER TO GO 3.BACK TO MAIN");
                }
            }

            else
            {

                if (a == 1)
                {
                    gotoxy(37,14);
                    cprintf("1.SEARCH SERIAL");
                    gotoxy(34,14);
                    cputs("   ");
                    gotoxy(27,23);
                    clreol();
                }

                else if (a == 2)
                {
                    gotoxy(37,15);
                    cprintf("2.SEARCH PRUDUCT NAME");
                    gotoxy(34,15);
                    cputs("   ");
                }

                else if (a == 3)
                {
                    gotoxy(37,16);
                    cprintf("3.SEARCH CASE");
                    gotoxy(34,16);
                    cputs("   ");
                }

                else if (a == 4)
                {
                    gotoxy(37,17);
                    cprintf("3.BACK");
                    gotoxy(34,17);
                    cputs("   ");
                }

            }

        }

        choice = getch();
        if (choice == 13)
        {
            if (d == 1)	searchid(&in);

            if (d == 2)	searchname(&in);

            if (d == 3)	searchcase(&in);

            if (d == 4)	menu();
        }

        if (choice == 0)
        {
            choice = getch();

            if (choice == 80)
            {
                d++;
                if (d > 4) d = 1;
                goto kee;
            }

            if (choice == 72)
            {
                d--;
                if (d < 1) d = 4;
                goto kee;
            }
        }
    }

}

void helpmenu()
{

    char *ch[] = {"INTRODUCTION","HOW TO USE ?","ABOUT PROJECT",
                  "3.BACK"
                 };
    int a;
    int d = 1;
    char choice;
    clrscr();

    box(26,3,55,5);
    gotoxy(28,4);
    cprintf("INVENTORY MANAGEMENT SYSTEM");
    box(8,6,28,8);
    gotoxy(12,7);
    cprintf("* 7.HELP MENU *");
    box(6,10,30,17);

    for(int i = 0; i < 4; i++)
    {
        gotoxy(11,12+i);
        cprintf("  %s   ",ch[i]);
    }

    _setcursortype(_NOCURSOR);

    gotoxy(5,22);
    cputs("===========================");
    gotoxy(5,24);
    cputs("===========================");

    while(1)
    {

kee:
        for(a = 1; a <= 4; ++a)
        {

            if(a == d)
            {


                if (d == 1)
                {
                    gotoxy(13,12);

                    cprintf("INTRODUCTION");
                    gotoxy(11,12);
                    cputs("¯>");
                    gotoxy(5,23);
                    cputs("PRESS ENTER FOR INTRODUCTION");
                }

                else if (d == 2)
                {
                    gotoxy(13,13);
                    cprintf("HOW TO USE ?");
                    gotoxy(11,13);
                    cputs("¯>");
                    gotoxy(5,23);
                    cputs("PRESS ENTER TO LEARN USAGE");
                }

                else if (d == 3)
                {
                    gotoxy(13,14);
                    cprintf("ABOUT PROJECT");
                    gotoxy(11,14);
                    cputs("¯>");
                    gotoxy(7,23);
                    cputs("PRESS ENTER FOR CONTACT");
                }

                else if (d == 4)
                {
                    gotoxy(13,15);
                    cprintf("3.BACK");
                    gotoxy(11,15);
                    cputs("¯>");
                    gotoxy(7,23);
                    cputs("PRESS ENTER TO GO 3.BACK");
                }
            }

            else
            {

                if (a == 1)
                {
                    gotoxy(13,12);
                    cprintf("INTRODUCTION");
                    gotoxy(11,12);
                    cputs("  ");
                    gotoxy(5,23);
                    clreol();
                }

                else if (a == 2)
                {
                    gotoxy(13,13);
                    cprintf("HOW TO USE ?");
                    gotoxy(11,13);
                    cputs("  ");
                }

                else if (a == 3)
                {
                    gotoxy(13,14);
                    cprintf("ABOUT PROJECT");
                    gotoxy(11,14);
                    cputs("  ");
                }

                else if (a == 4)
                {
                    gotoxy(13,15);
                    cprintf("3.BACK");
                    gotoxy(11,15);
                    cputs("  ");
                }
            }
        }

        choice = getch();
        if (choice == 13)
        {
            if (d == 1)	intro();

            if (d == 2)	usage();

            if (d == 3)	about();

            if (d == 4)	menu();
        }

        if (choice == 0)
        {
            choice = getch();

            if (choice == 80)
            {
                d++;
                if (d > 4) d = 1;
                goto kee;
            }

            if (choice == 72)
            {
                d--;
                if (d < 1) d = 4;
                goto kee;
            }
        }
    }

}

void intro()
{



    box(35,6,75,22);

    _setcursortype(_NOCURSOR);
    gotoxy(38,8);
    cputs("INVENTORY MANAGEMENT SYSTEM is a PROGRAM that");
    gotoxy(38,9);
    cputs("can used for Simple INVENTORY MANAGEMENT SYSTEM ");
    gotoxy(38,10);
    cputs("Purpose. It has a Beautiful GUI for");
    gotoxy(38,11);
    cputs("Easy Understanding for the Users.");
    gotoxy(38,13);
    cputs("Just Press Enter on The Option You");
    gotoxy(38,14);
    cputs("Want to View");
    gotoxy(39,17);
    cputs("PLZ! Give Me Your Comments About");
    gotoxy(39,18);
    cputs("The Program [INVENTORY MANAGEMENT SYSTEM ].");
    gotoxy(39,21);
    cputs("For Contact PLZ Read ABOUT Option");

    getch();

    helpmenu();

}

void usage()
{
    box(35,6,75,22);

    _setcursortype(_NOCURSOR);

    gotoxy(38,8);
    cputs("Simply By using Arrows Keys Move in");
    gotoxy(38,9);
    cputs("The Program as You Want. I Also Try");
    gotoxy(38,10);
    cputs("To Guide You Through The Instruction");
    gotoxy(38,11);
    cputs("Which Appaears Bottom of The Screen.");
    gotoxy(38,12);
    cputs("Just Follow The Instruction to Work.");
    gotoxy(39,18);
    cputs("If Still Then You Face Any Problem");
    gotoxy(39,21);
    cputs("Plz! Mail: sohel_rana_raju@yahoo.com");

    getch();

    helpmenu();

}

void about()
{

    box(35,6,75,22);

    _setcursortype(_NOCURSOR);
    gotoxy(48,8);
    cputs("*** MADE BY ***");
    gotoxy(48,12);
    cputs("*** CONTACT(MAIL) ***");
    gotoxy(47,16);
    cputs("*** MOBILE NO. ***");
    gotoxy(46,10);
    cputs("Sohel rana");
    gotoxy(43,14);
    cputs("sohel_rana_raju@yahoo.com");
    gotoxy(40,18);
    cputs("+8801921515927 or +8801677219415");
    gotoxy(37,21);
    cputs("PLZ! MAIL AS SUBJECT INVENTORY MANAGEMENT SYSTEM ");

    getch();

    helpmenu();

}

void quit()
{
    char ch;
    clrscr();

    _setcursortype(_NOCURSOR);
    box(26,5,55,7);
    gotoxy(29,6);
    cputs("+INVENTORY MANAGEMENT SYSTEM+");
    box(15,12,66,16);
    gotoxy(18,14);
    cputs("ARE YOU SURE YOU WANT TO 8.EXIT ?  [Y] / [N] : ");

    ch = getche();

    if (ch == 'Y' || ch == 'y')
    {
        gotoxy(24,18);
        cputs("THANK YOU FOR USING THIS PROGRAM");
        delay(2000);
        exit(0);
    }

    else if (ch == 'N'|| ch == 'n')
        menu();

    else
        quit();

}

void print(inventory *in)
{
    FILE *f;
    clrscr();

    putc('\n',stdprn);
    fputs("\n\t\t\tREPRT OF SALES",stdprn);
    putc('\n',stdprn);
    fputs("===========================",stdprn);
    putc('\n',stdprn);
    putc('\n',stdprn);

    gotoxy(10,9);
    fprintf(stdprn,"SERIAL NO.      NAME                   ADDING DATE    TK.");

    putc('\n',stdprn);
    putc('\n',stdprn);

    f = fopen("inventory.dat","rb");

    while( (fread(in, sizeof(struct inventory), 1, stdprn)) == 1)

    {
        fprintf(stdprn,"%d",in->id);
        fprintf(stdprn,"%s",in->name);
        fprintf(stdprn,"%d-%d-%d",in->day,in->month,in->year);
        fprintf(stdprn,"%.00lf\n",in->bal);
    }

    fclose(f);

}
