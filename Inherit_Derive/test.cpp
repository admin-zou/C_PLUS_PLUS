#define _CRT_SECURE_NO_WARNINGS
#include"inherit.h"

int main()
{
	//Relation::test();				//继承与派生类的关系
	//FUNC::test();					//6个默认函数的继续
	//MULTIPLE_INHERITANCE::test();    //多继承(菱形继承)
	//MULTIPLE_MANY::test();			//多重虚拟继承
	//POLYMORPHISM::test();			//多态
	//VIRTUAL_FUNC::test();			//虚表
	VIRTUAL_RING::test();			//虚菱形继承
	
	return 0;
}