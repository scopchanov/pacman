#include "KillPlayer.h"
#include "engine/GameTimer.h"
#include "engine/GameObject.h"
#include <QSoundEffect>

KillPlayer::KillPlayer(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_player{nullptr},
	m_effectDied{new QSoundEffect()}
{
	m_effectDied->setSource(QUrl::fromLocalFile(":/snd/audio/effects/died.wav"));
}

KillPlayer::~KillPlayer()
{
	m_effectDied->deleteLater();
}

GameObject *KillPlayer::player() const
{
	return m_player;
}

void KillPlayer::setPlayer(GameObject *player)
{
	m_player = player;
}

int KillPlayer::type() const
{
	return BT_KillPlayer;
}

void KillPlayer::performTimedActions()
{
	if (!m_player)
		return;

	const QList<QGraphicsItem *> &collidingItems{parent()->collidingItems()};

	for (auto *item : collidingItems)
		if (item == m_player) {
			gameTimer()->stop();
			m_effectDied->play();
		}
}
