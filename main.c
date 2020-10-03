#include<stdio.h>
#include<stdlib.h>
#include"spine.h"

int main()
{
    //Loading
    int n;
    Table * l = newData();
    char opt= 'a';
    BackDataSet* nova ;
    BackDataSet* movel ;
    LoadSpineDataCsv(l);
    printf("%d",countData(l));
    printf("\nBem Vindo!");
    while(opt != 's')
    {
      scanf("\n%c", &opt);
    }
}