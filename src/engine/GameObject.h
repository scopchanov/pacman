#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPathItem>

class AbstractBehavior;

class GameObject : public QGraphicsPathItem
{
public:
    explicit GameObject(QGraphicsItem *parent = nullptr);
    ~GameObject();

    void addBehavior(AbstractBehavior *behavior);
    int behaviorCount() const;
    AbstractBehavior *behavior(int n);

    void advance(int phase) override;

private:
    QList<AbstractBehavior *> m_behaviors;
};

#endif // GAMEOBJECT_H
