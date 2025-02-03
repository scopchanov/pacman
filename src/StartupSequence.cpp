#include "StartupSequence.h"
#include "Message.h"
#include <QSoundEffect>
#include <QTimer>

StartupSequence::StartupSequence(QObject *parent) :
	QObject{parent},
	m_message{new Message()},
	m_timer{new QTimer(this)},
	m_countDown{5},
	m_countBeep{new QSoundEffect(this)}
{
	m_message->setBasePosition(360, 624);
	m_countBeep->setSource(QUrl::fromLocalFile(":/snd/audio/effects/notification.wav"));

	connect(m_timer, &QTimer::timeout, this, &StartupSequence::onStartupTimeout);

	updateMessage();
}

StartupSequence::~StartupSequence()
{
	delete m_message;
}

Message *StartupSequence::message() const
{
	return m_message;
}

void StartupSequence::start()
{
	m_timer->start(1000);
}

void StartupSequence::updateMessage()
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

void StartupSequence::onStartupTimeout()
{
	m_countDown--;

	updateMessage();

	if (m_countDown)
		return;

	disconnect(m_timer, &QTimer::timeout, this, &StartupSequence::onStartupTimeout);
	connect(m_timer, &QTimer::timeout, this, &StartupSequence::deleteLater);

	emit go();
}
