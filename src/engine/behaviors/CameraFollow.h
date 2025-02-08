#ifndef CAMERAFOLLOW_H
#define CAMERAFOLLOW_H

#include "AbstractBehavior.h"

class QGraphicsView;

class CameraFollow : public AbstractBehavior
{
public:
	explicit CameraFollow(GameObject *parent = nullptr);

	QGraphicsView *view() const;
	void setView(QGraphicsView *view);
	int type() const override;

	void reset() override;

private:
	void performActions() override;

	QGraphicsView *_view;

};

#endif // CAMERAFOLLOW_H
