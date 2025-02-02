#ifndef CAMERAFOLLOW_H
#define CAMERAFOLLOW_H

#include "AbstractCharacterBehavior.h"

class QGraphicsView;

class CameraFollow : public AbstractCharacterBehavior
{
public:
	explicit CameraFollow(GameObject *parent = nullptr);

	QGraphicsView *view() const;
	void setView(QGraphicsView *view);

protected:
	void performActions() override;

private:
	QGraphicsView *m_view;
};

#endif // CAMERAFOLLOW_H
