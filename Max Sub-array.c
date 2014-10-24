#include<stdio.h>
#include<stdlib.h>
int* max_sub_array(int [], int, int);
int* max_sub_cross_array(int a[], int, int);
void main()
{
	int n,i;
	int* store=(int*)malloc(3*sizeof(int));
	printf("Length of the array : ");
	scanf("%d", &n);
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	store=max_sub_array(a,0,n-1);
	printf("\nMaximum sum of sub-array is : %d",store[2]);
	printf("\n\nThe sub array is :\n");
	for(i=store[0];i<=store[1];i++)
		printf("%d ",a[i]);
	free(store);
}
int* max_sub_array(int a[],int low,int high)
{
	int mid=(low+high)/2;
	int* store=(int*)malloc(3*sizeof(int));
	int* leftstore=(int*)malloc(3*sizeof(int));
	int* rightstore=(int*)malloc(3*sizeof(int));
	int* crossstore=(int*)malloc(3*sizeof(int));
	if(low==high)
	{
		store[0]=low;
		store[1]=high;
		store[2]=a[low];
		return store;
	}
	else
	{
		leftstore=max_sub_array(a,low,mid);
		rightstore=max_sub_array(a,mid+1,high);
		crossstore=max_sub_cross_array(a,low,high);
		if(leftstore[2]>=rightstore[2]&&leftstore[2]>=crossstore[2])
		{
			free(rightstore);
			free(crossstore);
			return leftstore;
		}
		else if(rightstore[2]>=leftstore[2]&&rightstore[2]>=crossstore[2])
		{
			free(leftstore);
			free(crossstore);
			return rightstore;
		}
		else
		{
			free(leftstore);
			free(rightstore);
			return crossstore;
		}
			
	}
}
int* max_sub_cross_array(int a[], int low, int high)
{
	int mid=(low+high)/2,i,leftsum=0,rightsum=0,sum=0,left,right;
	for(i=mid;i>=low;i--)
	{
		sum=sum+a[i];
		if(sum>leftsum)
		{
			leftsum=sum;
			left=i;
		}
	}
	sum=0;
	for(i=mid+1;i<=high;i++)
	{
		sum=sum+a[i];
		if(sum>rightsum)
		{
			rightsum=sum;
			right=i;
		}
	}
	sum=leftsum+rightsum;
	int* store=(int*)malloc(3*sizeof(int));
	store[0]=left;
	store[1]=right;
	store[2]=sum;
	return store;
}
