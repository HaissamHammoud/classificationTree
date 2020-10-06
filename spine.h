#ifndef SPINE_H_INCLUDED
#define SPINE_H_INCLUDED

typedef struct backDataSet BackDataSet;
typedef struct table Table;
typedef struct classification ValueClassification;
typedef struct classificationTable ClassificationTable;
typedef struct NO* ArvBin;

void interface();
//Cria um table sem vazio
Table * newData();

//insere a backDataSet em um table
void insertFrame(Table* l, BackDataSet* rec);
//indice
BackDataSet* SelectDataSetById(BackDataSet* r , int n, int count);
//marca a backDataSet como feita
void LoadSpineDataCsv(Table * l);
//Edita uma backDataSet especifica
int countData(Table * table);
// process data
void printSpineData(Table * table);
void generateClassificationTables(Table * table);
double Entropy(int countNormal, int countAbnormal, int total);
void GlobalEntropy(Table * table);
void GainRatio(ClassificationTable * classificationTable);
void getDoubleValue(double * receiver, FILE * fp);
void InsertInValueClassificationInOrder(ValueClassification * recl , ValueClassification * reca, int * quant, int max);
void insertFrame(Table* l, BackDataSet* rec);
void InsertInOrder(BackDataSet * recl , BackDataSet * reca, int * quant, int max);
ValueClassification * newValueClassData();
void printTree(ArvBin *raiz);
int insertTree(ArvBin* raiz, double gain, double threshhold, char name[30]);
ArvBin* createTree();
#endif
