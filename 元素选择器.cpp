
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;
struct Node {
	string tag;
	string id;
	int flag;
	int idx;
};
struct Tree {
	Tree *father;
	Node root;
int numChilds;
vector<Tree> childs;
}self;
vector<Node> nodes;
Tree tree;
int find(vector<Node> &nodes, int idx, int flag);
int findFlag(string &s);
int mysplit(string s, vector<string> &d);
void searchNodes(string s);
int findAllNode(Tree &tr, string s, int id, vector<Tree*> &data,bool isroot=true);
int findNode(Tree &tr, string s, int id, vector<Tree *> &data, bool isroot = true);
int main() {
	int n, m;
	cin >> n >> m;
	string ts;
	vector<string> d;
	Node tn;
	int numNodes = 0, tf;
	Tree tt, *curt = NULL;
	char cs[101];
	getchar();
	for (int i = 0;i < n;i++) {
		gets(cs);
		ts = cs;
		if (mysplit(ts, d) != 1) {
			tn.id = d[1].substr(1);
		}
		else {
			tn.id = "";
		}
		tf = findFlag(d[0]);
		tn.flag = tf;
		tn.tag = d[0].substr(tf);
		nodes.push_back(tn);
		tn.idx = numNodes;

		tt.root = tn;
		tt.numChilds = 0;
		if (find(nodes, numNodes - 1, tf) == -1) {
			tree = tt;
			curt = &tree;
		}
		else {
			while (curt->root.flag + 2 != tf) {
				curt = curt->father;
			}
			tt.father = curt;
			curt->childs.push_back(tt);
			curt->numChilds++;
			curt = &(curt->childs[curt->numChilds - 1]);
		}
		numNodes++;
	}
	d.clear();
	for (int i = 0;i < m;i++) {
		gets(cs);
		ts = cs;
		d.push_back(ts);
	}
	for (int i = 0;i < m;i++) {
		searchNodes(d[i]);
	}
	return 0;
}
void searchNodes(string s) {
	vector<string> d;
	mysplit(s, d);
	int sz = d.size();
	vector<Tree*> td;
	vector<Tree*> ftd;
	string ts;
	int id;
	ftd.push_back(&tree);
	for (int i = 0;i < sz;i++) {
		if (d[i][0] == '#') {
			id = 1;
			d[i] = d[i].substr(1);
		}
		else {
			id = 0;
		}
		td.clear();
		if (i < sz - 1) {
			for (int j = 0;j < ftd.size();j++) {
				findNode(*(ftd[j]), d[i], id, td, i==0);
			}
			ftd.assign(td.begin(), td.end());
		}
		else {
			for (int j = 0;j < ftd.size();j++) {
				findAllNode(*(ftd[j]), d[i], id, td, i == 0);
			}
		}
	}
	vector<int> di;
	for (int i = 0;i < td.size();i++) {
		di.push_back(td[i]->root.idx + 1);
	}
	sort(di.begin(), di.end());

	cout << di.size();
	for (int i = 0;i < di.size();i++) {
		cout << " " << di[i];
	}
	cout << endl;
}

int findAllNode(Tree &tr, string s, int id,vector<Tree*> &data,bool isroot) {
	int num = 0;
	if (id == 0) {
		if (isroot && tr.root.tag == s) {
			num++;
			data.push_back(&tr);
		}
		for (int i = 0;i < tr.numChilds;i++)
		{
			num += findAllNode(tr.childs[i], s, id, data,true);
		}
	}
	else {
		if (isroot && tr.root.id == s) {
			num++;
			data.push_back(&tr);
		}
		for (int i = 0;i < tr.numChilds;i++)
		{
			num += findAllNode(tr.childs[i], s, id, data,true);
		}
	}
	return num;
}
int findNode(Tree &tr, string s, int id,vector<Tree*> &data,bool isroot) {//0Îªtag1Îªid
	int num = 0;
	if (id == 0) {
		if (isroot && tr.root.tag == s) {
			num++;
			data.push_back(&tr);
		}
		else {
			for (int i = 0;i < tr.numChilds;i++)
			{
				num += findNode(tr.childs[i], s, id, data, true);
			}
		}
	}
	else {
		if (tr.root.id == s) {
			num++;
			data.push_back(&tr);
		}
		else {
			for (int i = 0;i < tr.numChilds;i++)
			{
				num += findNode(tr.childs[i], s, id, data,true);
			}
		}
	}
	return num;
}
int find(vector<Node> &ns, int idx, int flag) {//°üº¬idx 
	if (idx < 0)return -1;
	while (ns[idx].flag + 2 != flag)idx--;
	return idx;
}
int findFlag(string &s) {
	int i = 0;
	while (s[i] == '.')i++;
	return i;
}
int mysplit(string s, vector<string> &d) {
	d.clear();
	int idx = s.find(" ");
	int i = 0;
	int num = 1;
	while (idx != -1) {
		d.push_back(s.substr(i, idx-i));
		i = idx + 1;
		idx = s.find(" ", i);
		num++;
	}
	d.push_back(s.substr(i));
	return num;
	
}
