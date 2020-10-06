#include<stdio.h>
#include<stdlib.h>
#include"spine.h"

int main()
{
    //Loading
    int n, i;
    Table * l = newData();
    //BackDataSet* nova ;
    //BackDataSet* movel ;
    LoadSpineDataCsv(l);
    printf("\n\n %i", countData(l));
    printSpineData(l);
}