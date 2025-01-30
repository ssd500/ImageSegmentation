#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int num;
    struct node *next;
};
 
void create(struct node **);
void display(struct node *);
int survivor(struct node **, int);
 
int main()
{
    struct node *head = NULL;
    int survive, skip;
 
    create(&head);
    printf("The persons in circular list are:\n");
    display(head);
    printf("Enter the number of persons to be skipped: ");
    scanf("%d", &skip);
    survive = survivor(&head, skip);
    printf("The person to survive is : %d\n", survive);
    free(head);
 
    return 0;
}
 
int survivor(struct node **head, int k)
{
    struct node *p, *q;
    int i;
 
    q = p = *head;
    while (p->next != p)
    {
        for (i = 0; i < k - 1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        printf("%d has been killed.\n", p->num);
        free(p);
        p = q->next;
    }
    *head = p;
 
    return (p->num);
}
 
void create (struct node **head)
{
    struct node *temp, *rear;
    int a, ch;
 
    do
    {
        printf("Enter a number: ");
        scanf("%d", &a);
        temp = (struct node *)malloc(sizeof(struct node));
        temp->num = a;
        temp->next = NULL;
        if (*head == NULL)
        {
            *head = temp;
        }
        else
        {
            rear->next = temp;
        }
        rear = temp;
        printf("Do you want to add a number [1/0]? ");
        scanf("%d", &ch);
    } while (ch != 0);
    rear->next = *head;
}
 
void display(struct node *head)
{
    struct node *temp;
 
    temp = head;
    printf("%d   ", temp->num);
    temp = temp->next;
    while (head != temp)
    {
        printf("%d   ", temp->num);
        temp = temp->next;
    }
    printf("\n");
}
$ gcc josephus.c 
$ ./a.out
Enter a number: 1
Do you want to add a number [1/0]? 1
Enter a number: 2
Do you want to add a number [1/0]? 1
Enter a number: 3
Do you want to add a number [1/0]? 1
Enter a number: 4
Do you want to add a number [1/0]? 1
Enter a number: 5
Do you want to add a number [1/0]? 1
Enter a number: 6
Do you want to add a number [1/0]? 1
Enter a number: 7
Do you want to add a number [1/0]? 0
The persons in circular list are:
1   2   3   4   5   6   7   
Enter the number of persons to be skipped: 3
3 has been killed.
6 has been killed.
2 has been killed.
7 has been killed.
5 has been killed.
1 has been killed.
The person to survive is : 4