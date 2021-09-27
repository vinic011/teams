#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//definição de estruturas importantes
int i,j;
typedef char cadeia[21];
typedef char logic;
const logic FALSE = 0, TRUE = 1;
logic trocou;

//informações de cada time
typedef struct time time;
struct time
{
    cadeia nome;
    int pontos, vitorias, golspro, golscontra, saldogols;
};

//tabela dos times
typedef struct tabelatimes tabelatimes;
struct tabelatimes
{
    time VetorTimes[30];
    int ntimes;
};
tabelatimes TabTimes;

//resultado
typedef struct resultado resultado;
struct resultado
{
    int local, visitante;
};
resultado Jogos[30][30];


//declaração de arquivos e funções
FILE *filein, *fileout;
void InicializarArquivos ();
void LerArmazenarTimes ();
void EscreverTimes ();
void LerArmazenarJogos ();
void EscreverJogos ();
void PreencherTabTimes ();
void EscreverTabTimes ();
void OrdenarTabTimes ();
void EscreverClassificacaoFinal ();

//função main
int main ()
{
    InicializarArquivos ();
    LerArmazenarTimes ();
    EscreverTimes ();
    LerArmazenarJogos ();
    EscreverJogos ();
    PreencherTabTimes ();
    EscreverTabTimes ();
    OrdenarTabTimes ();
    EscreverClassificacaoFinal ();
    printf ("\n\n");
    system ("pause");
    return 0;
}

void InicializarArquivos ()
{
    printf ("RESULTADOS DE UM CAMPEONATO\n\n");
    printf ("Entrada de dados no arquivo input.txt\n\n");
    printf ("Relatorio dos Resultados no arquivo output.txt\n\n");
    filein = fopen ("input.txt", "r");
    fileout = fopen ("output.txt", "w");
    fprintf (fileout,"R E S U L T A D O S   D E   U M   C A M P E O N A T O\n\n");
}

void LerArmazenarTimes ()
{
    int len;
    char lixo;
    fscanf (filein, "%d%c", &TabTimes.ntimes, &lixo);
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        fgets (TabTimes.VetorTimes[i].nome, 26, filein);
        len = strlen(TabTimes.VetorTimes[i].nome);
        TabTimes.VetorTimes[i].nome[len-1] = '\0';
        TabTimes.VetorTimes[i].pontos = 0;
        TabTimes.VetorTimes[i].vitorias = 0;
        TabTimes.VetorTimes[i].golspro = 0;
        TabTimes.VetorTimes[i].golscontra = 0;
        TabTimes.VetorTimes[i].saldogols = 0;
    }
}

void EscreverTimes ()
{
    fprintf(fileout,"Times do campeonato:\n");
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        fprintf(fileout,"%s \n",TabTimes.VetorTimes[i].nome);
    }
}

void LerArmazenarJogos ()
{
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        for (j = 0; j<= TabTimes.ntimes-1; j++)
        {
            if(i!=j)
            {
                fscanf(filein, "%d",&Jogos[i][j].local);
                fscanf(filein, "%d",&Jogos[i][j].visitante);
            }
        }
    }
}

void EscreverJogos ()
{
    cadeia tres[3];
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        for (j = 0; j< 3; j++)
        {
            tres[i][j] = TabTimes.VetorTimes[i].nome[j];
        }
    }

    fprintf(fileout,"\nTabela Resultados:\n");
    fprintf(fileout,"                       ");

    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        for (j = 0; j< 3; j++)
        {
            fprintf(fileout,"%c",tres[i][j]);
        }
        fprintf(fileout,"    ");
    }

    fprintf(fileout,"\n");
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        fprintf(fileout,"%20s",TabTimes.VetorTimes[i].nome);
        for (j = 0; j<= TabTimes.ntimes-1; j++)
        {
            if(i == j)
            {
                fprintf(fileout,"  #####");
            }
            if(i!=j)
            {
                fprintf(fileout,"  %d x %d",Jogos[i][j].local,Jogos[i][j].visitante);
            }
        }
        fprintf(fileout,"\n");
    }

}

void PreencherTabTimes ()
{
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        for (j = 0; j <= TabTimes.ntimes-1; j++)
        {
            if(i!=j)
            {
                TabTimes.VetorTimes[i].golspro += Jogos[i][j].local;
                TabTimes.VetorTimes[j].golspro += Jogos[i][j].visitante;
                TabTimes.VetorTimes[i].golscontra += Jogos[i][j].visitante;
                TabTimes.VetorTimes[j].golscontra += Jogos[i][j].local;

                if(Jogos[i][j].local>Jogos[i][j].visitante)
                {
                    TabTimes.VetorTimes[i].vitorias += 1;
                    TabTimes.VetorTimes[i].pontos += 3;
                }
                if(Jogos[i][j].local<Jogos[i][j].visitante)
                {
                    TabTimes.VetorTimes[j].vitorias += 1;
                    TabTimes.VetorTimes[j].pontos += 3;
                }
                if(Jogos[i][j].local==Jogos[i][j].visitante)
                {
                    TabTimes.VetorTimes[i].pontos += 1;
                    TabTimes.VetorTimes[j].pontos += 1;
                }
            }
        }
    }
    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        TabTimes.VetorTimes[i].saldogols = TabTimes.VetorTimes[i].golspro -TabTimes.VetorTimes[i].golscontra;
    }
}

void EscreverTabTimes ()
{
    fprintf (fileout, "\nTabela de desempenho dos times:\n");
    fprintf (fileout, "%22s | %9s | %9s | %9s | %9s | %9s\n","Time", "Pontos", "Vitorias", "G Pro", "G Contra","Saldo G");

    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        fprintf (fileout, "%22s | %9d | %9d | %9d | %9d | %9d\n",
                 TabTimes.VetorTimes[i].nome,TabTimes.VetorTimes[i].pontos,
                 TabTimes.VetorTimes[i].vitorias,TabTimes.VetorTimes[i].golspro,
                 TabTimes.VetorTimes[i].golscontra,TabTimes.VetorTimes[i].saldogols);
    }
}

void OrdenarTabTimes ()
{
    time aux;
    //ordem pontos
    for (trocou = TRUE, j = TabTimes.ntimes -2; j >= 0 && trocou == TRUE; j--)
    {
        for (trocou = FALSE, i = 0; i <= j; i++)
        {
            if(TabTimes.VetorTimes[i].pontos<TabTimes.VetorTimes[i+1].pontos)
            {
                aux = TabTimes.VetorTimes[i];
                TabTimes.VetorTimes[i] = TabTimes.VetorTimes[i+1];
                TabTimes.VetorTimes[i+1] = aux;
                trocou = TRUE;
            }
        }
    }
    //ordem vitorias
    for (trocou = TRUE, j = TabTimes.ntimes -2; j >= 0 && trocou == TRUE; j--)
    {
        for (trocou = FALSE, i = 0; i <= j; i++)
        {
            if(TabTimes.VetorTimes[i].pontos==TabTimes.VetorTimes[i+1].pontos)
            {
                if(TabTimes.VetorTimes[i].vitorias<TabTimes.VetorTimes[i+1].vitorias)
                {
                    aux = TabTimes.VetorTimes[i];
                    TabTimes.VetorTimes[i] = TabTimes.VetorTimes[i+1];
                    TabTimes.VetorTimes[i+1] = aux;
                    trocou = TRUE;
                }
            }
        }
    }
    //ordem saldo de gols
    for (trocou = TRUE, j = TabTimes.ntimes -2; j >= 0 && trocou == TRUE; j--)
    {
        for (trocou = FALSE, i = 0; i <= j; i++)
        {
            if(TabTimes.VetorTimes[i].pontos==TabTimes.VetorTimes[i+1].pontos)
            {
                if(TabTimes.VetorTimes[i].vitorias==TabTimes.VetorTimes[i+1].vitorias)
                {
                    if(TabTimes.VetorTimes[i].saldogols<TabTimes.VetorTimes[i+1].saldogols)
                    {
                        aux = TabTimes.VetorTimes[i];
                        TabTimes.VetorTimes[i] = TabTimes.VetorTimes[i+1];
                        TabTimes.VetorTimes[i+1] = aux;
                        trocou = TRUE;
                    }
                }
            }
        }
    }
    //ordem gols pro
    for (trocou = TRUE, j = TabTimes.ntimes -2; j >= 0 && trocou == TRUE; j--)
    {
        for (trocou = FALSE, i = 0; i <= j; i++)
        {
            if(TabTimes.VetorTimes[i].pontos==TabTimes.VetorTimes[i+1].pontos)
            {
                if(TabTimes.VetorTimes[i].vitorias==TabTimes.VetorTimes[i+1].vitorias)
                {
                    if(TabTimes.VetorTimes[i].saldogols==TabTimes.VetorTimes[i+1].saldogols)
                    {
                        if(TabTimes.VetorTimes[i].golspro<TabTimes.VetorTimes[i+1].golspro)
                            aux = TabTimes.VetorTimes[i];
                        TabTimes.VetorTimes[i] = TabTimes.VetorTimes[i+1];
                        TabTimes.VetorTimes[i+1] = aux;
                        trocou = TRUE;
                    }
                }
            }
        }
    }
    //ordem alfabetica
    for (trocou = TRUE, j = TabTimes.ntimes -2; j >= 0 && trocou == TRUE; j--)
    {
        for (trocou = FALSE, i = 0; i <= j; i++)
        {
            if(TabTimes.VetorTimes[i].pontos==TabTimes.VetorTimes[i+1].pontos)
            {
                if(TabTimes.VetorTimes[i].vitorias==TabTimes.VetorTimes[i+1].vitorias)
                {
                    if(TabTimes.VetorTimes[i].saldogols==TabTimes.VetorTimes[i+1].saldogols)
                    {
                        if(TabTimes.VetorTimes[i].golspro==TabTimes.VetorTimes[i+1].golspro)
                        {
                            if(strcmp(TabTimes.VetorTimes[i].nome,TabTimes.VetorTimes[i+1].nome)< 0)
                            {
                                aux = TabTimes.VetorTimes[i];
                                TabTimes.VetorTimes[i] = TabTimes.VetorTimes[i+1];
                                TabTimes.VetorTimes[i+1] = aux;
                                trocou = TRUE;
                            }
                        }
                    }
                }
            }
        }
    }
}


void EscreverClassificacaoFinal ()
{
    fprintf (fileout, "\nTabela de desempenho dos times:\n");
    fprintf (fileout, "%22s | %9s | %9s | %9s | %9s\n","Time", "Pontos", "Vitorias", "Saldo G", "G Pro");

    for (i = 0; i <= TabTimes.ntimes-1; i++)
    {
        fprintf (fileout, "%d)%20s | %9d | %9d | %9d | %9d\n",i+1,
                 TabTimes.VetorTimes[i].nome,TabTimes.VetorTimes[i].pontos,
                 TabTimes.VetorTimes[i].vitorias,TabTimes.VetorTimes[i].saldogols,
                 TabTimes.VetorTimes[i].golspro);
    }
}










