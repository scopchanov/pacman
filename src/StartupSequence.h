#ifndef STARTUPSEQUENCE_H
#define STARTUPSEQUENCE_H

#include <QObject>

class QSoundEffect;
class Message;

class StartupSequence : public QObject
{
	Q_OBJECT
public:
	explicit StartupSequence(QObject *parent = nullptr);
	~StartupSequence();

	Message *message() const;

public slots:
	void start();

private:
	void updateMessage();

	Message *_message;
	QTimer *_timer;
	int _countDown;
	QSoundEffect *_countBeep;

private slots:
	void onStartupTimeout();

signals:
	void go();
};

#endif // STARTUPSEQUENCE_H
