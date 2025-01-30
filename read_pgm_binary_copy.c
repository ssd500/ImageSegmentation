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
    //unsigned char ch;
    unsigned char ch;
    FILE *f;
    f=fopen("wf5.pgm", "r");
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
       //printf("*");
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
      s1[j]='\0';
      r=atoi(s1);
      printf("Col:%d, Row:%d\n",c,r);
      s1[0]='\0';
      int k;
      for(i=0;i<r;i++)
       {
           for(j=0;j<c;j++)
            {
               ch=fgetc(f);
               //printf("%c %d  ",ch,(int)ch);
              // data[i][j]=atoi(s1);
                data[i][j]=(int)ch;
               //fscanf(f,"%d\t", &data[i][j]);
               printf(" %d %d %d\t\t",data[i][j],i,j);

            }
       }
      fclose(f);
      f=fopen("testout.pgm", "w");
      fprintf(f, "P5\n");
    fprintf(f, "%d %d\n", c, r);
    fprintf(f, "255\n");
    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++) { ch=data[i][j];
            //fprintf(f, "%d ", data[i][j]);
        //fprintf(f, "\n");
              fputc(ch,f); }
    }

 /*   for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            printf("%d\t", data[i][j]);
    }*/
    fclose(f);
}
