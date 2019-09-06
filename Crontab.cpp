#include <string.h>
#include <iostream>
#include <vector>
#include <stdio.h> 
using namespace std;
struct Data 
{
	vector<string> minutes;
	vector<string> hours;
	vector<string> day;
	vector<string> month;
	vector<string> week;
	string todo;
	vector<int> iday;
	vector<int> imonth;
	vector<int> iweek;
	vector<int> iminutes;
	vector<int> ihours;
}dataInf[20];

vector<string> infOut[20];
int num;
string dataStart, dataEnd;
struct Day
{
	int year,month,day,hours,minutes,week,flag;
};
vector<Day> days;
Day dd, de;
int strSplit(string &s, const char* c, vector<string> &outs);
bool check(Day &d, Data &data, bool isend, vector<Day> &outday,int flag);
bool checkDay(Day &d, Data &data);
bool checkWeek(Day &d, Data &data);
bool checkMonth(Day &d, Data &data);
int getWeek(Day &d);
bool checkR(int year);
int getdays(int year, int month);
int strToint(string &s, int start, int num);
void dataSplit(Data &data);
void takeMonth(string &s);
void takeWeek(string &s);
void myReplace(string &s, const char str[], const char c[]);
bool checkHours(int hour, Data &data);
bool checkTime(Day &d, Data &data, bool isend, vector<Day> &outday,int flag);
void setDay(int hours, int endMinutes, vector<int> &minutes, vector<Day> &outday, bool isend,int flag);
void incDay(Day &d);
bool testDay(Day &d1, Day &d2);
void putout(vector<Day> &outdays);
int main()
{
	int a; 
	cin >> num >> dataStart >> dataEnd;
	string tDay,tMonth,tWeek,todo,tminutes,thours;
	for (int i = 0;i < num;i++) {
		cin >> tminutes >> thours >> tDay >> tMonth >> tWeek >> todo;
		dataInf[i].day.push_back(tDay);
		dataInf[i].month.push_back(tMonth);
		dataInf[i].week.push_back(tWeek);
		dataInf[i].minutes.push_back(tminutes);
		dataInf[i].hours.push_back(thours);
		dataInf[i].todo = todo;
		dataSplit(dataInf[i]);
	}
	vector<string> tmp;
	int inum;
	for (int i = 0;i < num;i++) {
		if (dataInf[i].day[0][0] == '*')
		{
			dataInf[i].iday.push_back(-1);
		}
		else for (unsigned int j = 0;j < dataInf[i].day.size();j++) {
			inum = strSplit(dataInf[i].day[j], "-", tmp);
			dataInf[i].iday.push_back(strToint(tmp[0], 0, 4));
			if (inum == 2) {
				dataInf[i].iday.push_back(strToint(tmp[1],0,4));
			}
			else dataInf[i].iday.push_back(strToint(tmp[0], 0, 4));
		}

		if (dataInf[i].month[0][0] == '*')
		{
			dataInf[i].imonth.push_back(-1);
		}
		else for (unsigned j = 0;j < dataInf[i].month.size();j++) {
			inum = strSplit(dataInf[i].month[j], "-", tmp);
			dataInf[i].imonth.push_back(strToint(tmp[0], 0, 4));
			if (inum == 2) {
				dataInf[i].imonth.push_back(strToint(tmp[1], 0, 4));
			}
			else dataInf[i].imonth.push_back(strToint(tmp[0], 0, 4));
		}

		if (dataInf[i].week[0][0] == '*')
		{
			dataInf[i].iweek.push_back(-1);
		}
		else for (unsigned j = 0;j < dataInf[i].week.size();j++) {
			inum = strSplit(dataInf[i].week[j], "-", tmp);
			dataInf[i].iweek.push_back(strToint(tmp[0], 0, 4));
			if (inum == 2) {
				dataInf[i].iweek.push_back(strToint(tmp[1], 0, 4));
			}
			else dataInf[i].iweek.push_back(strToint(tmp[0], 0, 4));
		}

		if (dataInf[i].minutes[0][0] == '*')
		{
			dataInf[i].iminutes.push_back(-1);
		}
		else for (unsigned j = 0;j < dataInf[i].minutes.size();j++) {
			inum = strSplit(dataInf[i].minutes[j], "-", tmp);
			dataInf[i].iminutes.push_back(strToint(tmp[0], 0, 4));
			if (inum == 2) {
				dataInf[i].iminutes.push_back(strToint(tmp[1], 0, 4));
			}
			else dataInf[i].iminutes.push_back(strToint(tmp[0], 0, 4));
		}
		if (dataInf[i].hours[0][0] == '*')
		{
			dataInf[i].ihours.push_back(-1);
		}
		else for (unsigned j = 0;j < dataInf[i].hours.size();j++) {
			inum = strSplit(dataInf[i].hours[j], "-", tmp);
			dataInf[i].ihours.push_back(strToint(tmp[0], 0, 4));
			if (inum == 2) {
				dataInf[i].ihours.push_back(strToint(tmp[1], 0, 4));
			}
			else dataInf[i].ihours.push_back(strToint(tmp[0], 0, 4));
		}
	}

	dd.year = strToint(dataStart, 0, 4);
	dd.month = strToint(dataStart, 4, 2);
	dd.day = strToint(dataStart, 6, 2);
	dd.hours = strToint(dataStart, 8, 2);
	dd.minutes = strToint(dataStart, 10, 2);

	dd.week = getWeek(dd);

	de.year = strToint(dataEnd, 0, 4);
	de.month = strToint(dataEnd, 4, 2);
	de.day = strToint(dataEnd, 6, 2);
	de.hours = strToint(dataEnd, 8, 2);
	de.minutes = strToint(dataEnd, 10, 2);

	vector<Day> outdays;
	int flag;
	while (testDay(dd,de))
	{
		outdays.clear();
		if (dd.year == de.year && dd.month == de.month && dd.day == de.day) {
			dd.minutes = de.minutes;
			dd.hours = de.hours;
			flag = true;
		}
		else flag = false;
		for (int i = 0;i < num;i++) {
			check(dd, dataInf[i], flag, outdays,i);

		}
		putout(outdays);
		incDay(dd);
	}
    return 0;
}
void putout(vector<Day> &outdays) {
	vector<Day>::iterator ibegin,iend;
	vector<Day>::iterator tmp;
	int isize = outdays.size();
	char tmonth[10], tday[10], thours[10], tminutes[10];
	string smonth, sday, shours, sminutes;
	for (int i = 0;i < isize;i++) {
		ibegin = outdays.begin();
		iend = outdays.end();
		tmp = ibegin;
		for (;ibegin != iend;ibegin++) {
			if (ibegin->hours < tmp->hours) {
				tmp = ibegin;
			}
			else if (ibegin->hours == tmp->hours && ibegin->minutes < tmp->minutes) {
				tmp = ibegin;
			}
		}
		sprintf(tmonth, "%d", dd.month);
		sprintf(tday, "%d", dd.day);
		sprintf(thours, "%d", tmp->hours);
		sprintf(tminutes, "%d", tmp->minutes);
		char t;
		if (strlen(tmonth) == 1) {
			t=tmonth[0];
			tmonth[0]='0';
			tmonth[1]=t;
			tmonth[2]=0;
		}
			smonth = tmonth;

		if (strlen(tday) == 1) {
			t=tday[0];
			tday[0]='0';
			tday[1]=t;
			tday[2]=0;
		}
			sday = tday;

		if (strlen(thours) == 1) {
			t=thours[0];
			thours[0]='0';
			thours[1]=t;
			thours[2]=0;
		}
			shours = thours;

		if (strlen(tminutes) == 1) {
			t=tminutes[0];
			tminutes[0]='0';
			tminutes[1]=t;
			tminutes[2]=0;
		}
			sminutes = tminutes;

		cout << dd.year << smonth << sday << shours << sminutes << " " << dataInf[tmp->flag].todo << endl;
		outdays.erase(tmp);
	}

}
void incDay(Day &d) {
	if (d.day >= getdays(d.year, d.month)) {
		if (d.month < 12) d.month++;
		else {
			d.year++;
			d.month = 1;
		}
		d.day = 1;
	}
	else d.day++;
	d.week = (d.week + 1) % 7;
	d.hours = 0;
	d.minutes = 0;
}
bool testDay(Day &d1, Day &d2) {
	if (d1.year < d2.year)return true;
	if (d1.year == d2.year && d1.month < d2.month) return true;
	if (d1.year > d2.year) return false;
	if (d1.month == d2.month && d1.day < d2.day)return true;
	if (d1.month > d2.month)return false;
	if (d1.day == d2.day && d1.hours < d2.hours)return true;
	if (d1.day > d2.day)return false;
	if (d1.hours == d2.hours && d1.minutes < d2.minutes)return true;
	return false;
}
bool check(Day &d, Data &data, bool isend,vector<Day> &outday,int flag) {
	if (checkMonth(d, data) && checkDay(d, data) && checkWeek(d, data)) 
		return checkTime(d, data, isend, outday,flag);
//	if (checkWeek(d, data) && checkDay(d, data) && checkMonth(d, data))return true;
	return false;
}
bool checkDay(Day &d, Data &data) {
	if (data.iday.size() == 1)
	{
		return true;
	}
	else {
		int a, b;
		for (unsigned int i = 0;i < data.iday.size() / 2;i++) {
			a = data.iday[i*2];
			b = data.iday[i*2 + 1];
			if (d.day >= a&&d.day <= b)
				return true;
		}
		return false;
	}
	return false;
}
bool checkWeek(Day &d, Data &data) {
	if (data.iweek.size() == 1)
	{
		return true;
	}
	else {
		int a, b;
		for (unsigned int i = 0;i < data.iweek.size() / 2;i++) {
			a = data.iweek[i*2];
			b = data.iweek[i*2 + 1];
			if (d.week >= a&&d.week <= b)
				return true;
		}
		return false;
	}
	return false;
}
bool checkMonth(Day &d, Data &data) {
	if (data.imonth.size() == 1)
	{
		return true;
	}
	else {
		int a, b;
		for (unsigned int i = 0;i < data.imonth.size() / 2;i++) {
			a = data.imonth[i*2];
			b = data.imonth[i*2 + 1];
			if (d.month >= a&&d.month <= b)
				return true;
		}
		return false;
	}
	return false;
}
bool checkTime(Day &d, Data &data, bool isend,vector<Day> &outday,int flag) {//以天计
	if (isend) {
		for (int i = 0;i < d.hours;i++) {
			if(checkHours(i,data))
				setDay(i, 0, data.iminutes, outday, false,flag);
		}
		if (d.minutes>0)
		{
			if (checkHours(d.hours, data))
				setDay(d.hours, d.minutes - 1, data.iminutes, outday, true,flag);
		}
	}
	else {
		if (checkHours(d.hours, data))
			setDay(d.hours, d.minutes, data.iminutes, outday, false, flag);
		for (int i = d.hours + 1;i <= 23;i++) {
			if (checkHours(i, data))
				setDay(i, 0, data.iminutes, outday, false, flag);
		}
	}
	return false;
}
bool checkHours(int hour, Data &data) {
	for (int i = 0;i < data.ihours.size() / 2;i++) {
		if (hour >= data.ihours[i * 2] && hour <= data.ihours[i * 2 + 1])
			return true;
	}
	return false;
}
void setDay(int hours,int endMinutes,vector<int> &minutes,vector<Day> &outday,bool isend,int flag) {//包括
	Day tmp;
	tmp.hours = hours;
	if (minutes.size() == 1) {
		if (isend) {
			for (int i = 0;i <= endMinutes;i++) {
				tmp.minutes = i;
				tmp.flag = flag;
				outday.push_back(tmp);
			}
		}
		else {
			for (int i = endMinutes;i <= 59;i++) {
				tmp.minutes = i;
				tmp.flag = flag;
				outday.push_back(tmp);
			}
		}
		return;
	}
	for (int i = 0;i < minutes.size() / 2;i++) {
		int j = 0;
		for (int j = 0;minutes[i * 2] + j <= minutes[i * 2 + 1];j++) {
			if (isend) {
				if (minutes[i * 2] + j>=0 && minutes[i * 2] + j<=endMinutes)
				{
					tmp.minutes = minutes[i * 2] + j;
					tmp.flag = flag;
					outday.push_back(tmp);
				}
			}
			else {
				if (minutes[i * 2] + j >= endMinutes && minutes[i * 2] + j <= 59) {
					tmp.minutes = minutes[i * 2] + j;
					tmp.flag = flag;
					outday.push_back(tmp);
				}
			}
		}
	}
}
int getWeek(Day &d) {
	int dyear = d.year;
	int days = (dyear - 1970) * 365;
	int year = 1970;
	int numR = 0;
	while (checkR(year) == false && year < dyear)
		year++;
	if (year < dyear) {
		numR++;
		year += 4;
		while (year < dyear) {
			if (checkR(year))
				numR++;
			year += 4;
		}
	}
	days += numR;
	int dmonth = d.month;
	while (--dmonth >= 1) {
		days += getdays(dyear, dmonth);
	}
	days += d.day - 1;
	days %= 7;
	
	return (days + 4) % 7;
}
bool checkR(int year) {
	bool flag = (year % 4 == 0 && (year % 100 == 0 ? year % 400 == 0 : true));
	return flag;
}
int getdays(int year, int month) {
	switch (month)
	{
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
	case 2:
		if (checkR(year))return 29;
		return 28;
	}
	return -1;
}
int strToint(string &s, int start, int num) {
	int i = 0;
	string ss;
	ss=s.substr(start,num);
	sscanf(ss.c_str(), "%d", &i);
	return i;
}
void dataSplit(Data &data) {
	vector<string> s;
	strSplit(data.day[0], ",", s);
	data.day.assign(s.begin(),s.end());
	takeMonth(data.month[0]);
	strSplit(data.month[0], ",", s);
	data.month.assign(s.begin(), s.end());
	takeWeek(data.week[0]);
	strSplit(data.week[0], ",", s);
	data.week.assign(s.begin(), s.end());

	strSplit(data.minutes[0], ",", s);
	data.minutes.assign(s.begin(), s.end());
	strSplit(data.hours[0], ",", s);
	data.hours.assign(s.begin(), s.end());
}
void takeMonth(string &s) {
	myReplace(s, "Jan", "1");
	myReplace(s, "Feb", "2");
	myReplace(s, "Mar", "3");
	myReplace(s, "Apr", "4");
	myReplace(s, "May", "5");
	myReplace(s, "Jun", "6");
	myReplace(s, "Jul", "7");
	myReplace(s, "Aug", "8");
	myReplace(s, "Sep", "9");
	myReplace(s, "Oct", "10");
	myReplace(s, "Nov", "11");
	myReplace(s, "Dec", "12");
}
void takeWeek(string &s) {
	myReplace(s, "Sun", "0");
	myReplace(s, "Mon", "1");
	myReplace(s, "Tue", "2");
	myReplace(s, "Wed", "3");
	myReplace(s, "Thu", "4");
	myReplace(s, "Fri", "5");
	myReplace(s, "Sat", "6");
}
void myReplace(string &s, const char str[], const char c[]) {
	int i = 0, j = -1, len = strlen(str);
	while ((j = s.find(str, i)) != -1) {
		i = j;
		s.replace(j, len, c);
	}
}
int strSplit(string &s, const char* c, vector<string> &outs) {
	int i = 0, j = -1;
	int num = 0;
	outs.clear();
	int len = strlen(c);
	while ((j = s.find(c, i)) != -1)
	{	
		outs.push_back(s.substr(i, j - i));
		i = j + 1;
		num++;
	}
	num++;
	outs.push_back(s.substr(i));
	return num;
}
