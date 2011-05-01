#include "Serializer.h"
#include "test.h"
#include <string>
#include <stack>
#include <fstream>
using namespace std;

void writeToFile(const stringstream& s)
{
	ofstream myfile;
	myfile.open ("example.txt");
	myfile << s.str(); 
	myfile.close();
}

stringstream* readFromFile()
{
	std::ifstream in("example.txt");
	std::stringstream* buffer = new stringstream();
	*buffer << in.rdbuf();
	in.close();
	return buffer;
}

void test_priority_queue()
{
	cout<< "Testing for priorityQueue"<<endl;
	Serializer srz;
	priority_queue<int> q;
	q.push(3);
	q.push(2);
	q.push(3);
	cout<<"Original priorityQueue :"<<endl;
	priority_queue<int>  q1 =q;
	while(!q1.empty())
	{
		cout<<q1.top()<< endl;
		q1.pop();
	}
	//cout << " Serializing priority_queue..."<<endl;
	srz.save_object(q);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
	priority_queue<int> obj2; 
	dz.load_object(obj2);
	//cout << " Deserializing priority_queue..."<<endl;
	
	cout<<"Restored priority_queue :"<<endl;
	q1 = obj2;
	while(!q1.empty())
	{
		cout<<q1.top()<< endl;
		q1.pop();
	}
}

void test_deque()
{
	Serializer srz;
	cout<<"Testing deque"<<endl<<endl;
	cout<<"Data before serialization"<<endl;
	deque<int> d={1,2,3,4,5,6};
	for(auto x=d.begin();x!=d.end();++x)
		cout<<*x<<endl;
	//a<<d;
	srz.save_object(d);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();

	Deserializer dz(*contents);
	deque<int> d1;
	dz.load_object(d1);
	cout<<"Data after deserialization"<<endl;
	for(auto x=d1.begin();x!=d1.end();++x)
		cout<<*x<<endl;

}

void test_queue()
{
	Serializer srz;
	cout<<"Testing queue"<<endl<<endl;
	cout<<"Data before serialization"<<endl;
	queue<int> q;
	int val=1;
	while(val!=7)
		q.push(val++);
	int c=6;
	queue<int> qp=q;
	while(c)
	{
		cout<<qp.front()<<endl;
		qp.pop();
		--c;
	}
	//srz<<q;
	srz.save_object(q);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();

	Deserializer dz(*contents);
	queue<int> q1;
	dz.load_object(q1);
	//a>>q1;
	cout<<"Data after deserialization"<<endl;
	c=6;
	while(c--)
	{
		cout<<q.front()<<endl;
		q.pop();
	}
}



void testMap()
{
	Results obj;
	obj.inflate();
	cout << "Original Object: \n";
	obj.print();

	Serializer ar;
	ar.save_object(obj);
	writeToFile(ar.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
	Results obj2; 
	dz.load_object(obj2);

	cout << "\nRestored Object: \n";
	obj.print();
}

void testNamedMap()
{
	Results obj;
	obj.inflate();
	cout << "Original Object: \n";
	//obj.print();

	Serializer ar;
	ar.save_object(obj, "Results");
	writeToFile(ar.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
	string name = dz.get_name();
	cout << "Name: " << name << endl;
	if (name.compare("Results") == 0)
	{
		Results obj2; 
		dz.load_object(obj2);

		cout << "\nRestored Object: \n";
		obj.print();
	}

}

// this will test custom object pointer save/load
void testList()
{
	Serializer srz;
	node *root=new node(10);
	root->next=new node(45);
	root->next->next=new node(98763);
	root->next->next->next=0;

	cout << "\nOriginal List: \n";
	root->printList();

	srz.save_object(root);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
	node* root1;
	dz.load_object(root1);

	cout << "\nRestored List: \n";
	root1->printList();
}

// to test array of basic types/objects
void testArrays()
{
	Serializer srz;
	int arr[3]={5,1,3};

	cout << "Original: ";
	for(int i=0;i<3;++i)
		cout << arr[i] << ' ';
	cout << endl;

	srz.save_array(arr,3);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
	int sz=dz.get_array_size();
	int *arr1= new int[sz];
	dz.load_array(arr1);
	cout << "Restored: ";
	for(int i=0;i<sz;++i)
		cout << arr1[i] << ' ';
	cout << endl;
}

void test_tree()
{
 	tree t;
 	t.insert(2);
 	t.insert(4);
 	t.insert(7);
 	t.insert(0);
 	t.insert(9);
 	t.insert(3);
 	t.insert(6);
	// createloops
    cout<< "tree with loops"<<endl;
	treenode * tp = t.get_root();
	
	treenode * temp = tp;
	while(tp->right != NULL)
	{
		tp = tp->right;

	}
	tp->right = temp;
	
	while(tp->left != NULL)
	{
		tp = tp->left;

	}
	tp->left = temp;
	
	
	// create loop
	
	cout<< "Original tree"<<endl;
 	t.print();
	Serializer ar;
 	ar.save_object(t);
	writeToFile(ar.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);
 	tree t1;
	dz.load_object(t1);
	cout<< "Resurrected tree"<<endl;
	t1.print();
}

//test for containment
void testContainment()
{
	Serializer srz;
	containment obj;
	obj.inflate();

	cout << "Original Object: ";
	obj.print();
	srz.save_object(obj);
	writeToFile(srz.get_stream());
	
	stringstream* contents = readFromFile();
	Deserializer dz(*contents);

	containment res_obj;
	dz.load_object(res_obj);
	cout << "Restored Object: ";
	res_obj.print();
}

// test for inheritence
void testInheritence()
{
	Serializer ar;
	derived d;
	d.inflate();

	cout << "Original Object: ";
	d.print();
	ar.save_object(d);
	writeToFile(ar.get_stream());
	stringstream* contents = readFromFile();
	ar.print();
	Deserializer dz(*contents);	
	derived d1;
	dz.load_object(d1);
	cout << "Restored Object: ";
	d1.print();
}
void test_list(int num)
{
	Serializer ar;
	listnode *root=new listnode(1);
	for(int i=2;i<num;++i)
	{
		root->insert(i);
	}
	cout << "Original Object: ";
	root->print();
	ar.save_object(root);
	//ar.print();
	writeToFile(ar.get_stream());
	stringstream* contents = readFromFile();
	//ar.print();
	Deserializer dz(*contents);	
	listnode* root1;
	dz.load_object(root1);
	cout << "Restored Object: ";
	root1->print();
}
int main()
{
	//test_tree();
	//test_priority_queue();
	//	testMap();
	//testNamedMap();
	//	testList();

	//testContainment();
	//testInheritence();
	//	testArrays();
	//test_queue();
	//test_deque();
	//test_forward_list();
	//test_loop();
	//test_stack();
	for (int i=0; i < 10; i++)
		test_list(10);
	return 0;
}

/* test for forward_list */
void test_forward_list()
{
	Serializer srz;

	cout <<"Testing for Forward_list\n";

	forward_list<int> vi;
	vi.push_front(2);
	vi.push_front(5);
	srz.save_object(vi);

	writeToFile(srz.get_stream());
	stringstream* contents = readFromFile();
	cout << "Original FORWARD_LIST\n";
	for(auto i = vi.begin();i!= vi.end();i++)
	{
		std::cout<<*i<<endl;
	}

	forward_list<int> rl;
	Deserializer dz(*contents);
	dz.load_object(rl);
	cout<<"Restored list";
	for(auto i = rl.begin();i!= rl.end();i++)
	{
		cout<<*i<<endl;
	}
}

void test_loop()
{
	Serializer srz;
	node *root=new node();
	root->value=10;
	root->next=new node();
	root->next->value=20;
	root->next->next=root;

	srz.save_object(root);
	srz.print();

	writeToFile(srz.get_stream());
	stringstream* contents = readFromFile();

	Deserializer dz(*contents);
	node* root1;
	dz.load_object(root1);
	cout<<root1->value;
	cout<<root1->next->value;
	cout<<root1->next->next->value;
}

void test_stack()
{
	cout<< "Testing for Stack"<<endl;
	Serializer srz;
	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	cout<<"Original Stack :"<<endl;
	stack<int>  s1 = s;
	while(!s1.empty())
	{
		cout<<s1.top()<< endl;
		s1.pop();
	}
	//cout << " Serializing stack..."<<endl;
	srz.save_object(s);

	writeToFile(srz.get_stream());
	stringstream* contents = readFromFile();

	stack<int> s_restore;
	Deserializer dz(*contents);
	//a>>s_restore;
	//cout << " Deserializing stack..."<<endl;
	
	cout<<"Restored Stack :"<<endl;
	while(!s_restore.empty())
	{
		cout<<s_restore.top()<< endl;
		s_restore.pop();
	}
}
