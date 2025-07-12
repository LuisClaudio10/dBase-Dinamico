#include <stdio.h>
#include <windows.h>
#include <conio2.h>

void moldura(int Ci,int Li,int Cf,int Lf,int frente,int fundo)
{
	int a;
	textcolor(frente);
	textbackground(fundo);
	gotoxy(Ci,Li);
	printf("%c",201);
	gotoxy(Cf,Li);
	printf("%c",187);
	gotoxy(Ci,Lf);
	printf("%c",200);
	gotoxy(Cf,Lf);
	printf("%c", 188);
	for(int i = 2; i < Cf; i++)
    {
        gotoxy(i, Li);printf("%c", 205);
        gotoxy(i, Lf);printf("%c", 205);
    }
    for(int l = 2; l < Lf; l++)
    {
        gotoxy(Ci, l);printf("%c", 186);
        gotoxy(Cf, l);printf("%c", 186);
    }
	textcolor(7);
	textbackground(0);

}

void desenharmoldurafora()
{
    textcolor(LIGHTGRAY);
    textbackground(0);
    gotoxy(39, 13);printf("%c",201);
    gotoxy(91,13);printf("%c",187);
    gotoxy(39, 19);printf("%c",200);
    gotoxy(91,19);printf("%c",188);

    for(int i = 40; i < 91; i++)
    {
        gotoxy(i, 13);printf("%c", 205);
        gotoxy(i, 19);printf("%c", 205);
    }
    for(int i = 14; i < 19; i++)
    {
        gotoxy(39, i);printf("%c", 186);
        gotoxy(91, i);printf("%c", 186);
    }
}

void desenharEmail()
{
    gotoxy(40, 14);printf("%c",201);
    gotoxy(90,14);printf("%c",187);
    gotoxy(40, 18);printf("%c",200);
    gotoxy(90,18);printf("%c",188);
    
    for(int i = 41; i < 90; i++)
    {
        gotoxy(i, 14);printf("%c", 205);
        gotoxy(i, 18);printf("%c", 205);
    }
    for(int i = 15; i < 18; i++)
    {
        gotoxy(40, i);printf("%c", 186);
        gotoxy(90, i);printf("%c", 186);
    }
    textcolor(LIGHTGREEN);
    gotoxy(43, 16);printf("ENTER YOUR E-MAIL");
    desenharmoldurafora();
}

void desenharSenha()
{
    gotoxy(40, 14);printf("%c",201);
    gotoxy(90,14);printf("%c",187);
    gotoxy(40, 18);printf("%c",200);
    gotoxy(90,18);printf("%c",188);
    
    for(int i = 41; i < 90; i++)
    {
        gotoxy(i, 14);printf("%c", 205);
        gotoxy(i, 18);printf("%c", 205);
    }
    for(int i = 15; i < 18; i++)
    {
        gotoxy(40, i);printf("%c", 186);
        gotoxy(90, i);printf("%c", 186);
    }
    textcolor(LIGHTGREEN);
    gotoxy(43, 16);printf("ENTER YOUR PASSWORD");
    desenharmoldurafora();
}


void LimpaTela()
{
    textbackground(BLACK);
    textcolor(WHITE);
    for(int y = 0; y < 27; y++)
    {
        gotoxy(2, y);
        for(int x = 2; x < 120; x++)
        {
            printf(" ");
        }
    }
}

void PedirEmail(char *Email)
{
   textbackground(LIGHTGRAY);
   textcolor(0);
   gotoxy(62, 16);printf("                            ");
   gotoxy(62, 16);gets(Email);
}
void PedirSenha(char *Senha)
{
   textbackground(LIGHTGRAY);
   textcolor(0);
   gotoxy(63, 16);printf("                         ");
   gotoxy(63, 16);gets(Senha);
}

void desenhartimer()
{
    LimpaTela();
    int percen, pos;
    textcolor(LIGHTGREEN);
    for(percen = 2; percen <= 100; percen++)
    {
        if(percen == 99)
            pos = percen;
        gotoxy(4, 28);printf("%d%%", percen);
        gotoxy(percen, 29);printf("%c", 177);
        Sleep(20);
        gotoxy(4, 28);printf("    ");
    }
    for(int i = pos; i < 120; i++)
    {
        gotoxy(4, 28);printf("100%%");
        gotoxy(i, 29);printf("%c", 177);
        Sleep(10);
    }
    gotoxy(4, 28);printf("%d%%", percen-1);
    Sleep(1500);
    system("cls");
}

void commandlineLicensa()                                                                          
{
    textcolor(BLACK);
    textbackground(LIGHTGRAY);
    gotoxy(1, 27);printf("Command Line     ||<C:>||                            ||                     ||                             ||           ");
    textcolor(WHITE);
    textbackground(0);
    gotoxy(23, 29);printf("Pressione ENTER para aceitar o Contrato de Licenca e iniciar o dBASE III PLUS.");
    getch();
}
void molduramenu()
{
    textcolor(WHITE);
    gotoxy(22, 4);printf("%c",201);
    gotoxy(102, 4);printf("%c",187);
    for(int i = 23; i < 102; i++)
    {
        gotoxy(i, 4);printf("%c", 205);
        gotoxy(i, 22);printf("%c", 205);
    
    }
    for(int i = 5; i < 22; i++)
    {
        gotoxy(22, i);printf("%c", 186);
        gotoxy(102, i);printf("%c", 186);
    
    }
    gotoxy(45, 5);printf("dBASE III PLUS  versao 1.0  IBM/MSDOS");
    gotoxy(25, 6);printf("Copyright <c> Ashton-Tate 1984, 1985, 1986.  Todos os direitos reservados.");
    gotoxy(40, 7);printf("dBASE, dBASE III, dBASE III PLUS e Ashton-Tate");
    gotoxy(44, 8);printf("Sao marcas registradas da Ashton-Tate");

    gotoxy(27, 12);printf("Voce pode usar o software dBASE III PLUS e os materiais impressos no");
    gotoxy(27, 13);printf("pacote de software dBASE III PLUS sob os termos do Acordo de");
    gotoxy(27, 14);printf("Licenca de Software dBASE III PLUS.  Em resumo, a Ashton-Tate");
    gotoxy(27, 15);printf("concede a voce uma licenca pessoal, intransferivel e paga para usar");
    gotoxy(27, 16);printf("o dBASE III PLUS em um unico microcomputador ou estacao de trabalho.");
    gotoxy(27, 17);printf("Voce nao se torna o proprietario do pacote, nem tem o direito de");
    gotoxy(27, 18);printf("copiar ou alterar o software ou os materiais impressos. Voce e legalmente");
    gotoxy(27, 19);printf("responsavel por qualquer violacao do Acordo de Licenca ou das leis de");
    gotoxy(27, 20);printf("direitos autorais, marcas registradas ou segredos comerciais.");

    gotoxy(22, 22);printf("%c",200);
    gotoxy(102, 22);printf("%c", 188);

    commandlineLicensa();
}


void MenuLogin(char *Email, char *Senha)
{
    desenharEmail();
    PedirEmail(Email);
    LimpaTela();
    desenharSenha();
    PedirSenha(Senha);
    desenhartimer();
    molduramenu();
    system("cls");
}
