#include "archive.h"
//#include <iostream>
using namespace std;

class Student
{
	friend class archive;
public:
	
	char  gender;
	int age;
	double weight;
	vector<int> vi;
	map<char, int> mp;
	void add()
	{
		vi.push_back(2);
		vi.push_back(5);
		mp['f'] = 31;
		mp['i'] = 28;
		mp['r'] = 31;
		mp['s'] = 30;
		mp['t'] = 31;
		
	}
	void serialize(archive  &ar)
	{
		ar<<gender<<age<<weight;
		ar<<vi;
		ar<<mp;	
	}
	void deserialize(archive &ar)
	{
		ar>>gender>>age>>weight;
		ar>>vi;
		ar>>mp;
	}
};

int main()
{

	Student one;
	one.gender = 'F';
	one.age = 16;
	one.weight=17.5;
	one.add();
	//ofstream ofs("fifthgrade.ros");
   	//serializer srlz(ofs);
	//ofs.write((char *)&one, sizeof(one));
	archive a;
	a.save_object(one);
	Student two;
	a.load_object(two);
	cout<<two.gender<<" ";
	cout<<two.age<<" "<<two.weight<<" ";
	//cout<<one.vi[0];
	//cout<<one.vi[1];

	cout << "Size: "<< two.mp.size() << endl;
	for (auto iter = two.mp.begin(); iter != two.mp.end(); iter++)
	{
		cout << (*iter).first << " " << (*iter).second << endl;
	}

	return 0;
}
