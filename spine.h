#ifndef SPINE_H_INCLUDED
#define SPINE_H_INCLUDED

typedef struct backDataSet BackDataSet;
typedef struct table Table;
typedef struct valueClassification ValueClassification;
typedef struct valueClassificationTable ValueClassificationTable;

void interface();
//Cria um table sem vazio
Table * newData();

//insere a backDataSet em um table
void insertFrame(Table* l, BackDataSet* rec);
//indice
BackDataSet* SelectReceitaByNumber(BackDataSet* r , int n, int count);
//marca a backDataSet como feita
void LoadSpineDataCsv(Table * l);
//Edita uma backDataSet especifica
int countData(Table * table);
#endif
