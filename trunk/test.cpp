#include "archive.h"
//#include <iostream>
#include <string>
using namespace std;
class node
{
	friend class archive;
	archive& serialize(archive &ar)
	{
		ar<<value<<next;
	}
	archive& deserialize(archive &ar)
	{
		ar>>value>>next;
	}
	static node* allocate_memory()
	{
		node *temp=new node();
		return temp;
	}
	public:
	int value;
	node *next;
};

class base
{
	friend class archive;
	public:
	int a;
	
	archive& serialize(archive  &ar)
	{
		ar<<a;
		cout<<"Base: ";
		//ar.printString();
		return ar;
	}
	archive& deserialize(archive &ar)
	{
		return (ar>>a);
	}
};
class derived:public base

{
	friend class archive;
	public:
	int c;
	archive& serialize(archive &ar)
	{
		ar<<(ar.base_object<base>(*this))<<c;
	}

	archive& deserialize(archive &ar)
	{
		ar>>(ar.base_object<base>(*this))>>c;
	}
};
class containment_base
{
	friend class archive;
	public:
	base b;
	char c;
	archive& serialize(archive  &ar)
	{
		ar<<b<<c;//vi;	
		cout<<"containment_base: ";
		//ar.printString();
		return ar;
	}
	archive& deserialize(archive &ar)
	{
		ar>>b>>c;
		return ar;
	}

};

class Student
{
	friend class archive;
public:
	
	char  gender;
	int age;
	double weight;
	//vector<int> vi;
	map<string, int> mp; // does not work for char*
	//multimap<string, int> mm;
	void add()
	{
		/*
		vi.push_back(2);
		vi.push_back(5);
		*/

		mp["f"] = 31;
		mp["i"] = 28;
		mp["r"] = 31;
		mp["s"] = 30;
		mp["t"] = 31;
		
		/*
		mp[string("first name")] = 31;
		mp[string("second sname")] = 28;
		mp[string("third tname")] = 31;
		mp[string("fourth 4name")] = 30;
		mp[string("fifth f name")] = 31;
		*/

		/*
		mm.insert(pair<string, int>("a", 1));
		mm.insert(pair<string, int>("c", 2));
		mm.insert(pair<string, int>("b", 3));
		mm.insert(pair<string, int>("b", 4));
		mm.insert(pair<string, int>("a", 5));
		mm.insert(pair<string, int>("b", 6));
		*/
	}
	void serialize(archive  &ar)
	{
		//ar<<gender<<age<<weight;
		//ar<<vi;
		string s("this is my string");
		ar<<s;
		ar<<mp;	
		//cout << ar.s.str();
		//ar<<mm;	
	}
	void deserialize(archive &ar)
	{
		//ar>>gender>>age>>weight;
		//ar>>vi;
		string s;
		ar>>s;
		//cout << s << endl;
		ar>>mp;
		//ar>>mm;
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
	/*
	cout << "\nSize: "<< one.mp.size() << endl;
	for (auto iter = one.mp.begin(); iter != one.mp.end(); iter++)
	{
		cout << (*iter).first << " " << (*iter).second << endl;
	}
	*/

	archive a;
	a.save_object(one);
	Student two;
	a.load_object(two);
//	cout<<two.gender<<" ";
//	cout<<two.age<<" "<<two.weight<<" ";
	//cout<<one.vi[0];
	//cout<<one.vi[1];
	
	cout << "\nSize: "<< two.mp.size() << endl;
	for (auto iter = two.mp.begin(); iter != two.mp.end(); iter++)
	{
		cout << (*iter).first << " " << (*iter).second << endl;
	}
	
	/*
	// Multimap
	cout << "Size: "<< two.mm.size() << endl;
	for (auto iter = two.mm.begin(); iter != two.mm.end(); iter++)
	{
		cout << (*iter).first << " " << (*iter).second << endl;
	}
	*/

	//archive a;
	/* test for inheritence */
	/*
	derived d;
	d.a = 1;
	d.c=2;
	a.save_object(d);
	derived d1;
	a.load_object(d1);
	cout<<d1.a<<" "<<d1.c;

	cout<<"Pointers"<<endl;
	int arr[3]={1,2,3};
	a.save_array(arr,3);
	a.print();
	int sz=a.get_array_size();
	a.print();
	int *arr1= new int(sz);
	cout<<"Size is"<<sz<<endl;
	a.load_array(arr1);
	for(int i=0;i<sz;++i)
		cout<<arr1[i]<<endl;
	*/

#if 0
	archive a;
	node *root=new node();
	root->value=10;
	root->next=new node();
	root->next->value=20;
	root->next->next=root;

	a.save_object(root);
	a.print();
	node* root1;
	a.load_object(root1);
	cout<<root1->value;
	cout<<root1->next->value;
	cout<<root1->next->next->value;
#endif

#if 0
	archive ar;
	/* test for inheritence */
	derived d;
	d.a = 1;
	d.c=2;
	ar.save_object(d);
	derived d1;
	ar.load_object(d1);
	cout<<d1.a<<" "<<d1.c;
#endif
#if 0
	test for containment
	containment_base d;
	d.b.a=10;
	d.c='a';
	a.save_object(d);
	containment_base d1;
	a.load_object(d1);
	cout<<d1.b.a<<" "<<d1.c;
#endif
	return 0;
}
