#include "Energizer.h"
#include "Game.h"
#include "GameEvent.h"
#include "PathBuilder.h"
#include "actions/EnergizePlayer.h"
#include "actions/ScareEnemies.h"
#include "behaviors/Energizing.h"
#include "behaviors/EnergizerAnimation.h"
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
