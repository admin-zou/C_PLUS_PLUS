#ifndef INHERIT_H_
#define INHERIT_H_
#include <iostream>
#include <string>
using namespace std;

/////////�̳к����� 

//�̳���������Ĺ�ϵ
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
			//~Person();   //�����ֶ�����
			Person::~Person(); //�����ſ��Ե���
		}
	public:
		int _id;
	};

	void test()
	{
		Person p;
		Student s;
		Person* p1 = &p;
		//Person* p2 = &s;  //���м̳�ʱ����,������˽�м̳�ʱȴ������
		//s->fun();	//��������˽�м̳е�ʱ��s���ܷ��ʵĶ�����p2�ǿ��Է��ʵģ������߼�
		//p2->fun();	//effective c++ �н�����has_a��ϵ

		Person& p3 = p;
		//Person& p4 = s;   //���м̳�ʱ����,������˽�м̳�ʱȴ������

		Student* s1 = (Student*)&p;
		//s1->_id = 0; //�öβ�����s1�����ܷ��ʣ�д�����൱���ǽ�����
		Student* s2 = &s;
		Student& s3 = (Student&)p;
		//s3._id = 0; //�öβ�����s3,���ܷ��ʣ�д�����൱���ǽ�����
		Student& s4 = s;
	}
}

//6��Ĭ�Ϻ����ļ���
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
			:Person(s)  //������Ƭ
		{
			_id = s._id;
			cout << "Student(const Student& s)" << endl;
		}
		Student& operator=(const Student& s)
		{
			if (this != &s)
			{
				Person::operator=(s); //Ҳ�ᷢ����Ƭ
				_id = s._id;
				cout << "Student& operator=(const Student& s)" << endl;
			}
			return *this;
		}
		~Student()
		{
			cout << "~Student" << endl;
			//~Person();   //�����ֶ�����
			//Person::~Person(); //�����ſ��Ե���
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

//��̳�(���μ̳�)
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
	class B : virtual public A		//�̳�A
	{
	public:
		void func_b()
		{
			cout << "B-func" << endl;
		}
		int b;
	};
	class C :virtual  public A		//�̳�A
	{
	public:
		void func_c()
		{
			cout << "C-func" << endl;
		}
		int c;
	};
	class D :public B, public C		//�̳�B��C
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
		//ͨ���ڴ�仯�ɷ�������̳�����ͨ�̳е�����

		//�������
		/*d.B::a = 1;
		d.b = 2;
		d.C::a = 3;
		d.c = 4;
		d.d = 5;
		cout << sizeof(a) << endl;	//4
		cout << sizeof(b) << endl;	//8
		cout << sizeof(c) << endl;	//8
		cout << sizeof(d) << endl;	//20		���Կ���a���̳�������
		*/
		//�����
		d.B::a = 1;
		d.b = 2;
		d.C::a = 3;
		d.c = 4;
		d.d = 5;
		cout << sizeof(a) << endl;	//4
		cout << sizeof(b) << endl;	//12  a��b������һ��ָ��������ָ�루�ϸ���˵����ָ�룬ֻ��ƫ������
		cout << sizeof(c) << endl;	//12  a��c������һ��ָ��������ָ�루�ϸ���˵����ָ�룬ֻ��ƫ������
		cout << sizeof(d) << endl;	//24	  a b c d
		/***************************************************************************************************/
	}

}

//��̬
namespace POLYMORPHISM
{

	class A
	{
	public:
		void fun1() //����
		{
			cout << "A-func-1" << endl;
		}
		virtual void fun2() //���ǵ�������Ҫע��
		{
			cout << "A-func-2" << endl;
		}
		virtual A* fun3()
		{
			cout << "A-func-3��Э�䣩" << endl;
			return this;
		}
		//*���ص������������������ͬ*
		//�������������Ź�������
		void fun4()
		{
			cout << "void fun4()" << endl;
		}
		void fun4(int a)
		{
			cout << "void fun4(int)����" << endl;
		}
	private:
		int a;
	};

	class B : public A		//�̳�A
	{
	public:
		int fun1()
		{
			cout << "B-func-1����" << endl;
			return 0;
		}
		virtual void fun2() //���ǵ�������Ҫע��
		{
			cout << "B-func-2����" << endl;
		}
		virtual B* fun3()
		{
			cout << "B-func-3���ǣ�Э�䣩" << endl;
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
		cout << "����" << endl;
		a.fun1();
		b.fun1();
		cout << "����" << endl;
		p1->fun4();
		p1->fun4(0);
		cout << "���غ͸���" << endl;
		p1->fun1();
		p1->fun2();
		p1->fun3();
		p1 = &b;
		p1->fun1();
		p1->fun2();
		p1->fun3();
	}
}

//���
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

//����ʯ�̳�
namespace VIRTUAL_RING
{

	typedef void(*Func)();

	void PrintVTable(int *VTable)
	{
		cout << "����ַ��" << VTable << endl;
		for (int i = 0; VTable[i] != 0; i++)
		{
			printf("��VTable[%d]�ǣ�OX%p->", i, VTable[i]);
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
	class B : virtual public A		//�̳�A
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
	class C :virtual public A		//�̳�A
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
	class D :public B, public C		//�̳�B��C
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
		cout << "���A:" << endl;
		A a;
		int *fa1 = (int *)(*(int *)&a);
		PrintVTable(fa1);
		cout << "���B:" << endl;
		B b;
		int* fa2 = (int *)(*(int *)&b);
		PrintVTable(fa2);
		fa2 = (int *)*(int *)((char *)&b + sizeof(B)-sizeof(A));
		PrintVTable(fa2);
		cout << "���C:" << endl;
		C c;
		int* fa3 = (int *)(*(int *)&c);
		PrintVTable(fa3);
		fa3 = (int *)*(int *)((char *)&c + sizeof(C)-sizeof(A));
		PrintVTable(fa3);
		cout << "���D" << endl;
		D d;
		d.a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
		int* fa4 = (int *)(*(int *)&d);
		PrintVTable(fa4);
		fa4 = (int*)*((int*)(&d)) + ((sizeof(B)-sizeof(A)) / 4 + 1);
		PrintVTable(fa4);
		fa4 = (int*)*((int*)&d) + (sizeof(D)-sizeof(A)) / 4;
		PrintVTable(fa4);


		d.a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
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

//������ʯ�̳�test
namespace VIRTUAL_RING_TEST
{

	class Base
	{
	public:
		virtual void func1()
		{
			cout << "Base::func1()" << endl;
		}
		virtual void Basefunc2()
		{
			cout << "Base::func2()" << endl;
		}
	private:
		int b;
	};
	class Base1 :public virtual Base
	{
	public:
		virtual void func1()
		{
			cout << "Base1::func1()" << endl;
		}
		virtual void Base1func2()
		{
			cout << "Base1::func2()" << endl;
		}
	private:
		int b1;
	};
	class Base2 :public virtual Base
	{
	public:
		virtual void func1()
		{
			cout << "Base2::func1()" << endl;
		}
		virtual void Base2func2()
		{
			cout << "Base2::func2()" << endl;
		}
	private:
		int b2;
	};
	typedef void(*FUNC)();
	void PrintVTable(int *VTable)
	{
		cout << "����ַ��" << VTable << endl;
		for (int i = 0; VTable[i] != 0; i++)
		{
			printf("��VTable[%d]�ǣ�OX%x->", i, VTable[i]);
			FUNC p = (FUNC)VTable[i];
			p();
		}
		cout << endl;
	}
	class Derived : public Base1, public Base2
	{
	public:
		virtual void func1()
		{
			cout << "Derived::func1()" << endl;
		}
		virtual void Derivedfunc2()
		{
			cout << "Derived::func2()" << endl;
		}
		virtual void Derivedfunc3()
		{
			cout << "Derived::func3()" << endl;
		}
	private:
		int d1;
	};

	void test()
	{
		cout << sizeof(Base) << endl;
		//Base��ָ���麯�����ָ�� + b
		cout << sizeof(Base1) << endl;
		//Base1��ָ���麯�����ָ�� + Base1 ��ָ���������ָ�� + b1 + Base ��ָ���麯�����ָ�� + b
		cout << sizeof(Base2) << endl;
		//Base2��ָ�����麯�����ָ�� + Base2 ��ָ���������ָ�� + b2 + Base ��ָ�����麯�����ָ�� + b
		cout << sizeof(Derived) << endl;
		//Base1��ָ�����麯�����ָ�� + Base1 ��ָ���������ָ�� + b1
		//+ Base2��ָ�����麯�����ָ�� + Base2 ��ָ���������ָ�� + b2
		//+ d1
		//+ Base ��ָ���麯�����ָ�� + b

		//Base�Ķ���b :
		Base b;
		int *VTable = (int *)(*(int *)&b);
		PrintVTable(VTable);    //Base���麯����  

		//Base1�Ķ���b1 :
		//��1��Base1���麯������_vptr_B1��ָ��  
		Base1 b1;
		VTable = (int *)*(int *)&b1;
		PrintVTable(VTable);
		//��2��Base���麯����  
		VTable = (int *)*(int *)((char *)&b1 + sizeof(Base1)-sizeof(Base));  //��Base1�Ķ�����ڴ沼��  
		PrintVTable(VTable);

		//��3�� ������������
		// (a).b1�ĵ�ַ�����_vbptr�ĵ�ַ��ƫ����������Base1������ _vptr_B1��;
		// (b).Base�� _vptr_B �ĵ�ַ����� _vbptr �ĵ�ַ��ƫ����;

		//���в鿴������������ݣ�
		cout << *((int *)(*((int *)(&b1) + 1))) << endl;
		cout << *((int *)(*((int *)(&b1) + 1)) + 1) << endl;
	}
}


#endif