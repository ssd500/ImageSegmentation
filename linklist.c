#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct label
{
    int l;
    double avg;
    struct label *next;
    struct pos *ptr;
};

struct pos{
    int i,j;
    struct pos *link;
};

void link_list_display(struct label *h)
{
    
    struct label *copy=h;
 
    while(copy!=NULL)
    {
       printf(" %d :: ",copy->l );
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
void createGraph(int data)
{
    int m,n,count;
    double sum;
    struct label *head=NULL;
    struct label *copy=NULL;
    struct label *newNode;
    struct pos *newnode;
    struct pos *track=NULL;

    for(m=0,n=20;m<4;m++,n+=20)
     {
        newNode=(struct label*)malloc(sizeof(struct label));
        newNode->avg=0.0;
        newNode->l=n;
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
     
       //for(m=0;m<MAXROW;m++)
         //for(n=0;n<MAXCOL;n++)
           // if(visited[m][n]==copy->l)
               // {
       
           for(int k=0;k<3;k++)
            {
                    int x,y;
                    printf("Enter value of x and y :: ");
                    scanf("%d %d",&x,&y);  
       
                    newnode=(struct pos*)malloc(sizeof(struct pos));
                    newnode->i=x;
                    newnode->j=y;
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
                //}
            }
        copy=copy->next;
    }
    link_list_display(head);
   

              struct label *M=head;
	      struct label *N=head,*last=NULL;
	      int c=0;
              while(c<0)
		  {
                     M=M->next;
                     c++;
                  }c=0; 
	      while(c<2)
		  {
                       last=N;
                       N=N->next;
                       c++;
                  } 
              //printf("\n %f   %f   %f  %f\t",M->avg,N->avg,nodes[m],nodes[n]);
	      struct pos *mptr=M->ptr;
	      struct pos *nptr=N->ptr;
	      
              while(mptr->link!=NULL)
		{	
                   //printf(" \t[ %d  %d ] \t ",mptr->i,mptr->j); 
                   mptr=mptr->link;
                }
 		mptr->link=nptr;
		/*while(M->next!=N)
			M=M->next;*/
		last->next=N->next;
		N=NULL;
	     link_list_display(head);
   

}
int main()
{
 
  createGraph(5);

return 0;
}
