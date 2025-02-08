#include "SoundEngine.h"
#include <QSoundEffect>

SoundEngine::SoundEngine(QObject *parent) :
	QObject{parent}
{
	_effects.append(createEffect("notification", 0.25));
	_effects.append(createEffect("win", 0.5));
	_effects.append(createEffect("died", 1));
}

void SoundEngine::playEffect(EffectType type)
{
	_effects.at(type)->play();
}

QSoundEffect *SoundEngine::createEffect(const QString &name, qreal volume)
{
	auto *effect{new QSoundEffect(this)};
	const QString &path{":/snd/audio/effects/" + name + ".wav"};

	effect->setSource(QUrl::fromLocalFile(path));
	effect->setVolume(volume);

	return effect;
}
