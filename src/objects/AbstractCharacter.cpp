#include "AbstractCharacter.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include "behaviors/Moving.h"
#include <QBrush>

AbstractCharacter::AbstractCharacter(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{

}

QColor AbstractCharacter::paletteColor(int role) const
{
	return Game::ref().palette()->color(role);
}

void AbstractCharacter::setSpeed(qreal percent)
{
	auto *moving{findComponent(BT_Moving)};
	qreal originalSpeed{75.75757625};
	qreal nominalSpeed{3*originalSpeed};
	qreal speed{percent*nominalSpeed*0.01};

	if (moving)
		static_cast<Moving *>(moving)->setSpeed(speed);
}

void AbstractCharacter::reset()
{
	AbstractGameObject::reset();

	setBrush(paletteColor(colorRole()));
}
