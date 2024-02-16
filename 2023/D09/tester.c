#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long next(long *array, int count);

int part=1;

int main (int argc, char * argv[])
{
    char *filename = "test.txt";
    long result=0;
    char buf[125], *bufp;
    long set[120];
    int x;
    FILE * fp;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 125, fp) != NULL)
    {
        bufp=buf;
        for(x=0;*(bufp-1)!='\n';bufp++)
            set[x++]=strtol(bufp,&bufp,10);
        result+=next(set,x);
        printf("res: %ld\n", result);
    }
    printf("%ld\n",result);
    return 0;
}


long next(long *array, int count)
{
    long *start=malloc((count-1)*sizeof(long));
    long *put =start;
    int x, out=0;
    for(x=1;x<count;x++)
    {
        *(put++)=array[x]-array[x-1];
    }
    for(int i=0;i<x;i++)
        if(start[i]!=0)
        {
            out=next(start,x-1);
            break;
        }
    free(start);
    if(part==1)
        return array[x-1]+out;
    return array[0]-out;
}