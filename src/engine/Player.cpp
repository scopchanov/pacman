#include "Player.h"
#include "Game.h"
#include "engine/GameScene.h"
#include "engine/GameEvent.h"
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

void Player::setup(Game *game)
{
	auto *gameClock{game->clock()};
	auto *eventDotEaten{new GameEvent(game)};
	auto *eventPlayerWins{new GameEvent(game)};
	auto *playerController{new PlayerController(this)};
	auto *movement{new CharacterMovement(this)};
	auto *orientation{new PlayerOrientation(this)};
	auto *dotsEating{new DotsEating(this)};
	auto *enemyEating{new EnemyEating(this)};
	auto *animation{new PlayerAnimation(this)};

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(game->scene()->inputSystem());

	movement->setGameClock(gameClock);
	movement->setTilemap(game->walls());

	orientation->setMovement(movement);

	dotsEating->setGameClock(gameClock);
	dotsEating->setTilemap(game->dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	enemyEating->setDisabled(true);

	animation->setGameClock(gameClock);

	addBehavior(playerController);
	addBehavior(movement);
	addBehavior(orientation);
	addBehavior(dotsEating);
	addBehavior(enemyEating);
	addBehavior(animation);

	QObject::connect(eventDotEaten, &GameEvent::triggered, game, &Game::onDotEaten);
	QObject::connect(eventPlayerWins, &GameEvent::triggered, game, &Game::onPlayerWins);
}
