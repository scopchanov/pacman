#include "DotsEating.h"
#include "engine/GameController.h"
#include "engine/Tilemap.h"
#include <QPointF>
#include <QSoundEffect>

DotsEating::DotsEating() :
	AbstractCharacterBehavior(),
	m_effectEat{new QSoundEffect()},
	m_effectWin{new QSoundEffect()}
{
	m_effectEat->setSource(QUrl::fromLocalFile(":/snd/audio/effects/notification.wav"));
	m_effectEat->setVolume(0.25);
	m_effectWin->setSource(QUrl::fromLocalFile(":/snd/audio/effects/win.wav"));
	m_effectWin->setVolume(0.5);
}

DotsEating::~DotsEating()
{
	m_effectEat->deleteLater();
	m_effectWin->deleteLater();
}

void DotsEating::performActions()
{
	eatDotIfAvailable();
}

void DotsEating::eatDotIfAvailable()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!m_tilemap->hasTile(row, column))
		return;

	m_tilemap->resetTile(row, column);

	m_effectEat->play();

	if (m_tilemap->tileCount())
		return;

	m_gameController->stop();

	if (m_effectEat->isPlaying())
		m_effectEat->stop();

	m_effectWin->play();

	qDebug() << "You win!";
}
