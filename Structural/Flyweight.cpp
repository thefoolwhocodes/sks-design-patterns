/*
	The program demonstrates the Flyweight pattern:
	Intent:
		-> Use sharing to support large number of fine-grained objects efficiently.

	Motivation:
		-> Flyweight pattern describes how to share objects to allow their use at fine granularities without prohibitive cost.
		-> Flyweight is a shared object that can be used in multiple contexts simultaneously.
		-> Flyweight states:			
			(a).Intrinsic state
				-> Stored in flyweight.
				-> contains information that is independent of flyweight's context (shareable).
			(b).Extrinsic state
				-> It depends on and varies with the flyweight's context (non shareable).
				-> Client objects are responsible for passing extrinsic state to the flyweight when it needs it.
			
	Applicability:
		-> An application uses large number of objects.
		-> Storage costs are high because of the sheer quantity of objects.
		-> Many object state can be made extrinsic.
		-> Many groups of objects may be replaced by relatively few shared objects
			once extrinsic state is removed.

	Participants:
		(a).Flyweight:
			-> Declares an interface through which flyweights can receive and act on extrinsic state.
		(b).ConcreteFlyweight:
			-> Implements the Flyweight interface and adds storage for intrinsic state,if any.
			-> ConcreteFlyweight object must be shareable.
			-> Any state it stores must be intrinsic,it must be independent of the ConcreteFlyweight objects's context.
		(c).UnsharedConcreteFlyweight:
			-> Non shareable subclass.
			-> UnsharedConcreteFlyweight objects can have ConcreteFlyweight objects as children.
		(d).FlyweightFactory:
			-> Creates and manages Flyweight objects.
			-> Ensures the Flyweights are shared properly.
			-> When a client requests a flyweight,the FlyweightFactory object suppiles an existing instance
				or creates one,if none exists.
		(e).Client:
			-> Maintains a reference to flyweight(s).
			-> Computes or stores the extrinsic state of flyweight(s).

	Collaborations:
		-> Clients pass the extrinsic state to the flyweight when they invoke its operations.
		-> Clients should not instantiate ConcreteFlyweight directly.
		-> Clients must obtain ConcreteFlyweight objects exclusively from the FlyweightFactory object to 
			ensure they are shared properly.

	Consequences:
		-> May introduce run-time costs for transferring,finding and/or computing extrinsic state.
		-> Run-time costs are offset by space savings.

	Implementation(Things to be considered):
		(a).Removing extrinsic state:
			-> Ideally extrinsic state can be computed from a separate object structure, one with far smaller
				object requirements.
		(b).Managing shared object:
			-> Client should not instantiate objects directly.
			-> FlyweightFactory helps client locate a particular flyweight.

	Example:
		-> Document editor (Example vi).
		-> In document editor a flyweight is created for each alphabet.
		-> Character code is intrinsic state.
		-> A flyweight representing the letter "a" only stores the corresponding character code; it doesn't need to store
			its location or font.
		-> Clients supply the context-dependent information that the flyweight needs to draw itself.
*/

#include <iostream>
#include <string.h>

namespace Demo1
{
	class Icon
	{
		public:
		Icon(char *fileName)
		{
			strcpy(_name, fileName);
			if (!strcmp(fileName, "go"))
			{
				_width = 20;
				_height = 20;
			}
			if (!strcmp(fileName, "stop"))
			{
				_width = 40;
				_height = 40;
			}
			if (!strcmp(fileName, "select"))
			{
				_width = 60;
				_height = 60;
			}
			if (!strcmp(fileName, "undo"))
			{
				_width = 30;
				_height = 30;
			}
		}
		const char *getName()
		{
			return _name;
		}
		void draw(int x, int y)
		{
			std::cout << "   drawing " << _name << ": upper left (" << x << "," << y << 
			") - lower right (" << x + _width << "," << y + _height << ")" <<
			std::endl;
		}
		private:
		char _name[20];
		int _width;
		int _height;
	};

	class FlyweightFactory
	{
		public:
		static Icon *getIcon(char *name)
		{
			for (int i = 0; i < _numIcons; i++)
			if (!strcmp(name, _icons[i]->getName()))
				return _icons[i];
			_icons[_numIcons] = new Icon(name);
			return _icons[_numIcons++];
		}
		static void reportTheIcons()
		{
			std::cout << "Active Flyweights: ";
			for (int i = 0; i < _numIcons; i++)
				std::cout << _icons[i]->getName() << " ";
			std::cout << std::endl;
		}
		private:
		enum
		{
			MAX_ICONS = 5
		};
		static int _numIcons;
		static Icon *_icons[MAX_ICONS];
	};

	int FlyweightFactory::_numIcons = 0;
	Icon *FlyweightFactory::_icons[];

	class DialogBox
	{
		public:
		DialogBox(int x, int y, int incr): _iconsOriginX(x), _iconsOriginY(y),
		_iconsXIncrement(incr){}
		virtual void draw() = 0;

		protected:
		Icon *_icons[3];
		int _iconsOriginX;
		int _iconsOriginY;
		int _iconsXIncrement;
	};

	class FileSelection: public DialogBox
	{
		public:
		FileSelection(Icon *first, Icon *second, Icon *third): DialogBox(100, 100,
		100)
		{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
		}
		void draw()
		{
		std::cout << "drawing FileSelection:" << std::endl;
		for (int i = 0; i < 3; i++)
		_icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
		}
	};

	class CommitTransaction: public DialogBox
	{
		public:
		CommitTransaction(Icon *first, Icon *second, Icon *third): DialogBox(150,
		150, 150)
		{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
		}
		void draw()
		{
			std::cout << "drawing CommitTransaction:" << std::endl;
			for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX + (i *_iconsXIncrement), _iconsOriginY);
		}
	};
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::DialogBox *dialogs[2];
		dialogs[0] = new Demo1::FileSelection(Demo1::FlyweightFactory::getIcon("go"),
		Demo1::FlyweightFactory::getIcon("stop"), Demo1::FlyweightFactory::getIcon("select"));
		dialogs[1] = new Demo1::CommitTransaction(Demo1::FlyweightFactory::getIcon("select"),
		Demo1::FlyweightFactory::getIcon("stop"), Demo1::FlyweightFactory::getIcon("undo"));

		for (int i = 0; i < 2; i++)
			dialogs[i]->draw();

		Demo1::FlyweightFactory::reportTheIcons();

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}

