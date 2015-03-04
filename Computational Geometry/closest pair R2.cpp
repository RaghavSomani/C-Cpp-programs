#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <limits>
using namespace std;
const float FLT_MAX=numeric_limits<float>::max();
const float FLT_MIN=numeric_limits<float>::lowest();
class point
{
public:
	float x;
	float y;
	point(float a=0,float b=0):x(a),y(b) {};
};
pair<point,point> closest(vector<point> P);
pair<point,point> strip_closest(vector<point> S);
bool compare_x(point p, point q) { return (p.x<q.x); };
bool compare_y(point p, point q) { return (p.y<q.y); };
int main()
{
	ifstream fp("points.txt");
	int n;
	float x,y;
	fp>>n;
	vector<point> P;
	for(int i=0;i<n;i++)
	{
		fp>>x>>y;
		point p(x,y);
		P.push_back(p);
	}
	if(P.size()<2)
	{
		cout<<"You require more than 2 points\n";
		return 0;
	}
	pair<point,point> p=closest(P);
	cout<<"Closest points are\n";
	cout<<p.first.x<<" "<<p.first.y<<" and "<<p.second.x<<" "<<p.second.y<<endl;
	return 0;
}
float d(point p,point q)
{
	return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y));
}
pair<point,point> closest(vector<point> P)
{
	int n=P.size();
	if(P.size()==1)
	{
		point p(FLT_MAX,FLT_MAX);
		return {P[0],p};
	}
	if(P.size()==2)
	{
		return {P[0],P[1]};
	}
	if(P.size()==3)
	{
		float dist1=d(P[0],P[1]);
		float dist2=d(P[1],P[2]);
		float dist3=d(P[0],P[2]);
		float min_dist=min(min(dist1,dist2),dist3);
		if(min_dist==dist1)
			return {P[0],P[1]};
		else if(min_dist==dist2)
			return {P[1],P[2]};
		else if(min_dist==dist3)
			return {P[0],P[2]};
	}
	sort(P.begin(),P.end(),compare_x);
	vector<point> Q(P.begin(),P.begin()+(n/2));
	vector<point> R(P.begin()+(n/2),P.end());
	vector<point> S;
	pair<point,point> pair1=closest(Q);
	pair<point,point> pair2=closest(R);
	float dist1=d(pair1.first,pair1.second);
	float dist2=d(pair2.first,pair2.second);
	float delta=min(dist1,dist2);
	point min=*R.begin();
	for(int i=Q.size()-1;i>0;i--)
	{
		if(abs(Q[i].x - min.x) <= delta)
			S.push_back(Q[i]);
		else
			break;
	}
	for(int i=0;i<R.size();i++)
	{
		if(abs(R[i].x - min.x) <= delta)
			S.push_back(R[i]);
		else
			break;
	}
	pair<point,point> cross_pair=strip_closest(S);
	float dist3=d(cross_pair.first,cross_pair.second);
	float min_d=(dist3<delta)?dist3:delta;
	if(min_d==dist1)
		return pair1;
	else if(min_d==dist2)
		return pair2;
	else if(min_d==dist3)
		return cross_pair;
}
pair<point,point> strip_closest(vector<point> S)
{
	sort(S.begin(),S.end(),compare_y);
	pair<point,point> nearest={point (FLT_MIN,FLT_MIN),point (FLT_MAX,FLT_MAX)};
	float min=FLT_MAX, distance;
	for(int i=0;i<S.size();i++)
	{
		for(int j=i+1;j<=i+7&&j<S.size();j++)
		{
			distance=d(S[i],S[j]);
			if(distance<min)
			{
				min=distance;
				nearest={S[i],S[j]};
			}
		}
	}
	return nearest;
}