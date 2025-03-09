#ifndef FRUIT_H
#define FRUIT_H

#include <AbstractGameObject.h>

class Fruit : public AbstractGameObject
{
public:
	explicit Fruit(AbstractGameObject *parent = nullptr);

	int objectType() const override;

	void reset() override;
};

#endif // FRUIT_H
