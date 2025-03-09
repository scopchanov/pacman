#ifndef EATFRUIT_H
#define EATFRUIT_H

#include <AbstractAction.h>

class Fruit;

class EatFruit : public AbstractAction
{
	Q_OBJECT
public:
	explicit EatFruit(AbstractComponent *parent = nullptr);

	int type() const override;

protected:
	void performTasks() override;

private:
	void eatFruit(Fruit *fruit);

signals:
	void fruitEaten();
};

#endif // EATFRUIT_H
