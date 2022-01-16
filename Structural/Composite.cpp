/*
	The program demonstrates the Composite pattern:
		-> Compose objects into tree structures to represent part-whole hierarchies.
		-> It allows clients to treat individual objects and composition of objects uniformly.
		-> The key to this pattern is an abstract class that represents both, primitives and their containers.

	Participants:
		(a).Component:
			-> Abstract class that represents both primitives and their containers.
			-> Component class provides default bahaviour implementation,Leaf and Composite class will override them.
			-> Declares an interface for accessing and managing its child components.
			-> (Optional) Defines an inteface for accessing a component's parent in the recursive fashion,
				and implements it if possible.
		(b).Leaf:
			-> Represents leaf objects in the composition.
			-> It has no children.
			-> Defines behaviour for primitive objects in the composition.
			-> They dont implement child related operations like addChild(),removeChild() and getChild().
		(c).Composite:
			-> Stores child Components.
			-> Composite specific behaviour is implemented.
			-> Implements child related operations like Add,Remove and getChild.
		(d).Client:
			-> Manipulates objects in the composition through the Component interface.

	Collaborations:
		-> Clients use the Component class interface to interact with objects in the composite structure. If the recipient
			is a Leaf, then the request is handled directly. If the recipient is a Composite, then it usually forwards
			requests to its child components, possibly performing additional operations before and/or after forwarding.

	How it is achieved:
		-> Create a interface that makes containers and containees interchangeable.
		-> A uniform behaviour that is exercised uniformly across all containee and container objects.
		-> Container classes uses polymorphism to delegate to their containee objects.
		-> Child management methods [e.g. addChild(), removeChild()] should normally be defined in the Composite class.
		   The desire to treat Leaf and Composite objects uniformly may require that these methods be promoted
		   to the abstract Component class.
		-> Client uses Component class interface to interact with objects in composite structure.
		   If recipient is Leaf,it handles the request directly.If recipient is Composite,then it forwards request to 
		   child components.
*/

#include <iostream>
#include <string>
#include <list>

namespace Demo1
{

	//--------------------------Exception class starts-------------------------------------------	

	class Exception
	{
		public:
		Exception(const char* message);

		private:
		Exception();
		std::string _message;
	};

	Exception::Exception(const char* message)
	{
		_message.assign(message);
	}

	Exception::Exception()
	{}

	//--------------------------Exception class ends---------------------------------------------
	

	//--------------------------Component class starts-------------------------------------------

	class Equipment
	{
		public:
		virtual ~Equipment();

		int getId();
		void getName(std::string& name);
		virtual int getNetPrice();

		virtual void add(Equipment* equipment);
		virtual void remove(Equipment* equipment);

		protected:
		Equipment(int id,const char* name,int price);
		int _id;
		std::string _name;
		int _price;
	};

	Equipment::~Equipment()
	{
		std::cout<<"Destroying object"<<std::endl;
	}

	int Equipment::getId()
	{
		return _id;
	}

	void Equipment::getName(std::string& name)
	{
		_name.assign(name);
	}

	int Equipment::getNetPrice()
	{
		return _price;
	}

	//If this add is called it means the calling element is of Leaf type.
	//And if it of Leaf type,add should not be allowed.
	void Equipment::add(Equipment* equipment)
	{
		throw Exception("Cannot add elements to leaf");
	}

	//If this add is called it means the calling element is of Leaf type.
	//And if it of Leaf type,remove should not be allowed.
	void Equipment::remove(Equipment* equipment)
	{
		throw Exception("Cannot remove elements from leaf");
	}

	Equipment::Equipment(int id,const char* name,int price)
	{
		_id = id;
		_name.assign(name);
		_price = price;
	}

	//--------------------------Component class ends-------------------------------------------


	//--------------------------Leaf class starts----------------------------------------------

	class FloppyDisk : public Equipment
	{
		public:
		FloppyDisk(int id,const char* name,int price);

		private:
		FloppyDisk();
	};

	FloppyDisk::FloppyDisk(int id,const char* name,int price):Equipment(id,name,price)
	{}

	//--------------------------Leaf class ends-----------------------------------------------------


	//--------------------------Composite class starts----------------------------------------------

	class CompositeEquipment : public Equipment
	{
		public:
		CompositeEquipment(int id,const char* name,int price);
		virtual ~CompositeEquipment();
		virtual int getNetPrice();
		virtual void add(Equipment* equipment);
		virtual void remove(Equipment* equipment);
		protected:
		CompositeEquipment();
		private:
		std::list<Equipment*> _equipment;
	};

	CompositeEquipment::CompositeEquipment(int id,const char* name,int price):Equipment(id,name,price)
	{}

	CompositeEquipment::~CompositeEquipment()
	{
		std::cout<<"CompositeEquipment Destructor called"<<std::endl;
		std::cout<<"CompositeEquipment details.Id:"<<_id<<" Name:"<<_name<<std::endl;
		for(std::list<Equipment*>::iterator it = _equipment.begin(); it!=_equipment.end();++it)
		{
			delete (*it);
		}
	}

	int CompositeEquipment::getNetPrice()
	{
		std::cout<<"Composite equipment size is:"<<_equipment.size();

		int totalPrice = Equipment::getNetPrice();
		
		for(std::list<Equipment*>::iterator it = _equipment.begin(); it!=_equipment.end();++it)
		{
			totalPrice = totalPrice + (*it)->getNetPrice();
		}
		return totalPrice;
	}

	void CompositeEquipment::add(Equipment* equipment)
	{
		_equipment.push_back(equipment);
	}

	void CompositeEquipment::remove(Equipment* equipment)
	{
		int id = equipment->getId();
		for(std::list<Equipment*>::iterator it = _equipment.begin(); it!=_equipment.end();++it)
		{
			if(id == (*it)->getId())
			{
				std::string equipmentName;
				(*it)->getName(equipmentName);
				std::cout<<"Successfully removed element with Id:"<<(*it)->getId()<<" Name:"<<equipmentName<<std::endl;

				//This line should call destructor
				delete (*it);
				_equipment.erase(it);
			}
		}
	}

	class Chassis : public CompositeEquipment
	{
		public:
		Chassis(int id,const char* name,int price);

		private:
		Chassis();
	};

	Chassis::Chassis(int id,const char* name,int price):CompositeEquipment(id,name,price)
	{}

	//--------------------------Composite class ends----------------------------------------------
};

int main()
{
	{
		std::cout<<"Start of Demo1"<<std::endl;

		Demo1::Equipment* eq1 = new Demo1::FloppyDisk(1,"Floppy Disk1",100);
		Demo1::Equipment* eq2 = new Demo1::FloppyDisk(2,"Floppy Disk2.1",500);

		Demo1::Equipment* eq3 = new Demo1::Chassis(3,"Base Chassis1.0",5000);
		eq3->add(eq1);
		eq3->add(eq2);

		Demo1::Equipment* eq4 = new Demo1::FloppyDisk(4,"Main Disk1",1000);
		Demo1::Equipment* eq5 = new Demo1::Chassis(5,"Main Chassis2.1",5000);
		eq5->add(eq3);
		eq5->add(eq4);

		std::cout<<"Net price of assembly is:"<<eq5->getNetPrice()<<std::endl;

		{
			//Following line should delete all the contained objects
			delete eq5;
		}

		std::cout<<"End of Demo1"<<std::endl;
	}
	return 0;
}