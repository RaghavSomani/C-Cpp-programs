#include <stdio.h>
int main()
{
	int n,i=1,k,temp=1,j=0;
	scanf("%d",&n);
	if(n>1)
		k=n*0.5;
	else if(n==1)
		k=2;
	else
		return 0;
	int a[k],b[k];
	for(i=0;i<k;i++)
	{
		a[i]=0;
		b[i]=0;
	}
	for (i=2;n!=1;)
	{
		if(n%i==0)
		{
			if(i!=temp)
			{
				a[j]=i;
				j++;
			}
			b[j-1]++;
			n/=i;
			temp=i;
		}
		else if(i==2)
			i++;
		else
			i+=2;
	}
	for(i=0;i<j;i++)
		printf("%d ^ %d\n",a[i],b[i]);
	return 0;
}
