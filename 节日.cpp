#include<stdio.h>
#include<iostream>
#include <string>
using namespace std;
int getweek(int year,int month,int day);
int getnumweek(int year,int month,int num,int week);
int getDays(int year,int month);
bool isR(int year);
int main(){
	int a,b,c,y1,y2;
	cin>>a>>b>>c>>y1>>y2;
	int t;
	for(int i=y1;i<=y2;i++){
		t=getnumweek(i,a,b,c%7);
		if(t==-1){
			cout<<"none"<<endl;
			continue;
		}
		cout<<i<<"/";
		if(a<10) cout<<"0";
		cout <<a<<"/";\
		if(t<10)cout<<"0";
		cout << t<<endl;
	}
	return 0;
}
int getnumweek(int year,int month,int num,int week){
	int tweek=getweek(year,month,1);
	int t=week-tweek;
	if(t<0) t+=7;
	num= 1+(num-1)*7+t;
	if(getDays(year,month)<num) return -1;
	return num;
}
int getweek(int year,int month,int day){
	int days=(year-1850)*365;
	int ty=1850,num=0;
	while(ty<year&&isR(ty)==false) ty++;
	if(ty<year) {
		num++;
		ty+=4;
		while(ty<year){
			if(isR(ty)) num++;
			ty+=4;
		}
	}
	days+=num;
	for(int i=1;i<month;i++){
		days+=getDays(year,i);
	}
	days+=(day-1);
	return (days+2)%7;
}
int getDays(int year,int month){
	switch(month){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		return 31;
		case 4:
		case 6:
		case 9:
		case 11:
		return 30;	
	}
	return isR(year)?29:28;
}
bool isR(int year){
	return (year%100==0?year%400==0:year%4==0);
}
