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

struct valueClassification
{
    double value; // the value must be ordered
    int classification; // 0 to normal and 1 to abnormal

    struct valueClassification * ant;
    struct valueClassification * prox;
};

struct valueClassificationTable
{
    ValueClassification * firstDataFrame;
    ValueClassification * lastDataFrame;
    char attributeName[30]; // recieves the attribute name 
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

ValueClassificationTable * newClassData()
{
    ValueClassificationTable * newClassData = (ValueClassificationTable* )malloc(sizeof(ValueClassificationTable));
    newClassData->count = 0;
    newClassData->posAtual = 0;
    newClassData->firstDataFrame = NULL;
    newClassData->lastDataFrame = NULL;
    return newClassData;
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

void getDoubleValue(double * receiver, FILE * fp)
{
    int count = 0;
    char pos;
    char *eptr, string[30];
    pos = fgetc(fp);
    while(pos != ',')
    {
        string[count] = pos;
        count++;
        pos = fgetc(fp);
    }
    string[count]= '\0';
    *receiver = strtod(string, &eptr);
    printf("%s", string);
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
        getDoubleValue(&rec->pelvic_incidence, fp);
        getDoubleValue(&rec->pelvic_tilt, fp);
        getDoubleValue(&rec->lumbar_lordosis_angle, fp);
        getDoubleValue(&rec->sacral_slope, fp);
        getDoubleValue(&rec->pelvic_radius, fp);
        getDoubleValue(&rec->degree_spondylolisthesis, fp);
        getDoubleValue(&rec->pelvic_slope, fp);
        getDoubleValue(&rec->direct_tilt, fp);
        getDoubleValue(&rec->thoracic_slope, fp);
        getDoubleValue(&rec->cervical_tilt, fp);
        getDoubleValue(&rec->sacrum_angle, fp);
        getDoubleValue(&rec->scoliosis_slope, fp);
        count = 0;
        pos = fgetc(fp);
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
        printf("\n");
    }
    fclose(fp);
    printf("\n -----------------load concluded-------------------\n");
}

double entropy(Table * table)
{
    int i ;
    int tableCount = table->count;
    if(table->count == 0)
    {
        return 0.0;
    };
    for(i = 0; i < tableCount; i++ )
    {

    }
}

// value table functions

void insertValueClassificationTable(ValueClassificationTable* l, ValueClassification * rec)
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

void InsertInValueClassificationInOrder(ValueClassification * recl , ValueClassification * reca, int * quant, int max)
{
    if(recl->value > reca->value && *(quant)<max)
    {
        *quant = *(quant) + 1 ;
        printf(" %d ",*(quant));
        InsertInOrder(recl->prox, reca, quant, max);
    }
    else
    {   
        reca->ant = recl->ant;
        reca->prox = recl;
        recl->ant->prox = reca;
        recl->ant = reca;
    }
}

// function responsible for processing the data in order 
void processData(Table * table)
{
    int i, j ;
    BackDataSet * actual = table->firstDataFrame;
    ValueClassificationTable * classificationTable[12];
    // process all the rows
    classificationTable[0] = newClassData();
    for(i = 0 ; i < table->count ; i++ )
    {
        ValueClassification* rec = (ValueClassification*)malloc(sizeof(ValueClassification));
        //set the name for the property tavble
        strcpy(classificationTable[0]->attributeName,"pelvic_incidence");
        rec->value = actual->pelvic_incidence;
        insertValueClassificationTable(classificationTable[0],rec);
        actual = actual->prox;
    }

    classificationTable[1] = newClassData();
    for(i = 0 ; i < table->count ; i++ )
    {
        ValueClassification* rec = (ValueClassification*)malloc(sizeof(ValueClassification));
        //set the name for the property tavble
        strcpy(classificationTable[1]->attributeName,"pelvic_tilt");
        rec->value = actual->pelvic_tilt;
        insertValueClassificationTable(classificationTable[1],rec);
        actual = actual->prox;
    }

    classificationTable[2] = newClassData();
    for(i = 0 ; i < table->count ; i++ )
    {
        ValueClassification* rec = (ValueClassification*)malloc(sizeof(ValueClassification));
        //set the name for the property tavble
        strcpy(classificationTable[2]->attributeName,"lumbar_lordosis_angle");
        rec->value = actual->lumbar_lordosis_angle;
        insertValueClassificationTable(classificationTable[2],rec);
        actual = actual->prox;
    }

    classificationTable[3] = newClassData();
    for(i = 0 ; i < table->count ; i++ )
    {
        ValueClassification* rec = (ValueClassification*)malloc(sizeof(ValueClassification));
        //set the name for the property tavble
        strcpy(classificationTable[3]->attributeName,"sacral_slope");
        rec->value = actual->sacral_slope;
        insertValueClassificationTable(classificationTable[3],rec);
        actual = actual->prox;
    }

    classificationTable[4] = newClassData();
    for(i = 0 ; i < table->count ; i++ )
    {
        ValueClassification* rec = (ValueClassification*)malloc(sizeof(ValueClassification));
        //set the name for the property tavble
        strcpy(classificationTable[4]->attributeName,"pelvic_radius;");
        rec->value = actual->pelvic_radius;
        insertValueClassificationTable(classificationTable[4],rec);
        actual = actual->prox;
    }
    //return the value gain ratio

    //return the gain ratio of values


}

    // double pelvic_radius;
    // double degree_spondylolisthesis;
    // double pelvic_slope;
    // double direct_tilt;
    // double thoracic_slope;
    // double cervical_tilt;
    // double sacrum_angle;
    // double scoliosis_slope;