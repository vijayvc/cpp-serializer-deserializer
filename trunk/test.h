#include <typeinfo>
class node
{
	friend class Serializer;
	Serializer& serialize(Serializer &ar)
	{
		ar<<value<<next;
	}
	Serializer& deserialize(Serializer &ar)
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
	node(int val)
	{
		value = val;
		next = 0;
	}
	node() {}
	void printList()
	{
		cout << "List: \n";
		node* temp = this;
		while(temp)
		{
			cout << temp->value << endl;
			temp = temp->next;
		}
	}
};

class base
{
	friend class Serializer;
public:
	int a;
	
	Serializer& serialize(Serializer  &ar)
	{
		ar<<a;
		return ar;
	}
	Serializer& deserialize(Serializer &ar)
	{
		return (ar>>a);
	}
};

class derived:public base
{
	friend class Serializer;
	char c;
	Serializer& serialize(Serializer &ar)
	{
		ar<<(ar.base_object<base>(*this))<<c;
	}

	Serializer& deserialize(Serializer &ar)
	{
		ar>>(ar.base_object<base>(*this))>>c;
	}
public:
	void inflate()
	{
		c = 'D';
		a = 456809;
	}
	void print()
	{
		cout << "Contents: ";
		cout << c << ' ' << a << endl;
	}
};

class containment
{
	friend class Serializer;
private:
	base b;
	char c;
	Serializer& serialize(Serializer  &ar)
	{
		ar<<b<<c;
		return ar;
	}
	Serializer& deserialize(Serializer &ar)
	{
		ar>>b>>c;
		return ar;
	}
public:
	void inflate()
	{
		c = 'z';
		b.a = 4529;
	}
	void print()
	{
		cout << "Contents: ";
		cout << b.a << ' ' << c << endl;
	}
};

class Results 
{
	friend class Serializer;
public:
	map<string, int> marks; // name->mark
	multimap<string, int> mmarks; // name-> {set of marks}
	void inflate()
	{
		/*
		marks["vijay"] = 28;
		marks["venky"] = 31;
		marks["john"] = 31;
		marks["abcd"] = 30;
		marks["efgh"] = 31;
		*/
		//cout << "Types: \n";
		//cout<< typeid((*(marks.begin())).first).name() << endl;
		//cout<< typeid((*(marks.begin())).second).name() << endl;
		
		marks[string("first name")] = 31;
		marks[string("second sname")] = 28;
		marks[string("third tname")] = 31;
		marks[string("fourth 4name")] = 30;
		marks[string("fifth f name")] = 31;
		

		mmarks.insert(pair<string, int>("a", 1));
		mmarks.insert(pair<string, int>("c", 2));
		mmarks.insert(pair<string, int>("b", 3));
		mmarks.insert(pair<string, int>("b", 4));
		mmarks.insert(pair<string, int>("a", 5));
		mmarks.insert(pair<string, int>("b", 6));
	}
	void serialize(Serializer  &ar)
	{
		//ar<<string("abcd");
		ar<<marks;	
		ar<<mmarks;	
	}
	void deserialize(Serializer &ar)
	{
		ar>>marks;
		ar>>mmarks;
		//string s;
		//ar>>s;
	}
	void print()
	{
		cout << "Marks: \n";
		for (auto iter = marks.begin(); iter != marks.end(); iter++)
		{
			cout << (*iter).first << " " << (*iter).second << endl;
		}
		cout << "\nMMarks <multimap>: \n";
		for (auto iter = marks.begin(); iter != marks.end(); iter++)
		{
			cout << (*iter).first << " " << (*iter).second << endl;
		}
	}
};
