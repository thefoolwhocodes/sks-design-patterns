/*
    The program demonstrates the Bridge pattern:
	Intent:
        -> Decouples an abstraction from its implementation so that the two can vary independently.
		-> It proposes refactoring exponentially explosive inheritance hierarchy into two orthogonal hierarchies
			   one for abstrations
	           second for implmentations.

    Also known as:
        -> Handle/Body

	Applicability:
        -> Implementations can be selected at run time.
		-> Want to avoid a permanent binding between an abstraction and its implementation.
		-> Both the abstractions and their implementations should be extensible by subclassing.
		-> changes in the implementation of an abstraction should have no impact on clients,that is, their code should
			not have to be recompiled.
		-> You want to hide the implementation of an abstraction completely from clients.


	Participants
		(a).Abstraction
			-> Defines the abstraction's interface.
			-> Maintains a reference to an object of type Implementor.
		(b).RefinedAbstraction
			-> Extends the interface defined by Abstraction.
		(c).Implementor
			-> defines the interface for implementation classes. This interface	doesn't have to correspond exactly to
			Abstraction's interface,in fact the two interfaces can be quite different. Typically the Implementor interface
			provides only primitive operations, and	Abstraction defines higher-level operations based on these primitives.
		(d).ConcreteImplementor
			-> implements the Implementor interface and defines its concrete implementation.

	Collaborations
		-> Abstraction forwards client requests to its Implementor object.

	Problem:
		-> Most of the times abstract base class is subclassed to provide alternative implementations leading to an
	           exponentially explosive inheritance hierarchy.		       
		-> Interface and implementation is locked at compile time.
		-> Abstraction and implementation cannot be intependently extended or composed.

    How it is achieved:
        -> Publish interface in an inheritance hierarchy, and bury implementation in its own inheritance hierarchy.
		-> The interface class contains a pointer of abstract implementation class.This pointer is initialized with
			   an instance of a concrete implementation class.
		-> The client interacts with the interface class and in turn "delegates" all requests to the implementation class.


Without Bridge hierarchy:

					ThreadScheduler
					      |
		|---------------------------------------------------------------|
		|						                                        |
	PreemptiveThreadScheduler				                TimeSlicedThreadScheduler
		|							                                    |
		|                                                               |
		|							                                    |
		|							                                    |
  |-------------|----------|					          |-------------|----------|
UnixPTS      JAVAPTS   WindowsPTS				      UnixTSTS      JAVATSTS   WindowsTSTS


With Bridge hierarchy:


					ThreadScheduler ---------------------->ThreadScheduler_Implementation
					      |						                        | 
		|-----------------------------|						            |	
		|						      |	                                |		
 PreemptiveThreadScheduler	    	  |					                |	
		 							  |                                 |
		 							  |                                 |
		 							  |                                 |
		 	            TimeSlicedThreadScheduler		                |
		 					                              |-------------|----------|-------------|------------|------------|
		 						                        UnixPTS      JAVAPTS   WindowsPTS     UnixTSTS      JAVATSTS   WindowsTSTS

*/

#include <iostream>

namespace WithoutBridge
{
	//1st layer of abstraction
	class ThreadScheduler
	{
		public:
		virtual void tell()=0;
	};

	void ThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler called"<<std::endl;
	}

	//Second layer of abstraction
	class PreEmptiveThreadScheduler : public ThreadScheduler
	{
		public:
		virtual void tell()=0;
	};

	void PreEmptiveThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler::PreEmptiveThreadScheduler called"<<std::endl;
		ThreadScheduler::tell();
	}

	class TimeSlicedThreadScheduler : public ThreadScheduler
	{
		public:
		virtual void tell()=0;
	};

	void TimeSlicedThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler::TimeSlicedThreadScheduler called"<<std::endl;
		ThreadScheduler::tell();
	}

	//Third layer, Implementation layer
	class UNIXPTS : public PreEmptiveThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::PreEmptiveThreadScheduler::UNIXPTS called"<<std::endl;
			PreEmptiveThreadScheduler::tell();
		}
	};

	class WindowsPTS : public PreEmptiveThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::PreEmptiveThreadScheduler::WindowsPTS called"<<std::endl;
			PreEmptiveThreadScheduler::tell();
		}
	};

	class JAVAPTS : public PreEmptiveThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::PreEmptiveThreadScheduler::JAVAPTS called"<<std::endl;
			PreEmptiveThreadScheduler::tell();
		}
	};

	class UNIXTSTS : public TimeSlicedThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::TimeSlicedThreadScheduler::UNIXPTS called"<<std::endl;
			TimeSlicedThreadScheduler::tell();
		}
	};

	class WindowsTSTS : public TimeSlicedThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::TimeSlicedThreadScheduler::WindowsPTS called"<<std::endl;
			TimeSlicedThreadScheduler::tell();
		}
	};

	class JAVATSTS : public TimeSlicedThreadScheduler
	{
		public:
		virtual void tell()
		{
			std::cout<<"Implementation of ThreadScheduler::TimeSlicedThreadScheduler::JAVAPTS called"<<std::endl;
			TimeSlicedThreadScheduler::tell();
		}
	};
};


namespace WithBridge
{
	//First layer of Implementation's Abstraction
	class ThreadScheduler_Implementation
	{
		public:
		virtual void impl_tell()=0;
	};

	void ThreadScheduler_Implementation::impl_tell()
	{
		std::cout<<"Abstract interface ThreadScheduler_Implementation for Implementation called"<<std::endl;
	}

	//Second layer of implementation (All implementation is present at this layer)
	class UNIXPTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::UNIXPTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	class WindowsPTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::WindowsPTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	class JAVAPTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::JAVAPTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	class UNIXTSTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::UNIXTSTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	class WindowsTSTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::WindowsTSTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	class JAVATSTS : public ThreadScheduler_Implementation
	{
		public:
		void impl_tell()
		{
			std::cout<<"ThreadScheduler_Implementation::JAVATSTS Implementation called"<<std::endl;
			ThreadScheduler_Implementation::impl_tell();
		}
	};

	//1st layer of abstraction
	class ThreadScheduler
	{
		public:
		virtual void tell()=0;
		void setDelegate(ThreadScheduler_Implementation* delegate)
		{
			tsi = delegate;
		}

		virtual ~ThreadScheduler()
		{
			delete tsi;
		}

		private:
		ThreadScheduler_Implementation* tsi;
	};

	void ThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler"<<std::endl;
		tsi->impl_tell();
	}

	//Second layer of abstraction
	class PreEmptiveThreadScheduler : public ThreadScheduler
	{
		public:
		virtual void tell();
	};

	void PreEmptiveThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler::PreEmptiveThreadScheduler called"<<std::endl;
		ThreadScheduler::tell();
	}

	class TimeSlicedThreadScheduler : public ThreadScheduler
	{
		public:
		virtual void tell();
	};

	void TimeSlicedThreadScheduler::tell()
	{
		std::cout<<"Abstract interface ThreadScheduler::TimeSlicedThreadScheduler called"<<std::endl;
		ThreadScheduler::tell();
	}
};


int main()
{
	{
		std::cout<<std::endl;
		std::cout<<"-----------------------------Demonstration of first Demo:WithoutBridge-----------------------------"<<std::endl;
		WithoutBridge::ThreadScheduler *thSch = NULL;

		std::cout<<std::endl;
		thSch = new WithoutBridge::UNIXPTS;
		thSch->tell();
		delete thSch;

		std::cout<<std::endl;
		thSch = new WithoutBridge::WindowsPTS;
		thSch->tell();
		delete thSch;

		std::cout<<std::endl;
		thSch = new WithoutBridge::JAVAPTS;
		thSch->tell();
		delete thSch;

		std::cout<<std::endl;
		thSch = new WithoutBridge::UNIXTSTS;
		thSch->tell();
		delete thSch;

		std::cout<<std::endl;
		thSch = new WithoutBridge::WindowsTSTS;
		thSch->tell();
		delete thSch;

		std::cout<<std::endl;
		thSch = new WithoutBridge::JAVATSTS;
		thSch->tell();
		delete thSch;

		std::cout<<"-----------------------------End of first Demo-----------------------------"<<std::endl;
		std::cout<<std::endl;
	}

	{
		std::cout<<std::endl;
		std::cout<<"-----------------------------Demonstration of second Demo:WithBridge-----------------------------"<<std::endl;
		std::cout<<std::endl;
		WithBridge::ThreadScheduler *pthSch = new WithBridge::PreEmptiveThreadScheduler;
		pthSch->setDelegate(new WithBridge::UNIXPTS);
		pthSch->tell();
		delete pthSch;

		std::cout<<std::endl;
		pthSch = new WithBridge::PreEmptiveThreadScheduler;
		pthSch->setDelegate(new WithBridge::WindowsPTS);
		pthSch->tell();
		delete pthSch;

		std::cout<<std::endl;
		pthSch = new WithBridge::PreEmptiveThreadScheduler;
		pthSch->setDelegate(new WithBridge::JAVAPTS);
		pthSch->tell();
		delete pthSch;

		std::cout<<std::endl;
		WithBridge::ThreadScheduler *tsthSch = new WithBridge::TimeSlicedThreadScheduler;
		tsthSch->setDelegate(new WithBridge::UNIXTSTS);
		tsthSch->tell();
		delete pthSch;

		std::cout<<std::endl;
		tsthSch = new WithBridge::TimeSlicedThreadScheduler;
		tsthSch->setDelegate(new WithBridge::WindowsTSTS);
		tsthSch->tell();
		delete pthSch;

		std::cout<<std::endl;
		tsthSch = new WithBridge::TimeSlicedThreadScheduler;
		tsthSch->setDelegate(new WithBridge::JAVATSTS);
		tsthSch->tell();
		delete tsthSch;
		std::cout<<"-----------------------------End of second Demo-----------------------------"<<std::endl;
		std::cout<<std::endl;
	}

	return 0;
}
