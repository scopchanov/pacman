#include "GameObject.h"
#include "engine/GameScene.h"
#include "behaviors/AbstractBehavior.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>

GameObject::GameObject(GameObject *parent) :
	QGraphicsPathItem(parent)
{
#ifdef DEBUG
	auto *item{new QGraphicsRectItem(-12, -12, 24, 24, this)};

	item->setBrush(Qt::green);
	item->setFlag(ItemStacksBehindParent);
#endif
}

GameObject::~GameObject()
{
	while (!_behaviors.isEmpty())
		delete _behaviors.takeFirst();
}

void GameObject::addBehavior(AbstractBehavior *behavior)
{
	_behaviors.append(behavior);
}

int GameObject::behaviorCount() const
{
	return _behaviors.count();
}

AbstractBehavior *GameObject::behavior(int n) const
{
	return _behaviors.at(n);
}

AbstractBehavior *GameObject::findBehavior(int type) const
{
	for (auto *behavior : std::as_const(_behaviors))
		if (behavior->type() == type)
			return behavior;

	return nullptr;
}

int GameObject::type() const
{
	return QGraphicsItem::UserType;
}

void GameObject::reset()
{
	for (auto *behavior : std::as_const(_behaviors))
		behavior->reset();
}

void GameObject::advance(int phase)
{
	if (!phase)
		return;

	for (auto *behavior : std::as_const(_behaviors))
		behavior->execute();
}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	painter->save();
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->setClipping(true);
	painter->setClipRect(option->rect);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawPath(path());

#ifdef DEBUG
	painter->setPen(QPen(Qt::red, 1));
	painter->setBrush(Qt::transparent);
	painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));
#endif

	painter->restore();
}

void GameObject::deleteLater()
{
	if (scene())
		static_cast<GameScene *>(scene())->scheduleDelete(this);
	else
		delete this;
}
