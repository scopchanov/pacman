#ifndef EATENEMY_H
#define EATENEMY_H

#include <AbstractAction.h>

class Enemy;

class EatEnemy : public AbstractAction
{
	Q_OBJECT
public:
	explicit EatEnemy(AbstractComponent *parent = nullptr);

	int type() const override;

	void reset() override;

protected:
	void performTasks() override;

private:
	void eatEnemy(Enemy *enemy);
	int points() const;

	int _enemiesEaten;

signals:
	void enemyEaten(const QPointF &position);
};

#endif // EATENEMY_H
