#ifndef ANIMATION_H
#define ANIMATION_H

#include "AbstractBehavior.h"
#include <QPainterPath>

class GameObject;
class GameController;

class Animation : public AbstractBehavior
{
public:
	explicit Animation(GameObject *parent = nullptr);

	void setGameController(GameController *controller);
	void addPath(const QPainterPath &path);
	qreal frameDuration() const;
	void setFrameDuration(qreal value);

	void rewind();

	void execute() override;

private:
	GameController *m_controller;
	QList<QPainterPath> m_paths;
	qreal m_frameDuration;
	qreal m_timecode;
	int m_frameNumber;
};

#endif // ANIMATION_H
