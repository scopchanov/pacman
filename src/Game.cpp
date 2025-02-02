#include "Game.h"
#include "Message.h"
#include "engine/PathBuilder.h"
#include "engine/GameTimer.h"
#include "engine/Scene.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/CameraFollow.h"
#include "engine/behaviors/Animation.h"
#include "engine/Tilemap.h"
#include "engine/Tile.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTimer>
#include <QGraphicsView>

Game::Game(QObject *parent) :
	QObject(parent),
	m_gameTimer{new GameTimer(this)},
	m_scene{new Scene(this)},
	m_message(new Message()),
	m_player{nullptr}
{
	m_message->setBasePosition(360, 444);
	m_gameTimer->setScene(m_scene);
}

Scene *Game::scene() const
{
	return m_scene;
}

bool Game::configure(const QJsonObject &json)
{
	const QJsonArray &wallMatrix{json.value("walls").toArray()};
	const QJsonArray &dotMatrix{json.value("dots").toArray()};
	int rows{json.value("gridSize").toObject().value("rows").toInt()};
	int columns{json.value("gridSize").toObject().value("columns").toInt()};
	qreal width{json.value("cellSize").toObject().value("width").toDouble()};
	qreal height{json.value("cellSize").toObject().value("height").toDouble()};
	const QSizeF &cellSize{width, height};

	auto *tmLayout{createTilemap(rows, columns, cellSize)};
	auto *tmDots{createTilemap(rows, columns, cellSize)};
	m_player = createPlayer(tmLayout, tmDots);

	buildTilemap(tmLayout, wallMatrix, QPen(QColor(0x00A3FF), 4), QBrush(Qt::transparent));
	buildTilemap(tmDots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	m_scene->addItem(m_player);
	m_scene->addItem(tmLayout);
	m_scene->addItem(tmDots);

	return true;
}

void Game::start()
{
	auto *timer{new QTimer(this)};

	m_message->setText(tr("Get ready!"));
	m_scene->addItem(m_message);

	timer->setSingleShot(true);

	connect(timer, &QTimer::timeout, this, &Game::onStartupTimeout);

	timer->start(5000);
}

Tilemap *Game::createTilemap(int rows, int columns, const QSizeF &cellSize)
{
	auto *tilemap{new Tilemap()};

	tilemap->setGridSize(rows, columns);
	tilemap->setCellSize(cellSize);

	return tilemap;
}

void Game::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix, const QPen &pen, const QBrush &brush)
{
	int m{0};

	for (const auto &row : matrix) {
		const QJsonArray &columns{row.toArray()};
		int n{0};

		for (const auto &column : columns) {
			const QJsonObject &element{column.toObject()};
			Tile *tile{element.isEmpty() ? nullptr
										 : createTile(element["index"].toInt(),
													  pen, brush)};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

Tile *Game::createTile(int index, const QPen &pen, const QBrush &brush)
{
	auto *tile{new Tile()};

	tile->setPath(PathBuilder::build(PathBuilder::PathType(index)));
	tile->setPen(pen);
	tile->setBrush(brush);

	return tile;
}

GameObject *Game::createPlayer(Tilemap *tmLayout, Tilemap *tmDots)
{
	auto *player{new GameObject()};

	player->setPos(324, 552);

	auto *movement{new CharacterMovement(player)};
	auto *dotsEating{new DotsEating(player)};
	auto *cameraFollow{new CameraFollow(player)};
	auto *playerController{new PlayerController(player)};
	auto *animation{new Animation(player)};

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(m_scene->inputSystem());

	movement->setGameTimer(m_gameTimer);
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(150);
	movement->setNextMove(Vector2(-1, 0));

	dotsEating->setGameTimer(m_gameTimer);
	dotsEating->setTilemap(tmDots);

	cameraFollow->setView(m_scene->views().at(0));

	animation->setGameTimer(m_gameTimer);
	animation->addPath(PathBuilder::build(PathBuilder::PT_PlayerFrame1));
	animation->addPath(PathBuilder::build(PathBuilder::PT_PlayerFrame2));

	player->addBehavior(playerController);
	player->addBehavior(movement);
	player->addBehavior(cameraFollow);
	player->addBehavior(dotsEating);
	player->addBehavior(animation);

	player->setPath(PathBuilder::build(PathBuilder::PT_PlayerFrame1));
	player->setPen(QPen(Qt::transparent));
	player->setBrush(Qt::white);

	return player;
}

void Game::onStartupTimeout()
{
	sender()->deleteLater();

	m_scene->removeItem(m_message);

	m_gameTimer->start();
}
