#include "archive.hpp"

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
template<class T>
void archive::save_object(T &t)
{
	t.serialize(*this);
}

template<class T>
void archive::load_object(T &t)
{
	t.deserialize(*this);
}
template<class T>
archive& archive::operator<<(T& t)
{
	s<<t<<" ";
	return *this;
}

template<class T>
archive& archive::operator>>(T &t)
{
	s>>t;
	return *this;
}

/*int main()
{
	return 0;
}
*/
#if 0
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
#endif 
