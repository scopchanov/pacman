#include "Game.h"
#include "Message.h"
#include "StartupSequence.h"
#include "BonusText.h"
#include "Clock.h"
#include "GameStatus.h"
#include "GameLevel.h"
#include "AudioEngine.h"
#include "components/actions/DeleteGameObject.h"
#include "components/behaviors/Delaying.h"
#include "objects/Player.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>

Game::Game(QObject *parent) :
	QObject(parent),
	_level{nullptr},
	_status{new GameStatus(this)},
	_audioEngine{new AudioEngine(this)}
{
	connect(_audioEngine, &AudioEngine::victoryTunePlayed,
			this, &Game::playerWins);
	connect(_audioEngine, &AudioEngine::funeralTunePlayed,
			this, &Game::onFuneralTunePlayed);
}

GameLevel *Game::level() const
{
	return _level;
}

Clock *Game::clock() const
{
	return _level->clock();
}

Palette *Game::palette() const
{
	return _level->palette();
}

InputSystem *Game::inputSystem() const
{
	return _level->inputSystem();
}

GameStatus *Game::status() const
{
	return _status;
}

Game &Game::ref()
{
	static Game game;

	return game;
}

void Game::newGame()
{
	_status->reset();

	if (_level)
		_level->deleteLater();

	_level = new GameLevel(this);
}

void Game::start()
{
	auto *sequence{new StartupSequence(this)};

	_level->addItem(sequence->message());

	connect(sequence, &StartupSequence::go, clock(), &Clock::start);

	sequence->start();
}

void Game::stop()
{
	clock()->stop();
}

void Game::resume()
{
	clock()->start();
}

void Game::reset()
{
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
	auto *delayedDeleting{new Delaying()};
	auto *actDeleteGameObject{new DeleteGameObject(delayedDeleting)};

	actDeleteGameObject->setGameObject(text);

	delayedDeleting->addComponent(actDeleteGameObject);
	delayedDeleting->setDuration(2);

	text->addComponent(delayedDeleting);
	text->setText(QString::number(points));
	text->setPos(_level->player()->pos());

	_level->addItem(text);
	_status->increaseScore(points);
	_audioEngine->playEffect(AudioEngine::SND_EnemyEaten);
}

void Game::onPlayerEnergized()
{
	_status->increaseScore(5);
	_audioEngine->playEffect(AudioEngine::SND_DotEaten);
}

void Game::onPlayerWon()
{
	clock()->stop();
	_audioEngine->playEffect(AudioEngine::SND_PlayerWins);
}

void Game::onPlayerDied()
{
	clock()->stop();
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
