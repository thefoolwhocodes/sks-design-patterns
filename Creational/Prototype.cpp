/*
The program demonstrates the Prototype pattern.
	Intent:
		-> Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

	Applicability:
		-> When the classes to instantiate are specified at run-time, for example, by dynamic loading.
		-> When instances of a class can have one of only a few different combinations of state.

	Participants:
		(a).Prototype (Graphic)
			-> Declares an interface for cloning itself.
		(b).ConcretePrototype (Staff, WholeNote, HalfNote)
			-> Implements an operation for cloning itself.
		(c).Client (GraphicTool)
			-> Creates a new object by asking a prototype to clone itself.

	Implementation:
		1.Using a prototype manager.
			-> Keep a registry of available prototypes.
		2.Implement the Clone operation.
			-> Deep copy should be preffered.

	Works mainly using clone.

	1> Demo1
		-> Class to instantiate is specified at run-time.
		-> Classes to instantiate are created with the state.
		-> Deep copy is implemented through copy constructor.
*/

#include<iostream>
#include<string>

namespace Demo1
{
	class Prototype
	{
	protected:
		int _value;
		std::string _type;
	public:
		void displayState()
		{
			std::cout<<"Value:"<<_value<<std::endl;
			std::cout<<"Type:"<<_type<<std::endl;
		}
		virtual void useMe() = 0;
		virtual Prototype* clone()=0;
	};

	class ConcretePrototype1 : public Prototype
	{
	public:
		ConcretePrototype1(int number)
		{
			_value = number;
			_type = "Type1";
		}
		ConcretePrototype1(const ConcretePrototype1& RHS)
		{
			std::cout<<"ConcretePrototype1 Copy constructor called"<<std::endl;
			_value = RHS._value;
			_type = RHS._type;
		}
		virtual void useMe()
		{
			std::cout<<"ConcretePrototype1 getting used"<<std::endl;
		}
		virtual Prototype* clone()
		{
			return new ConcretePrototype1(*this);
		}
	};

	class ConcretePrototype2 : public Prototype
	{
	public:
		ConcretePrototype2(int number)
		{
			_value = number;
			_type = "Type2";
		}
		ConcretePrototype2(const ConcretePrototype2& RHS)
		{
			std::cout<<"ConcretePrototype2 Copy constructor called"<<std::endl;
			_value = RHS._value;
			_type = RHS._type;
		}
		virtual void useMe()
		{
			std::cout<<"ConcretePrototype2 getting used"<<std::endl;
		}
		virtual Prototype* clone()
		{
			return new ConcretePrototype2(*this);
		}
	};
}

int main()
{
	{
		std::cout<<"Demo1 starts"<<std::endl;
		//Type A cloning with state, example
		Demo1::Prototype *ptr1A = new Demo1::ConcretePrototype1(100);
		ptr1A->displayState();
		ptr1A->useMe();

		Demo1::Prototype *ptr2A = ptr1A->clone();
		ptr2A->displayState();
		ptr2A->useMe();

		//Type B cloning with state, example
		Demo1::Prototype *ptr1B = new Demo1::ConcretePrototype2(200);
		ptr1B->displayState();
		ptr1B->useMe();

		Demo1::Prototype *ptr2B = ptr1B->clone();
		ptr2B->displayState();
		ptr2B->useMe();
		std::cout<<"Demo1 ends"<<std::endl;
	}
	return 0;
}
