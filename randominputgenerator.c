#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int ntb;//number of trade banks
    // printf("number of trade banks(max limit 1000)=");
    scanf("%d",&ntb);//take input of number of tradebanks
    int nc;//number of currencies in each trade bank
    // printf("number of currencies for every tradebank(max limit 1000)");
    scanf("%d",&nc);
    for(int i=0;i<ntb;i++)
    {
        printf("1 B%d\n",i);//print 1 Bi where i is bank number
    }
    for(int i=0;i<ntb;i++)
    {
        for(int j=0;j<nc;j++)
        {
            printf("5 B%d c%d\n",i,j);
        }
    }
    for(int i=0;i<ntb;i++)
    {
        for(int j=0;j<nc;j++)
        {
            for(int k=0;k<nc;k++)
            {
                int doesedgeexist=rand()%2;
                if(doesedgeexist==1&& j!=k)
                {
                    int conversionrate=rand()%20;
                    conversionrate+=rand()%20;
                    printf("3 B%d c%d c%d %d\n",i,j,k,conversionrate+1);
                }
            }
        }
    }
    // printf("8\n");
    int from,to;
    from=rand()%nc;
    to=rand()%nc;
    printf("9 c%d c%d\n",to, from);
    
    for(int i=0;i<ntb;i++)
    {
        printf("2 B%d\n",i);//print 1 Bi where i is bank number
    }
    printf("10");
    return 0;
}