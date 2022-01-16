/*
    The program demonstrates the Adapter pattern:
    Intent:
        -> Converts the interface of a class into another interface that clients expect.
		-> Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

    Also known as:
        Wrapper

	Applicability:
		-> You want to use an existing class, and its interface does not match the one you need.
		-> You want to create a reusable class that cooperates with unrelated or unforeseen classes, that is, classes that
			don't necessarily have compatible interfaces.
		-> (object adapter only) you need to use several existing subclasses, but it's impractical to adapt their interface
			by subclassing every one. An object adapter can adapt the interface of its parent class.

	Participants:
		(a).Target
			-> Defines the domain-specific interface that Client uses.
		(b).Client
			-> Collaborates with objects conforming to the Target interface.
		(c).Adaptee
			-> Defines an existing interface that needs adapting.
		(d).Adapter
			-> Adapts the interface of Adaptee to the Target interface.

	Collaborations:
		-> Clients call operations on an Adapter instance. In turn, the adapter calls Adaptee operations that carry out the request.

	1> Demo1
		-> Demonstration of class Adapter.
*/


#include <iostream>

typedef int Coordinate;
typedef int Dimension;

namespace Demo1
{
	// Desired interface
	class Rectangle
	{
	  public:
		virtual void draw() = 0;
	};

	// Legacy component
	class LegacyRectangle
	{
	  public:
		LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
		{
			x1_ = x1;
			y1_ = y1;
			x2_ = x2;
			y2_ = y2;
			std::cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
			  << x2_ << "," << y2_ << ")" << std::endl;
		}
		void oldDraw()
		{
			std::cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << 
			  ") => (" << x2_ << "," << y2_ << ")" << std::endl;
		}
	  private:
		Coordinate x1_;
		Coordinate y1_;
		Coordinate x2_;
		Coordinate y2_;
	};

	// Adapter wrapper
	class RectangleAdapter: public Rectangle, private LegacyRectangle
	{
	  public:
		RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h):
		  LegacyRectangle(x, y, x + w, y + h)
		{
			std::cout << "RectangleAdapter: create.  (" << x << "," << y << 
			  "), width = " << w << ", height = " << h << std::endl;
		}
		virtual void draw()
		{
			std::cout << "RectangleAdapter: draw." << std::endl;
			oldDraw();
		}
	};
};



int main()
{
	Demo1::Rectangle *r = new Demo1::RectangleAdapter(120, 200, 60, 40);
	r->draw();

	return 0;
}
