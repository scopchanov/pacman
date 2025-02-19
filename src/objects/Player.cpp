#include "Player.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameGlobals.h"
#include "behaviors/Coloring.h"
#include "behaviors/CharacterMovement.h"
#include "behaviors/DotsEating.h"
#include "behaviors/EnemyEating.h"
#include "behaviors/PlayerAnimation.h"
#include "behaviors/PlayerController.h"
#include "behaviors/PlayerOrientation.h"

Player::Player(GameObject *parent) :
	Character(parent)
{

}

int Player::objectType() const
{
	return OBJ_Player;
}

void Player::setup()
{
	auto *eventDotEaten{new GameEvent()};
	auto *eventEnemyEaten{new GameEvent()};
	auto *eventPlayerWins{new GameEvent()};
	auto *coloring{new Coloring(this)};
	auto *playerController{new PlayerController(this)};
	auto *movement{new CharacterMovement(this)};
	auto *orientation{new PlayerOrientation(this)};
	auto *dotsEating{new DotsEating(this)};
	auto *enemyEating{new EnemyEating(this)};
	auto *animation{new PlayerAnimation(this)};

	coloring->setColor(Qt::white);

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(Game::ref().inputSystem());

	movement->setTilemap(Game::ref().walls());

	orientation->setMovement(movement);

	dotsEating->setTilemap(Game::ref().dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	enemyEating->setEvent(eventEnemyEaten);
	enemyEating->setEnabled(false);

	addBehavior(coloring);
	addBehavior(playerController);
	addBehavior(movement);
	addBehavior(orientation);
	addBehavior(dotsEating);
	addBehavior(enemyEating);
	addBehavior(animation);

	QObject::connect(eventDotEaten, &GameEvent::triggered, &Game::ref(), &Game::onDotEaten);
	QObject::connect(eventEnemyEaten, &GameEvent::triggered, &Game::ref(), &Game::onEnemyEaten);
	QObject::connect(eventPlayerWins, &GameEvent::triggered, &Game::ref(), &Game::onPlayerWins);
}
