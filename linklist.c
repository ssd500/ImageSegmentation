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
       printf(" %d --> ",copy->l );
       /*struct pos *track=copy->ptr;
       while(track!=NULL)
        {
           printf(" ( %d , %d ) ",track->i,track->j );
           track=track->link;
        }*/ 
        //printf("");   
        copy=copy->next;
    }
    printf("\n\n");

}

void bubblesort(struct label **header)
	{
		struct label *p1, *p2;
		for(p1=*header;p1->next!=NULL;p1=p1->next)
		{
			for(p2=p1->next;p2!=NULL;p2=p2->next)
			{
				if(p1->l<p2->l)
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
	}


struct pos* COG(struct label* q)
{
	int xavg=0,yavg=0,count=0;
	for(struct pos *track=q->ptr;track!=NULL;track=track->link)
	{
		xavg+=track->x;
		yavg+=track->y;
		count++;
	}
	if(count==0)
		return NULL;
	struct pos *CG=(pos*)malloc(sizeof(pos));
	CG->x=((double)xavg)/count;
	CG->y=((double)yavg)/count;
	return CG;
}

int decide_spatial(struct pos *first,struct pos *second)
{
	double x1=first->x,y1=first->y,x2=second->x,y2=second->y,dist=50;
	if(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))<dist)
		return 1; //yes merge
	else 
		return 0; //don't
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

    for(m=0,n=20;m<8;m++,n+=20)
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
        link_list_display(head);
	bubblesort(&head);
	link_list_display(head);


	
   
  
   /* copy=head;
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
		last->next=N->next;
		N=NULL;
	     link_list_display(head);*/
   

}
int main()
{
 
  createGraph(5);

return 0;
}
