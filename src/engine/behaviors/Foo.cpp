#include "Foo.h"
#include "EnemyController.h"

Foo::Foo(QObject *parent) :
	QObject{parent}
{

}

void Foo::setFoo(EnemyController *ctrl)
{
	m_c = ctrl;
}

void Foo::dodd()
{
	m_c->foo();
}
