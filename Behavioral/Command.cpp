/*
	The program demonstrates the Command pattern:
	Intent:
		-> Encapsulate a request as an object, thereby letting you parameterize clients with different requests,
			queue or log requests, and support undoable operations.

	Also Known as:
		Action, Transaction.

	Motivation:
		-> Turning the request itself into an object.This object can be stored and passed around like other objects.
		-> The key to this pattern is an abstract Command class, which declares an interface for executing operations.
		-> In the simplest form this interface includes an abstract Execute operation.
		-> Concrete Command subclasses specify a receiver-action pair by storing the receiver as an instance variable
			and by implementing Execute to invoke the request.
		-> The receiver has the knowledge required to carry out the request.
			
	Applicability:
		-> Parameterize objects by an action to perform.
		-> Specify,queue, and execute request at different times.
		-> Support undo:
			-> Can store state for reversing its effects in the command itself.
			-> The Command interface must have an added Unexecute operation that reverses the effects of a previous call to Execute.
			-> Executed commands are stored in a history list.
		-> Support logging changes so that they can be reapplied in case of a system crash.
		-> Structure a system around high-level operations built on primitives operations.


	Participants:
		(a).Command
			-> Declares an interface for executing an operation.
		(b).ConcreteCommand (PasteCommand, OpenCommand)
			-> Defines a binding between a Receiver object and an action.
			-> Implements Execute by invoking the corresponding operation(s) on Receiver.
		(c).Client (Application)
			-> Creates a ConcreteCommand object and sets its receiver.
		(d).Invoker (MenuItem)
			-> Asks the command to carry out the request.
		(e).Receiver (Document, Application)
			-> Knows how to perform the operations associated with carrying out a request.Any class may serve as a Receiver.

	Collaborations:
		-> The client creates a ConcreteCommand object and specifies its receiver.
		-> An Invoker object stores the ConcreteCommand object.
		-> The invoker issues a request by calling Execute on the command. When commands are undoable,
			ConcreteCommand stores state for undoing the command prior to invoking Execute.
		-> The ConcreteCommand object invokes operations on its receiver to carry out the request.

	Consequences:
		(a).Command decouples the object that invokes the operation from the one that knows how to perform it.
		(b).Commands are first-class objects.They can be manipulated and extended like any other object.
		(c).You can assemble commands into a composite command.
		(e).It's easy to add new Commands, because you don't have to change existing classes.

	Implementation(Things to be considered):
		(a).How intelligent should a command be?
		(b).Supporting undo and redo.
		(c).Avoiding error accumulation in the undo process.
		(e).Using C++ templates.
*/

#include <iostream>
#include <string>

namespace Demo1
{
	//Receiver
	class Person
	{
		public:
		void talk()
		{
			std::cout << " Person is talking" << std::endl;
		}
		void passOn()
		{
			std::cout << " Person is passing on" << std::endl;			
		}
		void gossip()
		{
			std::cout << " Person is gossiping" << std::endl;
		}
		void listen()
		{
			std::cout << " Person is listening" << std::endl;
		}
	};

	//Command
	class Command
	{
		public:
		virtual void execute() = 0;
	};

	//ConcreteCommand
	class TalkCommand : public Command
	{
		Person *_person;

		public:
		TalkCommand(Person *person)
		{
			_person = person;
		}
		void execute()
		{
			_person->talk();
		}
	};

	//ConcreteCommand
	class PassOnCommand : public Command
	{
		Person *_person;

		public:
		PassOnCommand(Person *person)
		{
			_person = person;
		}
		void execute()
		{
			_person->passOn();
		}
	};

	//ConcreteCommand
	class GossipCommand : public Command
	{
		Person *_person;

		public:
		GossipCommand(Person *person)
		{
			_person = person;
		}
		void execute()
		{
			_person->gossip();
		}
	};

	//ConcreteCommand
	class ListenCommand : public Command
	{
		Person *_person;

		public:
		ListenCommand(Person *person)
		{
			_person = person;
		}
		void execute()
		{
			_person->listen();
		}
	};
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		//Receiver starts
		Demo1::Person* receiver = new Demo1::Person;
		//Receiver ends

		//Client creates mapping
		//Available Commands starts
		Demo1::Command* talk = new Demo1::TalkCommand(receiver);
		Demo1::Command* passon = new Demo1::PassOnCommand(receiver);
		Demo1::Command* gossip = new Demo1::GossipCommand(receiver);
		Demo1::Command* listen = new Demo1::ListenCommand(receiver);
		//Available Commands ends

		//Invoker start
		talk->execute();
		passon->execute();
		gossip->execute();
		listen->execute();
		//Invoker end

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}

