#include "archive.h"
#include "test.h"
#include <string>
using namespace std;

void testMap()
{
	Results obj;
	obj.inflate();
	cout << "Original Object: \n";
	obj.print();

	archive ar;
	ar.save_object(obj);
	
	Results obj2; 
	ar.load_object(obj2);

	cout << "\nRestored Object: \n";
	obj.print();
}

// this will test custom object pointer save/load
void testList()
{
	archive a;
	node *root=new node(10);
	root->next=new node(45);
	root->next->next=new node(98763);
	root->next->next->next=0;

	cout << "\nOriginal List: \n";
	root->printList();

	a.save_object(root);
	//a.print();

	node* root1;
	a.load_object(root1);

	cout << "\nRestored List: \n";
	root1->printList();
}

// to test array of basic types/objects
void testArrays()
{
	archive a;
	int arr[3]={5,1,3};

	cout << "Original: ";
	for(int i=0;i<3;++i)
		cout << arr[i] << ' ';
	cout << endl;

	a.save_array(arr,3);
	//a.print();

	int sz=a.get_array_size();
	int *arr1= new int[sz];
	a.load_array(arr1);
	cout << "Restored: ";
	for(int i=0;i<sz;++i)
		cout << arr1[i] << ' ';
	cout << endl;
}

//test for containment
void testContainment()
{
	archive a;
	containment obj;
	obj.inflate();

	cout << "Original Object: ";
	obj.print();
	a.save_object(obj);

	containment res_obj;
	a.load_object(res_obj);
	cout << "Restored Object: ";
	res_obj.print();
}

// test for inheritence
void testInheritence()
{
	archive ar;
	derived d;
	d.inflate();

	cout << "Original Object: ";
	d.print();
	ar.save_object(d);

	derived d1;
	ar.load_object(d1);
	cout << "Restored Object: ";
	d1.print();
}

int main()
{
	testMap();
	//testList();
	//testContainment();
	//testInheritence();
	//testArrays();

	return 0;
}
