#include <iostream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<set>
#include<map>
#include<stack>
#include<algorithm>

using namespace std;

class ConditieMeteo
{
public:
	int temperatura;
	string descriere;
	string data;

	ConditieMeteo()
	{
		temperatura = 5;
		descriere = "";
		data = "01-01-2000";
	}

	ConditieMeteo(int temp, string desc, string dat)
	{
		temperatura = temp;
		descriere = desc;
		data = dat;
	}

	bool operator < (ConditieMeteo c) const
	{
		return this->data < c.data;
	}
};

ostream& operator<< (ostream& o, ConditieMeteo c)
{
	o << "Descriere: " << c.descriere << endl;
	o << "Temperatura: " << c.temperatura << endl;
	o << "Data " << c.data << endl;
	return o;
}


void afisare(ConditieMeteo c)
{
	cout << c;
}

int main()
{
	vector<ConditieMeteo> v;
	ConditieMeteo c1(0, "innorat", "14-01-2021");
	ConditieMeteo c2(-2, "ger", "15-01-2021");
	ConditieMeteo c3;

	v.push_back(c1);
	v.push_back(c2);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].data << endl;
	}

	v.push_back(c3);
	v.pop_back();

	for (vector<ConditieMeteo>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it).descriere << endl;
	}

	list<ConditieMeteo>l;
	l.push_back(c1);				// 0 ultimul
	l.push_front(c2);				// -2 primul
	l.insert(++l.begin(), c3);		// 5 il pune la jumate

	for (list<ConditieMeteo>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << it->temperatura << endl;
	}

	//l.pop_front();
	auto j = next(l.begin(), 2);
	l.erase(j);

	deque<ConditieMeteo> deq;
	deq.push_back(c1);
	deq.push_front(c2);

	for (int i = 0; i < deq.size(); i++)
	{
		cout << deq[i].descriere << endl;
	}

	deq.pop_back();

	set <ConditieMeteo> s;
	s.insert(c2);
	s.insert(c1);
	s.insert(c3);

	for (auto i = s.begin(); i != s.end(); i++)
	{
		cout << *i << endl;
	}

	map<string, ConditieMeteo> m;		// perechi de string si ConditieMeteo
	m.insert(make_pair(c1.data, c2));
	m.insert(pair<string, ConditieMeteo>(c2.data, c2));

	string zi;
	cout << "zi (dd/MM/yyyy): ";
	cin >> zi;

	auto it = m.find(zi);
	if (it != m.end())
	{
		cout << "Temperatura din ziua " << it->first << " a fost" << it->second.temperatura << endl;
	}
	else cout << "N am gasit ziua." << endl;

	cout << m[zi] << endl;
	
	stack<int, vector<int>> st;
	st.push(2);
	st.push(3);
	st.push(5);

	st.pop();
	cout << st.top() << endl;		// cine urmeaza

	sort(v.begin(), v.end());
	for_each(v.begin(), v.end(), afisare);

}