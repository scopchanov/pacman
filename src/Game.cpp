#include "Game.h"
#include "Message.h"
#include "StartupSequence.h"
#include "Clock.h"
#include "GameStatus.h"
#include "GameLevel.h"
#include "AudioEngine.h"
#include "components/actions/DeleteGameObject.h"
#include "components/behaviors/Delaying.h"
#include "objects/BonusText.h"
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
	// auto *sequence{new StartupSequence(this)};

	// _level->addItem(sequence->message());

	// connect(sequence, &StartupSequence::go, clock(), &Clock::start);

	// sequence->start();

	clock()->start();
}

void Game::stop()
{
	clock()->stop();
}

void Game::resume()
{
	start();
}

void Game::reset()
{
	_level->reset();

	start();
}

void Game::onDotEaten()
{
	rewardPoints(1, AudioEngine::SND_DotEaten);

	_level->onDotEaten();
}

void Game::onEnemyEaten(const QPointF &position)
{
	int points{sender()->property("points").toInt()};

	rewardBonus(points, position, AudioEngine::SND_EnemyEaten);
}

void Game::onFruitEaten(const QPointF &position)
{
	rewardBonus(10, position, AudioEngine::SND_EnemyEaten);
}

void Game::onPlayerEnergized(const QPointF &position)
{
	rewardBonus(5, position, AudioEngine::SND_DotEaten);
}

void Game::onPlayerWon()
{
	stopGame(AudioEngine::SND_PlayerWins);
}

void Game::onPlayerDied()
{
	stopGame(AudioEngine::SND_PlayerDies);
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

void Game::rewardBonus(int points, const QPointF &position, int sfxIndex)
{
	showBonusText(points, position, 2);
	rewardPoints(points, sfxIndex);
}

void Game::showBonusText(int points, const QPointF &position, qreal duration)
{
	auto *text{new BonusText()};
	auto *delaying{new Delaying()};
	auto *deleteGameObject{new DeleteGameObject(delaying)};

	deleteGameObject->setGameObject(text);

	delaying->addComponent(deleteGameObject);
	delaying->setDuration(duration);

	text->addComponent(delaying);
	text->setText(QString::number(points));
	text->setPos(position);

	_level->addItem(text);
}

void Game::rewardPoints(int points, int sfxIndex)
{
	_status->increaseScore(points);
	playSoundEffect(sfxIndex);
}

void Game::stopGame(int sfxIndex)
{
	clock()->stop();
	playSoundEffect(sfxIndex);
}

void Game::playSoundEffect(int sfxIndex)
{
	_audioEngine->playEffect(static_cast<AudioEngine::EffectType>(sfxIndex));
}
