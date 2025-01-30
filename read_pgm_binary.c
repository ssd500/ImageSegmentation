#include <stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define MAXROW 500
#define MAXCOL 500
int main()
{
    int data[MAXROW][MAXCOL];
    //char a[40];
    int flag=0;
    int i, j;
    int r, c;
    char s1[80],s2[80];
    unsigned char ch;
    FILE *f;
    f=fopen("wf4.pgm", "r");
    if (f==NULL)
      {
        printf("Cannot open");
        exit(1);
      }
     fgets(s1,80,f);
     while(atoi(s1)!=255)
      {
       strcpy(s2,s1);
       fgets(s1,80,f);
      }
     i=0;
     while(s2[i]!=' ')
      {
       s1[i]=s2[i];
       i++;
      }
      s1[i]='\0';
      c=atoi(s1);
      j=0;
      while(s2[i]==' ')
       i++;
      while(s2[i]!='\0')
       {
        s1[j]=s2[i];
        j++;
        i++;
       }
      r=atoi(s1);
      printf("Col:%d, Row:%d\n",c,r);
      for(i=0;i<r;i++)
       {
           for(j=0;j<c;j++)
            {
                ch=fgetc(f);
                data[i][j]=ch;
                printf("%d\t",data[i][j]);

            }
       }
      fclose(f);
      f=fopen("testout.pgm", "w");
      fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", c, r);
    fprintf(f, "255\n");
    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            fprintf(f, "%d\t", data[i][j]);
        fprintf(f, "\n");
    }

 /*   for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            printf("%d\t", data[i][j]);
    }*/
    fclose(f);
}
