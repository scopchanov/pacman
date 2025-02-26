#include "ComponentBuilder.h"
#include "Factory.h"
#include "Game.h"
#include "Event.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "GameLevel.h"
#include "actions/EnergizePlayer.h"
#include "actions/KillPlayer.h"
#include "actions/Teleport.h"
#include "behaviors/AbstractOrientatingBehavior.h"
#include "behaviors/Moving.h"
#include "behaviors/Coloring.h"
#include "behaviors/Moving.h"
#include "behaviors/Coloring.h"
#include "behaviors/DotsEating.h"
#include "behaviors/EnemyControlling.h"
#include "behaviors/EnemyEating.h"
#include "behaviors/Energizing.h"
#include "behaviors/Spawning.h"

ComponentBuilder::ComponentBuilder(QObject *parent) :
	QObject{parent},
	_gameObject{nullptr}
{

}

void ComponentBuilder::setGameObject(AbstractGameObject *gameObject)
{
	_gameObject = gameObject;
}

void ComponentBuilder::addColoring(const QColor &color)
{
	auto *coloring{new Coloring()};

	coloring->setColor(color);

	_gameObject->addComponent(coloring);
	_gameObject->setBrush(color);
}

void ComponentBuilder::addSpawning(const QPointF &position)
{
	auto *spawning{new Spawning()};

	spawning->setPosition(position);

	_gameObject->addComponent(spawning);
}

void ComponentBuilder::addMoving(int direction)
{
	auto *moving{new Moving()};

	moving->setTilemap(Game::ref().level()->walls());
	moving->setInitialDirection(dir2vec(direction));

	_gameObject->addComponent(moving);
}

void ComponentBuilder::addControlling(int type)
{
	auto *controller{Factory::createControlling(type)};

	controller->setMoving(moving());

	_gameObject->addComponent(controller);
}

void ComponentBuilder::addOrientating(int type)
{
	auto *orientating{Factory::createOrientating(type)};

	orientating->setMoving(moving());

	_gameObject->addComponent(orientating);
}

void ComponentBuilder::addAnimating(int type)
{
	_gameObject->addComponent(Factory::createAnimating(type));
}

void ComponentBuilder::addDotsEating()
{
	auto *dotsEating{new DotsEating()};
	auto *eventDotEaten{new Event()};
	auto *eventPlayerWins{new Event()};

	dotsEating->setTilemap(Game::ref().level()->dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	_gameObject->addComponent(dotsEating);

	connect(eventDotEaten, &Event::triggered, game(), &Game::onDotEaten);
	connect(eventPlayerWins, &Event::triggered, game(), &Game::onPlayerWins);
}

void ComponentBuilder::addEnemyEating()
{
	auto *enemyEating{new EnemyEating()};
	auto *eventEnemyEaten{new Event()};

	enemyEating->setEvent(eventEnemyEaten);
	enemyEating->setEnabled(false);

	_gameObject->addComponent(enemyEating);

	connect(eventEnemyEaten, &Event::triggered, game(), &Game::onEnemyEaten);
}

void ComponentBuilder::addKilling()
{
	auto *killPlayer{new KillPlayer()};

	_gameObject->addComponent(killPlayer);

	connect(killPlayer, &KillPlayer::playerDied, game(), &Game::onPlayerDied);
}

void ComponentBuilder::addEnergizing()
{
	auto *energizing{new Energizing()};
	auto *energizePlayer{new EnergizePlayer(energizing)};

	energizePlayer->setGameObject(_gameObject);
	energizing->addComponent(energizePlayer);

	_gameObject->addComponent(energizing);

	QObject::connect(energizePlayer, &EnergizePlayer::playerEnergized,
					 game(), &Game::onPlayerEnergized);
}

void ComponentBuilder::addTeleport(const QPointF &destination)
{
	auto *teleport{new Teleport()};

	teleport->setDestination(destination);

	_gameObject->addComponent(teleport);
}

Game *ComponentBuilder::game() const
{
	return &Game::ref();
}

Moving *ComponentBuilder::moving() const
{
	auto *behavior{_gameObject->findComponent(BT_Moving)};

	return behavior ? static_cast<Moving *>(behavior) : nullptr;
}

Vector2 ComponentBuilder::dir2vec(int direction) const
{
	return QHash<int, Vector2>{{0, V2_LEFT}, {1, V2_UP}, {2, V2_RIGHT},
							   {3, V2_DOWN}}.value(direction);
}
