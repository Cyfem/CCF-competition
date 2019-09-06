#include<stdio.h>
#include <vector>
#include <iostream>
using namespace std;
struct Vec{
	int node;
	vector<int>rodes;
}allvec[500];
struct Rode{
	int node1,node2;
	int c;
	int t;
};
vector<Rode> allrode;
vector<Rode> cdRode;
int veced[500];
int veced2[500];//路径上的前一个节点 
int veced3[500];//路径上的前一条边 
int getMin();
void putRode(int vec);
int getc(int t,int node1,int node2);
int main(){
	int n,m;
	int t,a,b,c;
	cin>>n>>m;
	Rode tmp;
	int numRodes=0;
	for(int i=0;i<500;i++){
		veced[i]=-1;
	}
	for(int i=0;i<m;i++){
		cin>>t>>a>>b>>c;
		tmp.node1=a;
		tmp.node2=b;
		tmp.c=c;
		tmp.t=t;
		allrode.push_back(tmp);
		numRodes++;
		allvec[a].rodes.push_back(numRodes-1);
		allvec[b].rodes.push_back(numRodes-1);
	}
	veced[1]=0;
	veced2[1]=1;
	veced3[1]=-1;
	putRode(1);
	while(getMin()!=n);
	printf("%d\n",veced[n]);
	return 0;
}
int getMin(){
	vector<Rode>::iterator begin=cdRode.begin(),end=cdRode.end(),t;
	int tc=9999999;
	int noded,wnoded,tmpc;
	for(;begin!=end;begin++){
		if(veced[begin->node1]>=0) noded=begin->node1;
		else noded=begin->node2;
		if(veced[begin->node1]>=0&&veced[begin->node2]>=0){
			continue;
		}else {
			if(begin->node1==noded) wnoded=begin->node2;
			else wnoded=begin->node1;
			if((tmpc=getc(begin-cdRode.begin(),noded,wnoded))<tc){
			tc=tmpc;
			t=begin;
			}
		}
	}
	noded=(veced[t->node1]>=0?t->node2:t->node1);
	veced[noded]=tc;
	veced2[noded]=(noded==t->node2?t->node1:t->node2);
	veced3[noded]=t-cdRode.begin();
	putRode(noded);
	return noded;
}
int getc(int t,int node1,int node2){
	if(cdRode[t].t==0) 
		return veced[node1]+cdRode[t].c;
	int num=0;
	while(cdRode[t].t==1){
		num+=(cdRode[t].c);
		if(veced2[node1]==node1)break;
		t=veced3[node1];
		node1=veced2[node1];
	}
	if(veced2[node1]==node1) return num*num;
	if(cdRode[t].node1==node1) return veced[cdRode[t].node2]+num*num;
	return veced[node1]+num*num;
}
void putRode(int vec){
	vector<Rode>::iterator begin=allrode.begin(),end=allrode.end();
	for(;begin!=end;begin++){
		if(begin->node1==vec||begin->node2==vec){
			if(veced[begin->node1]>=0&&veced[begin->node2]>=0)
			continue;
			else 
			cdRode.push_back(*begin);
		}
	}
}
