#ifndef ABSTRACTPERSONALITY_H
#define ABSTRACTPERSONALITY_H

#include <QObject>

class GameObject;
class Vector2;

class AbstractPersonality : public QObject
{
	Q_OBJECT
public:
	explicit AbstractPersonality(QObject *parent = nullptr);

	GameObject *player() const;
	void setPlayer(GameObject *player);

	virtual Vector2 calculateTargetPosition() const = 0;

private:
	GameObject *_player;
};

#endif // ABSTRACTPERSONALITY_H
