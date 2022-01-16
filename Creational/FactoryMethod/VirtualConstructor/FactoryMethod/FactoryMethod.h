#ifndef INC_FACTORYMETHOD_H
#define INC_FACTORYMETHOD_H

enum FactoryIndex
{
	DERIVED1 = 1,
	DERIVED2 = 2,	
	DERIVED3 = 3,
	DERIVED4 = 4
};

class Base
{
	public:
		Base* Create(FactoryIndex id);	
		~Base();	
		virtual void execute();
};

class Derived1 : public Base
{
	public:	
		~Derived1();	
		virtual void execute();
};

class Derived2 : public Base
{
	public:	
		~Derived2();
		virtual void execute();
};

class Derived3 : public Base
{
	public:	
		~Derived3();	
		virtual void execute();
};

class Derived4 : public Base
{
	public:	
		~Derived4();	
		virtual void execute();
};

#endif
