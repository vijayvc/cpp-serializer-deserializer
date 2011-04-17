#include <sstream>
#include<cstring>
#include <iostream>
#include <string>

using namespace std;
class archive
{
	stringstream s;
	
public:
	template<class T>
  archive& operator<<(T& t)
	{
		//std::cout<< "helo";
		//std::cout<< " "<<t;

		s<<t<<" ";
		//std::cout<<s.str();
		return *this;
	}

	template<class T>
	archive& operator>>(T &t)
	{
		char ch;
		s>>t;
		return *this;
	}
	archive(): s(stringstream::in | stringstream::out){}
	template<class T>
	void save_object(T &t)
	{
	   t.serialize(*this);
	}
	template<class T>
	void load_object(T &t)
	{
		t.deserialize(s);
	}
};
class Student
{
	friend class archive;
public:
	
	char  gender;
	int age;
    double weight;
	
	void serialize(archive  &ar)
	{
		ar<<gender<<age<<weight;	
	}
	void deserialize(istream &ar)
	{
		ar>>gender>>age>>weight;
	}
};


int main()
{

	Student one;
	one.gender = 'F';
	one.age = 16;
	one.weight=17.5;

	//ofstream ofs("fifthgrade.ros");
   	//serializer srlz(ofs);
	//ofs.write((char *)&one, sizeof(one));
    archive a;
	a.save_object(one);
	Student two;
	a.load_object(two);
	cout<<two.gender<<" ";
	cout<<two.age<<" "<<two.weight;
	return 0;
}
/*	
	ifstream ifs("fifthgrade.ros");
	serializer srlz(ifs);
	ifs.read((char *)&two, sizeof(two));
C
	cout << "Student Information\n";

	cout << "Student Name: " << two.FullName << endl;

	cout << "Address:      " << two.CompleteAddress << endl;

	if( two.Gender == 'f' || two.Gender == 'F' )

		cout << "Gender:       Female" << endl;

	else if( two.Gender == 'm' || two.Gender == 'M' )

		cout << "Gender:       Male" << endl;

	else

		cout << "Gender:       Unknown" << endl;

	cout << "Age:          " << two.Age << endl;

	if( two.LivesInASingleParentHome == true )

		cout << "Lives in a single parent home" << endl;

	else

		cout << "Doesn't live in a single parent home" << endl;

	

	cout << "\n";


	return 0;
*/
 /*{
}
class archive
{
	unsigned char *buffer;
	char* curr_ptr;
	int total_size;
	char* read_ptr;
	archive()
	{
	buffer=new char(256);
	}
	//ostream os;
	//istream is;
	template<class T>
	void operator<<(T t)
	{
		//reallocation 
		if((curr_ptr - buffer + sizeof(t)) > total_size)
		{
			total_size=total_size*2;
			unsigned char* tmp=new char(total_size);
			memcpy(tmp,buffer,total_size);
			int index = curr_ptr-buffer;
			buffer=tmp;
			curr_ptr=buffer +index;
		}
		*((T*)curr_ptr)=t;
		((T*)curr_ptr)++;
	}
	template<class T>
	void operator<<(T &t)
	{
		read_ptr=
	}
}
*/
