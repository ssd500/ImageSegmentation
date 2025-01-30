#include <iostream>
#include<math.h>
using namespace std;
int main()
{
  int N,i,j,k;
  double sum;
  for(i=0;i<2;i++)
   {
     k=1;
     sum=0;
     cout<<"Enter the length of the series :: ";
     cin>>N;

     for(j=1;j<=N;j++)
      {
       sum+=pow((double)j,(double)k);
       k++;
      }
     cout<<"\n The sum of the series is "<<sum<<endl;
   }
return 0;
}

