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
		s>>t;
		return *this;
	}

	// Vector Serialization/Deserialize
        template <class T>
        archive& operator<<(vector<T> &v );

	template <class T>
        archive& operator>>(vector<T> &v );

	// List Serialization/Deserialize
	template <class T>
        archive& operator<<(list<T> &v );

	template <class T>
        archive& operator>>(list<T> &v );

	// Map serialization/Deserialize
        template <class NameType, class ValueType>
        archive& operator<<(map<NameType, ValueType> &v );

	/*
	template <class NameType, class ValueType>
        archive& operator<<(map<const char*, ValueType> &v );
	*/

	template <class NameType, class ValueType >
        archive& operator>>(map<NameType, ValueType> &v );

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

// Vector Serialization/Deserialize
template <class T> archive& archive::operator<<(vector<T> &v )
{ 
	s<<v.size()<<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		s<< *i<<" ";
	}
	return *this;
}

template <class T> archive& archive::operator>>(vector<T> &v )
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
template <class T> archive& archive::operator<<(list<T> &v )
{ 
	s<<v.size()<<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		s<< *i<<" ";
	}
	return *this;
}

template <class T> archive& archive::operator>>(list<T> &v )
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
	archive& archive::operator<<(map<NameType, ValueType> &v )
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

template <class NameType, class ValueType>
	archive& archive::operator>>(map<NameType, ValueType> &v )
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
