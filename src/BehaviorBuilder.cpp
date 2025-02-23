#include "BehaviorBuilder.h"
#include "Factory.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "GameLevel.h"
#include "actions/EnergizePlayer.h"
#include "actions/ScareEnemies.h"
#include "behaviors/AbstractAnimatingBehavior.h"
#include "behaviors/AbstractOrientatingBehavior.h"
#include "behaviors/Moving.h"
#include "behaviors/Coloring.h"
#include "behaviors/Moving.h"
#include "behaviors/Coloring.h"
#include "behaviors/DotsEating.h"
#include "behaviors/EnemyControlling.h"
#include "behaviors/EnemyEating.h"
#include "behaviors/Energizing.h"
#include "behaviors/Killing.h"
#include "behaviors/PlayerControlling.h"
#include "behaviors/Spawning.h"
#include "behaviors/Teleporting.h"

BehaviorBuilder::BehaviorBuilder(QObject *parent) :
	QObject{parent},
	_gameObject{nullptr}
{

}

void BehaviorBuilder::setGameObject(AbstractGameObject *gameObject)
{
	_gameObject = gameObject;
}

void BehaviorBuilder::addColoring(const QColor &color)
{
	auto *coloring{new Coloring()};

	coloring->setColor(color);

	_gameObject->addBehavior(coloring);
	_gameObject->setBrush(color);
}

void BehaviorBuilder::addSpawning(const QPointF &position)
{
	auto *spawning{new Spawning()};

	spawning->setPosition(position);

	_gameObject->addBehavior(spawning);
}

void BehaviorBuilder::addMoving(int direction)
{
	auto *moving{new Moving()};

	moving->setTilemap(Game::ref().level()->walls());
	moving->setInitialDirection(dir2vec(direction));

	_gameObject->addBehavior(moving);
}

void BehaviorBuilder::addControlling(int type)
{
	auto *controller{Factory::createControlling(type)};

	controller->setMoving(moving());

	_gameObject->addBehavior(controller);
}

void BehaviorBuilder::addOrientating(int type)
{
	auto *orientating{Factory::createOrientating(type)};

	orientating->setMoving(moving());

	_gameObject->addBehavior(orientating);
}

void BehaviorBuilder::addAnimating(int type)
{
	_gameObject->addBehavior(Factory::createAnimating(type));
}

void BehaviorBuilder::addDotsEating()
{
	auto *dotsEating{new DotsEating()};
	auto *eventDotEaten{new GameEvent()};
	auto *eventPlayerWins{new GameEvent()};

	dotsEating->setTilemap(Game::ref().level()->dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	_gameObject->addBehavior(dotsEating);

	connect(eventDotEaten, &GameEvent::triggered,
			&Game::ref(), &Game::onDotEaten);
	connect(eventPlayerWins, &GameEvent::triggered,
			&Game::ref(), &Game::onPlayerWins);
}

void BehaviorBuilder::addEnemyEating()
{
	auto *enemyEating{new EnemyEating()};
	auto *eventEnemyEaten{new GameEvent()};

	enemyEating->setEvent(eventEnemyEaten);
	enemyEating->setEnabled(false);

	_gameObject->addBehavior(enemyEating);

	connect(eventEnemyEaten, &GameEvent::triggered,
			&Game::ref(), &Game::onEnemyEaten);
}

void BehaviorBuilder::addKilling()
{
	auto *killing{new Killing()};
	auto *eventPlayerDied{new GameEvent()};

	killing->setEventPlayerDies(eventPlayerDied);

	_gameObject->addBehavior(killing);

	connect(eventPlayerDied, &GameEvent::triggered,
			&Game::ref(), &Game::onPlayerDies);
}

void BehaviorBuilder::addEnergizing()
{
	auto *energizing{new Energizing()};
	auto *actEnergizePlayer{new EnergizePlayer(energizing)};
	auto *actFrightenEnemies{new ScareEnemies(energizing)};
	auto *eventPlayerEnergized{new GameEvent()};

	energizing->setEvent(eventPlayerEnergized);
	energizing->addAction(actEnergizePlayer);
	energizing->addAction(actFrightenEnemies);

	_gameObject->addBehavior(energizing);

	QObject::connect(eventPlayerEnergized, &GameEvent::triggered,
					 &Game::ref(), &Game::onPlayerEnergized);
}

void BehaviorBuilder::addTeleporting(const QPointF &destination)
{
	auto *teleporting{new Teleporting()};

	teleporting->setDestination(destination);

	_gameObject->addBehavior(teleporting);
}

Moving *BehaviorBuilder::moving() const
{
	auto *behavior{_gameObject->findBehavior(BT_Moving)};

	return behavior ? static_cast<Moving *>(behavior) : nullptr;
}

Vector2 BehaviorBuilder::dir2vec(int direction) const
{
	return QHash<int, Vector2>{{0, V2_LEFT}, {1, V2_UP}, {2, V2_RIGHT},
							   {3, V2_DOWN}}.value(direction);
}
