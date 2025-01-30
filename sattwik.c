#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//FILE *f;
//int i,j,k,l,r,c;
#define MAXROW 120
#define MAXCOL 180

struct label{
    int l;
    double avg;
    int len;
    struct label *next;
    struct pos *ptr;
};

struct pos{
    int i,j;
    struct pos *link;
};

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
                //printf("%d\t",data[i][j]);
            }
       }
       fclose(f);
       writeFile(data,"read.pgm");
}
int compare(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
void median_filter(int d[][MAXCOL],int fd[][MAXCOL],int r,int c)
{
    int sum,i,j,k,l,f_size=3;
    FILE *f;
    printf("~");
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            fd[i][j]=d[i][j];
         
        
    printf("~");
    for(i=2;i<r-2;i++)
     {
        for(j=2;j<c-2;j++)
         {
            //sum=0;
            int A[9],m=0;
            for(k=i-2;k<=i+2;k++)
                for(l=j-2;l<=j+2;l++)
                 {  
                     A[m++]=d[k][l];
                 }
             qsort(A,m,sizeof(int),compare);   
            fd[i][j]=A[4];
            //printf("%d\t",fd[i][j]);
        }
    }
    writeFile(fd,"filter.pgm");
}
void filter(int d[][MAXCOL],int fd[][MAXCOL],int r,int c){
    int sum,i,j,k,l;
    FILE *f;
    printf("~");
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            fd[i][j]=d[i][j];
         
        
    printf("~");
    for(i=1;i<r-1;i++)
     {
        for(j=1;j<c-1;j++)
         {
            sum=0;
            for(k=i-1;k<=i+1;k++)
                for(l=j-1;l<=j+1;l++)
                    sum=sum+d[k][l];
                
            sum=sum/9;
            fd[i][j]=sum;
            //printf("%d\t",fd[i][j]);
        }
    }
    writeFile(fd,"filter.pgm");
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

    writeFile(fd,"final.pgm");

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

void compMerge(int filterdata[][MAXCOL],int visited[][MAXCOL],int *no_of_label)
{
    int i,j,l=0,v;
    //printf("CompMerge");

    for(i=1;i<MAXROW;i++)
      for(j=1;j<MAXCOL;j++)
        {
        if(visited[i][j]==0)
          {
            l+=1;
            v=filterdata[i][j];
           // printf("Hi %d %d\t",i,j);
            mark(i,j,v,l,visited,filterdata,0);
          }
        }
     printf("\nNo of initial component %d ",l);
     *no_of_label=l;
    writeFile(visited,"exp.pgm");

}
void link_list_display(struct label *h)
{
    struct label *copy=h;
 
    while(copy!=NULL)
    {
       printf("\n\n %d :: ",copy->l );
       struct pos *track=copy->ptr;
       while(track!=NULL)
        {
           printf(" ( %d , %d ) ",track->i,track->j );
           track=track->link;
        } 
        printf("\n\n");   
        copy=copy->next;
    }
}

double computeavg(struct pos *p,int data[][MAXCOL])
{
	         double sum=0;
                 int count=0;
                  for(struct pos *track=p;track!=NULL;track=track->link)
                   {
                      sum+=data[track->i][track->j];
                      count++;
                   }
                  return sum/count;
}


void showLength(struct label *lb)
{       printf("\n\n");
	while(lb!=NULL){
		printf("%d\t",lb->len);
		lb=lb->next;
         }
}

double avglabels(struct label *l)
{
	double sum=0.0;
	int count=0;
	for(struct label *k=l;k!=NULL;k=k->next){
		sum+=k->len;
		count++;
	}
	return sum/count;
}

double stddev(struct label *l)
{
	double sum=0.0;
	int count=0;
	double w=avglabels(l);
	for(struct label *k=l;k!=NULL;k=k->next){
		sum+=(k->len-w)*(k->len-w);
		count++;
	}
	return sqrt(sum/count);
}

void createGraph(int data[][MAXCOL],int visited[][MAXCOL],int lcount)
{
    int m,n,count,T=45;
    double sum;
    struct label *head=NULL;
    struct label *copy=NULL;
    //struct label *newNode;
    struct pos *newnode=NULL;
    struct pos *track=NULL;
    for(m=0,n=1;m<lcount;m++,n++)
     {
        struct label *newNode=(struct label*)malloc(sizeof(struct label));
        newNode->avg=0.0;
        newNode->l=n;
	newNode->len=0;
        newNode->next=NULL;
        newNode->ptr=NULL;

        if(head==NULL)
            head=copy=newNode;
        else
        {
            copy->next=newNode;
            copy=newNode;
        }
       //printf("\n %d  %d \n",m,n );
     }
    struct label *tmp=head;
     while(tmp!=NULL)
      {
        // printf(" %d ",tmp->l);
         tmp=tmp->next;
      }
    copy=head;
    while(copy!=NULL)
     {
       track=copy->ptr;
        for(m=0;m<MAXROW;m++)
            for(n=0;n<MAXCOL;n++)
                if(visited[m][n]==copy->l)
                 {
                    newnode=(struct pos*)malloc(sizeof(struct pos));
                    newnode->i=m;
                    newnode->j=n;
		    copy->len++;
                    newnode->link=NULL;
                    if(copy->ptr==NULL)
                    {
                        copy->ptr=newnode;
                        track=newnode;
                    }
                    else{
                        track->link=newnode;
                        track=newnode;
                    }
                }
        copy=copy->next;
    }
   // link_list_display(head);
	copy=head;
	showLength(copy);
   
   for(copy=head;copy!=NULL;copy=copy->next)
    {
		copy->avg=computeavg(copy->ptr,data);
    }
  
   
    double adj[lcount][lcount];
    double nodes[lcount];
    
    for(copy=head,m=0;copy!=NULL;copy=copy->next)
        nodes[m++]=copy->avg;

    for(m=0;m<lcount;m++)
        for(n=0;n<lcount;n++)
            adj[m][n]=abs(nodes[m]-nodes[n]);
    
    double s=stddev(head);
    double a=avglabels(head);
    printf("\nAvg: %f \nStddev:   %f",a,s);


    for(m=0;m<lcount;m++)
       { 
         for(n=m+1;n<lcount;n++)
	  {
	   if( adj[m][n]!=-1)
             {
              struct label *M=head;
	      struct label *N=head,*last=NULL;
              
              while(nodes[m]!=-1 && M->avg!=nodes[m])
		    M=M->next;

	      while(nodes[n]!=-1 && N->avg!=nodes[n])
		  {
                    last=N;
                    N=N->next;
                  } 
	      if( N->len<a && adj[m][n]<T)
                 {
                    struct pos *mptr=M->ptr;
	            struct pos *nptr=N->ptr;
	        
                    struct pos *l=NULL;
                    while(mptr!=NULL)
	   	     {	
                       l=mptr;
                       mptr=mptr->link;
                     }
                
                    l->link=nptr;
	            last->next=N->next;
		    M->avg=computeavg(M->ptr,data);
                
                    nodes[m]=M->avg;
                    nodes[n]=-1;
                    for(int i=0;i<lcount;i++)
		     {
		       if(nodes[i]==-1)
		          adj[m][i]=adj[i][m]=-1;
		       else
		        {
		           //  printf("%f %f\t\t",adj[m][i],adj[i][m]);
		           adj[m][i]=adj[i][m]=abs(nodes[m]-nodes[i]);
		          //  printf("%f %f\n\n",adj[m][i],adj[i][m]);	
                        }
                        adj[n][i]=adj[i][n]=-1;
		     }
		    N=NULL;
	         }
	      }
	   }
       }    
     //link_list_display(head);

     copy=head;
     int c=0,d=1;
     while(copy!=NULL)
      { 
        c++;
        copy=copy->next;
      }

     printf(" \nNo of final component after merging %d\t ",c);

    copy=head;
    while(copy!=NULL)
     {
       track=copy->ptr;
       while(track!=NULL)
        {
           visited[track->i][track->j]=(d)*20;
           track=track->link;
        }
       d++;
       copy=copy->next;
     }
     
    copy=head;
    while(copy!=NULL)
     {
	struct pos *temp=copy->ptr;
	copy->len=0;
	while(temp!=NULL)
         {
	   copy->len++;
	   temp=temp->link;
	 }
        copy=copy->next;
     }
     copy=head;
     showLength(copy);
     writeFile(visited,"componentMerged.pgm"); 
}

int main()
{
    printf("~");
    FILE *f;
    int i,j,max,lcount=0;
    int data[MAXROW][MAXCOL];
    printf("~");
    int hist[256];
    printf("~");
    int filterdata[MAXROW][MAXCOL];
    int visited[MAXROW][MAXCOL]={0};

    int local[64];
    for(i=0;i<64;i++)
        local[i]=-1;

    readFile(data,"126007.pgm");
  //  return(0);
    printf("done reading\n");

    filter(data,filterdata,MAXROW,MAXCOL);
    //median_filter(data,filterdata,MAXROW,MAXCOL);
    printf("done filtering\n");

    createHist(filterdata,MAXROW,MAXCOL,hist);
   // printf("\n\n");

    int numMax=localMax(hist,local);

    printf("\nNo. of local maxima %d",numMax);

    //for(i=0;i<numMax;i++)
       // printf("\n\n%d",local[i]);

    distribute(local,filterdata,MAXROW,MAXCOL,numMax);

    printf("\nDone distributing");

    compMerge(filterdata,visited,&lcount);

    createGraph(data,visited,lcount);


}


