#ifndef ABSTRACTPERSONALITY_H
#define ABSTRACTPERSONALITY_H

#include <QPointF>

class AbstractGameObject;
class Player;
class Grid;
class Vector2;

class AbstractPersonality
{
public:
	explicit AbstractPersonality(AbstractGameObject *parent = nullptr);
	virtual ~AbstractPersonality() = default;

	AbstractGameObject *parent() const;
	void setParent(AbstractGameObject *parent);
	int colorRole() const;
	void setColorRole(int role);
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &point);
	virtual int type() const = 0;

	virtual Vector2 calculateTarget() const = 0;

protected:
	Player *player() const;
	Grid *grid() const;
	Vector2 playerCell() const;

private:
	AbstractGameObject *_parent;
	int _colorRole;
	QPointF _scatterTarget;
};

#endif // ABSTRACTPERSONALITY_H
