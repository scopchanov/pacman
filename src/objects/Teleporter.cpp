#include "Teleporter.h"
#include "PathBuilder.h"
#include "GameGlobals.h"
#include "behaviors/Teleporting.h"
#include <QPen>

Teleporter::Teleporter(GameObject *parent) :
	GameObject(parent)
{
	setPath(PathBuilder::teleporterPath());
	setPen(QPen(Qt::transparent));
	setBrush(Qt::transparent);
	setFlag(QGraphicsItem::ItemHasNoContents);
}

int Teleporter::objectType() const
{
	return OBJ_Teleporter;
}

void Teleporter::setup(const QPointF &src, const QPointF &dst)
{
	auto *teleporting{new Teleporting(this)};

	addBehavior(teleporting);
	teleporting->setDestination(dst);

	setPos(src);
}
