#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPathItem>

class AbstractBehavior;

class GameObject : public QGraphicsPathItem
{
public:
	enum ItemType : int {
		IT_GameObject = QGraphicsItem::UserType
	};

	explicit GameObject(GameObject *parent = nullptr);
    ~GameObject();

    void addBehavior(AbstractBehavior *behavior);
    int behaviorCount() const;
	AbstractBehavior *behavior(int n) const;
	AbstractBehavior *findBehavior(int type) const;
	int type() const override;

	virtual void reset();
	void advance(int phase) override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

	void deleteLater();

private:
	QList<AbstractBehavior *> _behaviors;
};

#endif // GAMEOBJECT_H
