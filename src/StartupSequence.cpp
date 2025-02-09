#include "StartupSequence.h"
#include "Message.h"
#include <QSoundEffect>
#include <QTimer>

StartupSequence::StartupSequence(QObject *parent) :
	QObject{parent},
	_message{new Message()},
	_timer{new QTimer(this)},
	_countDown{5},
	_countBeep{new QSoundEffect(this)}
{
	_message->setBasePosition(360, 444);
	_countBeep->setSource(QUrl::fromLocalFile(":/snd/audio/effects/notification.wav"));

	connect(_timer, &QTimer::timeout, this, &StartupSequence::onStartupTimeout);

	updateMessage();
}

Message *StartupSequence::message() const
{
	return _message;
}

void StartupSequence::start()
{
	_timer->start(1000);
}

void StartupSequence::updateMessage()
{
	if (_countDown) {
		_message->setText(tr("Get ready! %1").arg(_countDown));
		_countBeep->play();
	} else {
		_message->setText(tr("Go!"));
		_countBeep->play();
		_countBeep->play();
	}
}

void StartupSequence::onStartupTimeout()
{
	_countDown--;

	updateMessage();

	if (_countDown)
		return;

	disconnect(_timer, &QTimer::timeout, this, &StartupSequence::onStartupTimeout);
	connect(_timer, &QTimer::timeout, this, &StartupSequence::deleteLater);

	emit go();
}
