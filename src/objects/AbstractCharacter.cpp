#include "AbstractCharacter.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include "components/actions/tilemap/Move.h"
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
	auto *move{findComponent(ACT_Move)};
	qreal originalSpeed{75.75757625};
	qreal nominalSpeed{3*originalSpeed};
	qreal speed{percent*nominalSpeed*0.01};

	if (move)
		static_cast<Move *>(move)->setSpeed(speed);
}

void AbstractCharacter::reset()
{
	AbstractGameObject::reset();

	setBrush(paletteColor(colorRole()));
}
