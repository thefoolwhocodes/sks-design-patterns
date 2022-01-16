/*
	The program demonstrates the Decorator pattern:

	Intent:
		-> Attach additional responsibilities to an object dynamically.
		-> Decorators provide a flexible alternative to subclassing for extending functionality.

	Also know as:
		-> Wrapper

	Applicability:
		-> Adds responsibilities to individual objects dynamically and transparently against Inheritance 
			that is static.
		-> Other objects(instances) are not affected.
		-> Responsibilities can be withdrawn.
		-> When extension by subclassing is impractical.(Sometimes a large number of independent extensions
		   are possible and would produce an explosion of subclasses to support every combination.)

	Participants:
		(a).Component:
			-> Defines the interface for objects that can have responsibilities added to them dynamically.
		(b).ConcreteComponent:
			-> Defines an object to which additional responsibilities can be attached.
		(c).Decorator:
			-> Maintains a reference to a Component object and defines an interface that conforms
			   to Component's interface.
		(d).ConcreteDecorator:
			-> Adds responsibilities to the component.

	How it is achieved:
		-> Decorator forwards requests to its Component object.
		-> It may optionally perform additional operations before and after forwarding the request.

	Consequences:
		It has two key benefits and two liabilities
			-> More flexibility than static inheritance.
			-> Avoids feature-laden classes high up in the hierarchy.
			-> A decorator and its component aren't identical.
			-> Lots of little objects.

	Implementation(Things to be considered):
		Interface conformance:
			-> A decorator object's interface must conform to the interface of the component it decorates.
		Omitting the abstract Decorator class:
			-> When only one responsibilty is required, we can merge Decorator's responsibility for forwarding
				requests to the component into the ConcreteDecorator.
		Keeping Component classes lightweight:
			-> It should focus on defining an interface, not on storing data.
		Changing the skin of an object versus changing its guts
			-> We can think of a decorator as a skin over an object that changes its behavior.

	Few more Implementation related points:
		-> Encapsulating the original object inside an abstract wrapper interface.
		-> Core (concrete component) and Decorator both inherit from this abstract interface Component.
		-> The Decorator class declares a composition relationship to the Component interface.
		-> The Decorator class delegates to the core object using Component interface.
		-> Concrete Decorator classes delegates to Decorator base class.
		-> The client configures the type and ordering of Core and Decorator objects.
*/

#include <iostream>

namespace Demo1
{
	//COMPONENT (Abstract Interface)
	class Widget
	{
		public:
		virtual void draw() = 0;
	};

	//CONCRETECOMPONENT
	class TextField: public Widget
	{
		private:
		int width, height;

		public:

		TextField(int w, int h)
		{
			width = w;
			height = h;
		}

		void draw()
		{
			std::cout << "TextField: " << width << ", " << height << std::endl;
		}
	};


	//DECORATOR (Abstract Interface)
	class Decorator: public Widget
	{
		Widget *wid;

	  public:
		Decorator(Widget *w)
		{
			wid = w;
		}
	 
		void draw() 
		{
			wid->draw();
		}
	};

	//CONCRETEDECORATOR
	class BorderDecorator: public Decorator
	{
		public:
		BorderDecorator(Widget *w): Decorator(w){}

		void draw()
		{
			Decorator::draw();
			std::cout << "BorderDecorator"<< std::endl;
		}
	};

	class ScrollDecorator: public Decorator
	{
	  public:
		ScrollDecorator(Widget *w): Decorator(w){}

		void draw()
		{
			Decorator::draw();
			std::cout << "ScrollDecorator"<< std::endl;
		}
	};
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;
		Demo1::Widget *aWidget = new Demo1::BorderDecorator(new Demo1::BorderDecorator(new Demo1::ScrollDecorator(new Demo1::TextField(80, 24))));
		aWidget->draw();
		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}
