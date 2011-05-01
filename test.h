#include <typeinfo>

class listnode{
 	int data;
	listnode *next;
	public:	
	void serialize(Serializer &s)
	{
		s<<data<<next;
	}
	void deserialize(Deserializer &d)
	{
		d>>data>>next;
	}
	
	/*
	static listnode* allocate_memory()
	{
		listnode* temp=new listnode();
		return temp;
	}
	*/

	public:
	listnode(int x):data(x),next(NULL){}
	listnode(){}
	void insert(int val)
	{
		listnode* newnode=new listnode(val);
		listnode *root=this;
		if(root!=NULL)
		{
			while(root->next!=NULL)
			{
				root=root->next;
			}
		}
		root->next=newnode;
	}
	
	void print()
	{
		listnode *root=this;
		while(root!=NULL)
		{
			std::cout<<root->data<<" ";
			root=root->next;
		}
		cout << endl;
	}
};

struct treenode{
	 int data;
     treenode *left;
     treenode *right;
   
	 treenode ()
	 {
		 data =0;
		 left =NULL;
		 right = NULL;
	 }
	treenode (int x, treenode *l, treenode *r)
	 {
		 data =x;
		 left =l;
		 right = r;
	 }

	 Serializer& serialize(Serializer &ar)
	 {
		ar<<data<<left<<right;
		return ar;
	 }

	 Serializer & deserialize(Deserializer & ar)
	 {
		 ar>>data>>left>>right;
	     return ar;
	 }
	 
	static treenode * allocate_memory()
	{

		treenode *ptree = new treenode();
		return ptree;
	}
};

class tree
{
	public:
	treenode * p_tree;	
	int count;


	friend class Serializer;
	friend class Deserializer;
	tree()
	{
		count =0;
        p_tree = NULL;
	}

	treenode * ins(treenode *ptree,int num)
	{
		if (ptree == NULL)
		{
			ptree = new treenode(num,NULL,NULL);
			count++;

		}
		else
		{

		  if(count%2==0)
		    	ptree->left=ins(ptree->left,num);
		  else
		    	ptree->right=ins(ptree->right,num);
		}
		return(ptree);
	}

	void insert(int val)
	{
		p_tree = ins(p_tree,val);
	}
    treenode * get_root()
	{
         return p_tree;
	}
   

   void serialize(Serializer &ar)
   {
	   ar<<p_tree<<count;
	   //return ar;

   }
  Serializer& deserialize(Deserializer &ar)
   {
	   ar>>p_tree>>count;
	   return ar;

   }
    void show(treenode *ptree,int k)
	{   
		k++;
		if (k >= count)
			return;

		if (ptree == NULL)
		{
			return;
		}
		else
		{
			cout<<ptree->data<<endl;
			show(ptree->left,k);
			show(ptree->right,k);
		}
		return;
	}

	void print()
	{   int k = 0;
		show(p_tree,k);
	    k =0;
	}
};


class node
{
	friend class Serializer;
	friend class Deserializer;
	Serializer& serialize(Serializer &ar)
	{
		ar<<value<<next;
	}
	Serializer& deserialize(Deserializer &ar)
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
	friend class Deserializer;
public:
	int a;
	
	void serialize(Serializer  &ar)
	{
		ar<<a;
	}
	void deserialize(Deserializer &ar)
	{
		ar>>a;
	}
};

class derived:public base
{
	friend class Serializer;
	friend class Deserializer;
	char c;
	Serializer& serialize(Serializer &ar)
	{
		//ar<<(ar.base_object<base>(*this))<<c;
		ar<<*(static_cast<base*>(this))<<c;
	}

	Serializer& deserialize(Deserializer &ar)
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
		cout << a << ' ' << c << endl;
	}
};

class containment
{
	friend class Serializer;
	friend class Deserializer;
private:
	base b;
	char c;
	Serializer& serialize(Serializer  &ar)
	{
		ar<<b<<c;
		return ar;
	}
	Serializer& deserialize(Deserializer &ar)
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
	friend class Deserializer;
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
	void deserialize(Deserializer &ar)
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
