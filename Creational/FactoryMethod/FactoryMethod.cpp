/*
The program demonstrates the Factory Method pattern.
	Type 1: Factory method.

	Intent:
		-> Define an interface for creating an object, but let subclasses decide which class to instantiate.
		-> Factory Method lets a class defer instantiation to subclasses.

	Also Known As:
		-> Virtual Constructor.

	Applicability:
		-> A class can't anticipate the class of objects it must create.
		-> A class wants its subclasses to specify the objects it creates.
		-> Classes delegate responsibility to one of several helper subclasses, and you want to localize
			the knowledge of which helper subclass is the delegate.

	Participants:
		(a).Product
			-> Defines the interface of objects the factory method creates.
		(b).ConcreteProduct
			-> Implements the Product interface.
		(c).Creator
			-> Declares the factory method, which returns an object of type	Product.Creator may also define a
				default implementation of the factory method that returns a default ConcreteProduct	object.
			-> May call the factory method to create a Product object.
		(d)ConcreteCreator
			-> Overrides the factory method to return an instance of a ConcreteProduct.

	Collaborations:
		-> Creator relies on its subclasses to define the factory method so that it returns an instance of the
			appropriate ConcreteProduct.

	Consequences (Read once more):
		-> Factory methods eliminate the need to bind application-specific classes into your code.
		-> The code only deals with the Product interface; therefore it can work with any user-defined ConcreteProduct classes.
		-> A potential disadvantage of factory methods is that clients might have to subclass the Creator class just to create
			a particular ConcreteProduct object.
		-> Factory Method gives subclasses a hook for providing an extended version of an object.
		-> Connects parallel class hierarchies.

	Implementation:
		1.Non parameterized factory methods
			-> Creates only one kind of Product.
		2.Parameterized factory methods
			-> Another variation on the pattern lets the factory method create multiple kinds of products.
			-> The factory method takes a parameter that identifies the kind of object to create.
			-> All objects the factory method creates will share the Product interface.

	1> Demo1
		-> Demonstrates the use of non parameterized factory method.
		-> Also shows an variant of parallel class hierarchies where Product and ProjectCreator can be thought as
			parallel class hierarchies. 
*/


#include<iostream>

class Product
{
public:
	virtual void UseProject() = 0;
};

class UnisysProduct : public Product
{
public:
	virtual void UseProject()
	{
		std::cout<<"Use UnisysProduct"<<std::endl;
	}
};

class IBMProduct : public Product
{
public:
	virtual void UseProject()
	{
		std::cout<<"Use IBMProduct"<<std::endl;
	}
};

class ProjectCreator
{
public:
	virtual Product* createProject() = 0;
	Product* newProject()
	{
		std::cout<<"Creating Product"<<std::endl;
		return createProject();
	}
};

class UnisysProjectCreator : public ProjectCreator
{
public:
	virtual Product* createProject()
	{
		std::cout<<"UnisysProjectCreator called"<<std::endl;
		return new UnisysProduct;
	}
};

class IBMProjectCreator : public ProjectCreator
{
public:
	virtual Product* createProject()
	{
		std::cout<<"IBMProjectCreator called"<<std::endl;
		return new IBMProduct;
	}
};

int main()
{
	Product* proj = NULL;
	ProjectCreator* projCreator = NULL;

	projCreator = new UnisysProjectCreator;
	proj = projCreator->createProject();
	proj->UseProject();

	projCreator = new IBMProjectCreator;
	proj = projCreator->createProject();
	proj->UseProject();

	return 0;
}
