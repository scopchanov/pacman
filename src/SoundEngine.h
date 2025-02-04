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

	QList<QSoundEffect *> m_effects;
};

#endif // SOUNDENGINE_H
