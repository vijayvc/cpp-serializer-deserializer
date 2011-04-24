#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include<deque>
#include<queue>

using namespace std;

class archive
{
	stringstream s;
	map<void*,int> ser_map;
	map<int,void*> deser_map; 
public:
	void print()
	{
		cout<<"The stream is "<<s.str()<<endl;
	}
	
	template<class T>
	archive& save_array(T* ptr, int n)
	{
		int i;
		s<<n<<" ";
		for(i=0;i<n;i++,++ptr)
			(*this)<<*ptr;
		return *this;
	}
	template<class T>
	archive& load_array(T* ptr)
	{
		int len;
		s>>len;
		for(int i=0;i<len;++i,++ptr)
			(*this)>>*ptr;
		return *this;
	}
	int get_array_size()
	{
		int pos=s.tellg();
		int len;
		s>>len;
		s.seekg(pos, ios::beg);
		return len;
	}

	// Serialize/Deserialize pointers
	archive& operator<<(int* t)=delete;
	
	archive& operator>>(int* t)=delete;
	
	archive& operator<<(char* t)=delete;
	
	archive& operator>>(char* t)=delete;
	
	archive& operator<<(float* t)=delete;
	
	archive& operator>>(float* t)=delete;

	archive& operator<<(double* t)=delete;
	
	archive& operator>>(double* t)=delete;
	
	archive& operator<<(short* t)=delete;
	
	archive& operator>>(short* t)=delete;

	archive& operator<<(long double* t)=delete;
	
	archive& operator>>(long double* t)=delete;

	template<class T>
	archive& operator<<(T * &t)
	{
		if(t==NULL)
		{
			s<<0<<" ";
			return *this;
		}
		if(ser_map.find(t)!=ser_map.end())
		{
			s<<ser_map[t]<<" ";
		}
		else
		{
			unsigned n=ser_map.size()+1;
			ser_map[t]=n;
			s<<ser_map[t]<<" ";
			(*t).serialize(*this);
		}
		return *this;
	}

	template<class T>
	archive& operator>>(T * &t)
	{
		int n;
		s>>n;
		if(n==0)
		{
			t=NULL;
		}
		else if(deser_map.find(n) != deser_map.end())
		{
			t=(T*)deser_map[n];
		}
		else
		{
			T *p=T::allocate_memory();
			deser_map[n]=p;
			t=p;
			(*this)>>*p;
		}
		return (*this);
	}
	
	archive& operator<<(int& t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(int &t)
	{
		s>>t;
		return *this;
	}

	archive& operator<<(float& t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(float &t)
	{
		s>>t;
		return *this;
	}

	archive& operator<<(double &t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(double &t)
	{
		s>>t;
		return *this;
	}

	archive& operator<<(char& t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(char &t)
	{
		s>>t;
		return *this;
	}
	
	archive& operator<<(bool &t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(bool &t)
	{
		s>>t;
		return *this;
	}

	archive& operator<<(short & t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(short &t)
	{
		s>>t;
		return *this;
	}
	
	archive& operator<<(long double &t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(long double &t)
	{
		s>>t;
		return *this;
	}

	archive& operator<<(string &t)
	{
		int len=t.length();
		s<<len<<" ";
		for(int i=0;i<len;++i)
			s<<t[i];
		s<<" ";
		return *this;
	}

	archive& operator>>(string &t)
	{
		int len;
		s>>len;
		char *str = new char [1+len+1];
		memset(str, 0, len+2);
		s.read(str, len+1);
		t=str;
		return *this;
	}  
	
	template <class T>
	archive& operator<< (T&t)
	{
		t.serialize(*this);
		return *this;
	}

	template <class T>
	archive& operator>> (T&t)
	{
		t.deserialize(*this);
		return *this;
	}
	
	
	// General Serialization/Deserialization
	/*
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
	*/
	// Vector Serialization/Deserialize
	template <class T>
	archive& operator<<(vector<T> &v );
	
	template <class T>
	archive& operator>>(vector<T> &v );
	
	template <class T>
	archive& operator<<(deque<T> &v );
	
	template <class T>
	archive& operator>>(deque<T> &v );
	
	template <class T>
	archive& operator<<(queue<T> q);
	
	template <class T>
	archive& operator>>(queue<T> &q);

	
	template <class baseType>
	baseType& base_object(baseType& b);

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

	// Multi Map serialization/Deserialize
	template <class NameType, class ValueType>
	archive& operator<<(multimap<NameType, ValueType> &v );

	template <class NameType, class ValueType >
	archive& operator>>(multimap<NameType, ValueType> &v );

	// Named member functions
	archive(): s(stringstream::in | stringstream::out){}

	template<class T>
	void save_object(T &t)
	{
		//t.serialize(*this);
		(*this)<<t;
	}

	template<class T>
	void load_object(T &t)
	{
		//t.deserialize(*this);
		(*this)>>t;
	}
	
	template<class T>
	void save_object(T *t)
	{
		(*this)<<t;
	}

	template<class T>
	void load_object(T*& t)
	{
		(*this)>>t;
	}
};

// Vector Serialization/Deserialize
template <class T> archive& archive::operator<<(vector<T> &v )
{ 
	s<<v.size()<<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		(*this)<<*i;
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
		(*this)>> val;
		v.push_back(val);
		--size;
	}
	return *this;
}

// Deque Serialization/Deserialize

template <class T> archive& archive::operator<<(deque<T> &d )
{ 
	s<<d.size()<<" ";
	for(auto i = d.begin();i != d.end();i++)
	{
		(*this)<<*i;
	}
	return *this;
}

template <class T> archive& archive::operator>>(deque<T> &d )
{ 
	int size ;
	s>> size;

	while(size)
	{
		T val;
		(*this)>> val;
		d.push_back(val);
		--size;
	}
	return *this;
}

// Queue Serialization/Deserialize

template <class T> archive& archive::operator<<(queue<T> q )
{ 
	s<<q.size()<<" ";
	int size=q.size();
	while(size--)
	{
		(*this)<<q.front();
		q.pop();
	}
	return *this;
}

template <class T> archive& archive::operator>>(queue<T> &q)
{ 
	int size ;
	s>> size;

	while(size--)
	{
		T val;
		(*this)>> val;
		q.push(val);
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

template <class baseType>
	baseType& archive::base_object(baseType& b)
{

	//(*this)<<b;
	return b;
}

/*
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

template <class NameType, class ValueType>
	archive& archive::operator>>(map<NameType, ValueType> &v )
{ 
	int size ;
	s >> size;
//	std::cout<<s.str().length();
	while(size)
	{
		NameType name;
		ValueType val;
		s >> name;
		s >> val;
		v.insert(pair<NameType, ValueType>(name, val));
		//v[name]=val;
		--size;
	}
	return *this;
}

// Multi Map serialization/Deserialize
template <class NameType, class ValueType>
	archive& archive::operator<<(multimap<NameType, ValueType> &v )
{ 
	s<< v.size() <<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		s << (*i).first << " " << (*i).second << " ";
		//s<< *i<<" ";
	}
	return *this;
}

template <class NameType, class ValueType>
	archive& archive::operator>>(multimap<NameType, ValueType> &v )
{ 
	int size ;
	s >> size;
	std::cout<<s.str().length();
	while(size)
	{
		NameType name;
		ValueType val;
		s >> name;
		s >> val;
		v.insert(pair<NameType, ValueType>(name, val));
		//v[name]=val;
		--size;
	}
	return *this;
}
*/

template <class T>
	void writeMap(T &v, stringstream& s)
{
	s<< v.size() <<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		s << (*i).first << " " << (*i).second << " ";
	}
}

template <class NameType, class ValueType>
	archive& archive::operator<<(map<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}

template <class NameType, class ValueType>
	archive& archive::operator<<(multimap<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}

/*
template <class NameType, class ValueType>
	archive& archive::operator<<(unordered_map<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}

template <class NameType, class ValueType>
	archive& archive::operator<<(unordered_multimap<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}
*/

template <class NameType, class ValueType, class T>
	void readMap(T &v, stringstream& s )
{ 
	int size ;
	s >> size;
	//std::cout<<s.str()<<endl;
	while(size)
	{
		NameType name;
		ValueType val;
		s >> name;
		s >> val;
		v.insert(pair<NameType, ValueType>(name, val));
		//v[name]=val;
		--size;
	}
}

template <class NameType, class ValueType>
	archive& archive::operator>>(map<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, map<NameType, ValueType> >(v, s);
	return *this;
} 

template <class NameType, class ValueType>
	archive& archive::operator>>(multimap<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, multimap<NameType, ValueType> >(v, s);
	return *this;
}

/*
template <class NameType, class ValueType>
	archive& archive::operator>>(unordered_map<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_map<NameType, ValueType> >(v, s);
	return *this;
}

template <class NameType, class ValueType>
	archive& archive::operator>>(unordered_multimap<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_multimap<NameType, ValueType> >(v, s);
	return *this;
}
*/
