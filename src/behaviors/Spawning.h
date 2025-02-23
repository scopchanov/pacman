#ifndef SPAWNING_H
#define SPAWNING_H

#include <AbstractBehavior.h>
#include <QPointF>

class Spawning : public AbstractBehavior
{
public:
	explicit Spawning(AbstractGameObject *parent = nullptr);

	QPointF position() const;
	void setPosition(const QPointF &point);
	int type() const override;

	void reset() override;

private:
	void respawn();

	QPointF _position;
};

#endif // SPAWNING_H
