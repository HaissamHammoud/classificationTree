#ifndef SPINE_H_INCLUDED
#define SPINE_H_INCLUDED

typedef struct backDataSet BackDataSet;
typedef struct table Table;

void interface();
//Cria um table sem vazio
Table * newData();
//apenas cria uma backDataSet sem inserir ela no contexto
BackDataSet* novaReceita();
//insere a backDataSet em um table
void insertFrame(Table* l, BackDataSet* rec);
//indice
void indice(Table * l);
//folha as receitas funciona como indice
void printReceitas(BackDataSet * r, int i, Table * l);
//navega entre as receitas
void navegar(Table * l);
//exclui um elemento
void Delete(Table * l, int n);
//seleciona uma
BackDataSet* SelectReceitaByNumber(BackDataSet* r , int n, int count);
//marca a backDataSet como feita
void MarkAsDone(Table* l, int n);
//Salva um table
void Salvar(Table* l);
//carrega o table salvo
void LoadSpineDataCsv(Table * l);
//Edita uma backDataSet especifica
void EditReceita(Table * l , int n);
int countData(Table * table);
#endif
