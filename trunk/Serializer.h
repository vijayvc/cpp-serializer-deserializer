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

	// Serialize/Deserialize pointers
	Serializer& operator<<(int* t)=delete;
	
	
	Serializer& operator<<(const char*& t)
	{
		int length=0;
		const char *temp=t;
		while(*t++)
			length++;
		s<<length<<" ";
		t=temp;
		while(*t)
			s<<*t++<<" ";
	}
	
	
	Serializer& operator<<(float* t)=delete;
	

	Serializer& operator<<(double* t)=delete;
	
	
	Serializer& operator<<(short* t)=delete;
	

	Serializer& operator<<(long double* t)=delete;

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

	Serializer& operator<<(int& t)
	{
		s<<t<<" ";
		return *this;
	}

	Serializer& operator<<(float& t)
	{
		s<<t<<" ";
		return *this;
	}
	Serializer& operator<<(double &t)
	{
		s<<t<<" ";
		return *this;
	}
	Serializer& operator<<(char& t)
	{
		s<<t<<" ";
		return *this;
	}
	
	Serializer& operator<<(bool &t)
	{
		s<<t<<" ";
		return *this;
	}


	Serializer& operator<<(short & t)
	{
		s<<t<<" ";
		return *this;
	}


	Serializer& operator<<(long &t)
	{
		s<<t<<" ";
		return *this;
	}


	Serializer& operator<<(long double &t)
	{
		s<<t<<" ";
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

	Serializer& operator<<(string &t)
	{
		int len=t.length();
		s<<len<<" ";
		for(int i=0;i<len;++i)
			s<<t[i];
		s<<" ";
		return *this;
	}
  

	template <class T>
	Serializer& operator<< (T&t)
	{
		t.serialize(*this);
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
	Serializer& operator<<(deque<T> &v );
	
	template <class T>
	Serializer& operator<<(queue<T> q);
	
	template <class T> 
	Serializer& operator<<(priority_queue<T> q );

	template <class baseType>
	baseType& base_object(baseType& b);

	// List Serialization/Deserialize
	template <class T>
	Serializer& operator<<(list<T> &v );

	template <class T> 
	Serializer& operator<<(forward_list<T> &v );
	
	// Map serialization/Deserialize
	template <class NameType, class ValueType>
	Serializer& operator<<(map<NameType, ValueType> &v );

	/*
	template <class NameType, class ValueType>
	Serializer& operator<<(map<const char*, ValueType> &v );
	*/

	// Multi Map serialization/Deserialize
	template <class NameType, class ValueType>
	Serializer& operator<<(multimap<NameType, ValueType> &v );

	template <class T> Serializer& operator<<(stack<T> v );

		// Named member functions
	Serializer(): s(stringstream::out){}

	template<class T>
	void save_object(T &t, const string name="dummy")
	{
		//t.serialize(*this);
		s<<name<<' ';
		(*this)<<t;
	}


	template<class T>
	void save_object(T*& t, const string name="dummy")
	{
		s<<name<<' ';
		(*this)<<t;
	}

	const stringstream& get_stream()
	{
		return s;
	}

};

class Deserializer:public Serializer
{

	template <class Type>
	class TypeHasAllocateMem
	{
	// This type won't compile if the second template parameter isn't of type T,
	// so I can put a function pointer type in the first parameter and the function
	// itself in the second thus checking that the function has a specific signature.
	template <typename T, T> struct TypeCheck;

	typedef char Yes;
	typedef long No;

	// A helper struct to hold the declaration of the function pointer.
	// Change it if the function signature changes.
	template <typename T> struct AllocateMem
	{
		typedef T*(*fptr)();
	};

	template <typename T> static Yes HasAllocateMem(TypeCheck< typename AllocateMem<T>::fptr, T::allocate_memory >*);
	template <typename T> static No  HasAllocateMem(...);

	public:
		static bool const value = (sizeof(HasAllocateMem<Type>(0)) == sizeof(Yes));
	};

	template <class T, int size>
	class Select{};

	template<class T> 
	class Select<T,1> 
	{
		public:
		static T* f() { 
		return (T::allocate_memory()); 
		}
	};

	template<class T> 
	class Select<T,0> {
		public:
		static T* f() { 
			return (new T()); }
	};

	template <bool b, class T>
	T* alloc()
	{
		return (Select<T,b>::f()); 
	}
	
	bool retName;
	map<int,void*> deser_map; 

public:
	
	Deserializer(const stringstream& input):Serializer(input),retName(false)
	{
	}
	template<class T>
	void load_object(T &t)
	{
		if (! retName)
		{
			string str;
			s >> str;
		}
		(*this)>>t;
	}
	
	template<class T>
	void load_object(T*& t)
	{
		if (! retName)
		{
			string str;
			s >> str;
		}
		(*this)>>t;
	}

	int get_array_size()
	{
		int pos=s.tellg();
		int len;
		s>>len;
		s.seekg(pos, ios::beg);
		return len;
	}

	template<class T>
	void load_array(T* ptr)
	{
		int len;
		s>>len;
		for(int i=0;i<len;++i,++ptr)
			(*this)>>*ptr;
	}

	template<class T>
	void save_object(T& t) = delete;

	template<class T>
	void save_object(T *t) = delete;

	const string get_name()
	{
		retName = true;
		string str;
		s>>str;
		return str;
	}

	template <class T>
	Deserializer& operator>> (T&t)
	{
		t.deserialize(*this);
		return *this;
	}

	Deserializer& operator>>(int* t)=delete;
	//Deserializer& operator>>(char* t)=delete;
	Deserializer& operator>>(float* t)=delete;
	Deserializer& operator>>(double* t)=delete;
	Deserializer& operator>>(short* t)=delete;
	Deserializer& operator>>(long double* t)=delete;

	Deserializer& operator>>(char *& t)
	{
		char *p;
		int n;
		s>>n;
		p=new char[n+1];
		char *temp=p;
		for(int i=1;i<=n;++i)
		{
			s>>(*p++);
		}
		*p='\0';
		t=temp;
	}
	/*
	template <bool, class T>
	//template <>
	T* allocateObj()//<true, class T>()
	{
		return T::allocate_memory();
	}

	template <bool, class T>
	//template <>
	T* allocateObj<false, class T>()
	{
		return new T();
	}
	*/

	template<class T>
	Deserializer& operator>>(T * &t)
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
			T *p=alloc<TypeHasAllocateMem<T>::value, T>();
			deser_map[n]=p;
			t=p;
			(*this)>>*p;
		}
		return (*this);
	}
	inline Deserializer& operator>>(int &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(float &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(double &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(char &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(bool &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(short &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(long &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(long double &t)
	{
		s>>t;
		return *this;
	}
	Deserializer& operator>>(string &t)
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
	Deserializer& operator>>(vector<T> &v );
	
	template <class T>
	Deserializer& operator>>(deque<T> &v );
	
	template <class T>
	Deserializer& operator>>(queue<T> &q);

    template <class T> 
	Deserializer& operator>>(priority_queue<T>& q );
	
	template <class T>
	Deserializer& operator>>(list<T> &v );

	template <class T> 
	Deserializer& operator>>(forward_list<T> &v );

	template <class NameType, class ValueType >
	Deserializer& operator>>(map<NameType, ValueType> &v );

	template <class NameType, class ValueType >
	Deserializer& operator>>(multimap<NameType, ValueType> &v );

	template <class T> Deserializer& operator>>(stack<T> &v );
	

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

template <class T> Deserializer& Deserializer::operator>>(vector<T> &v )
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

template <class T> Deserializer& Deserializer::operator>>(stack<T> &v )
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

template <class T> Deserializer& Deserializer::operator>>(priority_queue<T> &q )
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

template <class T> Deserializer& Deserializer::operator>>(deque<T> &d )
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

template <class T> Deserializer& Deserializer::operator>>(queue<T> &q)
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

template <class T> Deserializer& Deserializer::operator>>(list<T> &v )
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

template <class T> Deserializer& Deserializer::operator>>(forward_list<T> &v )
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
	Deserializer& Deserializer::operator>>(map<NameType, ValueType> &v )
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
	Deserializer& Deserializer::operator>>(multimap<NameType, ValueType> &v )
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
	void readMap(T &v, Deserializer& ar)
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
	Deserializer& Deserializer::operator>>(map<NameType, ValueType> &v )
{ 
	//readMap<NameType, ValueType, map<NameType, ValueType> >(v, s);
	readMap<NameType, ValueType, map<NameType, ValueType> >(v, *this);
	return *this;
} 

template <class NameType, class ValueType>
	Deserializer& Deserializer::operator>>(multimap<NameType, ValueType> &v )
{ 
	//readMap<NameType, ValueType, multimap<NameType, ValueType> >(v, s);
	readMap<NameType, ValueType, multimap<NameType, ValueType> >(v, *this);
	return *this;
}

/*
template <class NameType, class ValueType>
	Deserializer& Deserializer::operator>>(unordered_map<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_map<NameType, ValueType> >(v, s);
	return *this;
}

template <class NameType, class ValueType>
	Deserializer& Deserializer::operator>>(unordered_multimap<NameType, ValueType> &v )
{ 
	readMap<NameType, ValueType, unordered_multimap<NameType, ValueType> >(v, s);
	return *this;
}
*/
