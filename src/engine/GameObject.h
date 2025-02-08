#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPathItem>

class AbstractBehavior;

class GameObject : public QGraphicsPathItem
{
public:
	explicit GameObject(GameObject *parent = nullptr);
    ~GameObject();

    void addBehavior(AbstractBehavior *behavior);
    int behaviorCount() const;
	AbstractBehavior *behavior(int n) const;
	AbstractBehavior *findBehavior(int type) const;
	int type() const override;

	void advance(int phase) override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
	QList<AbstractBehavior *> _behaviors;
};

#endif // GAMEOBJECT_H
