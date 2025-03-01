#ifndef SPAWN_H
#define SPAWN_H

#include <AbstractAction.h>
#include <QPointF>

class Spawn : public AbstractAction
{
public:
	explicit Spawn(AbstractComponent *parent = nullptr);

	QPointF position() const;
	void setPosition(const QPointF &point);
	int type() const override;

	void reset() override;

private:
	void respawn();

	QPointF _position;
};

#endif // SPAWN_H
