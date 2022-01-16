/*
	The program demonstrates the Chain of Responsibility Pattern:
	Intent:
		-> Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle
			the request.
		-> Chain the receiving objects and pass the request along the chain until an object handles it.
		-> Launch-and-leave requests with a single processing pipeline that contain many possible handlers.

	Motivation:
		-> The idea of this pattern is to decouple senders and receivers by giving multiple objects a chance to handle a request.
			The request gets passed along a chain of objects until one of them handles it.
		-> The first object in the chain receives the request and either handles it or forwards it to the next candidate on the chain,
			which does likewise.The object that made the request has no explicit knowledge of who will handle it—we say the request
				has an implicit receiver.
		-> To forward the request along the chain, and to ensure receivers remain implicit, each object on the chain shares a 
			common interface for handling requests and for accessing its successor on the chain.
			
	Applicability:
		-> More than one object may handle a request, and the handler isn't known a priori. The handler should be ascertained automatically.
		-> You want to issue a request to one of several objects without specifying the receiver explicitly.
		-> The set of objects that can handle a request should be specified dynamically.

	Participants:
		(a).Handler
			-> Defines an interface for handling requests.
				(optional) Implements the successor link.
		(b).ConcreteHandler
			-> Handles requests it is responsible for.
			-> Can access its successor.
			-> If the ConcreteHandler can handle the request, it does so;otherwise it forwards the request to its successor.
		(c).Client
			-> Initiates the request to a ConcreteHandler object on the chain.

	Collaborations:
		-> When a client issues a request, the request propagates along the chain until a ConcreteHandler object takes
			responsibility for handling it.

	Consequences:
		(a).Reduced coupling.
		(b).Added flexibility in assigning responsibilities to objects.
			-> You can add or change responsibilities for handling a request by adding to or otherwise changing
				the chain at run-time.
		(c).Receipt isn't guaranteed.

	Implementation(Things to be considered):
		(a).Connecting successors
			-> The Handler not only defines the interface for the requests but usually maintains the successor as well.
				That lets the handler provide a default implementation of HandleRequest that forwards the request to the successor (if any).
		(b).Chain of Responsibility is often applied in conjunction with Composite.
		(c).The base class maintains a "next" pointer.
		(d).Each derived class implements its contribution for handling the request.
		(e).If the request needs to be "passed on", then the derived class "calls back" to the base class, which delegates to the "next" pointer.
		(f).The client (or some third party) creates and links the chain (which may include a link from the last node to the root node).

	Example:
		-> ATM machine
*/

#include <iostream>
#include <vector>

namespace Demo1
{
	class Base
	{
		Base *next;
	  public:
		Base()
		{
			next = 0;
		}
		void setNext(Base *n)
		{
			next = n;
		}
		virtual void handle(int i)
		{
			next->handle(i);
		}
	};

	class Handler1: public Base
	{
	  public:
		void handle(int i)
		{
			if (1 != i)
			{
				std::cout << "H1 passed " << i << "  ";
				Base::handle(i);
			}
			else
			  std::cout << "H1 handled " << i << std::endl;
		}
	};

	class Handler2: public Base
	{
	  public:
		void handle(int i)
		{
			if (2 != i)
			{
				std::cout << "H2 passed " << i << "  ";
				Base::handle(i);
			}
			else
			  std::cout << "H2 handled " << i << std::endl;
		}
	};

	class Handler3: public Base
	{
	  public:
		void handle(int i)
		{
			if (3 != i)
			{
				std::cout << "H3 passed " << i << "  ";
				Base::handle(i);
			}
			else
			  std::cout << "H3 handled " << i << std::endl;
		}
	};
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::Handler1 root;
		Demo1::Handler2 two;
		Demo1::Handler3 thr;
		root.setNext(&two);
		two.setNext(&thr);
		root.handle(1);
		root.handle(2);
		root.handle(3);
		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}
