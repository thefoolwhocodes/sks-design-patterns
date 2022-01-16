/*
The program demonstrates the following:

	Intent:
		-> Provide an interface for creating families of related or dependent objects without specifying their
			concrete classes (Factory Method creates one product family).

	Also Known As:
		-> Kit.	

	Applicability:
		-> A system should be independent of how its products are created,composed, and represented.
		-> A system should be configured with one of multiple families of products.
		-> A family of related product objects is designed to be used together, and you need to enforce this constraint.
		-> You want to provide a class library of products, and you want to reveal just their interfaces, not their
			implementations.

	Participants:
		(a).AbstractFactory
			-> Declares an interface for operations that create abstract product objects.
		(b).ConcreteFactory
			-> Implements the operations to create concrete product objects.
		(c).AbstractProduct
			-> Declares an interface for a type of product object.
		(d).ConcreteProduct (MotifWindow, MotifScrollBar)
			-> Defines a product object to be created by the corresponding concrete factory.
			-> Implements the AbstractProduct interface.
		(e).Client
			-> Uses only interfaces declared by AbstractFactory and	AbstractProduct classes.

	Collaborations:
		-> Normally a single instance of a ConcreteFactory class is created at run-time. This concrete factory creates
			product objects having a particular implementation. To create different product objects, clients should use
			a different concrete factory.
		-> AbstractFactory defers creation of product objects to its ConcreteFactory subclass.

	Demo1)
		Inter related class explanations:
			It has a abstract class ConfigurationManager that has two derived types for Unisys and IBM
			It has a abstract class OpeartionsManager that has two derived types for Unisys and IBM
		Factory details:
			It has a abstract class SystemManagementAbstractFactory that has two derived types for Unisys and IBM
			The derived classed Unisys and IBM has one extra added method for creating new type that is OpeartionsManager.

	For every new class hierarchy added that has two types for Unisys and IBM one extra virtual method will be introduced
		in the factory.

*/

#include<iostream>

namespace Demo1
{
	//Inter related class declarations
	class ConfigurationManager
	{
	public:
		virtual void useConfigurationManager()=0;
	};

	//Type A
	class UnisysConfigurationManager : public ConfigurationManager
	{
	public:
		void useConfigurationManager()
		{
			std::cout<<"Use UnisysConfigurationManager"<<std::endl;
		}
	};

	//Type B
	class IBMConfigurationManager : public ConfigurationManager
	{
	public:
		void useConfigurationManager()
		{
			std::cout<<"Use IBMConfigurationManager"<<std::endl;
		}
	};

	class OperationsManager
	{
	public:
		virtual void useOperationsManager()=0;
	};

	//Type A
	class UnisysOperationsManager : public OperationsManager
	{
	public:
		virtual void useOperationsManager()
		{
			std::cout<<"Use UnisysOperationsManager"<<std::endl;
		}
	};

	//Type B
	class IBMOperationsManager : public OperationsManager
	{
	public:
		virtual void useOperationsManager()
		{
			std::cout<<"Use IBMOperationsManager"<<std::endl;
		}
	};


	//Factory class declarations
	class SystemManagementAbstractFactory
	{
	public:
		virtual ConfigurationManager* createConfigurationManager() = 0;
		virtual OperationsManager* createOpertionsManager() = 0;
	};

	//Type A Concrete Factory
	class UnisysSMConcreteFactory : public SystemManagementAbstractFactory
	{
	public:
		virtual ConfigurationManager* createConfigurationManager()
		{
			return new UnisysConfigurationManager;
		}
		virtual OperationsManager* createOpertionsManager()
		{
			return new UnisysOperationsManager;
		}
	};

	//Type B Concrete Factory
	class IBMSMConcreteFactory : public SystemManagementAbstractFactory
	{
	public:
		virtual ConfigurationManager* createConfigurationManager()
		{
			return new IBMConfigurationManager;
		}
		virtual OperationsManager* createOpertionsManager()
		{
			return new IBMOperationsManager;
		}
	};
};

int main()
{
	std::cout<<"Demo1 starts"<<std::endl;
	{
		//Type A kind of implementation
		Demo1::SystemManagementAbstractFactory* unisysSMFactory = new Demo1::UnisysSMConcreteFactory;
		Demo1::ConfigurationManager* cm = unisysSMFactory->createConfigurationManager();
		Demo1::OperationsManager* om = unisysSMFactory->createOpertionsManager();
		cm->useConfigurationManager();
		om->useOperationsManager();
	}
	{
		//Type B kind of implementation
		Demo1::SystemManagementAbstractFactory* ibmSMFactory = new Demo1::IBMSMConcreteFactory;
		Demo1::ConfigurationManager* cm = ibmSMFactory->createConfigurationManager();
		Demo1::OperationsManager* om = ibmSMFactory->createOpertionsManager();
		cm->useConfigurationManager();
		om->useOperationsManager();
	}
	std::cout<<"Demo1 ends"<<std::endl;

	return 0;
}
