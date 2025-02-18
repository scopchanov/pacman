#include "Game.h"
#include "Message.h"
#include "PathBuilder.h"
#include "StartupSequence.h"
#include "AiStateMachine.h"
#include "BonusText.h"
#include "GameClock.h"
#include "GameStatus.h"
#include "GameScene.h"
#include "Grid.h"
#include "engine/Tilemap.h"
#include "AudioEngine.h"
#include "engine/actions/DeleteGameObject.h"
#include "engine/behaviors/Delaying.h"
#include "engine/behaviors/EnemyController.h"
#include "engine/objects/Deenergizer.h"
#include "engine/objects/Pacman.h"
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
	_grid{new Grid(this)},
	_walls{new Tilemap()},
	_dots{new Tilemap()},
	_stateMachine{new AiStateMachine(this)},
	_player{new Pacman()},
	_deenergizer{new Deenergizer()}
{
	_scene->addItem(_deenergizer);

	connect(_clock, &GameClock::tick, _scene, &GameScene::makeTurn);
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

Player *Game::player() const
{
	return _player;
}

QList<Enemy *> Game::enemies() const
{
	return _enemies;
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

	buildTilemap(_dots, _dotMatrix, QPen(Qt::transparent), QBrush(0x999999));
	start();
}

Game &Game::ref()
{
	static Game game;

	return game;
}

void Game::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix,
						const QPen &pen, const QBrush &brush)
{
	int m{0};

	for (const auto &row : matrix) {
		const QJsonArray &columns{row.toArray()};
		int n{0};

		for (const auto &column : columns) {
			const QJsonObject &element{column.toObject()};
			auto *tile{element.isEmpty() ? nullptr
										 : createTile(element["index"].toInt(),
													  pen, brush)};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

QGraphicsPathItem *Game::createTile(int index, const QPen &pen, const QBrush &brush)
{
	auto *tile{new QGraphicsPathItem()};

	tile->setPath(PathBuilder::tilePath(PathBuilder::TileType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
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
	// auto *text{new BonusText()};
	// auto *delayedDeleting{new Delaying(text)};
	// auto *actDeleteGameObject{new DeleteGameObject(delayedDeleting)};

	// actDeleteGameObject->setGameObject(text);

	// delayedDeleting->addAction(actDeleteGameObject);
	// delayedDeleting->setDuration(2);

	// text->addBehavior(delayedDeleting);
	// text->setText(QString::number(points));
	// text->setPos(_player->pos());

	// _scene->addItem(text);
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
