/*
The program demonstrates the Singleton pattern.

	Intent:
		-> Ensure a class only has one instance.
		-> provide a global point of access to it.

	Participants:
		(a).Singleton
			-> Defines an Instance operation that lets clients access its unique instance.

	Implementation details:
		-> Move all constructors to private.
		-> Move copy constructor to private.
	
	1> Demo1:Demonstration of Singleton class implementation using static local variable.
	2> Demo2:Demonstration of Singleton class implementation using static heap variable.	
*/

#include<pthread.h>
#include<iostream>

namespace Demo1
{
	class Singleton
	{
	public:
		static Singleton& getInstance();

		void doWork()
		{
			std::cout<<"Doing work"<<std::endl;
		}
		
	private:
		Singleton()
		{
			std::cout<<"Constructor called"<<std::endl;
		}
		Singleton(const Singleton& obj)
		{
			std::cout<<"Copy constructor called"<<std::endl;
		}
	};	

	//static should not be part of function definition else it is compile time error
	Singleton& Singleton::getInstance()
	{
		static Singleton instance;
		return instance;
	}	
}

namespace Demo2
{
	class Singleton
	{
		public:		
		static Singleton* getInstance();
		~Singleton()
		{
			delete _instance;
		}
		
		void doWork()
		{
			std::cout<<"Singleton doing work"<<std::endl;
		}
		
		private:
		Singleton()
		{
			_instance = NULL;
		}
		
		Singleton(const Singleton& RHS){}
		
		static Singleton* _instance;
		static pthread_mutex_t _mutex;
	};	
	
	Singleton* Singleton::_instance = NULL;	
	pthread_mutex_t Singleton::_mutex =  PTHREAD_MUTEX_INITIALIZER;	
	
	Singleton* Singleton::getInstance()
	{
		if(NULL ==_instance)
		{
			pthread_mutex_lock(&_mutex);
			_instance = new Singleton;
			pthread_mutex_unlock(&_mutex);			
			return _instance;
		}
		else 
			return _instance;
	}	
}


int main()
{
	{
		std::cout<<"Demo1 starts"<<std::endl;
		//First way of calling
		Demo1::Singleton::getInstance().doWork();

		//Second way of calling
		//& is added to ensure that copy constructor call is not raised
		Demo1::Singleton& ref = Demo1::Singleton::getInstance();
		ref.doWork();
		std::cout<<"Demo1 ends"<<std::endl;		
	}
	{
		std::cout<<"Demo2 starts"<<std::endl;		
		Demo2::Singleton* obj = Demo2::Singleton::getInstance();
		obj->doWork();	
		std::cout<<"Demo2 ends"<<std::endl;				
	}
}
