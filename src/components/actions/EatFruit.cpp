#include "EatFruit.h"
#include "GameGlobals.h"
#include "objects/Fruit.h"

EatFruit::EatFruit(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int EatFruit::type() const
{
	return ACT_EatFruit;
}

void EatFruit::performTasks()
{
	const auto &collidingObjects{gameObject()->collidingObjects()};

	for (auto *object : collidingObjects)
		if (object->objectType() == OBJ_Fruit)
			eatFruit(static_cast<Fruit *>(object));
}

void EatFruit::eatFruit(Fruit *fruit)
{
	fruit->deleteLater();

	emit fruitEaten(fruit->pos());
}
