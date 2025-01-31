#include "Game.h"
#include "engine/GameController.h"
#include "engine/Scene.h"
#include "engine/behaviors/PlayerController.h"
#include "engine/behaviors/CharacterMovement.h"
#include "engine/behaviors/DotsEating.h"
#include "engine/Tilemap.h"
#include "engine/Tile.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

Game::Game(QObject *parent) :
	QObject(parent),
	m_controller{new GameController(this)},
	m_scene{new Scene(this)}
{
	m_controller->setScene(m_scene);
}

Scene *Game::scene() const
{
	return m_scene;
}

bool Game::config(const QJsonObject &json)
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
	auto *player{createPlayer(tmLayout, tmDots)};

	buildTilemap(tmLayout, wallMatrix);
	buildTilemap(tmDots, dotMatrix);

	m_scene->addItem(tmLayout);
	m_scene->addItem(tmDots);
	m_scene->addItem(player);

	return true;
}

void Game::start()
{
	m_controller->start();
}

Tilemap *Game::createTilemap(int rows, int columns, const QSizeF &cellSize)
{
	auto *tilemap{new Tilemap()};

	tilemap->setGridSize(rows, columns);
	tilemap->setCellSize(cellSize);

	return tilemap;
}

void Game::buildTilemap(Tilemap *tilemap, const QJsonArray &matrix)
{
	int m{0};

	for (const auto &row : matrix) {
		const QJsonArray &columns{row.toArray()};
		int n{0};

		for (const auto &column : columns) {
			const QJsonObject &element{column.toObject()};
			Tile *tile{element.isEmpty() ? nullptr
										 : createTile(element["x"].toInt(),
													  element["y"].toInt())};

			tilemap->setTile(m, n, tile);
			n++;
		}

		m++;
	}
}

Tile *Game::createTile(int x, int y)
{
	const QPixmap &palette{QPixmap(":/pix/images/palettes/pacman.png")};
	auto *tile{new Tile()};

	tile->setPixmap(palette.copy(x*24, y*24, 24, 24));

	return tile;
}

GameObject *Game::createPlayer(Tilemap *tmLayout, Tilemap *tmDots)
{
	auto *gameObject{new GameObject()};
	const QPixmap &palette{QPixmap(":/pix/images/palettes/pacman.png")};
	auto *movement{new CharacterMovement()};
	auto dotsEating{new DotsEating()};
	auto *playerController{new PlayerController()};

	gameObject->setPos(324, 552);

	playerController->setCharacterMovement(movement);
	playerController->setInputSystem(m_scene->inputSystem());

	movement->setGameObject(gameObject);
	movement->setGameController(m_controller);
	movement->setTilemap(tmLayout);
	movement->setMovingSpeed(200);
	movement->setNextMove(Vector2(-1, 0));

	dotsEating->setGameObject(gameObject);
	dotsEating->setGameController(m_controller);
	dotsEating->setTilemap(tmDots);

	gameObject->addBehavior(playerController);
	gameObject->addBehavior(movement);
	gameObject->addBehavior(dotsEating);
	gameObject->setPixmap(palette.copy(0, 0, 72, 72));

	return gameObject;
}
