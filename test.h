class node
{
	friend class archive;
	archive& serialize(archive &ar)
	{
		ar<<value<<next;
	}
	archive& deserialize(archive &ar)
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
	friend class archive;
public:
	int a;
	
	archive& serialize(archive  &ar)
	{
		ar<<a;
		return ar;
	}
	archive& deserialize(archive &ar)
	{
		return (ar>>a);
	}
};

class derived:public base
{
	friend class archive;
	char c;
	archive& serialize(archive &ar)
	{
		ar<<(ar.base_object<base>(*this))<<c;
	}

	archive& deserialize(archive &ar)
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
	friend class archive;
private:
	base b;
	char c;
	archive& serialize(archive  &ar)
	{
		ar<<b<<c;
		return ar;
	}
	archive& deserialize(archive &ar)
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
	friend class archive;
public:
	map<string, int> marks; // name->mark
	multimap<string, int> mmarks; // name-> {set of marks}
	void inflate()
	{
		marks["vijay"] = 28;
		marks["venky"] = 31;
		marks["john"] = 31;
		marks["abcd"] = 30;
		marks["efgh"] = 31;
		
		/*
		marks[string("first name")] = 31;
		marks[string("second sname")] = 28;
		marks[string("third tname")] = 31;
		marks[string("fourth 4name")] = 30;
		marks[string("fifth f name")] = 31;
		*/

		mmarks.insert(pair<string, int>("a", 1));
		mmarks.insert(pair<string, int>("c", 2));
		mmarks.insert(pair<string, int>("b", 3));
		mmarks.insert(pair<string, int>("b", 4));
		mmarks.insert(pair<string, int>("a", 5));
		mmarks.insert(pair<string, int>("b", 6));
	}
	void serialize(archive  &ar)
	{
		ar<<marks;	
	}
	void deserialize(archive &ar)
	{
		ar>>mmarks;
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
