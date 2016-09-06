#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

/*--------------------------------------------------*/
		     //只在堆上生成类的对象
class A
{	//只在堆上创建对象，此方法无法继承
public:
	A()
	{
		cout << "A()" << endl;
	}
	void Destroy()
	{
		delete this;
	}
private:
	~A()
	{
		cout << "~A()" << endl;
	}
};
void Test1()
{
	//A a;
	A *p = new A();
	p->Destroy();
}


class B
{	//只在堆上创建对象，声明为protected的无法继承
public:
	static B* Create()
	{
		return new B();
	}
	void Destroy()
	{
		delete this;
	}
protected:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}
};

void Test2()
{
	//B b;
	B *pa = B::Create();
	pa->Destroy();
}

/*-----------------------------------------*/
		//只在栈上开辟空间
class C
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}
private:
	int a;
	void * operator new(size_t);
	void operator delete(void *);
};
void Test3()
{
	//C *ptr = new C();
	C c;
}


int main()
{
	Test1();
	Test2();
	Test3();
	return 0; 
}
