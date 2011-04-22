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

		

	archive& operator<<(int& t)
	{
		s<<t<<" ";
		return *this;
	}
 
	archive& operator>>(int &t)
	{
		char ch;
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
		char ch;
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
		char ch;
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
		char ch;
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
		char ch;
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
		char *str = new char [len+2];
		s.getline(str,len+2);
		str[len+2]='\0';
		t=str+1;
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

template <class baseType>
   baseType& archive::base_object(baseType& b)
{

	//(*this)<<b;
	return b;
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
