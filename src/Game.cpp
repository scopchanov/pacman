#include "Game.h"
#include "Message.h"
#include "StartupSequence.h"
#include "AiStateMachine.h"
#include "BonusText.h"
#include "GameClock.h"
#include "GameStatus.h"
#include "GameScene.h"
#include "Grid.h"
#include "Tilemap.h"
#include "AudioEngine.h"
#include "actions/DeleteGameObject.h"
#include "behaviors/Delaying.h"
#include "behaviors/EnemyController.h"
#include "objects/Player.h"
#include "objects/Deenergizer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHash>

Game::Game(QObject *parent) :
	QObject(parent),
	_clock{new GameClock(this)},
	_scene{new GameScene(this)},
	_status{new GameStatus(this)},
	_stateMachine{new AiStateMachine(this)},
	_audioEngine{new AudioEngine(this)},
	_grid{new Grid(this)},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_player{new Player()},
	_deenergizer{new Deenergizer()}
{
	_scene->addItem(_walls);
	_scene->addItem(_dots);
	_scene->addItem(_player);
	_scene->addItem(_deenergizer);

	connect(_clock, &GameClock::tick, _scene, &GameScene::makeTurn);
	connect(_audioEngine, &AudioEngine::victoryTunePlayed, this, &Game::playerWins);
	connect(_audioEngine, &AudioEngine::funeralTunePlayed, this, &Game::onFuneralTunePlayed);
}

GameClock *Game::clock() const
{
	return _clock;
}

QGraphicsScene *Game::scene() const
{
	return _scene;
}

InputSystem *Game::inputSystem() const
{
	return _scene->inputSystem();
}

GameStatus *Game::status() const
{
	return _status;
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

Player *Game::player() const
{
	return _player;
}

QList<Enemy *> &Game::enemies()
{
	return _enemies;
}

Game &Game::ref()
{
	static Game game;

	return game;
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
	text->setPos(_player->pos());

	_scene->addItem(text);
	_status->increaseScore(points);
	_audioEngine->playEffect(AudioEngine::SND_EnemyEaten);
}

void Game::onPlayerEnergized()
{
	_deenergizer->reset();
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
