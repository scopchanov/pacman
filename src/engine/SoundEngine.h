#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QObject>

class QSoundEffect;

class SoundEngine : public QObject
{
	Q_OBJECT
public:
	enum EffectType : int {
		SND_DotEaten = 0,
		SND_PlayerWins,
		SND_PlayerDies
	};

	explicit SoundEngine(QObject *parent = nullptr);

	void playEffect(EffectType type);

private:
	QSoundEffect *createEffect(const QString &name, qreal volume);

	QList<QSoundEffect *> _effects;

private slots:
	void onPlayingChanged();

signals:
	void funeralMarchPlayed();
};

#endif // SOUNDENGINE_H
