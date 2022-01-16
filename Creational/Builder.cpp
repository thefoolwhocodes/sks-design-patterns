/*
The program demonstrates the Builder pattern.

	Intent:
		-> It separates the construction of a complex object from its representation so that the same construction process can create
			different representations.
		-> Here the sub parts that is created may or may not be related to each other,as for example PartA and PartB are not related.

	Applicability:
		-> The algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
		-> The construction process must allow different representations for the object that's constructed.	

	Participants:
		(a).Builder (TextConverter)
			-> Specifies an abstract interface for creating parts of a Product object.
		(b).ConcreteBuilder (ASCIIConverter, TeXConverter,TextWidgetConverter)
			-> Constructs and assembles parts of the product by implementing the Builder interface.
			-> Defines and keeps track of the representation it creates.
			-> Provides an interface for retrieving the product (e.g.,GetASCIIText, GetTextWidget).
		(c).Director (RTFReader)
			-> Constructs an object using the Builder interface.
		(d).Product (ASCIIText, TeXText, TextWidget)
			-> Represents the complex object under construction.
			-> ConcreteBuilder builds the product's internal representation	and defines the process by which it's assembled.
			-> Includes classes that define the constituent parts, including interfaces for assembling the parts into the final result.

	Collaborations:
		-> The client creates the Director object and configures it with the desired Builder object.
		-> Director notifies the builder whenever a part of the product should be built.
		-> Builder handles requests from the director and adds parts to the product.
		-> The client retrieves the product from the builder.
*/

#include<iostream>
#include<string>

class UnisysSystemManager
{
public:
	UnisysSystemManager(){std::cout<<"Use UnisysSystemManager"<<std::endl;}
	void doWork(){std::cout<<"doWork UnisysSystemManager"<<std::endl;}
};

class IBMSystemManager
{
public:
	IBMSystemManager(){std::cout<<"Use IBMSystemManager"<<std::endl;}
	void doWork(){std::cout<<"doWork IBMSystemManager"<<std::endl;}
};

class SystemManagerBuilder
{
public:
	virtual void create() = 0;
	virtual void BuildPartA(){std::cout<<"Default implementation BuildPartA"<<std::endl;}
	virtual void BuildPartB(){std::cout<<"Default implementation BuildPartB"<<std::endl;}
	virtual void BuildPartC(){std::cout<<"Default implementation BuildPartC"<<std::endl;}
	virtual void BuildPartD(){std::cout<<"Default implementation BuildPartD"<<std::endl;}
};

class UnisysSystemManagerConcreteBuilder : public SystemManagerBuilder
{
private:
	UnisysSystemManager* systemManager;
public:
	void create(){systemManager =  new UnisysSystemManager;}
	void BuildPartA(){std::cout<<"Concrete implementation BuildPartA"<<std::endl;}
	void BuildPartB(){std::cout<<"Concrete implementation BuildPartB"<<std::endl;}
	UnisysSystemManager* getSystemManager(){return systemManager;}
};

class IBMSystemManagerConcreteBuilder : public SystemManagerBuilder
{
private:
	IBMSystemManager* systemManager;
public:
	void create(){systemManager =  new IBMSystemManager;}
	void BuildPartC(){std::cout<<"Concrete implementation BuildPartC"<<std::endl;}
	void BuildPartD(){std::cout<<"Concrete implementation BuildPartD"<<std::endl;}
	IBMSystemManager* getSystemManager(){return systemManager;}
};


class SystemManagerDirector
{
private:
	SystemManagerBuilder* builder;
public:
	void setBuilder(SystemManagerBuilder* buiderPtr){builder = buiderPtr;}
	void construct(std::string sys)
	{
		if("Unisys" == sys)
		{
			//Builder handles requests from the director and adds parts to the product
			builder->create();
			builder->BuildPartA();
			builder->BuildPartB();
		}
		else if ("IBM" == sys)
		{
			//Builder handles requests from the director and adds parts to the product
			builder->create();
			builder->BuildPartC();
			builder->BuildPartD();
		}
	}
};

int main()
{
	UnisysSystemManagerConcreteBuilder* unisysSMBuilder = new UnisysSystemManagerConcreteBuilder;
	SystemManagerDirector* smCreator = new SystemManagerDirector;
	//Configure the director with desired builder object
	smCreator->setBuilder(unisysSMBuilder);
	smCreator->construct("Unisys");
	//Ready to use (assembled) object should be taken directly from concrete builder
	UnisysSystemManager* usm = unisysSMBuilder->getSystemManager();
	usm->doWork();

	IBMSystemManagerConcreteBuilder* ibmSMBuilder = new IBMSystemManagerConcreteBuilder;
	//Configure the director with desired builder object
	smCreator->setBuilder(ibmSMBuilder);
	smCreator->construct("IBM");
	//Ready to use (assembled) object should be taken directly from concrete builder
	IBMSystemManager* ism = ibmSMBuilder->getSystemManager();
	ism->doWork();

	return 0;
}
