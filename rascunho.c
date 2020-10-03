void insertDoubleData(FILE *fp ,BackDataSet* rec)
{
    char *eptr;
    char str[6],string[100];
    int count = 0;
    char pos;
    pos = fgetc(fp);
    while(pos != ',')
    {
        string[count] = pos;
        count++;
        pos = fgetc(fp);
    }
    string[count]= '\0';
    rec->pelvic_incidence = strtod(string, &eptr);
    //pos = fgetc(fp);
}

void insertStringDatae(FILE *fp ,BackDataSet* rec)
{
    char *eptr;
    char str[6],string[100];
    int count = 0;
    char pos;
    pos = fgetc(fp);
    while(pos != ',')
    {
        string[count] = pos;
        count++;
        pos = fgetc(fp);
    }
    string[count]= '\0';
    rec->pelvic_incidence = strtod(string, &eptr);
    //pos = fgetc(fp);
}