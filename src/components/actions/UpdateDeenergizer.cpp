#include "UpdateDeenergizer.h"
#include "AbstractGameObject.h"
#include "GameGlobals.h"
#include "PathBuilder.h"
#include "components/behaviors/Delaying.h"
#include <QGraphicsScene>

UpdateDeenergizer::UpdateDeenergizer(AbstractComponent *parent) :
	AbstractAction(parent)
{

}

int UpdateDeenergizer::type() const
{
	return ACT_UpdateDeenergizer;
}

void UpdateDeenergizer::reset()
{
	updateDeenergizer(0);
}

void UpdateDeenergizer::performTasks()
{
	auto *component{gameObject()->findComponent(BT_Delaying)};

	if (!component || !component->isEnabled())
		return;

	updateDeenergizer(barLength(component));
}

void UpdateDeenergizer::updateDeenergizer(qreal len)
{
	gameObject()->setPath(PathBuilder::dynamicObjectPath(OBJ_Deenergizer, len));
	gameObject()->update();
}

qreal UpdateDeenergizer::barLength(AbstractComponent *component) const
{
	auto *delaying{static_cast<Delaying *>(component)};

	return 648*(1 - delaying->time()/delaying->duration());
}
