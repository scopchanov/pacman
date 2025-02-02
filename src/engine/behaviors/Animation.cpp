#include "Animation.h"
#include "engine/GameObject.h"
#include "engine/GameController.h"

Animation::Animation(GameObject *parent) :
	AbstractBehavior(parent),
	m_controller{nullptr},
	m_frameDuration{200},
	m_timecode{0},
	m_frameNumber{1}
{

}

void Animation::setGameController(GameController *controller)
{
	m_controller = controller;
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

void Animation::execute()
{
	if (!parent() || !m_controller)
		return;

	m_timecode += 1000*m_controller->deltaTime();

	if (m_timecode < m_frameDuration)
		return;

	parent()->setPath(m_paths.at(m_frameNumber));

	m_timecode = 0;
	m_frameNumber++;

	if (m_frameNumber >= m_paths.count())
		rewind();
}
