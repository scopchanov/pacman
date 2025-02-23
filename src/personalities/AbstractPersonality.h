#ifndef ABSTRACTPERSONALITY_H
#define ABSTRACTPERSONALITY_H

#include <QPointF>

class GameObject;
class Player;
class Grid;
class Vector2;

class AbstractPersonality
{
public:
	explicit AbstractPersonality(GameObject *parent = nullptr);
	virtual ~AbstractPersonality() = default;

	GameObject *parent() const;
	void setParent(GameObject *parent);
	Player *player() const;
	Grid *grid() const;
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &point);
	virtual int type() const = 0;

	virtual Vector2 calculateTarget() const = 0;

protected:
	Vector2 playerCell() const;

private:
	GameObject *_parent;
	QPointF _scatterTarget;
};

#endif // ABSTRACTPERSONALITY_H
