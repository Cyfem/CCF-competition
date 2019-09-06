#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int main(){
	int n;
	vector<int> d;
	int t;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>t;
		d.push_back(t);
	}
	int sz=d.size();
	for(int i=0;i<n;i++){
		if(i==0){
			cout<<(d[0]+d[1])/2;
		}else if(i==sz-1){
			cout<<(d[sz-1]+d[sz-2])/2;
		}else{
			cout<<(d[i]+d[i+1]+d[i-1])/3;
		}
		cout<<" ";
	}
	cout<<endl;
	return 0;
}
