#include "Game.h"
#include "Message.h"
#include "StartupSequence.h"
#include "AiStateMachine.h"
#include "BonusText.h"
#include "GameClock.h"
#include "GameStatus.h"
#include "GameLevel.h"
#include "AudioEngine.h"
#include "GamePalette.h"
#include "actions/DeleteGameObject.h"
#include "behaviors/Delaying.h"
#include "behaviors/EnemyControlling.h"
#include "objects/Deenergizer.h"
#include "objects/Player.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>

Game::Game(QObject *parent) :
	QObject(parent),
	_clock{new GameClock(this)},
	_level{new GameLevel(this)},
	_status{new GameStatus(this)},
	_palette{new GamePalette(this)},
	_stateMachine{new AiStateMachine(this)},
	_audioEngine{new AudioEngine(this)}
{
	stateMachine()->setGameClock(_clock);

	connect(_clock, &GameClock::tick, _level, &GameLevel::makeTurn);
	connect(_audioEngine, &AudioEngine::victoryTunePlayed, this, &Game::playerWins);
	connect(_audioEngine, &AudioEngine::funeralTunePlayed, this, &Game::onFuneralTunePlayed);
}

GameClock *Game::clock() const
{
	return _clock;
}

GameLevel *Game::level() const
{
	return _level;
}

InputSystem *Game::inputSystem() const
{
	return _level->inputSystem();
}

GameStatus *Game::status() const
{
	return _status;
}

GamePalette *Game::palette() const
{
	return _palette;
}

AiStateMachine *Game::stateMachine() const
{
	return _stateMachine;
}

Game &Game::ref()
{
	static Game game;

	return game;
}

void Game::start()
{
	auto *sequence{new StartupSequence(this)};

	_level->addItem(sequence->message());

	connect(sequence, &StartupSequence::go, _clock, &GameClock::start);

	sequence->start();
}

void Game::stop()
{
	_clock->stop();
}

void Game::resume()
{
	_clock->start();
}

void Game::reset()
{
	_stateMachine->reset();
	_level->reset();

	start();
}

void Game::onDotEaten()
{
	_status->increaseScore(1);
	_audioEngine->playEffect(AudioEngine::SND_DotEaten);
}

void Game::onEnemyEaten()
{
	int points{sender()->property("points").toInt()};
	auto *text{new BonusText()};
	auto *delayedDeleting{new Delaying(text)};
	auto *actDeleteGameObject{new DeleteGameObject(delayedDeleting)};

	actDeleteGameObject->setGameObject(text);

	delayedDeleting->addAction(actDeleteGameObject);
	delayedDeleting->setDuration(2);

	text->addBehavior(delayedDeleting);
	text->setText(QString::number(points));
	text->setPos(_level->player()->pos());

	_level->addItem(text);
	_status->increaseScore(points);
	_audioEngine->playEffect(AudioEngine::SND_EnemyEaten);
}

void Game::onPlayerEnergized()
{
	_level->deenergizer()->reset();
	_status->increaseScore(5);
	_audioEngine->playEffect(AudioEngine::SND_DotEaten);
}

void Game::onPlayerWins()
{
	_clock->stop();
	_audioEngine->playEffect(AudioEngine::SND_PlayerWins);
}

void Game::onPlayerDies()
{
	_clock->stop();
	_audioEngine->playEffect(AudioEngine::SND_PlayerDies);
}

void Game::onFuneralTunePlayed()
{
	if (_status->lifesLeft()) {
		_status->removeLife();
		reset();
	} else {
		emit gameOver();
	}
}
