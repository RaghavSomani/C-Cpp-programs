#include<stdio.h>
#include<string.h>
#include<time.h>
void main()
{
	clock_t start, end;
	start=clock();
	float time;
	int n,i,j;
	printf("Enter the number of lines: ");
	scanf("%d", &n);
	char a[n][50];
	int b[n];
	for(i=0;i<n;i++)
	{
		printf("%d. ", i);
		scanf("%s", a[i]);
		b[i]=strlen(a[i]);
	}
	int temp,sum1,sum2,k;
	char str[50];
	for(i=0;i<(n-1);i++)
	{
		for(j=1;j<=(n-i-1);j++)
		{
			sum1=0;
			sum2=0;
			str[50]='\0';
			if(strlen(a[j])<strlen(a[j-1]))
			{
				temp=b[j];
				b[j]=b[j-1];
				b[j-1]=temp;
				strcpy(str,a[j-1]);
				strcpy(a[j-1],a[j]);
				strcpy(a[j],str);
			}
			if(b[j]==b[j-1])
			{
				for(k=0;k<b[j];k++)
				{
					sum1=sum1+a[j][k];
					sum2=sum2+a[j-1][k];
				}
				if(sum2>sum1)
				{
					temp=b[j];
					b[j]=b[j-1];
					b[j-1]=temp;
					strcpy(str,a[j-1]);
					strcpy(a[j-1],a[j]);
					strcpy(a[j],str);
				}
			}
		}
	}
	for(i=0;i<n;i++)
	{
		puts(a[i]);
	}
	end=clock();
	time=end-start;
	printf("The program ran for %f", time/CLOCKS_PER_SEC);
}
