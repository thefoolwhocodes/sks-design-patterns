/*
	The program demonstrates the Proxy pattern:
	Intent:
		-> Provide a surrogate or placeholder for another object to control access to it.

	Also known as:
		-> Surrogate

	Motivation:
		-> One reason for controlling access to an object is to defer the full cost of its creation and initialization
			until we actually need to use it.
			
	Applicability:
		-> Remote proxy provides a local representative for an object in an different address space.
		-> Virtual proxy creates expensive objects on demand.
		-> Protection proxy controls access to the original object.
		-> Smart reference proxy is a replacement for a bare pointer with additional actions
			when object is accessed.
				-> Counting the number of references to the real object so that it can be freed automatically.
				-> Loading a persistent object into memory when it is first referenced.
				-> Checking that the real object is locked before it is accessed to ensure that no other object can
					change it.

	Participants:
		(a).Subject:
			-> Defines the common interface for RealSubject and Proxy so that a Proxy can be used anywhere a Real subject is expected.
		(b).RealSubject:
			-> Defines the real object that the Proxy represents.
		(c).Proxy:
			-> Maintains a reference that lets the proxy access the RealSubject.Proxy may refer to a Subject if the RealSubject and Subject
				interfaces are same.
			-> Provides an interface identical to Subject's so that a proxy can be substituted for the real object.
			-> Controls access to the RealSubject and may be responsible for creating and deleting it.
			-> Other responsibilities depend on the kind of proxy (Applicability section can be referred).

	Collaborations:
		-> Proxy forwards requests to RealSubject when appropriate, depending on the kind of proxy.

	Consequences:
		-> A remote proxy can hide the fact that an object resides in a different address space.
		-> A virtual proxy can perform optmizations such as creating an object on demand and copy-on-write.
		-> Both protection proxies and smart references allow additional housekeeping tasks when an object is accessed.

	Implementation(Things to be considered):
		(a).Overloading the member access operator in c++.
		(b).Using doesNotUnderstand in Smalltalk.
		(c).Proxy does not always have to know the type real subject.
			-> If a Proxy class can deal with its subject solely through an abstract interface,then there is no need
				to make a Proxy class for each RealSubject.
			-> If Proxy are going to instantiate RealSubjects (such as in virtual proxy),then they have to know the concrete class.

	Example:
		-> Stub code in RPC,CORBA and SOAP.
		-> Smart pointer.
*/

#include <iostream>
#include <string.h>

//Virtual Proxy example
namespace Demo1
{
	class RealImage
	{
		int m_id;
	  public:
		RealImage(int i)
		{
			m_id = i;
			std::cout << "   $$ ctor: " << m_id << '\n';
		}
		~RealImage()
		{
			std::cout << "   dtor: " << m_id << '\n';
		}
		void draw()
		{
			std::cout << "   drawing image " << m_id << '\n';
		}
	};

	class Image
	{
		RealImage *m_the_real_thing;
		int m_id;
		static int s_next;
	  public:
		Image()
		{
			m_id = s_next++;
			m_the_real_thing = 0;
		}
		~Image()
		{
			delete m_the_real_thing;
		}
		void draw()
		{
			if (!m_the_real_thing)
			  m_the_real_thing = new RealImage(m_id);
			m_the_real_thing->draw();
		}
	};
	int Image::s_next = 1;
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::Image images;
		images.draw();

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}
