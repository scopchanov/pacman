#include "AnimatePlayer.h"

AnimatePlayer::AnimatePlayer(AbstractComponent *parent) :
	AbstractAnimate(parent)
{
	setFrameRate(150);
}

void AnimatePlayer::reset()
{
	setValue(45);
	updateParent();
}

void AnimatePlayer::update()
{
	if (value() > 45)
		setValue(0);
}
