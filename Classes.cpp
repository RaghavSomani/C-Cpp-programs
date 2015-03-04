#include <iostream>
#include <string>
using namespace std;
enum MealType{NO_PREF, REGULAR, LOW_FAT, VEGETARIAN};
class Passenger
{
	string name;
	MealType mealPref;
	bool isFreqFlyer;
	string freqFlyerNo;
	int* vector;
public:
	Passenger();
	Passenger(const string &nm, MealType mPref, string ffn);
	Passenger(const Passenger &pass);
	~Passenger();
	bool isFrequentFlyer() const
	{
		return isFreqFlyer;
	};
	void Display()
	{
		cout<<name<<endl;
		cout<<mealPref<<endl;
		cout<<isFreqFlyer<<endl;
		cout<<freqFlyerNo<<endl;
	}
	void makeFreqFlyer(const string &newFreqFlyerNo);
};
Passenger::Passenger()
{
	name        ="NO_NAME";
	mealPref    =NO_PREF;
	isFreqFlyer =false;
	freqFlyerNo ="NONE";
	vector      =new int[10];
}
Passenger::Passenger(const string &nm, MealType mPref, string ffn)
{
	name        =nm;
	mealPref    =mPref;
	isFreqFlyer =(ffn!="NONE");
	freqFlyerNo =ffn;
	vector      =new int[10];
}
Passenger::Passenger(const Passenger &pass)
{
	name        =pass.name;
	mealPref    =pass.mealPref;
	isFreqFlyer =pass.isFreqFlyer;
	freqFlyerNo =pass.freqFlyerNo;
	vector      =pass.vector;
}
Passenger::~Passenger()
{
	delete [] vector;
}
void Passenger::makeFreqFlyer(const string &newFreqFlyerNo)
{
	isFreqFlyer =true;
	freqFlyerNo =newFreqFlyerNo;
}
int main()
{
	// Passenger p1("Raghav",VEGETARIAN,"1234");	// parameterized constructor called
	// Passenger p2;								// default constructor called
	// Passenger p3(p1);							// copy constructor called
	// Passenger p4=p1;
	// p1.Display();
	return 0;
}