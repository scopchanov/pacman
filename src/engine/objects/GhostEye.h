#ifndef GHOSTEYE_H
#define GHOSTEYE_H

#include <QGraphicsEllipseItem>

class Vector2;

class GhostEye : public QGraphicsEllipseItem
{
public:
	explicit GhostEye(QGraphicsItem *parent = nullptr);

	void orient(const Vector2 &direction);

private:
	QGraphicsEllipseItem *_iris;
};

#endif // GHOSTEYE_H
