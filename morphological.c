#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAXROW 120
#define MAXCOL 180

void opening(int arr[][MAXCOL]);
void closing(int arr[][MAXCOL]);
struct label{
    int l;
    int avg;
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
void distribute(int lo[],int fd[][MAXCOL],int r,int c,int n)
{
    int i,j,k;
    //int s=findSize(lo);
    FILE *f;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            {
            if(fd[i][j]<lo[0]&&fd[i][j]>=0)
                fd[i][j]=0;
            else if(fd[i][j]<256&&fd[i][j]>=lo[n-1])
                fd[i][j]=255;
	    }

      for(k=1;k<n;k++)
	   {
	        int mat[MAXROW][MAXCOL]={0};
		for(i=0;i<r;i++)
		  for(j=0;j<c;j++)
                    if(fd[i][j]<lo[k]&&fd[i][j]>=lo[k-1])
			{
			  mat[i][j]=255;
			}
		
		 opening(mat);
                 closing(mat);
		for(i=0;i<r;i++)
		  for(j=0;j<c;j++)
			if(mat[i][j]==255)
                           fd[i][j]=(256*k)/n;                
            }
  /*  for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            printf("%d\t",fd[i][j]);*/

    writeFile(fd,"label_after_dist.pgm");

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
    //writeFile(visited,"after_comp_finding.pgm");

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
   int sum=0;
   int count=0;
   for(struct pos *track=p;track!=NULL;track=track->link)
     {
       sum+=data[track->i][track->j];
       count++;
     }
   return sum/count;
}


void showLength(struct label *lb)
{      
     printf("\n\n");
     while(lb!=NULL)
     {
	//printf("[%d,%d]\t",lb->len,lb->avg);
        printf("%d\t",lb->len);
	lb=lb->next;
     }
     printf("\n\n");       
}

int avglabels(struct label *l)
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
	int w=avglabels(l);
	for(struct label *k=l;k!=NULL;k=k->next){
		sum+=(k->len-w)*(k->len-w);
		count++;
	}
	return sqrt(sum/count);
}

void bubblesort(struct label **header)
	{
		struct label *p1, *p2;
		for(p1=*header;p1->next!=NULL;p1=p1->next)
		{
			for(p2=p1->next;p2!=NULL;p2=p2->next)
			{
				if(p1->len<p2->len)
				{
					struct label *t1, *t2, *tmp=p1->next, *q1=p1, *q2=p2;
					
                                        
					
				     if(q1->next!=q2){
					for(t1=*header;t1!=NULL&&t1->next!=p1;t1=t1->next){}
					
                                        for(t2=*header;t2->next!=p2;t2=t2->next){}
                                        q1->next=q2->next;
					t2->next=q1;
					p2=q1;
					if(t1!=NULL)
						t1->next=q2;
					else   
					  *header=q2;

					q2->next=tmp;
					p1=q2;
					}
					else{
					  for(t1=*header;t1!=NULL&&t1->next!=p1;t1=t1->next){}
					  q1->next=q2->next;
					  q2->next=q1;
					  p2=q1;
					  if(t1!=NULL)
						t1->next=q2;
					  else
						*header=q2;
					  p1=q2;
					}
					//link_list_display(*header);
				}
			}
		}
		//showLength(*header);
	}



struct pos* COG(struct label* q)
{
	int xavg=0,yavg=0,count=0;
	for(struct pos *track=q->ptr;track!=NULL;track=track->link)
	{
		xavg+=track->i;
		yavg+=track->j;
		count++;
	}
	if(count==0)
		return NULL;
	struct pos *CG=(struct pos*)malloc(sizeof(struct pos));
	CG->i=((double)xavg)/count;
	CG->j=((double)yavg)/count;
	return CG;
}

int decide_spatial(struct pos *first,struct pos *second)
{
	double x1=first->i,y1=first->j,x2=second->i,y2=second->j,dist=20;
	if(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))<dist){
		return 1; //yes merge
	}
	else {
		return 0; //don't
	}
}


void createGraph(int data[][MAXCOL],int visited[][MAXCOL],int lcount)
{
    int m,n,count,sum;
    double T=35.0;
    struct label *head=NULL;
    struct label *copy=NULL;   
    struct pos *track=NULL;
      int Count=0;
 
    for(m=0,n=1;m<lcount;m++,n++)
     {
        struct label *newNode=(struct label*)malloc(sizeof(struct label));
        newNode->avg=0;
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
     }    
     
    copy=head;
    while(copy!=NULL)
     {
        track=copy->ptr;
        for(m=0;m<MAXROW;m++)
            for(n=0;n<MAXCOL;n++)
                if(visited[m][n]==copy->l)
                 {
                    struct pos *newnode=(struct pos*)malloc(sizeof(struct pos));
                    newnode->i=m;
                    newnode->j=n;
		    copy->len++;
                    newnode->link=NULL;
                    if(copy->ptr==NULL)
                    {
                        copy->ptr=newnode;
                        track=newnode;
                    }
                    else
                    {
                        track->link=newnode;
                        track=newnode;
                    }
                }
       copy=copy->next;
    }
   
    for(copy=head;copy!=NULL;copy=copy->next)
      {
	copy->avg=computeavg(copy->ptr,data);
      }
    
    //double s=stddev(head);
    int a=avglabels(head);
    printf("\nAvg: %d \n",a);
    bubblesort(&head);
	copy=head;
    showLength(copy);  

    int *nodes=(int *)malloc(sizeof(int)*lcount);
    for(copy=head,m=0;copy!=NULL;copy=copy->next)
        nodes[m++]=copy->avg;
    

   for(m=0;m<lcount;m++)
       { 
        for(n=m+1;n<lcount;n++)
	 {
          if(m!=n)
          {
           
           if( nodes[m]!=-1 && nodes[n]!=-1 )
           {
              //printf(" m= %d n= %d\n ",m,n);
              struct label *M=head;
	      struct label *N=head,*last=NULL;
              
	      while(M!=NULL && M->avg!=nodes[m])    
              M=M->next;
              //printf(" M->avg= %d nodes[m]= %d \t",M->avg,nodes[m]);
	      
    	     while(N!=NULL && N->avg!=nodes[n])
    	      {
                 last=N;
                 N=N->next;
              } 
	    //struct pos *mcg=COG(M),*ncg=COG(N);
            //int g=decide_spatial(mcg,ncg);
		//printf("%d\t",g);
		//printf("%d,%d\t",m,n);
	   // if(N->len < a && fabs(nodes[m]-nodes[n]) <= T )
          
            if( N->len<a )
            {
             Count++;    
             struct pos *mptr=M->ptr;
	     struct pos *nptr=N->ptr;
	     struct pos *l=NULL;
             while(mptr!=NULL)
	      {	
               l=mptr;
               mptr=mptr->link;
              }
             l->link=nptr;
             N->ptr=NULL;
	     last->next=N->next;
             //free(N);
	     M->avg=computeavg(M->ptr,data);
	     //M->len+=N->len;                
            //printf(" %d----> ", M->len);
             
              struct pos *temp=M->ptr;
              M->len=0;
              while(temp!=NULL)
               {
                 M->len++;
                 temp=temp->link;
               }
              // printf(" %d    m= %d n= %d\n", M->len,m,n);
               //printf(" %d    m= %d n= %d  NSize= %d\n", M->len,m,n,N->len);
             nodes[m]=M->avg;
             nodes[n]=-1;
             //N=NULL;             
	    }
            else
            {
                printf("\t[%d   %d]",N->len,a);
            }  
            /*copy=head;
             int count=0;
             while(copy!=NULL)
                {
                  count++;
                  copy=copy->next;
                }
             printf("[ %d]\t",count);*/
	    }
           /*else
            {
               printf("[**  %d   %d  **]\t",nodes[m],nodes[n]);
            }*/
          }
        
        }
      }    
      printf(" %d \n",Count);
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
     double l=computeavg(copy->ptr,data);
     while(track!=NULL)
      {
       visited[track->i][track->j]=0;       
       visited[track->i][track->j]=(int)l;
       track=track->link;
      }
       //d++;
     copy=copy->next;
    }
  
   /*copy=head;
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
   }*/
   copy=head;
   showLength(copy);
   writeFile(visited,"after_componentMerged.pgm"); 
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

int localMax(int hi[],int lo[])
{
    int i,j=0,countUp=0,countDown=0,flag=0,max,thresh=35;
    for(i=1;i<256;i++)
       {
        if(hi[i]>hi[i-1])
          {
            if(flag==1)
                {
                flag=0;
                if(countUp>=thresh&&countDown>=thresh)
                   {
                    lo[j++]=max;
                   }
                countUp=0;
                }
            max=i;
            countUp+=hi[i]-hi[i-1];
            countDown=0;

          }
        else if(hi[i]<hi[i-1])
         {
            countDown+=hi[i-1]-hi[i];
            flag=1;
         }
    }
    return j;
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
    //writeFile(fd,"filter.pgm");
}
void threshold(int filterdata[][MAXCOL],int thresh)
{

   for(int i=0;i<MAXROW;i++)
    for(int j=0;j<MAXCOL;j++)
      {
          if(filterdata[i][j]<thresh)
               filterdata[i][j]=0;
          else
               filterdata[i][j]=255;
      }
}
void dilate(int image[][MAXCOL])
{
    for (int i=0; i<MAXROW; i++)
       for (int j=0; j<MAXCOL; j++)
        {
            if (image[i][j] ==255)
            {
                //ans[i][j]=2;
                if (i>0 && image[i-1][j]==0) image[i-1][j] = 2;
                if (j>0 && image[i][j-1]==0) image[i][j-1] = 2;
                if (i+1<MAXROW && image[i+1][j]==0) image[i+1][j] = 2;
                if (j+1<MAXCOL && image[i][j+1]==0) image[i][j+1] = 2;
            }
        }    

    for (int i=0; i<MAXROW; i++)
       for (int j=0; j<MAXCOL; j++)
            if (image[i][j] == 2)
                 image[i][j] = 255;
}
void erosion(int image[][MAXCOL])
{
    int ans[MAXROW][MAXCOL];
    for(int i=0;i<MAXROW;i++)
       for(int j=0;j<MAXCOL;j++)
          ans[i][j]=image[i][j];

    for (int i=0; i<MAXROW; i++)
       for (int j=0; j<MAXCOL; j++)
         if (image[i][j] ==255)
            {
               int c1=0,c2=0,c3=0,c4=0;     
                if (i>0 && image[i-1][j]==255) 
                      c1 = 1;
                if (j>0 && image[i][j-1]==255) 
                      c2=1;
                if (i+1<MAXROW && image[i+1][j]==255) 
                      c3=1;
                if (j+1<MAXCOL && image[i][j+1]==255) 
                      c4=1;
                if( c1==1 && c2==1 && c3==1 && c4==1 )
                  continue;
                else
                  ans[i][j]=0;   
            }
	for(int i=0;i<MAXROW;i++)
       for(int j=0;j<MAXCOL;j++)
          image[i][j]=ans[i][j];
}

void opening(int arr[][MAXCOL])
{
	erosion(arr);
	dilate(arr);
}

void closing(int arr[][MAXCOL])
{
	dilate(arr);
	erosion(arr);
}

int main()
{
    FILE *f;
    int i,j,max,lcount=0;
    int data[MAXROW][MAXCOL];
    int hist[256];
    int filterdata[MAXROW][MAXCOL];
    int visited[MAXROW][MAXCOL]={0};

    int local[64];
    for(i=0;i<64;i++)
        local[i]=-1;

    readFile(data,"3.pgm");
    printf("done reading\n");

    filter(data,filterdata,MAXROW,MAXCOL);
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
   
   return 0;
}

