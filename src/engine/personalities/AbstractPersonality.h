#ifndef ABSTRACTPERSONALITY_H
#define ABSTRACTPERSONALITY_H

#include <QPointF>

class GameObject;
class Grid;
class Vector2;

class AbstractPersonality
{
public:
	enum PersonalityType : int {
		PT_Shadowing = 0,
		PT_Speeding,
		PT_Shying,
		PT_Poking
	};

	explicit AbstractPersonality(GameObject *parent = nullptr);
	virtual ~AbstractPersonality() = default;

	GameObject *parent() const;
	void setParent(GameObject *parent);
	GameObject *player() const;
	void setPlayer(GameObject *player);
	Grid *grid() const;
	void setGrid(Grid *grid);
	QPointF scatterTarget() const;
	void setScatterTarget(const QPointF &point);
	virtual int type() const = 0;

	virtual Vector2 calculateTarget() const = 0;

private:
	GameObject *_parent;
	GameObject *_player;
	Grid *_grid;
	QPointF _scatterTarget;
};

#endif // ABSTRACTPERSONALITY_H
