#include "Energizer.h"
#include "PathBuilder.h"
#include "engine/Game.h"
#include "engine/GameEvent.h"
#include "engine/actions/EnergizePlayer.h"
#include "engine/actions/ScareEnemies.h"
#include "engine/behaviors/Energizing.h"
#include "engine/behaviors/EnergizerAnimation.h"
#include <QPen>

Energizer::Energizer(GameObject *parent) :
	GameObject(parent)
{
	auto *energizing{new Energizing(this)};
	auto *animation{new EnergizerAnimation(this)};
	auto *actEnergizePlayer{new EnergizePlayer(energizing)};
	auto *actFrightenGhosts{new ScareEnemies(energizing)};
	auto *eventPlayerEnergized{new GameEvent()};

	energizing->setEvent(eventPlayerEnergized);
	energizing->setPlayer(Game::ref().player());
	energizing->addAction(actEnergizePlayer);
	energizing->addAction(actFrightenGhosts);

	setPath(PathBuilder::animatedObjectPath(PathBuilder::GO_Energizer, 16));
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);

	addBehavior(energizing);
	addBehavior(animation);

	QObject::connect(eventPlayerEnergized, &GameEvent::triggered,
					 &Game::ref(), &Game::onPlayerEnergized);
}
