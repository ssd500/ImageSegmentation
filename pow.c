#include<stdio.h>
#include<math.h>
int main()
{
  int N,i,j,k;
  double sum;
  for(i=0;i<2;i++)
   {
     k=1;
     sum=0; 
     printf("Enter the length of the series :: ");
     scanf("%d",&N);
     
     for(j=1;j<=N;j++)
      {
       sum+=pow((double)j,(double)k);
       k++;
      }  
     printf("\n The sum of the series is %f\n",sum);
   }
return 0;
}
