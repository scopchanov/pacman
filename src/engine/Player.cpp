#include "Player.h"
#include "Game.h"
#include "engine/GameScene.h"
#include "engine/GameEvent.h"
#include "engine/behaviors/Coloring.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/EnemyEating.h"
#include "engine/behaviors/PlayerAnimation.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"

Player::Player(GameObject *parent) :
	Character(parent)
{

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
	playerController->setInputSystem(static_cast<GameScene *>(Game::ref().scene())->inputSystem());

	movement->setSpeed(181.818183);
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
