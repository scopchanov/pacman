#ifndef ANIMATION_H
#define ANIMATION_H

#include "AbstractTimedBehavior.h"
#include <QPainterPath>

class GameObject;
class GameTimer;

class Animation : public AbstractTimedBehavior
{
public:
	explicit Animation(GameObject *parent = nullptr);

	void addPath(const QPainterPath &path);
	qreal frameDuration() const;
	void setFrameDuration(qreal value);
	int type() const override;

	void rewind();

private:
	void performTimedActions() override;

	QList<QPainterPath> m_paths;
	qreal m_frameDuration;
	qreal m_timecode;
	int m_frameNumber;
	qreal m_angle;
};

#endif // ANIMATION_H
