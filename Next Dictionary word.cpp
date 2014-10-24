#include<stdio.h>
#include<string.h>
int main()
{
    int t,i,temp,len,j,k;
    scanf("%d",&t);
    char c[100];
    for(i=0;i<t;i++)
    {
		scanf("%s",c);
    	len=strlen(c);
    	j=len-1;
		while(c[j-1]>=c[j]&&j>0)
			j--;
		temp=j-1;
		if(temp==-1)
		{
			printf("no answer\n");
			continue;
		}
		j=temp+1;
    	while(c[j]>c[temp])
    		j++;
    	c[j-1]=c[temp]+c[j-1]-(c[temp]=c[j-1]);
    	
		/*for(j=temp+1;j<len;j++)
    		for(k=temp+1;k<len-1;k++)
    			if(c[k]>c[k+1])
    				c[k]=c[k+1]+c[k]-(c[k+1]=c[k]);	*/
    	for(j=temp+1;j<((temp+len+1)/2);j++)
    	{
    		c[j]=c[len-j+temp]+c[j]-(c[len-j+temp]=c[j]);
    	}
    	printf("%s\n",c);
    }
}
