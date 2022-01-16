/* The program demonstrates the Factory Method (Virtual Constructor) pattern.
	Type 2: Parameterized factory method.
	
	Intent:	
		-> Decouple object creation from its type.
		-> To create a copy of an object or a new object without knowing its concrete type.
	
	1> Demo1: Simple implementation of Virtual Constructor.
		-> User class is open for modifications for any new concrete class addition in Base class Inheritance tree (classes served by FactoryMethod).
		-> Same can be proved by adding new concrete class named "Derived4" in FactoryMethod and passing the index of "DERIVED4" from main after commenting the line in "compile.sh" that compiles "User" class.
*/

#include "FactoryUser.h"
#include "FactoryMethod.h"

#include<iostream>

int main()
{
	User usrObj(DERIVED4);
	usrObj.doJob();
}
