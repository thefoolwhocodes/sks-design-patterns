/*
	The program demonstrates the Iterator pattern:
	Intent:
		-> Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

	Also Known as:
		Cursor

	Motivation:
		-> The key idea in this pattern is to take the responsibility for access and traversal out of the traversed object (may be a list) 
			and put it into	an iterator object.
		-> The Iterator class defines an interface for accessing the traversed object's (may be a list) elements.
		-> An iterator object is responsible for keeping track of the current element; that is, it knows which elements have been traversed
			already.
			
	Applicability:
		-> To access an aggregate object's contents without exposing its internal representation.
		-> To support multiple traversals of aggregate objects.
		-> To provide a uniform interface for traversing different aggregate structures (that is, to support polymorphic iteration).


	Participants:
		(a).Iterator
			->defines an interface for accessing and traversing elements.
		(b).ConcreteIterator
			-> Implements the Iterator interface.
			-> Keeps track of the current position in the traversal of the aggregate.
		(c).Aggregate
			-> Defines an interface for creating an Iterator object.
		(d).ConcreteAggregate
			-> Implements the Iterator creation interface to return an instance of the proper ConcreteIterator.

	Collaborations:
		-> A ConcreteIterator keeps track of the current object in the aggregate and can compute the succeeding object in the traversal.

	Consequences:
		(a).It supports variations in the traversal of an aggregate.
		(b).Iterators simplify the Aggregate interface.
		(c).More than one traversal can be pending on an aggregate.

	Implementation(Things to be considered):
		(a).Who controls the iteration?
			->external iterator:Client controls the iteration
			->internal iterator:Iterator controls the iteration
		(b).Iterators implementation using freind.
		(c).Iterators implementation using subclassing of aggregate and exposing the underlying methods
			of aggregate using protected to Iterator.

*/

#include <iostream>

namespace Demo1
{
	class StackIter;

	class Stack
	{
		int items[10];
		int sp;
		public:
		friend class StackIter;
		Stack()
		{
			sp =  - 1;
		}
		void push(int in)
		{
			items[++sp] = in;
		}
		int pop()
		{
			return items[sp--];
		}
		bool isEmpty()
		{
			return (sp ==  - 1);
		}
		StackIter *createIterator() const; // 2. Add a createIterator() member
	};

	class StackIter
	{
		// 1. Design an "iterator" class
		const Stack *stk;
		int index;
		public:
		StackIter(const Stack *s)
		{
			stk = s;
		}
		void first()
		{
			index = 0;
		}
		void next()
		{
			index++;
		}
		bool isDone()
		{
			return index == stk->sp + 1;
		}
		int currentItem()
		{
			return stk->items[index];
		}
	};

	StackIter *Stack::createIterator()const
	{
		return new StackIter(this);
	}

	bool operator == (const Stack &l, const Stack &r)
	{
		// 3. Clients ask the container object to create an iterator object
		StackIter *itl = l.createIterator();
		StackIter *itr = r.createIterator();

		// 4. Clients use the first(), isDone(), next(), and currentItem() protocol
		for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
			if (itl->currentItem() != itr->currentItem())
				break;

		bool ans = itl->isDone() && itr->isDone();

		delete itl;
		delete itr;

		return ans;
	}
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::Stack s1;
		for (int i = 1; i < 5; i++)
			s1.push(i);

		Demo1::Stack s2(s1), s3(s1), s4(s1), s5(s1);
		s3.pop();
		s5.pop();
		s4.push(2);
		s5.push(9);

		std::cout << "1 == 2 is " << (s1 == s2) << std::endl;
		std::cout << "1 == 3 is " << (s1 == s3) << std::endl;
		std::cout << "1 == 4 is " << (s1 == s4) << std::endl;
		std::cout << "1 == 5 is " << (s1 == s5) << std::endl;

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}
