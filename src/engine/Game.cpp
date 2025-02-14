#include "Game.h"
#include "Message.h"
#include "StartupSequence.h"
#include "engine/AiStateMachine.h"
#include "engine/GameStatus.h"
#include "engine/GameScene.h"
#include "engine/GameClock.h"
#include "engine/Grid.h"
#include "engine/Pacman.h"
#include "engine/AudioEngine.h"
#include "engine/Tilemap.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/GameClock.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>

Game::Game(QObject *parent) :
	QObject(parent),
	_clock{new GameClock(this)},
	_status{new GameStatus(this)},
	_scene{new GameScene(this)},
	_audioEngine{new AudioEngine(this)},
	_grid{new Grid()},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_stateMachine{new AiStateMachine(this)},
	_pacman{new Pacman()}
{
	connect(_clock, &GameClock::tick, _scene, &GameScene::advance);
	connect(_audioEngine, &AudioEngine::victoryTunePlayed, this, &Game::playerWins);
	connect(_audioEngine, &AudioEngine::funeralTunePlayed, this, &Game::onFuneralTunePlayed);
}

GameClock *Game::clock() const
{
	return _clock;
}

GameStatus *Game::status() const
{
	return _status;
}

GameScene *Game::scene() const
{
	return _scene;
}

AiStateMachine *Game::stateMachine() const
{
	return _stateMachine;
}

Grid *Game::grid() const
{
	return _grid;
}

Tilemap *Game::walls() const
{
	return _walls;
}

Tilemap *Game::dots() const
{
	return _dots;
}

void Game::start()
{
	auto *sequence{new StartupSequence(this)};

	_scene->addItem(sequence->message());

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

void Game::restart()
{
	_status->reset();
	_stateMachine->reset();
	_scene->reset();
	_dots->clear();

	// buildTilemap(_dots, _dotMatrix, QPen(Qt::transparent), QBrush(0x999999));
	start();
}

void Game::reset()
{
	_stateMachine->reset();
	_scene->reset();
	start();
}

void Game::onDotEaten()
{
	_status->increaseScore(1);
	_audioEngine->playEffect(AudioEngine::SND_DotEaten);
}

void Game::onPlayerEnergized()
{
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
