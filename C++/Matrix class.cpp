#include <iostream>
using namespace std;
class Matrix
{
	int rows;
	int cols;
	int** A;
public:
	Matrix(int r, int c)
	{
		rows=r;
		cols=c;
		A = new int* [rows];
		for(int i=0;i<rows;++i)
			A[i]=new int [cols];
	};
	Matrix(Matrix& P)
	{
		if(this!=&P)
		{
			rows=P.rows;
			cols=P.cols;
			A = new int* [rows];
			for(int i=0;i<rows;++i)
				A[i]=new int [cols];
			for(int i=0;i<rows;++i)
				for(int j=0;j<cols;j++)
					A[i][j]=P.A[i][j];
		}
	}
	~Matrix()
	{
		for(int i=0;i<rows;i++)
			delete [] A[i];
		delete [] A;
	}
	friend Matrix operator *(Matrix& P, Matrix& Q)
	{
		if(P.cols==Q.rows)
		{
			int r=P.rows;
			int c=Q.cols;
			Matrix R(r,c);
			int ** X=P.A;
			int ** Y=Q.A;
			int ** Z=R.A;
			for(int i=0;i<r;i++)
				for(int j=0;j<c;j++)
				{
					Z[i][j]=0;
					for(int k=0;k<P.cols;k++)
						Z[i][j]+=X[i][k]*Y[k][j];
				}
			return R;
		}
	}
	Matrix& operator = (const Matrix& P)
	{
		if(this!=&P)
		{
			for(int i=0;i<rows;i++)
				delete [] A[i];
			delete [] A;
			rows=P.rows;
			cols=P.cols;
			A = new int* [rows];
			for(int i=0;i<rows;++i)
				A[i]=new int [cols];
			for(int i=0;i<rows;++i)
				for(int j=0;j<cols;j++)
					A[i][j]=P.A[i][j];
		}
		return *this;
	}
	void print()
	{
		for(int i=0;i<rows;++i)
			for(int j=0;j<cols;++j)
				cout<<A[i][j]<<" \n"[j==cols-1];
			cout<<endl;
	}
	void getMatrix()
	{
		cout<<"Enter Matrix :\n";
		for(int i=0;i<rows;++i)
			for(int j=0;j<cols;++j)
				cin>>A[i][j];
	}
};
int main()
{
	int n,m;
	cout<<"Enter dimension of Matrix A :\n";
	cin>>n>>m;
	Matrix A(n,m);
	A.getMatrix();
	cout<<"Enter dimension of Matrix B :\n";
	int p,q;
	cin>>p>>q;
	Matrix B(p,q);
	B.getMatrix();
	if(m==p)
	{
		Matrix C(n,q);
		C=A*B;
		cout<<"Multiplying matrix A and B\n";
		cout<<"Matrix A*B : \n";
		C.print();
	}
	else
		cout<<"Cannot multiply A and B, check dimensions\n";
	return 0;
}