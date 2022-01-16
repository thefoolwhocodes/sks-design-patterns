#include<FactoryUser.h>

User::User(FactoryIndex id)
{
	_ptr = Base::Create(id);
}

User::~User()
{
	delete _ptr;
}

void User::doJob()
{
	_ptr->execute();
}
