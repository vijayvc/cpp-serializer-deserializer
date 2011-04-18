#include <sstream>
#include<cstring>
#include <iostream>
#include <string>
#include<vector>
#include<list>
#include <map>

using namespace std;
class archive
{
	stringstream s;
	
public:
	// General Serialization/Deserialization
	template<class T>
        archive& operator<<(T& t)
	{
		s<<t<<" ";
		return *this;
	}
 
	template<class T>
	archive& operator>>(T &t)
	{
		char ch;
		s>>t;
		return *this;
	}
       
	// Vector Serialization/Deserialize
        template <class T>
        archive& operator<<(vector<T> &v )
        { 
		s<<v.size()<<" ";
		for(auto i = v.begin();i != v.end();i++)
		{
			s<< *i<<" ";
		}
		return *this;
        }

	template <class T>
        archive& operator>>(vector<T> &v )
        { 
		int size ;
		s>> size;

		while(size)
		{
			T val;
			s>> val;
			v.push_back(val);
			--size;
		}
		return *this;
	}

	// List Serialization/Deserialize
	template <class T>
        archive& operator<<(list<T> &v )
        { 
		s<<v.size()<<" ";
		for(auto i = v.begin();i != v.end();i++)
		{
			s<< *i<<" ";
		}
		return *this;
        }

	template <class T>
        archive& operator>>(list<T> &v )
        { 
		int size ;
		s>> size;

		while(size)
		{
			T val;
			s>> val;
			v.push_back(val);
			--size;
		}
		return *this;
	}

	// Map serialization/Deserialize
        template <class NameType, class ValueType>
        archive& operator<<(map<NameType, ValueType> &v )
        { 
		s<< v.size() <<" ";
		for(auto i = v.begin();i != v.end();i++)
		{
			s << (*i).first << " " << (*i).second << " ";
			//s<< *i<<" ";
		}
		return *this;
        }

	/*
	template <class NameType, class ValueType>
        archive& operator<<(map<const char*, ValueType> &v )
        { 
		s<< v.size() <<" ";
		for(auto i = v.begin();i != v.end();i++)
		{
			s << (*i).first << " " << (*i).second << " ";
			//s<< *i<<" ";
		}
		return *this;
        }
	*/

	template <class NameType, class ValueType >
        archive& operator>>(map<NameType, ValueType> &v )
        { 
		int size ;
		s >> size;

		while(size)
		{
			NameType name;
			ValueType val;
			s >> name;
			s >> val;
			v[name]=val;
			--size;
		}
		return *this;
	}

	// Named member functions
	archive(): s(stringstream::in | stringstream::out){}

	template<class T>
	void save_object(T &t)
	{
		t.serialize(*this);
	}

	template<class T>
	void load_object(T &t)
	{
		t.deserialize(*this);
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
	map<char, int> mp;
	void add()
	{
		//vi.push_back(2);
		//vi.push_back(5);
		mp['f'] = 31;
		mp['i'] = 28;
		mp['r'] = 31;
		mp['s'] = 30;
		mp['t'] = 31;
	}
	void serialize(archive  &ar)
	{
		ar<<gender<<age<<weight<<mp;//vi;	
	}
	void deserialize(archive &ar)
	{
		ar>>gender>>age>>weight;
		ar>>mp;//vi;
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
