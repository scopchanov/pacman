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

	Message *m_message;
	QTimer *m_timer;
	int m_countDown;
	QSoundEffect *m_countBeep;

private slots:
	void onStartupTimeout();

signals:
	void go();
};

#endif // STARTUPSEQUENCE_H
