#include "ObjectBuilder.h"
#include "Factory.h"
#include "Game.h"
#include "GameGlobals.h"
#include "AbstractGameObject.h"
#include "components/actions/EatEnemy.h"
#include "components/actions/EnergizePlayer.h"
#include "components/actions/ManageLevelState.h"
#include "components/actions/KillPlayer.h"
#include "components/actions/Spawn.h"
#include "components/actions/Teleport.h"
#include "components/actions/control/ControlEnemy.h"
#include "components/actions/orientate/AbstractOrientate.h"
#include "components/actions/tilemap/EatDot.h"
#include "components/actions/tilemap/Move.h"

ObjectBuilder::ObjectBuilder(QObject *parent) :
	QObject{parent},
	_gameObject{nullptr}
{

}

void ObjectBuilder::setGameObject(AbstractGameObject *gameObject)
{
	_gameObject = gameObject;
}

void ObjectBuilder::addManageLevelState(const StepDurations &stepDurations)
{
	auto *manageLevelState{new ManageLevelState()};

	for(const auto &pair : stepDurations)
		manageLevelState->setStepDuration(pair.first, pair.second);

	_gameObject->addComponent(manageLevelState);
}

void ObjectBuilder::addSpawn(const QPointF &position)
{
	auto *spawn{new Spawn()};

	spawn->setPosition(position);

	_gameObject->addComponent(spawn);
}

void ObjectBuilder::addMove(int direction)
{
	auto *move{new Move()};

	move->setInitialDirection(dir2vec(direction));

	_gameObject->addComponent(move);
}

void ObjectBuilder::addControl(int type)
{
	auto *control{Factory::createControl(type)};

	control->setMove(move());

	_gameObject->addComponent(control);
}

void ObjectBuilder::addOrientate(int type, Move *move)
{
	auto *orientate{Factory::createOrientate(type)};

	orientate->setMove(move);

	_gameObject->addComponent(orientate);
}

void ObjectBuilder::addAnimate(int type)
{
	_gameObject->addComponent(Factory::createAnimate(type));
}

void ObjectBuilder::addEatDot()
{
	auto *eatDot{new EatDot()};

	_gameObject->addComponent(eatDot);

	connect(eatDot, &EatDot::dotEaten, game(), &Game::onDotEaten);
	connect(eatDot, &EatDot::playerWon, game(), &Game::onPlayerWon);
}

void ObjectBuilder::addEatEnemy()
{
	auto *eatEnemy{new EatEnemy()};

	eatEnemy->setEnabled(false);

	_gameObject->addComponent(eatEnemy);

	connect(eatEnemy, &EatEnemy::enemyEaten, game(), &Game::onEnemyEaten);
}

void ObjectBuilder::addKillPlayer()
{
	auto *killPlayer{new KillPlayer()};

	_gameObject->addComponent(killPlayer);

	connect(killPlayer, &KillPlayer::playerDied, game(), &Game::onPlayerDied);
}

void ObjectBuilder::addEnergizePlayer()
{
	auto *energizePlayer{new EnergizePlayer()};

	_gameObject->addComponent(energizePlayer);

	QObject::connect(energizePlayer, &EnergizePlayer::playerEnergized,
					 game(), &Game::onPlayerEnergized);
}

void ObjectBuilder::addTeleport(const QPointF &destination)
{
	auto *teleport{new Teleport()};

	teleport->setDestination(destination);

	_gameObject->addComponent(teleport);
}

Game *ObjectBuilder::game() const
{
	return &Game::ref();
}

Move *ObjectBuilder::move() const
{
	auto *component{_gameObject->findComponent(ACT_Move)};

	return component ? static_cast<Move *>(component) : nullptr;
}

Vector2 ObjectBuilder::dir2vec(int direction) const
{
	return QHash<int, Vector2>{{0, V2_LEFT}, {1, V2_UP}, {2, V2_RIGHT},
							   {3, V2_DOWN}}.value(direction);
}
