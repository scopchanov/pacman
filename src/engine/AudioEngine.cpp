#include "AudioEngine.h"
#include <QSoundEffect>

AudioEngine::AudioEngine(QObject *parent) :
	QObject{parent}
{
	_effects.append(createEffect("notification", 0.25));
	_effects.append(createEffect("win", 0.5));
	_effects.append(createEffect("died", 1));
}

void AudioEngine::playEffect(EffectType type)
{
	_effects.at(type)->play();
}

QSoundEffect *AudioEngine::createEffect(const QString &name, qreal volume)
{
	auto *effect{new QSoundEffect(this)};
	const QString &path{":/snd/audio/effects/" + name + ".wav"};

	effect->setSource(QUrl::fromLocalFile(path));
	effect->setVolume(volume);

	connect(effect, &QSoundEffect::playingChanged, this, &AudioEngine::onPlayingChanged);

	return effect;
}

void AudioEngine::onPlayingChanged()
{
	auto *effect{static_cast<QSoundEffect *>(sender())};

	if (effect->isPlaying())
		return;

	switch (_effects.indexOf(effect)) {
	case SND_PlayerWins:
		emit victoryTunePlayed();
		break;
	case SND_PlayerDies:
		emit funeralTunePlayed();
		break;
	default:
		break;
	}
}
