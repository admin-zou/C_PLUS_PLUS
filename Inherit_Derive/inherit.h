#ifndef INHERIT_H_
#define INHERIT_H_
#include <iostream>
#include <string>
using namespace std;

/////////继承和派生

//继承与派生类的关系
namespace   Relation
{

	class Person
	{
	public:
		void fun()
		{}
		void show()
		{
			cout << _name << endl;
		}
		~Person()
		{
			cout << "~Person" << endl;
		}
	public:
		string _name;
	};

	class Student :protected Person
	{
	public:
		void show()
		{
			cout << _name << " " << _id << endl;
		}
		~Student()
		{
			cout << "~Student" << endl;
			//~Person();   //不能手动调用
			Person::~Person(); //这样才可以调用
		}
	public:
		int _id;
	};

	void test()
	{
		Person p;
		Student s;
		Person* p1 = &p;
		//Person* p2 = &s;  //共有继承时可以,保护和私有继承时却不可以
		//s->fun();	//保护或者私有继承的时候，s不能访问的东西，p2是可以访问的，不合逻辑
		//p2->fun();	//effective c++ 中讲到的has_a关系

		Person& p3 = p;
		//Person& p4 = s;   //共有继承时可以,保护和私有继承时却不可以

		Student* s1 = (Student*)&p;
		//s1->_id = 0; //该段不属于s1，不能访问（写），相当于是借来的
		Student* s2 = &s;
		Student& s3 = (Student&)p;
		//s3._id = 0; //该段不属于s3,不能访问（写），相当于是借来的
		Student& s4 = s;
	}
}

//6个默认函数的继续
namespace FUNC
{
	class Person
	{
	public:
		Person(const char* str = "")
			:_name(str)
		{
			cout << "Person(const char* str = "")" << endl;
		}
		Person(const Person& p)
			:_name(p._name)
		{
			cout << "Person(const Person& p)" << endl;
		}
		Person& operator=(const Person& p)
		{
			if (this != &p)
			{
				_name = p._name;
				cout << "Person& operator=(const Person& p)" << endl;
			}
			return *this;
		}
		~Person()
		{
			cout << "~Person" << endl;
		}
	public:
		string _name;
	};

	class Student :public Person
	{
	public:
		Student(const char* s = "", int id = 0)
			:Person(s)
			, _id(id)
		{
			cout << "Student(const char* s ,int id) " << endl;
		}
		Student(const Student& s)
			:Person(s)  //发生切片
		{
			_id = s._id;
			cout << "Student(const Student& s)" << endl;
		}
		Student& operator=(const Student& s)
		{
			if (this != &s)
			{
				Person::operator=(s); //也会发生切片
				_id = s._id;
				cout << "Student& operator=(const Student& s)" << endl;
			}
			return *this;
		}
		~Student()
		{
			cout << "~Student" << endl;
			//~Person();   //不能手动调用
			//Person::~Person(); //这样才可以调用
		}
	public:
		void show()
		{
			cout << _name << " " << _id << endl;
		}

		int _id;
	};


	void test()
	{
		Person p("hello");
		Student s1("hello world", 2);
		Student s2(s1);
		Student s3;
		s3 = s2;
	}
}

//多继承(菱形继承)
namespace  MULTIPLE_INHERITANCE
{
	class A
	{
	public:
		void func_a()
		{
			cout << "A-func" << endl;
		}

		int a;
	};
	class B : virtual public A		//继承A
	{
	public:
		void func_b()
		{
			cout << "B-func" << endl;
		}
		int b;
	};
	class C :virtual  public A		//继承A
	{
	public:
		void func_c()
		{
			cout << "C-func" << endl;
		}
		int c;
	};
	class D :public B, public C		//继承B，C
	{
	public:
		void func_d()
		{
			cout << "D-func" << endl;
		}
		int d;
	};

	void test()
	{
		A a;
		B b;
		C c;
		D d;
		/***************************************************************************************************/
		//通过内存变化可分析，虚继承与普通继承的区别

		//非虚基类
		/*d.B::a = 1;
		d.b = 2;
		d.C::a = 3;
		d.c = 4;
		d.d = 5;
		cout << sizeof(a) << endl;	//4
		cout << sizeof(b) << endl;	//8
		cout << sizeof(c) << endl;	//8
		cout << sizeof(d) << endl;	//20		可以看出a被继承了两次
		*/
		//虚基类
		d.B::a = 1;
		d.b = 2;
		d.C::a = 3;
		d.c = 4;
		d.d = 5;
		cout << sizeof(a) << endl;	//4
		cout << sizeof(b) << endl;	//12  a，b，加上一个指向虚基类的指针（严格来说不是指针，只是偏移量）
		cout << sizeof(c) << endl;	//12  a，c，加上一个指向虚基类的指针（严格来说不是指针，只是偏移量）
		cout << sizeof(d) << endl;	//24	  a b c d
		/***************************************************************************************************/
	}

}

//多重虚继承
namespace MULTIPLE_MANY
{
	class A
	{
	public:
		virtual void funA()
		{
			cout << "A-fun" << endl;
		}
		virtual void fun_A()
		{
			cout << "A-fun_A" << endl;
		}

		int a;
	};
	class B
	{
	public:
		virtual void funB()
		{
			cout << "B-fun" << endl;
		}
		virtual void fun_B()
		{
			cout << "B-fun_B" << endl;
		}

		int b;
	};
	class C
	{
	public:
		virtual void funC()
		{
			cout << "C-fun" << endl;
		}
		virtual void fun_C()
		{
			cout << "C-fun_C" << endl;
		}

		int c;
	};

	class D :public A, public B, public C
	{
	public:
		virtual void funA()
		{
			cout << "D-funA" << endl;
		}
		virtual void funB()
		{
			cout << "D-funB" << endl;
		}
		virtual void funC()
		{
			cout << "D-funC" << endl;
		}
		virtual void funD()
		{
			cout << "fun-D" << endl;
		}

		int d;
	};

	typedef void (*Fun)();
	
	void PrintVtable(int* PTable)
	{
		printf("虚表地址：%p\n",PTable);
		for (int i = 0; PTable[i] != 0; ++i)
		{
			printf("第%d个虚函数:%p ",i,PTable[i]);
			Fun p = (Fun)PTable[i];
			p();
		}
		printf("\n");
	}
	
	void test()
	{
		D d;
		d.a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
	//虚表A
		int* Vtable1 = (int*)*(int*)(&d);  //根据在内存中分布位置来转化
		PrintVtable(Vtable1);
	//虚表B
		int* Vtable2 = (int*)*((int*)(&d) + sizeof(A) / 4 ); //根据在内存中分布位置来转化
		PrintVtable(Vtable2);
	//虚表C
		int* Vtable3 = (int*)*((int*)(&d) + (sizeof(A)+sizeof(B)) / 4); //根据在内存中分布位置来转化
		PrintVtable(Vtable3);
	}
}

//多态
namespace POLYMORPHISM
{

	class A
	{
	public:
		void fun1() //隐藏
		{
			cout << "A-func-1" << endl;
		}
		virtual void fun2() //覆盖的条件需要注意
		{
			cout << "A-func-2" << endl;
		}
		virtual A* fun3()
		{
			cout << "A-func-3（协变）" << endl;
			return this;
		}
		//*重载的条件：作用域必须相同*
		//下面两个函数才构成重载
		void fun4()
		{
			cout << "void fun4()" << endl;
		}
		void fun4(int a)
		{
			cout << "void fun4(int)重载" << endl;
		}
	private:
		int a;
	};

	class B : public A		//继承A
	{
	public:
		int fun1()
		{
			cout << "B-func-1隐藏" << endl;
			return 0;
		}
		virtual void fun2() //覆盖的条件需要注意
		{
			cout << "B-func-2覆盖" << endl;
		}
		virtual B* fun3()
		{
			cout << "B-func-3覆盖（协变）" << endl;
			return this;
		}
	private:
		int b;
	};

	void test()
	{
		A a;
		B b;
		A* p1;
		p1 = &a;
		cout << "隐藏" << endl;
		a.fun1();
		b.fun1();
		cout << "重载" << endl;
		p1->fun4();
		p1->fun4(0);
		cout << "隐藏和覆盖" << endl;
		p1->fun1();
		p1->fun2();
		p1->fun3();
		p1 = &b;
		p1->fun1();
		p1->fun2();
		p1->fun3();
	}
}

//虚表
namespace VIRTUAL_FUNC
{
	class Base1 {
	public:
		virtual void f() { cout << "Base1::f" << endl; }
		virtual void g() { cout << "Base1::g" << endl; }
		virtual void h() { cout << "Base1::h" << endl; }

	};

	class Base2 {
	public:
		virtual void f() { cout << "Base2::f" << endl; }
		virtual void g() { cout << "Base2::g" << endl; }
		virtual void h() { cout << "Base2::h" << endl; }
	};

	class Base3 {
	public:
		virtual void f() { cout << "Base3::f" << endl; }
		virtual void g() { cout << "Base3::g" << endl; }
		virtual void h() { cout << "Base3::h" << endl; }
	};

	class Derive : public Base1, public Base2, public Base3 {
	public:
		virtual void f() { cout << "Derive::f" << endl; }
		virtual void g1() { cout << "Derive::g1" << endl; }
	};

	typedef void(*Fun)(void);

	void test()
	{
		Fun pFun = NULL;

		Derive d;
		int** pVtab = (int**)&d;

		//Base1's vtable
		//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
		pFun = (Fun)pVtab[0][0];
		pFun();

		//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
		pFun = (Fun)pVtab[0][1];
		pFun();

		//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
		pFun = (Fun)pVtab[0][2];
		pFun();

		//Derive's vtable
		//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
		pFun = (Fun)pVtab[0][3];
		pFun();

		//The tail of the vtable
		pFun = (Fun)pVtab[0][4];
		cout << pFun << endl;

		//Base2's vtable
		//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
		pFun = (Fun)pVtab[1][0];
		pFun();

		//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
		pFun = (Fun)pVtab[1][1];
		pFun();

		pFun = (Fun)pVtab[1][2];
		pFun();

		//The tail of the vtable
		pFun = (Fun)pVtab[1][3];
		cout << pFun << endl;

		//Base3's vtable
		//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
		pFun = (Fun)pVtab[2][0];
		pFun();

		//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
		pFun = (Fun)pVtab[2][1];
		pFun();

		pFun = (Fun)pVtab[2][2];
		pFun();

		//The tail of the vtable
		pFun = (Fun)pVtab[2][3];
		cout << pFun << endl;
	}

}

//虚钻石继承
namespace VIRTUAL_RING
{

	typedef void(*Func)();

	void PrintVTable(int *VTable)
	{
		cout << "虚表地址：" << VTable << endl;
		for (int i = 0; VTable[i] != 0; i++)
		{
			printf("第VTable[%d]是：OX%p->", i, VTable[i]);
			Func p = (Func)VTable[i];
			p();
		}
		cout << endl;
	}


	class A
	{
	public:
		virtual void fun1()
		{
			cout << "A-func1" << endl;
		}
		virtual void fun2()
		{
			cout << "A-func2" << endl;
		}

		int a;
	};
	class B : virtual public A		//继承A
	{
	public:
		virtual void fun1()
		{
			cout << "B-func1" << endl;
		}
		virtual void fun3()
		{
			cout << "B-func3" << endl;
		}

		int b;
	};
	class C :virtual public A		//继承A
	{
	public:
		virtual void fun1()
		{
			cout << "C-func1" << endl;
		}
		virtual void fun4()
		{
			cout << "C-func4" << endl;
		}

		int c;
	};
	class D :public B, public C		//继承B，C
	{
	public:
		virtual void fun1()
		{
			cout << "D-func1" << endl;
		}
		virtual void fun5()
		{
			cout << "D-func5" << endl;
		}
		int d;
	};

	void test()
	{
		cout << "虚表A:" << endl;
		A a;
		int *fa1 = (int *)(*(int *)&a);
		PrintVTable(fa1);
		
		cout << "虚表B:" << endl;
		B b;
		int* fa2 = (int *)(*(int *)&b);
		PrintVTable(fa2);
		fa2 = (int *)*(int *)((char *)&b + sizeof(B)-sizeof(A));
		PrintVTable(fa2);
		
		cout << "虚表C:" << endl;
		C c;
		int* fa3 = (int *)(*(int *)&c);
		PrintVTable(fa3);
		fa3 = (int *)*(int *)((char *)&c + sizeof(C)-sizeof(A));
		PrintVTable(fa3);
		
		cout << "虚表D" << endl;
		D d;
		d.a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
	//虚表1	
		int* fa4 = (int *)(*(int *)&d);
		PrintVTable(fa4);
	//虚表2	
		//fa4 = (int*)*((int*)(&d)) + (sizeof(B) / 4 - 1);
		fa4 = (int*)*((int*)&d + sizeof(B) / 4 - 2);  //根据在内存中的分布来转化
		PrintVTable(fa4);
	//虚表3	
		//fa4 = (int*)*((int*)&d) + (sizeof(D)-sizeof(A)) / 4;
		fa4 =  (int*)*((int*)&b +(sizeof(B)+sizeof(C)) / 4 -3); //根据在内存中的分布来转化
		PrintVTable(fa4);

		A* p;
		p = &a;
		p->fun1();
		p->fun2();
		p = &b;
		p->fun1();
		p->fun2();
		p = &c;
		p->fun1();
		p->fun2();
		p = &d;
		p->fun1();
		p->fun2();

	}

}

#endif