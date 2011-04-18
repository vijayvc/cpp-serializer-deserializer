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
        archive& operator<<(T& t);
	template<class T>
	archive& operator>>(T &t);
	/*
	{
		s<<t<<" ";
		return *this;
	}
 
	{
		s>>t;
		return *this;
	}
       */
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
	void save_object(T &t);

	template<class T>
	void load_object(T &t);
	/*
	{
		t.serialize(*this);
	}

	template<class T>
	void load_object(T &t)
	{
		t.deserialize(*this);
	}
	*/
};
