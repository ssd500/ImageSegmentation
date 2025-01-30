#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//FILE *f;
//int i,j,k,l,r,c;
#define MAXROW 120
#define MAXCOL 180

void writeFile(int arr[][MAXCOL],char string[])
{
    FILE *f;
    int i,j;
    f=fopen(string,"w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", MAXCOL, MAXROW);
    fprintf(f, "255\n");
    for (i=0; i<MAXROW; i++)
    {
        for (j=0; j<MAXCOL; j++)
            fprintf(f, "%d ", arr[i][j]);
        fprintf(f, "\n");
    }
}

void readFile(int data[][MAXCOL],char str[]){
    FILE *f;
    int i,j,r,c;
    printf("~");
    char s1[80],s2[80];
    unsigned char ch;
    f=fopen(str, "r");
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
     printf("~%s ",s1);
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
       writeFile(data,"wf4Check.pgm");
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
    writeFile(fd,"wf4Fil.pgm");
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

    writeFile(fd,"wf4Fin.pgm");

}


void mark(int i,int j,int value,int level,int visit[][MAXCOL],int filterdata[][MAXCOL],int count)
{
    visit[i][j]=level;

    /// North
    if( (i-1)>=0)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i-1][j]==0 )
        if( filterdata[i-1][j]==value)
         {
            // pix_count++;
            mark(i-1,j,value,level,visit,filterdata,count);
         }
     }

    ///North-East
    if( (j+1)<=MAXCOL&&(i-1)>=0)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i-1][j+1]==0 )
        if( filterdata[i-1][j+1]==value)
         {
            // pix_count++;
            mark(i-1,j+1,value,level,visit,filterdata,count);
         }
     }
    ///East
   if( (j+1)<=MAXCOL)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i][j+1]==0 )
        if( filterdata[i][j+1]==value)
         {
            // pix_count++;
            mark(i,j+1,value,level,visit,filterdata,count);
         }
     }

     ///South-East
     if( (j+1)<=MAXCOL&&(i+1)<=MAXROW)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i+1][j+1]==0 )
        if( filterdata[i+1][j+1]==value)
         {
            // pix_count++;
            mark(i+1,j+1,value,level,visit,filterdata,count);
         }
     }
    ///South
    if( (i+1)<=MAXROW)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i+1][j]==0 )
        if( filterdata[i+1][j]==value)
         {
            // pix_count++;
            mark(i+1,j,value,level,visit,filterdata,count);
         }
     }

     ///South-West
     if( (i+1)<=MAXROW&&(j-1)>=0)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i+1][j-1]==0 )
        if( filterdata[i+1][j-1]==value)
         {
            // pix_count++;
            mark(i+1,j-1,value,level,visit,filterdata,count);
         }
     }
    ///West
    if( (j-1)>=0)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i][j-1]==0 )
        if( filterdata[i][j-1]==value)
         {
            // pix_count++;
            mark(i,j-1,value,level,visit,filterdata,count);
         }
     }
     /// North-West
    if( (j-1)>=0&&(i-1)>=0)
     {
       //cout<<" "<<visited_img.at<int>(i-1,j)<<endl;
       if( visit[i-1][j-1]==0 )
        if( filterdata[i-1][j-1]==value)
         {
            // pix_count++;
            mark(i-1,j-1,value,level,visit,filterdata,count);
         }
     }
     return;
}

void compMerge(int filterdata[][MAXCOL],int visited[][MAXCOL])
{
    int i,j,l=0,v;
    //printf("CompMerge");

    for(i=1;i<MAXROW;i++)
      for(j=1;j<MAXCOL;j++)
        {
        if(visited[i][j]==0)
          {
            l+=20;
            v=filterdata[i][j];
           // printf("Hi %d %d\t",i,j);
            mark(i,j,v,l,visited,filterdata,0);
          }
        }
    writeFile(visited,"exp.pgm");

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
    int visited[MAXROW][MAXCOL]={0};

    int local[64];
    for(i=0;i<64;i++)
        local[i]=-1;

    readFile(data,"3.pgm");
  //  return(0);
    printf("done reading\n");

    filter(data,filterdata,MAXROW,MAXCOL);
    printf("done filtering\n");

    createHist(filterdata,MAXROW,MAXCOL,hist);
    printf("\n\n");

    int numMax=localMax(hist,local);

    printf("\n\n%d",numMax);

    for(i=0;i<numMax;i++)
        printf("\n\n%d",local[i]);

    distribute(local,filterdata,MAXROW,MAXCOL,numMax);

    printf("Done distributing");

    compMerge(filterdata,visited);


}
