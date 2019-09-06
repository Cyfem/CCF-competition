#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int getNum(vector<int> &a,vector<int> &b);
void takeHours(vector<int> &d,int a,int b);
int main(){
	int n;
	vector<int> a,b;
	int t1,t2;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>t1>>t2;
		takeHours(a,t1,t2);
	}
	for(int i=0;i<n;i++){
		cin>>t1>>t2;
		takeHours(b,t1,t2);
	}
	cout<<getNum(a,b)<<endl;
	return 0;
}
int getNum(vector<int> &a,vector<int> &b){
	int ia=0,ib=0;
	int sza=a.size(),szb=b.size();
	int num=0;
	while(ia<sza && ib<=szb){
		if(a[ia]==b[ib]) {
			num++;
			ia++;
			ib++;	
		}else if(a[ia]<b[ib])ia++;
		else ib++;
	}
	return num;
}
void takeHours(vector<int> &d,int a,int b){
	for(int i=0;i<b-a;i++){
		d.push_back(a+i);
	} 
}
