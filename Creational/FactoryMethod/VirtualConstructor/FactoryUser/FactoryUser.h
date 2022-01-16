#ifndef INC_FACTORYUSER_H
#define INC_FACTORYUSER_H

#include "FactoryMethod.h"

//User class that is using the inheritance hierarchy
//User class should be open for inheritance hierarchy modifications
class User
{
	private:
		Base* _ptr;
	
	public:
		User(FactoryIndex id);	
		~User();	
		void doJob();
};

#endif
