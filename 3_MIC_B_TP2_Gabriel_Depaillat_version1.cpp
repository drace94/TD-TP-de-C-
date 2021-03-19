#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int main(void) {
	//-----------------------------Exercice 1--------------------------------------
	vector<float> v1(10);
	for (int i=0;i<(int)v1.size();i++) v1[i]=((float)(i))/10.0;
	vector<float> v2;
	v2=v1;
	for (int i=0;i<(int)(v1.size())/2;i++) v2.pop_back();
	cout << "[";
	for (int i=0;i<(int)v1.size();i++) cout << v1[i] << " ";
	cout << "]" << endl;
	cout << "[";
	for (int i=0;i<(int)v2.size();i++) cout << v2[i] << " ";
	cout << "]" << endl;
	cout << endl;
	//------------------------------Exercice 2--------------------------------------
	list<char> l1;
	list<char>::iterator it2,nb_iter;
	for(char i='a';i!='k';i++) l1.push_back(i);
	list<char> l2(l1);
	int k = l1.size();
	for (int i=0;i<k/2;i++) l2.pop_front();
	
	nb_iter = find(l2.begin(),l2.end(),'f');
	l2.erase(l2.begin(),nb_iter);
	for(it2=l1.begin();it2!=l1.end();it2++) cout <<*it2 << " ";
	cout << endl;
	for(it2=l2.begin();it2!=l2.end();it2++) cout <<*it2 << " ";
	cout << endl;
	cout << endl;
	//------------------------------Exercice 3--------------------------------------
	set<string> s1;
	s1.insert("Paul");
	s1.insert("Hugo");
	s1.insert("Wessim");
	s1.insert("Arthur");
	set<string>::iterator it;
	for(it=s1.begin();it!=s1.end();it++) cout << *it << " ";
	cout << endl;
	s1.erase("Arthur");s1.erase("Hugo");
	for(it=s1.begin();it!=s1.end();it++) cout << *it << " ";
	cout << endl;
	cout << endl;
	//-----------------------------Exercice 4--------------------------------------
	map<string,long int> M { {"Hugo",729361439},{"Gabriel",752639608},{"Arthur",610293610},{"Wessim",522984732},{"Joanne",223746382}};
	map<string,long int>::iterator it4;
	for (it4=M.begin();it4!=M.end();it4++) cout << it4->first << " a pour num 0" << it4->second << endl;
	cout << endl;
	for (it4=M.begin();it4!=M.end();it4++) {
		if (it4->second/100000000 == 5) {                                                       //Je n'ai pas trouvé de meilleure
			it4 = M.erase(it4);								//alternative
		}
	}
	cout << endl;
	for (it4=M.begin();it4!=M.end();it4++) cout << it4->first << " a pour num 0" << it4->second << endl;
	cout << endl;
	//------------------------------Exercice 5-------------------------------------
	vector<string> V(5);
	V[0] = "semimarath";
	V[1] = "vraissemblance";
	V[2] = "equation";
	V[3] = "cactus";
	V[4] = "ordinateur";
	vector<string>::iterator iter;
	for(iter=V.begin();iter!=V.end();iter++) cout <<*iter<<" ";
	cout << endl;
	sort(V.begin(),V.end());
	for(iter=V.begin();iter!=V.end();iter++) cout <<*iter<<" ";
	cout << endl;
	cout << endl;
	//------------------------------Exercice 6-------------------------------------
	list<string> L;
	list<string>::iterator it3,m1;
	L.push_back("Il");
	L.push_back("fait");
	L.push_back("beau");
	m1 = find(L.begin(),L.end(),"beau");
	L.insert(m1,"très");
	for (it3=L.begin();it3!=L.end();it3++) cout << *it3 << " ";
	cout << endl;
	cout << endl;
	//-------------------------------------------------------------------
	return(0);
}