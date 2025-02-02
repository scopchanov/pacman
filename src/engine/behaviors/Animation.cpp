#include "Animation.h"
#include "engine/GameObject.h"
#include "engine/GameTimer.h"

Animation::Animation(GameObject *parent) :
	AbstractTimedBehavior(parent),
	m_frameDuration{200},
	m_timecode{0},
	m_frameNumber{1}
{

}

void Animation::addPath(const QPainterPath &path)
{
	m_paths.append(path);
}

qreal Animation::frameDuration() const
{
	return m_frameDuration;
}

void Animation::setFrameDuration(qreal value)
{
	m_frameDuration = value;
}

void Animation::rewind()
{
	m_frameNumber = 0;
}

void Animation::performTimedActions()
{
	m_timecode += 1000*gameTimer()->deltaTime();

	if (m_timecode < m_frameDuration)
		return;

	parent()->setPath(m_paths.at(m_frameNumber));

	m_timecode = 0;
	m_frameNumber++;

	if (m_frameNumber >= m_paths.count())
		rewind();
}
