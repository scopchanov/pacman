#include "DotsEating.h"
#include "engine/GameTimer.h"
#include "engine/Tilemap.h"
#include <QPointF>
#include <QSoundEffect>

DotsEating::DotsEating(GameObject *parent) :
	AbstractSpatialBehavior(parent),
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

int DotsEating::type() const
{
	return BT_DotsEating;
}

void DotsEating::performSpatialActions()
{
	if (!m_effectEat || !m_effectWin)
		return;

	eatDotIfAvailable();
}

void DotsEating::eatDotIfAvailable()
{
	const QPoint &cell{currentCell().toPoint()};
	int row{cell.y()};
	int column{cell.x()};

	if (!tilemap()->hasTile(row, column))
		return;

	tilemap()->resetTile(row, column);

	m_effectEat->play();

	if (tilemap()->tileCount())
		return;

	gameTimer()->stop();

	if (m_effectEat->isPlaying())
		m_effectEat->stop();

	m_effectWin->play();

	qDebug() << "You win!";
}
