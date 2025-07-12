#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>
#include <time.h>

#include "TadMoldura.h"
#include "Tad.h"

#define MAXCOMANDO 100

void CriarUnidade(Diretorio **Dir)
{
    Diretorio *D = (Diretorio*)malloc(sizeof(Diretorio));
    D->top = NULL;
    D->ListaArquivos = NULL;
    D->unidade = 'D';
    Diretorio *C = (Diretorio*)malloc(sizeof(Diretorio));
    D->bottom = C;


    C->unidade = 'C';
    C->ListaArquivos = NULL;
    C->top = D;
    C->bottom = NULL;
    (*Dir) = C;
}
void ExibirCommandLine(Diretorio *Dir, Arquivos *Aberto, int *Pos, int *SetDeleted, Status *posicao)
{
    if(Aberto != NULL)
    {
        if(*Pos == 0)
        {
            textbackground(LIGHTGRAY);
            textcolor(BLACK);
            gotoxy(1, 27);printf("                                                                                                                        ");
            gotoxy(1, 27);printf("Command Line     ||<%c:>||%s                 ||Rec: None                  ||                   ||        ", Dir->unidade, Aberto->NomeDBF);
        }
        else
        {
            int contador = 0;
            Status *stat;
            stat = Aberto->ListaStatus;
            while(stat != NULL)
            {
                if(*SetDeleted == 1 && stat->status == 'T')
                    contador++;
                else
                    if(*SetDeleted == 0)
                        contador++;
                stat = stat->prox;
            }
            if(*SetDeleted == 0)
            {
                textbackground(LIGHTGRAY);
                textcolor(BLACK);
                gotoxy(1, 27);printf("                                                                                                                        ");
                gotoxy(1, 27);printf("Command Line     ||<%c:>||%s                 ||Rec: %d/%d                  ||                   ||        ", Dir->unidade, Aberto->NomeDBF, *Pos, contador);
            }
            else
            {
                if(posicao->status == 'F')
                { 
                    textbackground(LIGHTGRAY);
                    textcolor(BLACK);
                    gotoxy(1, 27);printf("                                                                                                                        ");
                    gotoxy(1, 27);printf("Command Line     ||<%c:>||%s                 ||Rec: None                  ||                   ||        ", Dir->unidade, Aberto->NomeDBF);
                }
                else
                {
                    textbackground(LIGHTGRAY);
                    textcolor(BLACK);
                    gotoxy(1, 27);printf("                                                                                                                        ");
                    gotoxy(1, 27);printf("Command Line     ||<%c:>||%s                 ||Rec: %d/%d                  ||                   ||        ", Dir->unidade, Aberto->NomeDBF, *Pos, contador);
                }
            }   
        }
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(1, 26);printf("                                                                                                                        ");
        gotoxy(6, 26);
    }
    else
    {
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
        gotoxy(1, 27);printf("Command Line     ||<%c:>||                            ||                     ||                             ||           ", Dir->unidade);
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(1, 26);printf("                                                                                                                        ");
        gotoxy(6, 26);
    }
}
void ExibirCampos(Arquivos *arq, Diretorio *dir, int *pos, int *SetDeleted, Status *posicao)
{
    if(arq == NULL)
    {
        gotoxy(47, 10); printf("Nao ha Nenhum Arquivo em Uso!!");
        textcolor(WHITE);
        textbackground(BLACK);
        gotoxy(1, 26); printf("                                                                                                                        ");
    }
    else
    {
        Campos *auxcamp;
        int c, L;
        int contadorRegistros = 1;

        textbackground(BLACK);
        textcolor(WHITE);
        
        auxcamp = arq->ListaCampos;
        c = 10;  
        L = 7;

        Status *stat;
        stat = arq->ListaStatus;
        gotoxy(2, 5); printf("----------------------------------------------------------------------------------------------------------------------");
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
        gotoxy(2, 6); printf(" "); 
        gotoxy(2, 6); printf("R");
        while(auxcamp != NULL)
        {
            textbackground(LIGHTGRAY);
            textcolor(BLACK);
            gotoxy(c, 6);
            printf("%s", auxcamp->FieldName);
            textbackground(BLACK);
            textcolor(WHITE);
            c += 20;

            auxcamp->Patual = auxcamp->ListaValores;
            auxcamp = auxcamp->prox;
        }

        auxcamp = arq->ListaCampos;
        c = 10;
        L = 7;

        while(stat != NULL)
        {
            auxcamp = arq->ListaCampos;
            c = 10;
            while(auxcamp != NULL)
            {
                if(*SetDeleted == 0)
                {
                    if(stat->status == 'F')
                    {
                        gotoxy(2, L);printf("*%d", contadorRegistros);
                    }
                    else
                    {
                        gotoxy(2, L);printf("%d", contadorRegistros);
                    }
                    switch(auxcamp->Type)
                    {
                        case 'N': gotoxy(c, L);printf("%.*f", auxcamp->Dec, auxcamp->Patual->Dado.valorN); break;
                        case 'D': gotoxy(c, L);printf("%s", auxcamp->Patual->Dado.valorD); break;
                        case 'L': gotoxy(c, L);printf("%c", auxcamp->Patual->Dado.valorL); break;
                        case 'C': gotoxy(c, L);printf("%s", auxcamp->Patual->Dado.valorC); break;
                        case 'M': gotoxy(c, L);printf("%s", auxcamp->Patual->Dado.valorM); break;
                            
                    }
                }
                else
                {
                    if(stat->status == 'T')
                    {
                        gotoxy(2, L);
                        printf("%d", contadorRegistros);
                        gotoxy(c, L);
                        switch(auxcamp->Type)
                        {
                            case 'N': printf("%.*f", auxcamp->Dec, auxcamp->Patual->Dado.valorN); break;
                            case 'D': printf("%s", auxcamp->Patual->Dado.valorD); break;
                            case 'L': printf("%c", auxcamp->Patual->Dado.valorL); break;
                            case 'C': printf("%s", auxcamp->Patual->Dado.valorC); break;
                            case 'M': printf("%s", auxcamp->Patual->Dado.valorM); break;
                        }    
                    }
                }
                c += 20;
                auxcamp->Patual = auxcamp->Patual->prox;
                auxcamp = auxcamp->prox;
            }
            contadorRegistros++;
            L++;
            stat = stat->prox;
        }

        auxcamp = arq->ListaCampos;
        while(auxcamp != NULL)
        {
            auxcamp->Patual = auxcamp->ListaValores;
            auxcamp = auxcamp->prox;
        }
        ExibirCommandLine(dir, arq, pos, SetDeleted, posicao);
    }
}
void AdicionarValores(Arquivos *aberto, Diretorio *dir, int *pos, Status **posicao)
{
    LimpaTela();
    textbackground(LIGHTGRAY);
    textcolor(BLACK);
    gotoxy(1, 27);printf("                                                                                                                        ");                                                                                                          
    gotoxy(1, 27);printf("APPEND                ||<%c:>||%s                 ||                    ||                      ||         ", dir->unidade, aberto->NomeDBF);
    Campos *aux;
    aux = aberto->ListaCampos;
    int Linha = 10;
    char Continuar;
    Continuar = 'S';
    int cont = *pos; 
    while(Continuar == 'S')
    {
        Status *stats = (Status*)malloc(sizeof(Status));
        stats->prox = NULL;
        stats->status = 'T';
        while(aux != NULL)
        {
            textcolor(WHITE);
            textbackground(BLACK);
            gotoxy(40, Linha);printf("%s", aux->FieldName);
            Valores *valor;
            valor = (Valores*)malloc(sizeof(Valores));
            valor->prox = NULL;
            char auxiliar[50];
            switch(aux->Type)
            {
                case 'N':   do{
                                textcolor(BLACK);
                                textbackground(LIGHTGRAY);
                                gotoxy(55, Linha);printf("             ");
                                gotoxy(55, Linha);
                                fflush(stdin);
                                gets(auxiliar);
                                if(strlen(auxiliar) > aux->Width)
                                {
                                    textcolor(WHITE);
                                    textbackground(0);
                                    gotoxy(55, Linha);printf("                                                                 ");
                                }
                            }while(strlen(auxiliar) > aux->Width);
                            float numero;
                            numero = atof(auxiliar);
                            valor->Dado.valorN = numero;
                            break;

                case 'D':   do{
                                textcolor(BLACK);
                                textbackground(LIGHTGRAY);
                                gotoxy(55, Linha);printf("           ");
                                gotoxy(55, Linha);
                                fflush(stdin);
                                gets(auxiliar);
                                if(strlen(auxiliar) > aux->Width)
                                {
                                    textcolor(WHITE);
                                    textbackground(0);
                                    gotoxy(55, Linha);printf("                                                                 ");
                                }
                            }while(strlen(auxiliar) > aux->Width);
                            strcpy(valor->Dado.valorD, auxiliar);
                            break;
                
                case 'L':   do{
                                textcolor(BLACK);
                                textbackground(LIGHTGRAY);
                                gotoxy(55, Linha);
                                printf("          ");
                                gotoxy(55, Linha);
                                fflush(stdin);
                                scanf(" %c", &valor->Dado.valorL);
                                valor->Dado.valorL = toupper(valor->Dado.valorL);
                                if(valor->Dado.valorL != 'T' && valor->Dado.valorL != 'F')
                                {
                                    textcolor(WHITE);
                                    textbackground(0);
                                    gotoxy(55, Linha);printf("                                                                 ");
                                }
                            }while(valor->Dado.valorL != 'T' && valor->Dado.valorL != 'F');
                            break;
                case 'C':   do{
                                textcolor(BLACK);
                                textbackground(LIGHTGRAY);
                                gotoxy(55, Linha);printf("                                      ");
                                gotoxy(55, Linha);
                                fflush(stdin);
                                gets(auxiliar);
                                if(strlen(auxiliar) > aux->Width)
                                {
                                    textcolor(WHITE);
                                    textbackground(0);
                                    gotoxy(55, Linha);printf("                                                                 ");
                                }
                            }while(strlen(auxiliar) > aux->Width);
                            strcpy(valor->Dado.valorC, auxiliar);
                            break;

                case 'M': do{
                                textcolor(BLACK);
                                textbackground(LIGHTGRAY);
                                gotoxy(55, Linha);printf("                                      ");
                                gotoxy(55, Linha);
                                fflush(stdin);
                                gets(auxiliar);
                                if(strlen(auxiliar) > aux->Width)
                                {
                                    textcolor(WHITE);
                                    textbackground(0);
                                    gotoxy(55, Linha);printf("                                                                 ");
                                }
                            }while(strlen(auxiliar) > aux->Width);
                            strcpy(valor->Dado.valorM, auxiliar);
                            break;
            }
            if(aux->ListaValores == NULL)
            {
                aux->ListaValores = valor;
                aux->Patual = aux->ListaValores;
            }
            else
            {
                Valores *auxvalor;
                auxvalor = aux->ListaValores;
                while(auxvalor->prox != NULL)
                    auxvalor = auxvalor->prox;
                
                auxvalor->prox = valor;

            };
            aux->Patual = valor;
            Linha = Linha + 2;
            aux = aux->prox;
        }
        if(aberto->ListaStatus == NULL)
        {
            aberto->ListaStatus = stats;
        }
        else
        {
            Status *auxstatus = aberto->ListaStatus;
            while(auxstatus->prox != NULL)
                auxstatus = auxstatus->prox;

            auxstatus->prox = stats;
        }
        cont++;
        *pos = cont;
        (*posicao) = stats;
        LimpaTela();
        gotoxy(50, 12);printf("Deseja Continuar?(S/N)");
        gotoxy(50, 13);
        Continuar = toupper(getch());
        if(Continuar == 'S')
        {
            LimpaTela();
            Linha = 10;
            aux = aberto->ListaCampos;
        }  
    }
}

void Create(char Nomearquivo[50], Diretorio **Dir, Arquivos **aberto, int *pos, Status **stat)
{
    system("cls");
    Arquivos *novo = (Arquivos*)malloc(sizeof(Arquivos));
    strcpy(novo->NomeDBF, Nomearquivo);
    char Data[11];
    char Hora[6];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strftime(Data, sizeof(Data), "%d/%m/%Y", &tm);
    strftime(Hora, sizeof(Hora), "%H:%M", &tm);
    strcpy(novo->Data, Data);
    strcpy(novo->hora, Hora);
    novo->ListaCampos = NULL;
    novo->ListaStatus = NULL;
    novo->prox = NULL;
    if((*Dir)->ListaArquivos == NULL)
    {
        novo->ant = NULL;
        (*Dir)->ListaArquivos = novo;
    }
    else
    {
        Arquivos *aux;
        aux = (*Dir)->ListaArquivos;
        while(aux->prox != NULL)
            aux = aux->prox;
        
        aux->prox = novo;
        novo->ant = aux;
    }
    (*aberto) = novo;
    *pos = 0;
    (*stat) = NULL;
    char Fieldname[30];
    gotoxy(37, 8);printf("Field Name            Type            Width               Dec");
    gotoxy(37, 9);printf("================================================================");
    textbackground(LIGHTGRAY);
    textcolor(BLACK);
    gotoxy(1, 27);printf("                                                                                                                        ");                                                                                                          
    gotoxy(1, 27);printf("CREATE                ||<%c:>||%s                 ||                    ||                      ||         ", (*Dir)->unidade, Nomearquivo);
    gotoxy(37, 11);printf("             ");
    gotoxy(37, 11);
    fflush(stdin);
    gets(Fieldname);
    int L = 11;
    int num = 1;
    while(strcmp(Fieldname, "\0") != 0)
    {
        Campos *caixa = (Campos*)malloc(sizeof(Campos));
        caixa->prox = NULL;
        caixa->ListaValores = NULL;
        strcpy(caixa->FieldName, Fieldname);
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(35, L);printf("%d", num);
        textbackground(LIGHTGRAY);
        textcolor(BLACK);
        do
        {
            gotoxy(58, L);printf("          ");
            gotoxy(58, L);
            fflush(stdin);
            scanf(" %c", &caixa->Type);
            caixa->Type = toupper(caixa->Type);
        }while(caixa->Type != 'N' && caixa->Type != 'C' && caixa->Type != 'D' && caixa->Type != 'M' && caixa->Type != 'L');
        switch(caixa->Type)
        {
            case 'N': gotoxy(58, L);printf("Numeric");
                      break;
            case 'C': gotoxy(58, L);printf("Character");
                      break;
            case 'D': gotoxy(58, L);printf("Date");
                      break;
            case 'M': gotoxy(58, L);printf("Memo");
                      break;
            case 'L': gotoxy(58, L);printf("Logical");
                      break;           
        }
        if(caixa->Type == 'L')
        {
            gotoxy(75, L);printf("      ");
            caixa->Width = 1;
            gotoxy(75, L);printf("%d", caixa->Width);
        }
        else
        {
            gotoxy(75, L);printf("      ");
            fflush(stdin);
            gotoxy(75, L);scanf("%d", &caixa->Width);
        }
        if(caixa->Type == 'N')
        {
            gotoxy(95, L);printf("     ");
            gotoxy(95, L);scanf("%d", &caixa->Dec);
        }
        if(novo->ListaCampos == NULL)
        {
            novo->ListaCampos = caixa;
        }
        else
        {
            Campos *aux;
            aux = novo->ListaCampos;
            while(aux->prox != NULL)
                aux = aux->prox;
            
            aux->prox = caixa;
        }
        L = L + 2;
        num++;
        if(num == 9)
        {
            LimpaTela();
            gotoxy(0, L);printf("                                                                                                                        ");  
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(37, 8);printf("Field Name            Type            Width               Dec");
            gotoxy(37, 9);printf("================================================================");
            L = 11;
            textbackground(LIGHTGRAY);
            textcolor(BLACK);
            gotoxy(1, 27);printf("                                                                                                                        ");  
            gotoxy(1, 27);printf("CREATE                ||<%c:>||%s                 ||                    ||                      ||         ", (*Dir)->unidade, Nomearquivo);
        }
        gotoxy(37, L);printf("             ");
        gotoxy(37, L);
        fflush(stdin);
        gets(Fieldname);
    }
    LimpaTela();
    gotoxy(54, 15);printf("Arquivo Criado!!");
}

void dividirComando(char primeiraPalavra[MAXCOMANDO], char restoComando[MAXCOMANDO], char comando[MAXCOMANDO])
{
	int contPP, contRC = 0;
	for(contPP=0; contPP < MAXCOMANDO && comando[contPP] != '\0' && comando[contPP] != ' '; contPP++)	
		primeiraPalavra[contPP] = comando[contPP];
	
	primeiraPalavra[contPP] = '\0';
	
	if(comando[contPP] != '\0')
	{
		contPP++;
		
		for(contRC = 0; comando[contPP] != '\0'; contRC++,contPP++)
			restoComando[contRC] = comando[contPP];
	}
	
	restoComando[contRC] = '\0';
}
void DIR(Diretorio *Dir, Arquivos *aberto, int *pos, int *SetDeleted, Status *posicao)
{
    Arquivos *aux = Dir->ListaArquivos;

    int L = 5;
    gotoxy(2, 3); printf("Database Files");
    gotoxy(56, 3); printf("# Records");
    gotoxy(80, 3); printf("Last Update");
    gotoxy(100, 3); printf("Size");
    while(aux != NULL)
    {
        int totalRegistros = 0;
        int totalCamposWidth = 0;
        int sizeFinal = 0;

        Status *statusAtual = aux->ListaStatus;
        while(statusAtual != NULL)
        {
            totalRegistros++;
            statusAtual = statusAtual->prox;
        }

        Campos *campoAtual = aux->ListaCampos;
        while(campoAtual != NULL)
        {
            totalCamposWidth += campoAtual->Width;
            campoAtual = campoAtual->prox;
        }

        sizeFinal = totalCamposWidth * totalRegistros;

        gotoxy(2, L);   printf("%s", aux->NomeDBF);
        gotoxy(56, L);  printf("%d", totalRegistros);
        gotoxy(80, L);  printf("%s", aux->Data);
        gotoxy(100, L); printf("%d", sizeFinal);

        L++;
        aux = aux->prox;
    }
    ExibirCommandLine(Dir, aberto, pos, SetDeleted, posicao);
}

void Use(Diretorio *Dir, Arquivos **aberto, char nomearquivo[50], int *pos, Status **Posicao)
{
    Arquivos *aux;
    aux = Dir->ListaArquivos;
    while(aux != NULL && stricmp(nomearquivo, aux->NomeDBF) != 0)
        aux = aux->prox;
    
    if(aux != NULL)
    {
        gotoxy(50, 15);printf("Arquivo em Uso: %s.", aux->NomeDBF);
        (*aberto) = aux;
        *pos = 0;
        (*Posicao) = NULL;
    }
    else
    {
        gotoxy(40, 15);printf("Arquivo com Nome: %s Nao encontrado!!", nomearquivo);
    }
    textcolor(WHITE);
    textbackground(BLACK);
    gotoxy(1, 26);printf("                                                                                                                        "); 
}
void ListStructure(Diretorio *Dir, Arquivos *aberto, int *pos, int *SetDeleted, Status *posicao)
{
    if(aberto != NULL)
    {
        Campos *camp;
        int L;
        gotoxy(40, 8); 
        printf("Structure for database: %c:%s", Dir->unidade, aberto->NomeDBF);

        gotoxy(40, 9); 
        printf("Number of data records: ");

        gotoxy(40, 10); 
        printf("Date: %s", aberto->Data);

        textbackground(LIGHTGRAY);
        textcolor(0);

        gotoxy(40, 12); printf("Field");
        gotoxy(50, 12); printf("Field Name");
        gotoxy(70, 12); printf("Type");
        gotoxy(85, 12); printf("Width");
        gotoxy(95, 12); printf("Dec");

        textbackground(BLACK);
        textcolor(WHITE);
        L = 14;
        camp = aberto->ListaCampos;
        int cont = 1, total = 0;
        while(camp != NULL)
        {
            gotoxy(40, L); printf("%d", cont);
            gotoxy(50, L); printf("%s", camp->FieldName);
            switch(camp->Type)
            {
                case 'N': gotoxy(70, L);printf("Numeric");
                        break;
                case 'C': gotoxy(70, L);printf("Character");
                        break;
                case 'D': gotoxy(70, L);printf("Date");
                        break;
                case 'M': gotoxy(70, L);printf("Memo");
                        break;
                case 'L': gotoxy(70, L);printf("Logical");
                        break;
            }
            gotoxy(85, L);printf("     ");
            gotoxy(85, L); printf("%d", camp->Width);
            if(camp->Type == 'N')
            {
                gotoxy(95, L); printf("     ");
                gotoxy(95, L); printf("%d", camp->Dec);
            }
            cont++;
            total += camp->Width;
            L++;
            camp = camp->prox;
        }
        camp = aberto->ListaCampos;
        Valores *auxvalor = NULL;
        int contador = 0;
        if(camp != NULL)
        {
            auxvalor = camp->ListaValores;
            while(auxvalor != NULL)
            {
                contador++;
                auxvalor = auxvalor->prox;
            }
        }
        gotoxy(65, 9);printf("%d", contador);
        gotoxy(40, L);printf("Total:");
        gotoxy(85, L);printf("%d", total);
        ExibirCommandLine(Dir, aberto, pos, SetDeleted, posicao);
    }
    else
    {
        gotoxy(50, 15); 
        printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}
void SetDefault(Diretorio **Dir, char Diretorio[30], Arquivos **aberto, int *pos, Status **Posicao)
{
    char diretorio;
    int tamanho = strlen(Diretorio);
    diretorio = Diretorio[tamanho - 2];
    if(diretorio == 'C' || diretorio == 'c')
    {  if((*Dir)->unidade == 'C')
        {
            gotoxy(53, 15);printf("Unidade Atual = %c", (*Dir)->unidade);
        }
        else
        {
            (*Dir) = (*Dir)->bottom; 
            gotoxy(53, 15);printf("Unidade Atual = %c", (*Dir)->unidade);
        }
    }
    else
    {   
        if(diretorio == 'D' || diretorio == 'd')
        {
            if((*Dir)->unidade == 'D')
            {
                gotoxy(53, 15);printf("Unidade Atual = %c", (*Dir)->unidade);
                
            }
            else
            {
                (*Dir) = (*Dir)->top; 
                gotoxy(53, 15);printf("Unidade Atual = %c", (*Dir)->unidade);
            }
        }
                    
    }
    (*aberto) = NULL;
    *pos = 0;
    *Posicao = NULL;
}

void Append(Arquivos *aberto, Diretorio *Dir, int *Pos, Status **posicao)
{
    if(aberto != NULL)
        AdicionarValores(aberto, Dir, Pos, posicao);
    else
    {
        gotoxy(50, 15); 
        printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}


char verifica(char Str[50], char valor[50])
{
    int j;
    for(int i = 0; i < strlen(Str); i++)
    {
        char String[50] = "";
        int l = 0, j;
        if(toupper(Str[i]) == toupper(valor[0]))
        {
            j = i;
            for(int k = 0; k < strlen(valor); k++)
            {
                if(toupper(Str[j]) == toupper(valor[k]))
                {
                    String[l] = valor[k];
                    l++;
                }
                j++;
            }
            String[l] = '\0';
            if(stricmp(String, valor) == 0)
                return 1;
        }
    }
    return 0;
}
void ListFor(Diretorio *Dir, Arquivos *aberto, char Campo[50], char parametro[50], int *pos, int *SetDeleted, Status *posicao)
{
    gotoxy(50, 15);printf("%s", Campo);
    if(aberto != NULL)
    {
        char palavra[50] = "";
        int j = 0;
        for(int i = 0; parametro[i] != '\0'; i++)
        {
            if(parametro[i] != '"')
            {
                palavra[j] = parametro[i];
                j++;
            }
        }
        palavra[j] = '\0';
        Campos *aux;
        aux = aberto->ListaCampos;
        while(aux != NULL && stricmp(aux->FieldName, Campo) != 0)
            aux = aux->prox;
        if(aux != NULL)
        {
            int C = 12;
            gotoxy(2, 6); printf(" "); 
            gotoxy(2, 6); printf("Record#");

            aux = aberto->ListaCampos;
            while(aux != NULL)
            {
                gotoxy(C, 6);
                printf("%s", aux->FieldName);
                aux->Patual = aux->ListaValores;
                C += 20;
                aux = aux->prox;
            }
            Status *stat;
            stat = aberto->ListaStatus;
            int record = 1;
            int L = 7;
            char String[50];
            while(stat != NULL)
            {
                int encontrou = 0;
                C = 12;
                aux = aberto->ListaCampos;
                int contador = 0;
                while(aux != NULL)
                {
                    if(aux->Type == 'N')
                    {
                        itoa(aux->Patual->Dado.valorN, String, 10);
                        if(verifica(String, palavra))
                            encontrou = 1;
                    }
                    else
                    {
                        if(aux->Type == 'L')
                        {
                            if(parametro[1] == aux->Patual->Dado.valorL)
                                encontrou = 1;
                        }
                        else
                        {
                            if(aux->Type == 'C')
                            {
                                if(verifica(aux->Patual->Dado.valorC, palavra))
                                {
                                    encontrou = 1;
                                }
                            }
                            else
                            {
                                if(aux->Type == 'D')
                                {
                                    if(verifica(aux->Patual->Dado.valorD, palavra))
                                         encontrou = 1;
                                }
                                else
                                {
                                    if(verifica(aux->Patual->Dado.valorM, palavra))
                                        encontrou = 1;
                                }
                            }
                            
                        }
                    }
                    aux = aux->prox;
                }
                if(encontrou)
                {
                    C = 12;
                    if(*SetDeleted == 0)
                    {   
                        gotoxy(2, L);
                        if(stat->status == 'F')
                            printf("*%d", record);
                        
                        else
                            printf("%d", record);

                        aux = aberto->ListaCampos;
                        while(aux != NULL)
                        {
                            gotoxy(C, L);

                            if(aux->Type == 'N')
                                printf("%.*f", aux->Dec, aux->Patual->Dado.valorN);
                            else if(aux->Type == 'C')
                                printf("%s", aux->Patual->Dado.valorC);
                            else if(aux->Type == 'L')
                                printf("%c", aux->Patual->Dado.valorL);
                            else if(aux->Type == 'D')
                                printf("%s", aux->Patual->Dado.valorD);
                            else if(aux->Type == 'M')
                                printf("%s", aux->Patual->Dado.valorM);
                            
                            aux = aux->prox;
                            C += 20;
                        }
                        L++;
                    }
                    else
                    {
                        if(encontrou)
                        {
                            if(stat->status == 'T')
                            {
                                gotoxy(2, L);printf("%d", record);
                                aux = aberto->ListaCampos;
                                while(aux != NULL)
                                {
                                    gotoxy(C, L);

                                    if(aux->Type == 'N')
                                        printf("%.*f", aux->Dec, aux->Patual->Dado.valorN);
                                    else if(aux->Type == 'C')
                                        printf("%s", aux->Patual->Dado.valorC);
                                    else if(aux->Type == 'L')
                                        printf("%c", aux->Patual->Dado.valorL);
                                    else if(aux->Type == 'D')
                                        printf("%s", aux->Patual->Dado.valorD);
                                    else if(aux->Type == 'M')
                                        printf("%s", aux->Patual->Dado.valorM);

                                    aux = aux->prox;
                                    C += 20;
                                }
                                L++;
                            }
                        }
                    }
                }
                stat = stat->prox;
                record++;
                aux = aberto->ListaCampos;
                while(aux != NULL)
                {
                    aux->Patual = aux->Patual->prox;
                    aux = aux->prox;
                }
            }
            ExibirCommandLine(Dir, aberto, pos, SetDeleted, posicao);
        }
        else
        {
            gotoxy(50, 15);
            printf("Nome do Campo nao Existe!!");
        }
    }
    else
    {
        gotoxy(50, 15); 
        printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}

void Display(Diretorio *Dir, Arquivos *aberto, int *pos, int *SetDeleted, Status *Posicao)
{
    LimpaTela(); 
    ExibirCommandLine(Dir, aberto, pos, SetDeleted, Posicao); 
    if(aberto != NULL)
    {
        if(*pos == 0)
        {
            gotoxy(50, 15);
            printf("Nao ha Nenhum registro ou Nenhuma Posicao!!");
        }
        else
        {
            int contador = 1;
            Status *status = aberto->ListaStatus;
            if(status != NULL)
            {
                if(*SetDeleted == 1 && Posicao->status == 'F')
                {
                    gotoxy(50, 15);printf("Registro Inativo!!");
                }
                else
                {
                    int linha = 7;
                    gotoxy(2, 6); printf("Record#");
                    Campos *aux = aberto->ListaCampos;
                    int C = 12;
                    while(aux != NULL)
                    {
                        gotoxy(C, 6);
                        printf("%s", aux->FieldName);
                        aux->Patual = aux->ListaValores;
                        C += 20;
                        aux = aux->prox;
                    }
                    aux = aberto->ListaCampos;
                    if(Posicao->status == 'F')
                    {
                        gotoxy(2, 7);printf("*%d", *pos);
                    }
                    else
                    {
                        gotoxy(2, 7);printf("%d", *pos);
                    }
                    C = 12;
                    while(aux != NULL)
                    {
                        int valorPos = 1;
                        while(valorPos < *pos && aux->Patual != NULL)
                        {
                            aux->Patual = aux->Patual->prox;
                            valorPos++;
                        }
                        gotoxy(C, linha);
                        if(aux->Patual != NULL)
                        {
                            switch(aux->Type)
                            {
                                case 'N': printf("%.*f", aux->Dec, aux->Patual->Dado.valorN); break;
                                case 'D': printf("%s", aux->Patual->Dado.valorD); break;
                                case 'L': printf("%c", aux->Patual->Dado.valorL); break;
                                case 'C': printf("%s", aux->Patual->Dado.valorC); break;
                                case 'M': printf("%s", aux->Patual->Dado.valorM); break;
                            }
                        }
                        C += 20;
                        aux = aux->prox;
                    }
                }
            }
        }
    }
    else
    {
        gotoxy(50, 15);
        printf("Nenhum arquivo aberto!");
    }
}

void Locate(Diretorio *Dir, Arquivos *aberto, int *pos, Status **Posicao, char Campo[50], char parametro[50], int *SetDeleted)
{
    LimpaTela(); 
    if(aberto != NULL)
    {
        char Str[50];
        int i, j = 0;
        for(i = 0; parametro[i] != '\0'; i++)
        {
            if(parametro[i] != '"')
            {
                if(j == 0)
                    Str[j] = toupper(parametro[i]);  
                else
                    Str[j] = tolower(parametro[i]);  
                
                j++;
            }
        }
        Str[j] = '\0';
        Campos *aux;
        aux = aberto->ListaCampos;
        Status *stat = aberto->ListaStatus;
        while(aux != NULL)
        {
            aux->Patual = aux->ListaValores;
            aux = aux->prox;
        }
        int contador = 1;
        int encontrou = 0;
        stat = aberto->ListaStatus; 
        while(stat != NULL && !encontrou)
        {
            aux = aberto->ListaCampos;
            while(aux != NULL)
            {
                if(stricmp(Campo, aux->FieldName) == 0)
                {
                    switch(aux->Type)
                    {
                        case 'N':
                            if(atof(Str) == aux->Patual->Dado.valorN)
                                encontrou = 1;
                            break;

                        case 'C':
                            if(stricmp(Str, aux->Patual->Dado.valorC) == 0)
                                encontrou = 1;
                            break;

                        case 'D':
                            if(stricmp(Str, aux->Patual->Dado.valorD) == 0)
                                encontrou = 1;
                            break;

                        case 'M':
                            if(stricmp(Str, aux->Patual->Dado.valorM) == 0)
                                encontrou = 1;
                            break;

                        case 'L':
                            if(toupper(Str[0]) == aux->Patual->Dado.valorL)
                                encontrou = 1;
                            break;
                    }
                }
                aux = aux->prox;
            }
            if(!encontrou)
            {
                stat = stat->prox;
                contador++;

                aux = aberto->ListaCampos;
                while(aux != NULL)
                {
                    if(aux->Patual != NULL)
                        aux->Patual = aux->Patual->prox;
                    aux = aux->prox;
                }
            }
        }
        if(encontrou)
        {
            *pos = contador;
            *Posicao = stat;
            
            if(*SetDeleted == 0)
            {
                if(stat->status == 'F')
                {
                    gotoxy(2, 6);
                    printf("Record =  *%d", *pos);
                }
                else
                {
                    gotoxy(2, 6);
                    printf("Record =  %d", *pos);
                }
            }
            else
            {
                if(stat->status == 'T')
                {
                    gotoxy(2, 6);
                    printf("Record =  %d", *pos);
                }
                else
                {
                    gotoxy(50, 15);printf("Registro nao encontrado!");
                }
            }
        }
        else
        {
            gotoxy(50, 15);
            printf("Registro nao encontrado!");
        }
        ExibirCommandLine(Dir, aberto, pos, SetDeleted, *Posicao);
    }
    else
    {
        gotoxy(50, 15);
        printf("Nenhum arquivo aberto!");
    }
}


void Goto(Diretorio *Dir, Arquivos *aberto, int *pos, Status **Posicao, char parametro[50], int *SetDeleted) //Tratar com o SetDeleted.
{
    LimpaTela();
    if(aberto != NULL)
    {
        char Str[50];
        int i, j = 0;
        for(i = 0; parametro[i] != '\0'; i++)
        {
            if(parametro[i] != '"')
            {
                Str[j] = parametro[i];  
                j++;
            }
        }
        Str[j] = '\0';

        int numerousuario = atoi(Str);
        int contador = 0;
        Status *stat = aberto->ListaStatus;
        while(stat != NULL)
        {
            contador++;
            stat = stat->prox;
        }
        if(numerousuario > 0 && numerousuario <= contador)
        {
            int contador = 1;
            stat = aberto->ListaStatus;
            while(contador < numerousuario)
            {
                contador++;
                stat = stat->prox;
            }
            if(*SetDeleted == 0)
            {
                (*pos) = numerousuario;
                (*Posicao) = stat;
            }
            else
            {
                if(stat->status == 'T')
                {
                    (*pos) = numerousuario;
                    (*Posicao) = stat;
                }
                else
                {
                    gotoxy(50, 15);printf("Registro nao Existe!!");
                }
            }  
        }
        else
        {
            gotoxy(50, 15);printf("Registros fora do Alcance!!");
        }
    }
    ExibirCommandLine(Dir, aberto, pos, SetDeleted, *Posicao);
}

void SetDeletedF(char RestoComando[50], int *SetDeleted)
{
    if(stricmp(RestoComando, "ON") == 0)
        (*SetDeleted) = 1;
    else
        if(stricmp(RestoComando, "OFF") == 0)
            (*SetDeleted) = 0;
}


void Delete(Diretorio *Dir, Arquivos *aberto, int *pos, Status **Posicao, int *SetDeleted)
{
    ExibirCommandLine(Dir, aberto, pos, SetDeleted, *Posicao);
    if(aberto != NULL)
    {
        if(*pos > 0)
        {
            (*Posicao)->status = 'F';
            gotoxy(5, 6);printf("1 record deleted");
        }
        else
        {   
             gotoxy(50, 15);printf("Nao ha Nenhum Registro!!"); 
        }
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha nenhum arquivo em Uso!!");
    }
}
void Deleteall(Diretorio *Dir, Arquivos *aberto)
{
    if(aberto != NULL)
    {
        Status *stat = aberto->ListaStatus;
        int contador = 0;
        while(stat != NULL)
        {
            stat->status = 'F';
            contador++;
            stat = stat->prox;
        }
        gotoxy(5, 6);printf("%d record deleted", contador);
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha nenhum arquivo em Uso!!");
    }
}

void Recall(Diretorio *Dir, Arquivos *aberto, int *pos, Status **Posicao, int *SetDeleted)
{
    if(aberto != NULL)
    {
        if(*SetDeleted == 0)
        {
            if(*pos > 0)
            {
                (*Posicao)->status = 'T';
                gotoxy(5, 6);printf("1 record recalled");
            }
            else
            {
                gotoxy(50, 15);printf("Nao ha Nenhum Registro!!");
            }
        }
        else
        {
            gotoxy(44, 15);printf("o Comando SET DELETED OFF deve ser Executado antes!!");
        }
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha nenhum arquivo em Uso!!");
    }
}

void RecallAll(Diretorio *Dir, Arquivos *aberto, int *SetDeleted)
{
    if(aberto != NULL)
    {
        if(*SetDeleted == 0)
        {
            Status *stat = aberto->ListaStatus;
            int contador = 0;
            while(stat != NULL)
            {
                if(stat->status == 'F')
                    contador++;
                stat->status = 'T';
                stat = stat->prox;
            }
            gotoxy(5, 6);printf("%d record recalled", contador);
        }
        else
        {
            gotoxy(44, 15);printf("o Comando SET DELETED OFF deve ser Executado antes!!");
        }
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha nenhum arquivo em Uso!!");
    }
}

void Edit(Diretorio *Dir, Arquivos *aberto, int *SetDeleted, int *Pos, Status *posicao)
{
    if(aberto != NULL)
    {
        if(*Pos == 0)
        {
            gotoxy(50, 15);
            printf("Nao ha Nenhum registro ou Nenhuma Posicao!!");
        }
        else
        {
            if(*SetDeleted == 1 && posicao->status == 'F')
            {
                gotoxy(50, 15);printf("Registro Inativo!!");
            }
            else
            {
                Campos *aux;
                aux = aberto->ListaCampos;
                int Linha = 10;
                int contador;
                Status *stat;
                stat = aberto->ListaStatus;
                contador = 0;
                while(stat != NULL)
                {
                    contador++;
                    stat = stat->prox;
                }
                textbackground(LIGHTGRAY);
                textcolor(BLACK);
                gotoxy(1, 27);printf("                                                                                                                        ");                                                                                                          
                gotoxy(1, 27);printf("EDIT                ||<%c:>||%s                 ||Rec: %d/%d                  ||                   ||         ", Dir->unidade, aberto->NomeDBF, *Pos, contador);
                textbackground(BLACK);
                textcolor(WHITE);
                gotoxy(1, 26);printf("                                                                                                                        ");
                gotoxy(6, 26);
                while(aux != NULL)
                {
                    aux->Patual = aux->ListaValores;
                    contador = 1;
                    while(contador < *Pos)
                    {
                        aux->Patual = aux->Patual->prox;
                        contador++;
                    }
                    aux = aux->prox;
                }
                aux = aberto->ListaCampos;
                while(aux != NULL)
                {
                    textcolor(WHITE);
                    textbackground(BLACK);
                    gotoxy(40, Linha);printf("%s", aux->FieldName);
                    char auxiliar[50];
                    switch(aux->Type)
                    {
                        case 'N':   do{
                                        textcolor(BLACK);
                                        textbackground(LIGHTGRAY);
                                        gotoxy(55, Linha);printf("             ");
                                        gotoxy(55, Linha);
                                        fflush(stdin);
                                        gets(auxiliar);
                                        if(strlen(auxiliar) > aux->Width)
                                        {
                                            textcolor(WHITE);
                                            textbackground(0);
                                            gotoxy(55, Linha);printf("                                                                 ");
                                        }
                                    }while(strlen(auxiliar) > aux->Width);
                                    float numero;
                                    numero = atof(auxiliar);
                                    aux->Patual->Dado.valorN = numero;
                                    break;

                        case 'D':   do{
                                        textcolor(BLACK);
                                        textbackground(LIGHTGRAY);
                                        gotoxy(55, Linha);printf("           ");
                                        gotoxy(55, Linha);
                                        fflush(stdin);
                                        gets(auxiliar);
                                        if(strlen(auxiliar) > aux->Width)
                                        {
                                            textcolor(WHITE);
                                            textbackground(0);
                                            gotoxy(55, Linha);printf("                                                                 ");
                                        }
                                    }while(strlen(auxiliar) > aux->Width);
                                    strcpy(aux->Patual->Dado.valorD, auxiliar);
                                    break;
                        
                        case 'L':   do{
                                        textcolor(BLACK);
                                        textbackground(LIGHTGRAY);
                                        gotoxy(55, Linha);
                                        printf("          ");
                                        gotoxy(55, Linha);
                                        fflush(stdin);
                                        scanf(" %c", &aux->Patual->Dado.valorL);
                                        aux->Patual->Dado.valorL = toupper(aux->Patual->Dado.valorL);
                                        if(aux->Patual->Dado.valorL != 'T' && aux->Patual->Dado.valorL != 'F')
                                        {
                                            textcolor(WHITE);
                                            textbackground(0);
                                            gotoxy(55, Linha);printf("                                                                 ");
                                        }
                                    }while(aux->Patual->Dado.valorL != 'T' && aux->Patual->Dado.valorL != 'F');
                                    break;
                        case 'C':   do{
                                        textcolor(BLACK);
                                        textbackground(LIGHTGRAY);
                                        gotoxy(55, Linha);printf("                                      ");
                                        gotoxy(55, Linha);
                                        fflush(stdin);
                                        gets(auxiliar);
                                        if(strlen(auxiliar) > aux->Width)
                                        {
                                            textcolor(WHITE);
                                            textbackground(0);
                                            gotoxy(55, Linha);printf("                                                                 ");
                                        }
                                    }while(strlen(auxiliar) > aux->Width);
                                    strcpy(aux->Patual->Dado.valorC, auxiliar);
                                    break;

                        case 'M': do{
                                        textcolor(BLACK);
                                        textbackground(LIGHTGRAY);
                                        gotoxy(55, Linha);printf("                                      ");
                                        gotoxy(55, Linha);
                                        fflush(stdin);
                                        gets(auxiliar);
                                        if(strlen(auxiliar) > aux->Width)
                                        {
                                            textcolor(WHITE);
                                            textbackground(0);
                                            gotoxy(55, Linha);printf("                                                                 ");
                                        }
                                    }while(strlen(auxiliar) > aux->Width);
                                    strcpy(aux->Patual->Dado.valorM, auxiliar);
                                    break;
                    }
                    Linha += 2;
                    aux = aux->prox;
                }
                LimpaTela();
                gotoxy(50, 15);printf("Registro Alterado!!"); 
            }
        }
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha nenhum arquivo em Uso!!");
    }
}

void Pack(Arquivos *aberto, int *Pos, Status **posicao)
{
    if(aberto != NULL)
    {
        int registrosRemovidos = 0;
        Status *statAtual = aberto->ListaStatus;
        Status *statAnterior = NULL;
        Campos *aux;
        aux = aberto->ListaCampos;
        while(aux != NULL)
        {
            aux->Patual = aux->ListaValores;
            aux = aux->prox;
        }
        int cont = 1;
        while(statAtual != NULL)
        {
            aux = aberto->ListaCampos;
            if(statAtual->status == 'F')
            {
                while(aux != NULL)
                {
                    Valores *valorAtual = aux->ListaValores;
                    Valores *valorAnterior = NULL;

                    int contador = 1;
                    while(valorAtual != NULL && contador < cont)
                    {
                        valorAnterior = valorAtual;
                        valorAtual = valorAtual->prox;
                        contador++;
                    }
                    if(valorAtual != NULL)
                    {
                        if(valorAnterior == NULL)
                            aux->ListaValores = valorAtual->prox;
                        else
                            valorAnterior->prox = valorAtual->prox;
                        
                        free(valorAtual);
                    }
                    aux->Patual = aux->ListaValores; 
                    aux = aux->prox;  
                }
                Status *statusExcluir = statAtual;
                if(statAtual == *posicao)
                {
                    *posicao = NULL;
                    *Pos = 0;
                } 
                if(statAnterior == NULL)
                {
                    aberto->ListaStatus = statAtual->prox;
                    statAtual = aberto->ListaStatus;
                }
                else
                {
                    statAnterior->prox = statAtual->prox;
                    statAtual = statAnterior->prox;
                }
                free(statusExcluir);
                registrosRemovidos++;  
            }
            else
            {
                statAnterior = statAtual;
                statAtual = statAtual->prox;
                cont++;
            }
        }
        LimpaTela();
        gotoxy(44, 15);printf("%d registro(s) removido(s) permanentemente!", registrosRemovidos);
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}

void Zap(Arquivos *aberto, int *pos, Status **posicao)
{
    if(aberto != NULL)
    {
        Campos *aux;
        aux = aberto->ListaCampos;
        while(aux != NULL)
        {
            aux->Patual = aux->ListaValores;
            aux = aux->prox;
        }
        Status *stat, *statExclusao;
        stat = aberto->ListaStatus;
        while(stat != NULL)
        {
            aux = aberto->ListaCampos;
            while(aux != NULL)
            {
                if(aux->Patual != NULL)
                {
                    Valores *excluir;
                    excluir = aux->Patual;
                    aux->Patual = aux->Patual->prox;
                    free(excluir);
                }
                aux = aux->prox;
            }
            statExclusao = stat;
            stat = stat->prox;
            free(statExclusao);
        }
        aux = aberto->ListaCampos;
        while(aux != NULL)
        {
            aux->ListaValores = NULL;
            aux->Patual = NULL;
            aux = aux->prox;
        }
        aberto->ListaStatus = NULL;
        *pos = 0;
        (*posicao) = NULL;
        LimpaTela();
        gotoxy(44, 15);printf("Todos os Registros foram Removidos!");
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}
void Ordenar(Arquivos *C, int i, int j)
{
    Campos *aux = C->ListaCampos;
    Valores *auxi, *auxj;
    char auxiliar[50];
    while(aux != NULL)
    {
        auxi = auxj = aux->ListaValores;
        int cont1 = 0;
        int cont2 = 0;
        while(cont1 < i)
        {
            auxi = auxi->prox;
            cont1++;
        }
        while(cont2 < j)
        {
            auxj = auxj->prox;
            cont2++;
        }
        if(aux->Type == 'N')
        {
            float auxiliar = auxi->Dado.valorN;
            auxi->Dado.valorN = auxj->Dado.valorN;
            auxj->Dado.valorN = auxiliar;
        }
        else
        {
            if(aux->Type == 'C')
            {
                strcpy(auxiliar, auxi->Dado.valorC);
                strcpy(auxi->Dado.valorC, auxj->Dado.valorC);
                strcpy(auxj->Dado.valorC, auxiliar);
            }
            else
            {
                if(aux->Type == 'D')
                {
                    strcpy(auxiliar, auxi->Dado.valorD);
                    strcpy(auxi->Dado.valorD, auxj->Dado.valorD);
                    strcpy(auxj->Dado.valorD, auxiliar);
                }
                else
                {
                    if(aux->Type == 'L')
                    {
                        char t = auxi->Dado.valorL;
                        auxi->Dado.valorL = auxj->Dado.valorL;
                        auxj->Dado.valorL = t;
                    }
                    else
                    {
                        strcpy(auxiliar, auxi->Dado.valorM);
                        strcpy(auxi->Dado.valorM, auxj->Dado.valorM);
                        strcpy(auxj->Dado.valorM, auxiliar);
                    }
                }
            }
        }
        aux = aux->prox;
    }
    Status *Auxiliar1, *Auxiliar2;
    Auxiliar1 = Auxiliar2 = C->ListaStatus;
    int contador1, contador2;
    contador1 = 0, contador2 = 0;
    while(contador1 < i)
    {
        Auxiliar1 = Auxiliar1->prox;
        contador1++;
    }
    while(contador2 < j)
    {
        Auxiliar2 = Auxiliar2->prox;
        contador2++;
    }
    char auxiliarn;
    auxiliarn = Auxiliar1->status;
    Auxiliar1->status = Auxiliar2->status;
    Auxiliar2->status = auxiliarn;
}
void converteStr(char D[50])
{
    char Auxiliar[11];
    Auxiliar[0] = D[6];  
    Auxiliar[1] = D[7];  
    Auxiliar[2] = D[8];  
    Auxiliar[3] = D[9];  
    Auxiliar[4] = D[3];  
    Auxiliar[5] = D[4];  
    Auxiliar[6] = D[0];  
    Auxiliar[7] = D[1];  
    Auxiliar[8] = '\0';
    strcpy(D, Auxiliar);
}
void Sort(char Campo[50], Arquivos *aberto)
{
    Campos *aux;
    aux = aberto->ListaCampos;
    while(aux != NULL && stricmp(aux->FieldName, Campo) != 0)
        aux = aux->prox;
    
    if(aux != NULL)
    {
        if(aux->ListaValores != NULL)
        {
            int i = 0;
            int j;
            Valores *auxI, *auxJ;
            auxI = aux->ListaValores;
            while(auxI->prox != NULL)
            {
                auxJ = auxI->prox;
                j = i + 1;
                while(auxJ != NULL)
                {
                    if(aux->Type == 'N')
                    {
                        if(auxI->Dado.valorN > auxJ->Dado.valorN)
                            Ordenar(aberto, i, j);
                    }
                    else
                    {
                        if(aux->Type == 'L')
                        {
                            if(auxI->Dado.valorL > auxJ->Dado.valorL)
                                Ordenar(aberto, i, j);
                        }
                        else
                        {
                            if(aux->Type == 'C')
                            {      
                                if(stricmp(auxI->Dado.valorC, auxJ->Dado.valorC) > 0)
                                {
                                    Ordenar(aberto, i, j);
                                }
                            }
                            else
                            {
                                if(aux->Type == 'D')
                                {
                                    char data1[11], data2[11];
                                    strcpy(data1, auxI->Dado.valorD);
                                    strcpy(data2, auxJ->Dado.valorD);
                                    converteStr(data1);
                                    converteStr(data2);
                                    if(strcmp(data1, data2) > 0)
                                        Ordenar(aberto, i, j);
                                }
                                else
                                {
                                    if(stricmp(auxI->Dado.valorM, auxJ->Dado.valorM) > 0)
                                        Ordenar(aberto, i, j);
                                }
                            }
                        }
                    }
                    auxJ = auxJ->prox;
                    j++;
                }
                auxI = auxI->prox;
                i++;
            }
            gotoxy(50, 15);printf("Campo Ordenado!!");
        }
        else
        {
            LimpaTela();
            gotoxy(50, 15);printf("Nao ha registros para ordenar!!");
        }
    }
    else
    {
        LimpaTela();
        gotoxy(50, 15);printf("Campo nao Existe!!");
    }
}
void CadastrarCampo(char *type, int *width, int *dec, char Campo[50])
{
    gotoxy(37, 8);printf("Field Name            Type            Width               Dec");
    gotoxy(37, 9);printf("================================================================");
    textbackground(LIGHTGRAY);
    textcolor(BLACK);
    gotoxy(37, 11);printf("             ");
    gotoxy(37, 11);
    fflush(stdin);
    gets(Campo);
    do
    {
        gotoxy(58, 11);printf("          ");
        gotoxy(58, 11);
        fflush(stdin);
        scanf(" %c", type);
        *type = toupper(*type);
    }while(*type != 'N' && *type != 'C' && *type != 'D' && *type != 'M' && *type != 'L');
    switch(*type)
    {
        case 'N': gotoxy(58, 11);printf("Numeric");
                break;
        case 'C': gotoxy(58, 11);printf("Character");
                break;
        case 'D': gotoxy(58, 11);printf("Date");
                break;
        case 'M': gotoxy(58, 11);printf("Memo");
                break;
        case 'L': gotoxy(58, 11);printf("Logical");
                break;           
    }
    if(*type == 'L')
    {
        gotoxy(75, 11);printf("      ");
        *width = 1;
        gotoxy(75, 11);printf("%d", *width);
    }
    else
    {
        gotoxy(75, 11);printf("      ");
        gotoxy(75, 11);scanf("%d", width);
    }
    if(*type == 'N')
    {
        gotoxy(95, 11);printf("     ");
        gotoxy(95, 11);scanf("%d", dec);
    }
}
void ModifyStructure(Arquivos *aberto)
{
    if(aberto != NULL)
    {
        LimpaTela();
        int contador = 0;
        Status *stat = aberto->ListaStatus;
        while(stat != NULL)
        {
            contador++;
            stat = stat->prox;
        }
            if(contador == 0)
            {
                char op;
                gotoxy(45, 15);printf("Deseja Modificar os campos ou criar novos?(M/N)");
                gotoxy(45, 16);
                op = toupper(getch());
                char type;
                int dec, width;
                char Campo[50];
                Campos *aux;
                if(op == 'M')
                {
                    LimpaTela();
                    gotoxy(45, 15);printf("Digite o nome do campo que deseja Alterar");
                    gotoxy(45, 16);
                    fflush(stdin);
                    gets(Campo);
                    aux = aberto->ListaCampos;
                    while(aux != NULL && stricmp(Campo, aux->FieldName) != 0)
                        aux = aux->prox;
                    
                    LimpaTela();
                    if(aux != NULL)
                    {
                        CadastrarCampo(&type, &width, &dec, Campo);
                        strcpy(aux->FieldName, Campo);
                        aux->Type = type;
                        aux->Width = width;
                        aux->Dec = dec;
                        LimpaTela();
                        gotoxy(50, 15);printf("Campo Alterado!!");
                    }
                    else
                    {
                        gotoxy(50, 15);printf("Campo Nao Encontrado!!");
                    }
                }
                else
                {
                    if(op == 'N')
                    {
                        LimpaTela();
                        CadastrarCampo(&type, &width, &dec, Campo);
                        aux = aberto->ListaCampos;
                        while(aux->prox != NULL)
                            aux = aux->prox;
                        
                        Campos *caixa = (Campos*)malloc(sizeof(Campos));
                        caixa->prox = NULL;
                        aux->prox = caixa;
                        strcpy(caixa->FieldName, Campo);
                        caixa->Type = type;
                        caixa->Dec = dec;
                        caixa->Width = width;
                        caixa->ListaValores = NULL;
                        caixa->Patual = NULL;
                        LimpaTela();
                        gotoxy(50, 15);printf("Campo Criado!!");
                    }
                    else
                    {
                        gotoxy(50, 15);printf("Opcao Invalida!!");
                    }
                }
            }
            else
            {
                gotoxy(42, 15);printf("Para usar esse comando Nao deve existir Registros!!");
            }
    }
    else
    {
        gotoxy(50, 15);printf("Nao ha Nenhum Arquivo em Uso!!");
    }
}
void executarComando(char comandoCompleto[MAXCOMANDO], Diretorio **Dir, Arquivos **aberto, int *pos, Status **posicao, int *SetDeleted)
{
	char primeiraPalavra[MAXCOMANDO], restoComando[MAXCOMANDO];
	
	dividirComando(primeiraPalavra, restoComando, comandoCompleto);
	
	if(stricmp(primeiraPalavra, "DISPLAY") == 0)
	{
		Display(*Dir, *aberto, pos, SetDeleted, *posicao);
	}
    else if(stricmp(primeiraPalavra, "QUIT") == 0)
	{
	}
    else if(stricmp(primeiraPalavra, "SORT") == 0)
    {
        if(stricmp(restoComando, "") == 0)
        {
            gotoxy(45, 15); 
			printf("Erro, o comando create precisa de um parametro");
        }
        else
        {
            Sort(restoComando, *aberto);
        }
    }
    else if(stricmp(primeiraPalavra, "CLEAR") == 0)
	{
		LimpaTela();
	}
	else if(stricmp(primeiraPalavra, "EDIT") == 0)
	{
		Edit(*Dir, *aberto, SetDeleted, pos, *posicao);
	}
	else if(stricmp(primeiraPalavra, "DELETE") == 0)
	{
		if(stricmp(restoComando, "") == 0)
		{
			Delete(*Dir, *aberto, pos, posicao, SetDeleted);
		}
		else if(stricmp(restoComando, "ALL") == 0)
		{
			Deleteall(*Dir, *aberto);
		}
	}
	else if(stricmp(primeiraPalavra, "RECALL") == 0)
	{
		if(strlen(comandoCompleto) == 6)
		{
			Recall(*Dir, *aberto, pos, posicao, SetDeleted);
		}
		else if(stricmp(restoComando, "ALL") == 0)
		{
			RecallAll(*Dir, *aberto, SetDeleted);
		}
	}
	else if(stricmp(primeiraPalavra, "PACK") == 0)
	{
		Pack(*aberto, pos, posicao);
	}
	else if(stricmp(primeiraPalavra, "ZAP") == 0)
	{
		Zap(*aberto, pos, posicao);
	}
	else if(stricmp(primeiraPalavra, "DIR") == 0)
	{
		DIR(*Dir, *aberto, pos, SetDeleted, *posicao);
	}
	else if(stricmp(primeiraPalavra, "APPEND") == 0)
	{
		Append(*aberto, *Dir, pos, posicao);
	}
	else if(stricmp(primeiraPalavra, "SORT") == 0)
	{
		printf("Executar comando SORT\n");
	}
	else if(stricmp(primeiraPalavra, "CLEAR") == 0)
	{
		printf("Executar comando CLEAR\n");
	}
	else if(stricmp(primeiraPalavra, "CREATE") == 0)
	{
        if(stricmp(restoComando, "") == 0)
		{
			gotoxy(45, 15); 
			printf("Erro, o comando create precisa de um parametro");
		}
        else
        {
            Create(restoComando, Dir, aberto, pos, posicao);
        }
	}
	else if(stricmp(primeiraPalavra, "USE") == 0)
	{
        if(stricmp(restoComando, "") == 0)
		{
			gotoxy(45, 15); 
			printf("Erro, o comando USE precisa de um parametro");
		}
        else
        {
            Use(*Dir, aberto, restoComando, pos, posicao);
        }
	}
	else if(stricmp(primeiraPalavra, "SET") == 0)
	{
		if(stricmp(restoComando, "DEFAULT TO D:") == 0)
		{
			SetDefault(Dir, restoComando, aberto, pos, posicao);
		}
		else if(stricmp(restoComando, "DEFAULT TO C:") == 0)
		{
			SetDefault(Dir, restoComando, aberto, pos, posicao);
		}
		else if(stricmp(restoComando, "DELETED OFF") == 0)
		{
			SetDeletedF("OFF", SetDeleted);
		}
		else if(stricmp(restoComando, "DELETED ON") == 0)
		{
			SetDeletedF("ON", SetDeleted);
		}
		else
        {
            gotoxy(53, 15);printf("Comando invalido.");
        
        }
	}
	else if(stricmp(primeiraPalavra, "LIST") == 0)
	{
		if(stricmp(restoComando, "") == 0)
		{
			ExibirCampos(*aberto, *Dir, pos, SetDeleted, *posicao);
		}
		else if(stricmp(restoComando, "STRUCTURE") == 0)
		{
			ListStructure(*Dir, *aberto, pos, SetDeleted, *posicao);
		}	
		else
		{		
			dividirComando(primeiraPalavra, restoComando, restoComando);	
			if(stricmp(primeiraPalavra, "FOR") == 0)
			{
				dividirComando(primeiraPalavra, restoComando, restoComando);
                char Campo[50];
                strcpy(Campo, primeiraPalavra);
				dividirComando(primeiraPalavra, restoComando, restoComando);	
				if(stricmp(primeiraPalavra, "=") == 0)
				{
					ListFor(*Dir, *aberto, Campo, restoComando, pos, SetDeleted, *posicao);
				}
				else
                {
                    gotoxy(53, 15);printf("Comando invalido.");
                    
                }
			}
			else
            {
                gotoxy(53, 15);printf("Comando invalido.");
                
            }
		}	
	}
	else if(stricmp(primeiraPalavra, "LOCATE") == 0)
	{
		dividirComando(primeiraPalavra, restoComando, restoComando);
		if(stricmp(primeiraPalavra, "FOR") == 0)
		{
			dividirComando(primeiraPalavra, restoComando, restoComando);
            char auxiliar[50];
            strcpy(auxiliar, primeiraPalavra);
			dividirComando(primeiraPalavra, restoComando, restoComando);
			if(stricmp(primeiraPalavra, "=") == 0)
			{
				Locate(*Dir, *aberto, pos, posicao, auxiliar, restoComando, SetDeleted);
			}
			else
            {
                gotoxy(53, 15);printf("Comando invalido.");
                
            }
			
		}
		else
	    {
            gotoxy(53, 15);printf("Comando invalido.");
            
	    }
	}
	else if(stricmp(primeiraPalavra, "GOTO") == 0)
	{	
        if(stricmp(restoComando, "") == 0)
		{
			gotoxy(45, 15); 
			printf("Erro, o comando GOTO precisa de um parametro");
		}
        else
		    Goto(*Dir, *aberto, pos, posicao, restoComando, SetDeleted);
	}
	else if(stricmp(primeiraPalavra, "MODIFY") == 0)
	{	if(stricmp(restoComando, "STRUCTURE") == 0)
			ModifyStructure(*aberto);
        else
        {
            gotoxy(53, 15);printf("Comando invalido.");
            
        }
	}
	else
	{
		gotoxy(53, 15);printf("Comando invalido.");
        
	}	
}
void toUppercase(char texto[MAXCOMANDO]) 
{
	int i;
    for (i = 0; i < strlen(texto); i++) 
        texto[i] = toupper(texto[i]);
    
    texto[i] = '\0';
}

int main(void)
{
    //Funções prontas: CREATE, LIST, LIST STRUCTURE, DIR, USE, SET DEFAULT, APPEND, LIST FOR, LOCATE FOR, DELETE, SET DELETED, GOTO, DISPLAY, EDIT, QUIT, CLEAR, RECALL, RECALL ALL, DELETE ALL, PACK, ZAP, MODIFY STRUCTURE, SORT.
    Diretorio *Raiz = NULL;
    CriarUnidade(&Raiz); 
    char Email[50], Senha[50];
    MenuLogin(Email, Senha);
    char Comando[50];
    Arquivos *aberto = NULL;
    char comandoCompleto[MAXCOMANDO];
    int Pos = 0;
    int setDeleted = 0;
    Status *Posicao = NULL;
    do
    { 
        ExibirCommandLine(Raiz, aberto, &Pos, &setDeleted, Posicao);
        textbackground(BLACK);
        textcolor(WHITE);
        gotoxy(44, 29);printf("Enter a dBASE I I I PLUS command.");
        gotoxy(6, 26);
        fflush(stdin);
        gets(comandoCompleto);
        //toUppercase(comandoCompleto);
        executarComando(comandoCompleto, &Raiz, &aberto, &Pos, &Posicao, &setDeleted);
    }while(stricmp(comandoCompleto, "QUIT") != 0);       
}
