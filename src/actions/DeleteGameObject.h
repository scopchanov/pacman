#ifndef DELETEGAMEOBJECT_H
#define DELETEGAMEOBJECT_H

#include "AbstractAction.h"

class AbstractGameObject;

class DeleteGameObject : public AbstractAction
{
public:
	explicit DeleteGameObject(AbstractBehavior *parent = nullptr);

	int type() const override;

	AbstractGameObject *gameObject() const;
	void setGameObject(AbstractGameObject *gameObject);

private:
	void performTask() override;

	AbstractGameObject *_gameObject;
};

#endif // DELETEGAMEOBJECT_H
