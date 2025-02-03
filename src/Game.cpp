#include "Game.h"
#include "Message.h"
#include "engine/PathBuilder.h"
#include "engine/GameTimer.h"
#include "engine/Scene.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/PlayerOrientation.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/behaviors/CameraFollow.h"
#include "engine/behaviors/Animation.h"
#include "engine/behaviors/Teleporting.h"
#include "engine/behaviors/Debug.h"
#include "engine/Tilemap.h"
#include "engine/Grid.h"
#include "engine/Tile.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTimer>
#include <QSoundEffect>

Game::Game(QObject *parent) :
	QObject(parent),
	m_gameTimer{new GameTimer(this)},
	m_scene{new Scene(this)},
	m_message(new Message()),
	m_countDown{0},
	m_countBeep{new QSoundEffect(this)}
{
	m_message->setBasePosition(360, 444);
	m_gameTimer->setScene(m_scene);
	m_countBeep->setSource(QUrl::fromLocalFile(":/snd/audio/effects/notification.wav"));
}

Scene *Game::scene() const
{
	return m_scene;
}

bool Game::configure(const QJsonObject &json)
{
	const QJsonArray &wallMatrix{json.value("walls").toArray()};
	const QJsonArray &dotMatrix{json.value("dots").toArray()};
	const QJsonObject &gridSize{json.value("gridSize").toObject()};
	const QJsonObject &cellSize{json.value("cellSize").toObject()};
	int rows{gridSize.value("rows").toInt()};
	int columns{gridSize.value("columns").toInt()};
	qreal width{cellSize.value("width").toDouble()};
	qreal height{cellSize.value("height").toDouble()};
	auto *grid{new Grid()};
	auto *tmLayout{new Tilemap()};
	auto *tmDots{new Tilemap()};

	grid->setGridSize(rows, columns);
	grid->setCellSize(QSizeF(width, height));

	tmLayout->setGrid(grid);
	tmDots->setGrid(grid);

	buildTilemap(tmLayout, wallMatrix, QPen(QColor(0x00A3FF), 4), QBrush(Qt::transparent));
	buildTilemap(tmDots, dotMatrix, QPen(Qt::transparent), QBrush(0x999999));

	m_scene->addItem(createPlayer(tmLayout, tmDots));
	m_scene->addItem(tmLayout);
	m_scene->addItem(tmDots);
	m_scene->addItem(createTeleporter(grid->cellPosition(15, 0), grid->cellPosition(15, 28)));
	m_scene->addItem(createTeleporter(grid->cellPosition(15, 29), grid->cellPosition(15, 2)));

	return true;
}

void Game::start()
{
	auto *timer{new QTimer(this)};

	m_countDown = 5;
	updateMessage();
	m_scene->addItem(m_message);

	// timer->setSingleShot(false);

	connect(timer, &QTimer::timeout, this, &Game::onStartupTimeout);

	timer->start(1000);
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

	player->setPos(360, 588);

	auto *movement{new CharacterMovement(player)};
	auto *orientation{new PlayerOrientation(player)};
	auto *dotsEating{new DotsEating(player)};
	auto *cameraFollow{new CameraFollow(player)};
	auto *playerController{new PlayerController(player)};
	auto *animation{new Animation(player)};

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(m_scene->inputSystem());

	movement->setGameTimer(m_gameTimer);
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(200);
	movement->setNextMove(Vector2(-1, 0));

	orientation->setMovement(movement);

	dotsEating->setGameTimer(m_gameTimer);
	dotsEating->setTilemap(tmDots);

	cameraFollow->setView(m_scene->views().at(0));

	animation->setGameTimer(m_gameTimer);
	animation->addPath(PathBuilder::build(PathBuilder::PT_PlayerFrame1));
	animation->addPath(PathBuilder::build(PathBuilder::PT_PlayerFrame2));

	player->addBehavior(playerController);
	player->addBehavior(movement);
	player->addBehavior(orientation);
	player->addBehavior(animation);
	player->addBehavior(cameraFollow);
	player->addBehavior(dotsEating);

	player->setPath(PathBuilder::build(PathBuilder::PT_PlayerFrame1));
	player->setPen(QPen(Qt::transparent));
	player->setBrush(Qt::white);

	return player;
}

GameObject *Game::createTeleporter(const QPointF &src, const QPointF &dst)
{
	auto *teleporter{new GameObject()};
	auto *teleporting{new Teleporting(teleporter)};

	teleporting->setDestination(dst);

	teleporter->setPos(src);
	teleporter->addBehavior(teleporting);

	teleporter->setPath(PathBuilder::build(PathBuilder::PT_Teleporter));
	teleporter->setPen(QPen(Qt::transparent));
	teleporter->setBrush(Qt::transparent);
	teleporter->setFlag(QGraphicsItem::ItemHasNoContents);

	return teleporter;
}

void Game::updateMessage()
{
	if (m_countDown) {
		m_message->setText(tr("Get ready! %1").arg(m_countDown));
		m_countBeep->play();
	} else {
		m_message->setText(tr("Go!"));
		m_countBeep->play();
		m_countBeep->play();
	}
}

void Game::onStartupTimeout()
{
	m_countDown--;

	updateMessage();

	if (m_countDown)
		return;

	auto *timer{static_cast<QTimer *>(sender())};

	disconnect(timer, &QTimer::timeout, this, &Game::onStartupTimeout);
	connect(timer, &QTimer::timeout, this, &Game::onHideTimeout);

	m_gameTimer->start();
}

void Game::onHideTimeout()
{
	sender()->deleteLater();

	m_scene->removeItem(m_message);
}
