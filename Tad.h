union TpDados
{
    float valorN;
    char valorD[10];
    char valorL;
    char valorC[50];
    char valorM[50];
};
typedef union TpDados Dados;

struct TpValor
{
    Dados Dado;  
    struct TpValor *prox;
};
typedef struct TpValor Valores;

struct TpStatus
{
    char status;
    struct TpStatus *prox;
};
typedef struct TpStatus Status;

struct TpCampos
{
    Valores *Patual;
    char FieldName[50];
    char Type;
    int Width;
    int Dec;
    Valores *ListaValores;  
    struct TpCampos *prox;
};

typedef struct TpCampos Campos;

struct TpArquivo
{
    char NomeDBF[30];
    char Data[11];  
    char hora[6];
    Status *ListaStatus;  
    Campos *ListaCampos;  
    struct TpArquivo *ant, *prox;
};
typedef struct TpArquivo Arquivos;

struct TpDir
{
    struct TpDir *top, *bottom;
    char unidade;
    Arquivos *ListaArquivos;
};
typedef struct TpDir Diretorio;

