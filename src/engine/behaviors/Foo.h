#ifndef FOO_H
#define FOO_H

#include <QObject>

class EnemyController;

class Foo : public QObject
{
	Q_OBJECT
public:
	explicit Foo(QObject *parent = nullptr);

	void setFoo(EnemyController *ctrl);

	void dodd();

private:
	EnemyController *m_c;
signals:
};

#endif // FOO_H
