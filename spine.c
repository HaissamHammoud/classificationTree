#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 
#include"spine.h"

// data structure to get the data table
struct backDataSet
{
    double pelvic_incidence;
    double pelvic_tilt;
    double lumbar_lordosis_angle;
    double sacral_slope;
    double pelvic_radius;
    double degree_spondylolisthesis;
    double pelvic_slope;
    double direct_tilt;
    double thoracic_slope;
    double cervical_tilt;
    double sacrum_angle;
    double scoliosis_slope;
    char classifycation[10];

    //Nos
    struct backDataSet * ant;
    struct backDataSet * prox;
};

// Refers to the inicial data structure
struct table
{
    BackDataSet * firstDataFrame;
    BackDataSet * lastDataFrame;
    int posAtual;
    int count;
};


//Cria um table sem vazio
Table * newData()
{
    Table * newData = (Table* )malloc(sizeof(Table));
    newData->count = 0;
    newData->posAtual = 0;
    newData->firstDataFrame = NULL;
    newData->lastDataFrame = NULL;
    return newData;
}

//seleciona uma backDataSet, para uso interno apenas
BackDataSet* SelectReceitaByNumber(BackDataSet* r , int n, int count)
{
    if(count == n)
    {
        return r;
    }
    else
    {
        SelectReceitaByNumber(r->prox , n , count+1);
    }
}

//Pega a posição onde será inserida a backDataSet
void InsertInOrder(BackDataSet * recl , BackDataSet * reca, int * quant, int max)
{
    // if(strcmp(recl->titulo, reca->titulo)<0 && *(quant)<max)
    // {
    //     *quant = *(quant) + 1 ;
    //     printf(" %d ",*(quant));
    //     InsertInOrder(recl->prox, reca, quant, max);
    // }
    // else
    // {   
        reca->ant = recl->ant;
        reca->prox = recl;
        recl->ant->prox = reca;
        recl->ant = reca;
    //}
}

int countData(Table * table)
{
    return table->count;
}

//insere a backDataSet em um table
void insertFrame(Table* l, BackDataSet* rec)
{
    int quant = 0;
    //caso seja a primeira backDataSet, inserir no inicio
    if(l->count == 0 )
    {
        l->firstDataFrame = rec;
        l->lastDataFrame = rec;
        rec->ant = rec;
        rec->prox = rec;
        l->count = (l->count)+ 1;
        printf("%d",l->count);
    }
    else
    {
        InsertInOrder(l->firstDataFrame ,rec, &quant, l->count);
        if(quant == 0)
        {
            l->firstDataFrame = rec;
        }
        else if(quant == (l->count)-1)
        {
            l->lastDataFrame = rec;
        }
        l->count = (l->count) + 1;
    }
}

//indice
void indice(Table * l)
{
    char o;
    int i = 0;
    printReceitas(l->firstDataFrame, i, l);
    printf("\n####Para continuar digite qualquer botao####");
    scanf("%c", &o);
    scanf("%c", &o);
}

//folha as receitas funciona como indice
void printReceitas(BackDataSet * r, int i, Table * l)
{
    if(i < l->count)
    {
        printf("\n Nome: %s", r->classifycation);
        printf(" id: %d", i);
        printReceitas(r->prox , i+1, l);
    }
}

// implement a bether load when the data structure become dynamic
void LoadSpineDataCsv(Table * l)
{
    int i,count;
    FILE *fp;
    char str[14],string[100], pos;
    char *eptr;
    float f;
    fp = fopen("data/test.csv", "r");
    pos = fgetc(fp);
    printf("\n\n\n Loading spine data...\n\n\n");
    while(pos != EOF )
    {
        BackDataSet* rec = (BackDataSet*)malloc(sizeof(BackDataSet));
        if(feof(fp))
        {
            break;
        }
        //carrega o titulo
        count = 0;
        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->pelvic_incidence = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;
        //carrega o tempo
        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->pelvic_tilt = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->lumbar_lordosis_angle = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->sacral_slope = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->pelvic_radius = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->degree_spondylolisthesis = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->pelvic_slope = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->direct_tilt = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->thoracic_slope = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->cervical_tilt = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->sacrum_angle = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            
            string[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        string[count]= '\0';
        rec->scoliosis_slope = strtod(string, &eptr);
        pos = fgetc(fp);
        count = 0;

        while(pos != ',')
        {
            str[count] = pos;
            count++;
            pos = fgetc(fp);
        }
        str[count]= '\0';
        strcpy(rec->classifycation, str);
        insertFrame(l, rec);
        pos = fgetc(fp);
    }
    fclose(fp);
    printf("\n -----------------load concluded-------------------\n");
}