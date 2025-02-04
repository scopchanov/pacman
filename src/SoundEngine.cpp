#include "SoundEngine.h"
#include <QSoundEffect>

SoundEngine::SoundEngine(QObject *parent) :
	QObject{parent}
{
	m_effects.append(createEffect("notification", 0.25));
	m_effects.append(createEffect("win", 0.5));
	m_effects.append(createEffect("died", 1));
}

void SoundEngine::playEffect(EffectType type)
{
	m_effects.at(type)->play();
}

QSoundEffect *SoundEngine::createEffect(const QString &name, qreal volume)
{
	auto *effect{new QSoundEffect(this)};
	const QString &path{":/snd/audio/effects/" + name + ".wav"};

	effect->setSource(QUrl::fromLocalFile(path));
	effect->setVolume(volume);

	return effect;
}
