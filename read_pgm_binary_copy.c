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
    int r=64, c=64;
    char s1[1],s2[1];
    unsigned char ch;
    FILE *f;
    f=fopen("testout.pgm", "r");
    if (f==NULL)
      {
        printf("Cannot open");
        exit(1);
      }
     fgets(s1,40,f);
     while(atoi(s1)!=255)
      {
       strcpy(s2,s1);
       fgets(s1,1,f);
       printf("*");
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
