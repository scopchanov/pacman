#include "Player.h"
#include "GameEngine.h"
#include "GameController.h"
#include "engine/GameScene.h"
#include "engine/GameEvent.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/PlayerAnimation.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"

Player::Player(GameObject *parent) :
	Character(parent)
{

}

void Player::setup(GameEngine *game)
{
	auto *gameTimer{game->gameController()->gameTimer()};
	auto *eventDotEaten{new GameEvent(game)};
	auto *eventPlayerWins{new GameEvent(game)};
	auto *playerController{new PlayerController(this)};
	auto *movement{new CharacterMovement(this)};
	auto *orientation{new PlayerOrientation(this)};
	auto *dotsEating{new DotsEating(this)};
	auto *animation{new PlayerAnimation(this)};

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(game->scene()->inputSystem());

	movement->setGameTimer(gameTimer);
	movement->setTilemap(game->walls());

	orientation->setMovement(movement);

	dotsEating->setGameTimer(gameTimer);
	dotsEating->setTilemap(game->dots());
	dotsEating->setEvent(DotsEating::ET_DotEaten, eventDotEaten);
	dotsEating->setEvent(DotsEating::ET_PlayerWins, eventPlayerWins);

	animation->setGameTimer(gameTimer);

	addBehavior(playerController);
	addBehavior(movement);
	addBehavior(orientation);
	addBehavior(dotsEating);
	addBehavior(animation);

	QObject::connect(eventDotEaten, &GameEvent::triggered, game, &GameEngine::onDotEaten);
	QObject::connect(eventPlayerWins, &GameEvent::triggered, game, &GameEngine::onPlayerWins);
}
