#ifndef DELETEGAMEOBJECT_H
#define DELETEGAMEOBJECT_H

#include "AbstractAction.h"

class GameObject;

class DeleteGameObject : public AbstractAction
{
public:
	explicit DeleteGameObject(AbstractBehavior *parent = nullptr);

	int type() const override;

	GameObject *gameObject() const;
	void setGameObject(GameObject *gameObject);

private:
	void performTask() override;

	GameObject *_gameObject;
};

#endif // DELETEGAMEOBJECT_H
