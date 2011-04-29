#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include<deque>
#include<queue>
#include <forward_list>
#include <stack>

using namespace std;

class Serializer
{
private:
	map<void*,int> ser_map;
	map<int,void*> deser_map; 
protected:
	stringstream s;
	Serializer(const stringstream& input):s(input.str(), stringstream::in)
	{
	}
public:
	void print()
	{
		cout<<"The stream is "<<s.str()<<endl;
	}
	
	template<class T>
	Serializer& save_array(T* ptr, int n)
	{
		int i;
		s<<n<<" ";
		for(i=0;i<n;i++,++ptr)
			(*this)<<*ptr;
		return *this;
	}

	template<class T>
	Serializer& load_array(T* ptr)
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
	Serializer& operator<<(int* t)=delete;
	
	Serializer& operator>>(int* t)=delete;
	
	Serializer& operator<<(const char* t)=delete;
	
	Serializer& operator>>(char* t)=delete;
	
	Serializer& operator<<(float* t)=delete;
	
	Serializer& operator>>(float* t)=delete;

	Serializer& operator<<(double* t)=delete;
	
	Serializer& operator>>(double* t)=delete;
	
	Serializer& operator<<(short* t)=delete;
	
	Serializer& operator>>(short* t)=delete;

	Serializer& operator<<(long double* t)=delete;
	
	Serializer& operator>>(long double* t)=delete;

	template<class T>
	Serializer& operator<<(T * &t)
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
	Serializer& operator>>(T * &t)
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
	
	Serializer& operator<<(int& t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(int &t)
	{
		s>>t;
		return *this;
	}

	Serializer& operator<<(float& t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(float &t)
	{
		s>>t;
		return *this;
	}

	Serializer& operator<<(double &t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(double &t)
	{
		s>>t;
		return *this;
	}

	Serializer& operator<<(char& t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(char &t)
	{
		s>>t;
		return *this;
	}
	
	Serializer& operator<<(bool &t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(bool &t)
	{
		s>>t;
		return *this;
	}

	Serializer& operator<<(short & t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(short &t)
	{
		s>>t;
		return *this;
	}
	
	Serializer& operator<<(long double &t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator>>(long double &t)
	{
		s>>t;
		return *this;
	}

	Serializer& operator<<(const string &t)
	{
		int len=t.length();
		s<<len<<" ";
		for(int i=0;i<len;++i)
			s<<t[i];
		s<<" ";
		return *this;
	}

	Serializer& operator>>(string &t)
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
	Serializer& operator<< (T&t)
	{
		t.serialize(*this);
		return *this;
	}

	template <class T>
	Serializer& operator>> (T&t)
	{
		t.deserialize(*this);
		return *this;
	}
	
	
	// General Serialization/Deserialization
	/*
	template<class T>
	Serializer& operator<<(T& t)
	{
		s<<t<<" ";
		return *this;
	}

	template<class T>
	Serializer& operator>>(T &t)
	{
		s>>t;
		return *this;
	}
	*/
	// Vector Serialization/Deserialize
	template <class T>
	Serializer& operator<<(vector<T> &v );
	
	template <class T>
	Serializer& operator>>(vector<T> &v );
	
	template <class T>
	Serializer& operator<<(deque<T> &v );
	
	template <class T>
	Serializer& operator>>(deque<T> &v );
	
	template <class T>
	Serializer& operator<<(queue<T> q);
	
	template <class T>
	Serializer& operator>>(queue<T> &q);

	template <class T> 
	Serializer& operator<<(priority_queue<T> q );

    template <class T> 
	Serializer& operator>>(priority_queue<T>& q );
	
	template <class baseType>
	baseType& base_object(baseType& b);

	// List Serialization/Deserialize
	template <class T>
	Serializer& operator<<(list<T> &v );
	
	template <class T>
	Serializer& operator>>(list<T> &v );

	template <class T> 
	Serializer& operator<<(forward_list<T> &v );
	
	template <class T> 
	Serializer& operator>>(forward_list<T> &v );

	// Map serialization/Deserialize
	template <class NameType, class ValueType>
	Serializer& operator<<(map<NameType, ValueType> &v );

	/*
	template <class NameType, class ValueType>
	Serializer& operator<<(map<const char*, ValueType> &v );
	*/

	template <class NameType, class ValueType >
	Serializer& operator>>(map<NameType, ValueType> &v );

	// Multi Map serialization/Deserialize
	template <class NameType, class ValueType>
	Serializer& operator<<(multimap<NameType, ValueType> &v );

	template <class NameType, class ValueType >
	Serializer& operator>>(multimap<NameType, ValueType> &v );

	template <class T> Serializer& operator<<(stack<T> v );

	template <class T> Serializer& operator>>(stack<T> &v );
	
	// Named member functions
	Serializer(): s(stringstream::out){}

	template<class T>
	void save_object(T &t)
	{
		//t.serialize(*this);
		(*this)<<t;
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

	const stringstream& get_stream()
	{
		return s;
	}
};

class Deserializer:public Serializer
{
public:
	Deserializer(const stringstream& input):Serializer(input)
	{
	}
	template<class T>
	void load_object(T &t)
	{
		//t.deserialize(*this);
		(*this)>>t;
	}
	template<class T>
	void save_object(T& t) = delete;
};

// Vector Serialization/Deserialize
template <class T> Serializer& Serializer::operator<<(vector<T> &v )
{ 
	s<<v.size()<<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		(*this)<<*i;
	}
	return *this;
}

template <class T> Serializer& Serializer::operator>>(vector<T> &v )
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

// Stack Serialization/Deserialize
template <class T> Serializer& Serializer::operator<<(stack<T> v )
{ 
	vector<T> temp;
	s<<v.size()<<" ";
	while(!v.empty())
	{
		auto beg = temp.begin();
		temp.insert(beg,v.top());
		v.pop();
	}
	for(auto i = temp.begin();i!= temp.end();i++)
		(*this)<<*i;
	//cout<<s.str();
	return *this;
}

template <class T> Serializer& Serializer::operator>>(stack<T> &v )
{ 
	int size ;
	s>> size;

	while(size)
	{
		T val;
		(*this)>> val;
		v.push(val);
		--size;
	}
	return *this;
}

// Priority Queue Serialization/Deserialize
template <class T> Serializer& Serializer::operator<<(priority_queue<T> q )
{ 
	s<<q.size()<<" ";
	while(!q.empty())
	{
		T val = q.top();
		(*this)<<val;
		q.pop();
	}
	//cout<<s.str();
	return *this;
}

template <class T> Serializer& Serializer::operator>>(priority_queue<T> &q )
{ 
	int size ;
	s>> size;

	while(size)
	{
		T val;
		(*this)>> val;
		q.push(val);
		--size;
	}
	return *this;
}

// Deque Serialization/Deserialize

template <class T> Serializer& Serializer::operator<<(deque<T> &d )
{ 
	s<<d.size()<<" ";
	for(auto i = d.begin();i != d.end();i++)
	{
		(*this)<<*i;
	}
	return *this;
}

template <class T> Serializer& Serializer::operator>>(deque<T> &d )
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

template <class T> Serializer& Serializer::operator<<(queue<T> q )
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

template <class T> Serializer& Serializer::operator>>(queue<T> &q)
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
template <class T> Serializer& Serializer::operator<<(list<T> &v )
{ 
	s<<v.size()<<" ";
	for(auto i = v.begin();i != v.end();i++)
	{
		s<< *i<<" ";
	}
	return *this;
}

template <class T> Serializer& Serializer::operator>>(list<T> &v )
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

// Forward_List Serialization/Deserialize
template <class T> Serializer& Serializer::operator<<(forward_list<T> &v )
{ 
	int size = 0;
	vector<int> vec;
	for(auto i = v.begin();i != v.end();i++)
	{
		size++;
		vec.insert(vec.begin(),*i);
	}
	//s<<size<<" ";
	(*this)<<vec;
	return *this;
}

template <class T> Serializer& Serializer::operator>>(forward_list<T> &v )
{ 
	int size ;
	s>> size;

	while(size)
	{
		T val;
		(*this)>> val;
		v.push_front(val);
		--size;
	}
	return *this;
}

template <class baseType>
	baseType& Serializer::base_object(baseType& b)
{

	//(*this)<<b;
	return b;
}

/*
// Map serialization/Deserialize
template <class NameType, class ValueType>
	Serializer& Serializer::operator<<(map<NameType, ValueType> &v )
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
	Serializer& Serializer::operator>>(map<NameType, ValueType> &v )
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
	Serializer& Serializer::operator<<(multimap<NameType, ValueType> &v )
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
	Serializer& Serializer::operator>>(multimap<NameType, ValueType> &v )
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
	void writeMap(T &v, Serializer& ar)
{
	int size = v.size();
	ar << size;
	for(auto i = v.begin();i != v.end();i++)
	{
		ar << (*i).first << (*i).second;
	}
}

template <class NameType, class ValueType>
	Serializer& Serializer::operator<<(map<NameType, ValueType> &v )
{
	//writeMap(v, s);
	writeMap(v, *this);
	return *this;
}

template <class NameType, class ValueType>
	Serializer& Serializer::operator<<(multimap<NameType, ValueType> &v )
{
	//writeMap(v, s);
	writeMap(v, *this);
	return *this;
}

/*
template <class NameType, class ValueType>
	Serializer& Serializer::operator<<(unordered_map<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}

template <class NameType, class ValueType>
	Serializer& Serializer::operator<<(unordered_multimap<NameType, ValueType> &v )
{
	writeMap(v, s);
	return *this;
}
*/

template <class NameType, class ValueType, class T>
	void readMap(T &v, Serializer& ar)
{ 
	int size ;
	ar >> size;
	//std::cout<<s.str()<<endl;
	while(size)
	{
		NameType name;
		ValueType val;
		ar >> name;
		ar >> val;
		v.insert(pair<NameType, ValueType>(name, val));
		//v[name]=val;
		--size;
	}
}

template <class NameType, class ValueType>
	Serializer& Serializer::operator>>(map<NameType, ValueType> &v )
{ 
	//readMap<NameType, ValueType, map<NameType, ValueType> >(v, s);
	readMap<NameType, ValueType, map<NameType, ValueType> >(v, *this);
	return *this;
} 

template <class NameType, class ValueType>
	Serializer& Serializer::operator>>(multimap<NameType, ValueType> &v )
{ 
	//readMap<NameType, ValueType, multimap<NameType, ValueType> >(v, s);
	readMap<NameType, ValueType, multimap<NameType, ValueType> >(v, *this);
	return *this;
}

/*
template <class NameType, class ValueType>
	Serializer& Serializer::operator>>(unordered_map<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_map<NameType, ValueType> >(v, s);
	return *this;
}

template <class NameType, class ValueType>
	Serializer& Serializer::operator>>(unordered_multimap<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_multimap<NameType, ValueType> >(v, s);
	return *this;
}
*/
