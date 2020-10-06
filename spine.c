#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 
#include"spine.h"

void GlobalEntropy(Table * table);
//
// data structure to get the data table
// data types declaration
//
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
    int classification; // 0 to normal 1 to abnormal

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
    double gain;
};

struct classification
{
    double value; // the value must be ordered
    int classification; // 0 to normal and 1 to abnormal

    struct classification * ant;
    struct classification * prox;
};

struct classificationTable
{
    // a order by value table to compare value with classification
    ValueClassification * firstDataFrame;
    ValueClassification * lastDataFrame;
    double entropy;
    double threshold;
    char attributeName[30]; // recieves the attribute name 
    int posAtual;
    int count;
};

// Tree structure

struct NO
{
    double threshold; //recebe o valor para tomada de decisão x > value = esq <= direita
    double value; // recebe o gain ratio para a decisão de onde colocar o no
    char valueName[30];
    struct NO *esq;
    struct NO *dir;
};


// INICIALIZADORES // 

ArvBin* createTree()
{
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
};

Table * newData()
{
    Table * newData = (Table* )malloc(sizeof(Table));
    newData->count = 0;
    newData->posAtual = 0;
    newData->firstDataFrame = NULL;
    newData->lastDataFrame = NULL;
    return newData;
}

ClassificationTable * newClassData()
{
    ClassificationTable * newClassData = (ClassificationTable* )malloc(sizeof(ClassificationTable));
    newClassData->count = 0;
    newClassData->posAtual = 0;
    newClassData->firstDataFrame = NULL;
    newClassData->lastDataFrame = NULL;
    return newClassData;
}

ValueClassification * newValueClassData()
{
    ValueClassification * newValueClassData = (ValueClassification* )malloc(sizeof(ValueClassification));
    return newValueClassData;
}


// INSERÇÔES //

int insertTree(ArvBin* raiz, double gain, double threshhold, char name[30])
{
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->value = gain;
    novo->threshold = threshhold;
    strcpy(novo->valueName,name );
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(gain == atual->value){
                free(novo);
                return 0;//elemento j� existe
            }

            if(gain > atual->value)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(gain > ant->value)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}



//BACKDATASET //
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

void InsertInOrder(BackDataSet * recl , BackDataSet * reca, int * quant, int max)
{
        reca->ant = recl->ant;
        reca->prox = recl;
        recl->ant->prox = reca;
        recl->ant = reca;
}

// VALUE DATA//

void insertValueClassificationTable(ClassificationTable* l, ValueClassification * rec)
{
    int quant = 0;

    if(l->count == 0 )
    {
        l->firstDataFrame = rec;
        l->lastDataFrame = rec;
        rec->ant = rec;
        rec->prox = rec;
        l->count = (l->count)+ 1;
    }
    else
    {
        InsertInValueClassificationInOrder(l->firstDataFrame ,rec, &quant, l->count);
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
        InsertInValueClassificationInOrder(recl->prox, reca, quant, max);
    }
    else
    {   
        reca->ant = recl->ant;
        reca->prox = recl;
        recl->ant->prox = reca;
        recl->ant = reca;
    }
}


int countData(Table * table)
{
    return table->count;
}

// Read file functions //

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
        if(strcmp(str,"normal") == 0)
        {
            rec->classification = 0;
        }
        else
        {
            rec->classification = 1;
        }
        insertFrame(l, rec);
        pos = fgetc(fp);
    }
    fclose(fp);
    printf("\n -----------------load concluded-------------------\n");
}

// processing data functions //

void generateClassificationTables(Table * table)
{
    ArvBin tree = createTree();
    int i = 0;
    int j = 0;
    ClassificationTable * classification[12];
    for(i = 0 ; i < 12 ; i++)
    {
        classification[i] = newClassData();
    }
    // give a name to table data
    strcpy(classification[0]->attributeName,"pelvic_incidence");
    strcpy(classification[1]->attributeName,"pelvic_tilt");
    strcpy(classification[2]->attributeName,"lumbar_lordosis_angle");
    strcpy(classification[3]->attributeName,"sacral_slope");
    strcpy(classification[4]->attributeName,"pelvic_radius");
    strcpy(classification[5]->attributeName,"degree_spondylolisthesis");
    strcpy(classification[6]->attributeName,"pelvic_slope");
    strcpy(classification[7]->attributeName,"direct_tilt");
    strcpy(classification[8]->attributeName,"thoracic_slope");
    strcpy(classification[9]->attributeName,"cervical_tilt");
    strcpy(classification[10]->attributeName,"sacrum_angle");
    strcpy(classification[11]->attributeName,"scoliosis_slope");
    BackDataSet * row = table->firstDataFrame;
    for(i = 0 ; i< table->count; i++)
    {
        int class = row->classification;
        for(j = 0 ; j < 12 ; j++)
        {
            ValueClassification* rec = newValueClassData();
            if(j == 0 )
            rec->value = row->pelvic_incidence;
                else if(j == 1)
                    rec->value = row->pelvic_tilt;
                else if(j == 2)
                    rec->value = row->lumbar_lordosis_angle;
                else if(j == 3)
                    rec->value = row->sacral_slope;
                else if(j == 4)
                    rec->value = row->pelvic_radius;
                else if(j == 5)
                    rec->value = row->degree_spondylolisthesis;
                else if(j == 6)
                    rec->value = row->pelvic_slope;
                else if(j == 7)
                    rec->value = row->direct_tilt;
                else if(j == 8)
                    rec->value = row->thoracic_slope;
                else if(j == 9)
                    rec->value = row->cervical_tilt;
                else if(j == 10)
                    rec->value = row->sacrum_angle;
                else if(j == 11)
                    rec->value = row->scoliosis_slope;

            rec->classification = class;
            insertValueClassificationTable(classification[j], rec);
        }
        row = row->prox;
    }
    GlobalEntropy(table);
    for(i = 0 ; i < 12 ; i++)
    {
        printf("%s\n",classification[i]->attributeName);
        GainRatio(classification[i]);
        printf("entropy --> %lf",classification[i]->entropy);
        printf("---  threshhold --> %lf\n\n",classification[i]->threshold);
        insertTree(tree,classification[i]->entropy,classification[i]->threshold,classification[i]->attributeName);
    }
    printTree(tree);
}

void GainRatio(ClassificationTable * classificationTable)
{
    int i,j, normalCount = 0, abnormalCount = 0, currentClass;
    double currentValue, smallestEntropy = 1.0, betterValue,actualEntropy = 0.0, totalPositive;
    ValueClassification * row = classificationTable->firstDataFrame;
    ValueClassification * row2 = classificationTable->firstDataFrame;
    currentClass = row->classification;
    betterValue = row->value;
    for(i = 0 ; i < classificationTable->count ; i++)
    {
        totalPositive = 0;
        currentValue = row->value;
        normalCount = 0;
        abnormalCount = 0;
        row2 = classificationTable->firstDataFrame;
        for(j = 0; j < classificationTable->count; j++)
        {
            if(row2->value <= currentValue && row2->classification == 1)
            {
                abnormalCount++;
                totalPositive++;
            }
            else
            {
                if(row2->value <= currentValue )
                {
                    totalPositive++;
                }
                normalCount++;
            }
            row2 = row2->prox;
        }
        row = row->prox;
        actualEntropy = Entropy(normalCount, abnormalCount ,totalPositive );
        if(actualEntropy < smallestEntropy) 
        {
            smallestEntropy = actualEntropy;
            betterValue = row->value;
        }
    }
    classificationTable->threshold = betterValue;
    classificationTable->entropy = smallestEntropy;
}

void GlobalEntropy(Table * table)
{
    int countNormal = 0 , countAbnormal = 0;
    int i;\
    double entropy;
    BackDataSet * row = table->firstDataFrame;

    for(i = 0 ; i < table->count; i++)
    {
        if(row->classification == 0)
        {
            countNormal++;
        }
        else
        {
            countAbnormal++;
        } 
        row = row->prox;
    }
    
    entropy = Entropy(countNormal,countAbnormal, table->count);
    table->gain = entropy;
    printf("\nentropyyy --%lf\n", entropy);
}

double Entropy(int countNormal, int countAbnormal, int total)
{
    double entropy2 =0.0,p1=0.0, p2=0.0;
    p1 = -((double)countAbnormal/(double)total)*log2((double)countAbnormal/(double)total); 
    p2 = ((double)countNormal/(double)total) * log2((double)countNormal/(double)total);
    entropy2 = fabs((p2)-(p1));
    return entropy2;
}

void printRows(BackDataSet * row, int count, int position)
{
    position++;
    if(count > position)
    {
        printRows(row->prox,count, position);
    }
}

void printTree(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf(" (%lf %lf <> %s )",(*raiz)->threshold,(*raiz)->value, (*raiz)->valueName);
        printf("\n");
        printTree(&((*raiz)->esq));
        printTree(&((*raiz)->dir));
    }
}
