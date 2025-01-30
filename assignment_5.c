#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node
{
   int name;
   struct Node *right;
   struct Node *left;
   struct Node *parent;
}node;

node *Tree;
int L1=0;
int L2=0;
node* create_node()
{
  int d;
  printf("Enter -999 if you want to put null on this node \nEnter the name of this node :: ");
  scanf("%d",&d);
  if(d==-999)
    {
       return NULL;
    }
 
  node *p=(node *)malloc(sizeof(node));
  if(p==NULL)
   {
       printf("Memory Full...\n");
       exit(0);
   }
  
  p->name=d;
  p->right=NULL;
  p->left=NULL;
  return p;
}
node* make_tree(node *T)
{
  node *p=create_node();
  
  if(p==NULL)
    {
       return NULL;
    }
  p->parent=T;
  p->left=make_tree(p);
  p->right=make_tree(p);
  return p;
}
void display(node *p)
{
   if(p)
    {
      printf(" %d ",p->name);
      display(p->left);
      display(p->right);
    }
}
void check_relation_validity(node *T,int person1,int person2,char relation[])
{
   if(T)
    {
        if(T->name==person1)
         {
            if( strcmp(relation,"p")==0)
              {
                  if( T->parent!=NULL && T->parent->name==person2 )
                    printf("\nYES\n");
                  else
                    printf("\nNO\n");
              }
            else if( strcmp(relation,"gp")==0)
              {
                  if( T->parent!=NULL && T->parent->parent!=NULL && T->parent->parent->name==person2 )
                    printf("\nYES\n");
                  else
                    printf("\nNO\n");
              }
            else if( strcmp(relation,"ggp")==0)
              {
                  if( T->parent!=NULL && T->parent->parent!=NULL && T->parent->parent->parent!=NULL && T->parent->parent->parent->name==person2 )
                    printf("\nYES\n");
                  else
                    printf("\nNO\n");
              }
            else if( strcmp(relation,"gggp")==0)
              {
                  if( T->parent!=NULL && T->parent->parent!=NULL && T->parent->parent->parent!=NULL && T->parent->parent->parent->parent!=NULL && T->parent->parent->parent->parent->name==person2 )
                    printf("\nYES\n");
                  else
                    printf("\nNO\n");
              }
             return;
         }
         check_relation_validity(T->left,person1,person2,relation);
         check_relation_validity(T->right,person1,person2,relation);
         
    }
}
void find_child(node *T, int name)
{
  if(T)
    {
        if(T->name==name)
         {
             if(T->left!=NULL)
                printf("\nLeft child :: %d",T->left->name);
             else
                printf("\n It does not have any left child");
             if(T->right!=NULL)
                printf("\nRight child :: %d",T->right->name);
             else
                printf("\n It does not have any right child");
             return;
         }
         find_child(T->left,name); 
         find_child(T->right,name);
    }
}
void find_parent(node *T, int name)
{
  if(T)
    {
        if(T->name==name)
         {
            if(T->parent!=NULL) 
               printf("\nParent of %d is :: %d",name,T->parent->name);
            else
               printf("\nThis is the first node..");
            return;
         }
         find_parent(T->left,name); 
         find_parent(T->right,name);
    }
}

int main()
{
  node *Tree;
  Tree=NULL;  
  int nm,level=0,person1,person2,l1=0,l2=0,flag=0;
  int name;
  Tree= make_tree(Tree);
  printf("The given tree is \n\n");
  display(Tree);
  int ch=1;
  char relation[100];

 do{
  
  printf("\n Press 1 for child finding\n Press 2 for parent finding\n Press 3 for Relation validity checking\n Press 0 for exit\n Give your input ");
  scanf("%d",&ch);
  switch(ch)
   {
     case 1:  
              printf("Enter the node for which you want to know its child ");
              scanf("%d",&name);
              find_child(Tree,name);
              break;
     
     case 2:  
              printf("Enter the node for which you want to know its parent ");
              scanf("%d",&name);
              find_parent(Tree,name);
              break;
 
     case 3:  printf("\nFor relation input,\nFor parent give input 'p'\nFor grand parent give input 'gp'\nFor great grand parent give input 'ggp'\nFor great great grand parent give input 'gggp'\n");
              printf("\nEnter the name of first persen1, relation, preson2 :: ");
              scanf("%d%s%d",&person1,relation,&person2);
              check_relation_validity(Tree,person1,person2,relation);
              break;
     case 0:  exit(0);
   }
  }while(1);

return 0;
}






