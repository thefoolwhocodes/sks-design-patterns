#include<iostream>
#include<FactoryMethod.h>

Base::~Base(){}

void Base::execute()
{
	std::cout<<"In Base"<<std::endl;
}

Derived1::~Derived1(){}	
void Derived1::execute()
{
	std::cout<<"In Derived1"<<std::endl;
}

Derived2::~Derived2(){}	
void Derived2::execute()
{
	std::cout<<"In Derived2"<<std::endl;
}		

Derived3::~Derived3(){}
void Derived3::execute()
{
	std::cout<<"In Derived3"<<std::endl;
}

Derived4::~Derived4(){}
void Derived4::execute()
{
	std::cout<<"In Derived4"<<std::endl;
}

//Factory Method
Base* Base::Create(FactoryIndex id)
{
    // Just expand the if-else ladder, if new Derived class is created
    // User code need not be recompiled to create newly added class objects 
    if( id == DERIVED1)
    {
        return new Derived1;
    }
    else if( id == DERIVED2 )
    {
        return new Derived2;
    }
    else if( id == DERIVED3 )
    {
        return new Derived3;
    }
    else if( id == DERIVED4 )
    {
        return new Derived4;
    }	
}
