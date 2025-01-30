#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//FILE *f;
//int i,j,k,l,r,c;
#define MAXROW 256
#define MAXCOL 256

void readFile(int data[][MAXCOL]){
    FILE *f;
    int i,j,r,c;
    printf("~");
    char s1[80],s2[80];
    unsigned char ch;
    f=fopen("wf4.pgm", "r");
    if (f==NULL)
      {
        printf("Cannot open");
        exit(1);
      }
    fgets(s1,80,f);
    printf("~%s",s1);
     while(atoi(s1)!=255)
      {
       strcpy(s2,s1);
       fgets(s1,80,f);
      }
     printf("~");
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
      for(i=0;i<r;i++)
       {
           for(j=0;j<c;j++)
            {
              //  fscanf(f,"%d\t", &data[i][j]);
                ch=fgetc(f);
                data[i][j]=ch;
                printf("%d\t",data[i][j]);
            }
       }
       fclose(f);
       f=fopen("wf4Check.pgm","w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", c, r);
    fprintf(f, "255\n");
    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            fprintf(f, "%d ", data[i][j]);
        fprintf(f, "\n");
    }
}

void filter(int d[][MAXCOL],int fd[][MAXCOL],int r,int c){
    int sum,i,j,k,l;
    FILE *f;
    printf("~");
    for(i=0;i<r;i++)
        for(j=0;j<c;j++){
            fd[i][j]=d[i][j];
         //   printf("%d\t",fd[i][j]);
        }
    printf("~");
    for(i=2;i<r-2;i++){
        for(j=2;j<c-2;j++){
            //printf("%d",i);
            sum=0;
            for(k=i-2;k<=i+2;k++){
                for(l=j-2;l<=j+2;l++){
                    //printf("%d",k);
                    sum=sum+d[k][l];
                }
            }
            sum=sum/25;
            fd[i][j]=sum;
            printf("%d\t",fd[i][j]);
        }
    }
    f=fopen("wf4Fil.pgm","w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", c, r);
    fprintf(f, "255\n");
    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            fprintf(f, "%d\t", fd[i][j]);
        fprintf(f, "\n");
    }
    printf("~");
}

void createHist(int d[][MAXCOL],int r,int c,int hist[]){
    int i,j,k;
    for(i=0;i<256;i++)
        hist[i]=0;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            k=d[i][j];
            hist[k]=hist[k]+1;
        }
    }
}

int localMax(int hi[],int lo[]){
    int i,j=0,countUp=0,countDown=0,flag=0,max,thresh=35;
    for(i=1;i<256;i++){
        if(hi[i]>hi[i-1]){
            if(flag==1){
                flag=0;
                if(countUp>=thresh&&countDown>=thresh){
                    lo[j++]=max;
                }
                countUp=0;
            }
            max=i;
            countUp+=hi[i]-hi[i-1];
            countDown=0;

        }
        else if(hi[i]<hi[i-1]){
            countDown+=hi[i-1]-hi[i];
            flag=1;
        }
    }
    return j;
}

int findSize(int lo[]){
    int i;
    for(i=0;i<64;i++)
        if(lo[i]=-1)
            return i;
}

void distribute(int lo[],int fd[][MAXCOL],int r,int c,int n){
    int i,j,k;
    //int s=findSize(lo);
    FILE *f;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++){
            if(fd[i][j]<lo[0]&&fd[i][j]>=0)
                fd[i][j]=0;
            else if(fd[i][j]<256&&fd[i][j]>=lo[n-1])
                fd[i][j]=255;
            else{
                for(k=1;k<n;k++)
                    if(fd[i][j]<lo[k]&&fd[i][j]>=lo[k-1])
                        fd[i][j]=256*k/n;
            }

        }
  /*  for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            printf("%d\t",fd[i][j]);*/
    f=fopen("wf4Fin.pgm","w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", c, r);
    fprintf(f, "255\n");
    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
            fprintf(f, "%d\t", fd[i][j]);
        fprintf(f, "\n");
    }
    printf("~");

}

void mark(int r,int c,int v,int l,int visited[][MAXCOL],int filterdata[][MAXCOL]){
    if(r<0||r>255||c<0||c>255)
        return;
    visited[r][c]=l;
    if(filterdata[r-1][c]==v)
        mark(r-1,c,v,l,visited,filterdata);
    if(filterdata[r+1][c]==v)
        mark(r+1,c,v,l,visited,filterdata);
    if(filterdata[r][c-1]==v)
        mark(r,c-1,v,l,visited,filterdata);
    if(filterdata[r][c+1]==v)
        mark(r,c+1,v,l,visited,filterdata);
   /* if(filterdata[r-1][c]==v)
        mark(r-1,c,v,l);
    if(filterdata[r-1][c]==v)
        mark(r-1,c,v,l);
    if(filterdata[r-1][c]==v)
        mark(r-1,c,v,l);
    if(filterdata[r-1][c]==v)
        mark(r-1,c,v,l);*/
}

void compMerge(int filterdata[][MAXCOL],int visited[][MAXCOL]){
    int i,j,l=0,v;
    for(i=1;i<255;i++)
    for(j=1;j<255;j++){
        if(visited[i][j]==0){
            l++;
            v=filterdata[i][j];
            mark(i,j,v,l,visited,filterdata);
        }
    }
    FILE *f;
    f=fopen("exp.pgm","w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", 256, 256);
    fprintf(f, "255\n");
    for(i=0;i<256;i++)
        for(j=0;j<256;j++)
            fprintf(f, "%d\t", visited[i][j]);
    fclose(f);
}


int main(){
    printf("~");
    FILE *f;
    int i,j,max;
    int data[MAXROW][MAXCOL];
    printf("~");
    int hist[256];
    printf("~");
    int filterdata[MAXROW][MAXCOL];
   // int finaldata[MAXROW][MAXCOL];
    int local[64];
    for(i=0;i<64;i++)
        local[i]=-1;
    readFile(data);
  //  return(0);
    printf("done reading\n");
    filter(data,filterdata,256,256);
    printf("done filtering\n");
    createHist(filterdata,256,256,hist);
    printf("\n\n");
    //int sum=0;
    /*for(i=0;i<256;i++){
        printf("%d\t",hist[i]);
       // sum+=hist[i];
    }*/
   // printf("%d %d\t",sum,65536);
/*   max=-1;
   for(i=0;i<256;i++)
        if(hist[i]>max)
            max=hist[i];
    for(i=0;i<256;i++)
        hist[i]=(hist[i]*100)/max;
        printf("\n\n");
    for(i=0;i<256;i++){
        printf("%d\t",hist[i]);*/
       // sum+=hist[i];

    int numMax=localMax(hist,local);

    printf("\n\n%d",numMax);
    for(i=0;i<numMax;i++)
        printf("\n\n%d",local[i]);
    distribute(local,filterdata,256,256,numMax);
    int visited[MAXROW][MAXCOL];
    compMerge(filterdata,visited);

  /*  f=fopen("exp.pgm","w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", 256, 256);
    fprintf(f, "255\n");
    for(i=0;i<256;i++)
        for(j=0;j<256;j++)
            fprintf(f, "%d\t", filterdata[i][j]);
    fclose(f);*/
}

