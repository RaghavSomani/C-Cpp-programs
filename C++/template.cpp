#include<iostream>
using namespace std;

template <typename T>
class BoVector
{		
	T arr[1000];
	int size;
	public:
		BoVector():size(0){}
		void push(T x)
		{
			arr[size]=x;
			size++;
		}
		T get(int i)
		{
			return arr[i];
		}
		int getSize()
		{
			return size;
		}
		void print()
		{
			for (int i = 0; i < size; i++)
				cout<<arr[i]<<endl;
		}
};
template <typename T>
T square(T x)
{
	return x*x;
}

template <typename T>
BoVector<T> operator * ( BoVector<T>&rhs1,BoVector<T>&rhs2)
{
	{
		BoVector<T> ret;
		for (int i = 0; i < rhs1.getSize(); i++)
			ret.push(rhs1.get(i)*rhs2.get(i));
		return ret;
	}
}

int main(int argc, char  *argv[])
{
	BoVector<int> bv;
	bv.push(2);
	bv.push(5);
	bv.push(8);
	bv.push(9);
	cout<<"Print squared bv: "<<endl;
	bv=square(bv);
	bv.print();
	cout<<square(5.5)<<endl;
	return 0;
}