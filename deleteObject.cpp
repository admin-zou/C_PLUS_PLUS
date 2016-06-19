//这里主要说明了一个问题，就是子类的析构函数不会被调用的情况
#include <iostream>
using namespace std;

class A
{
public:
	A(int a = 0)
		:_a(a)
	{}
	~A()
	{
		cout << "~A" << endl;
	}
protected:
	int _a;
};

class B :public A
{
public:
	B(int a = 0, int b = 0)
		: A(a)
		, _b(b)
	{}
	~B()
	{
		cout << "B" << endl;
	}
protected:
	int _b;
};

int main()
{
	/*父类指针指指向子类new出来的对象*/
	A* base = new B;
	
	/* delete的时候，只会调用父类的析构函数，子类的析构函数不会调用，这很容易造成问题，
	若子类中有new出来的空间，那么就会导致类存泄露 */
	delete base; 

	return 0;
}
