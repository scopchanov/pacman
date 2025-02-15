#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>

class QSoundEffect;

class AudioEngine : public QObject
{
	Q_OBJECT
public:
	enum EffectType : int {
		SND_DotEaten = 0,
		SND_EnemyEaten,
		SND_PlayerWins,
		SND_PlayerDies
	};

	explicit AudioEngine(QObject *parent = nullptr);

	void playEffect(EffectType type);

private:
	QSoundEffect *createEffect(const QString &name, qreal volume);

	QList<QSoundEffect *> _effects;

private slots:
	void onPlayingChanged();

signals:
	void victoryTunePlayed();
	void funeralTunePlayed();
};

#endif // AUDIOENGINE_H
