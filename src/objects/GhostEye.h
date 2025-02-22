#ifndef GHOSTEYE_H
#define GHOSTEYE_H

#include <QGraphicsEllipseItem>

using Pair = QPair<int, int>;

class Vector2;

class GhostEye : public QGraphicsEllipseItem
{
public:
	explicit GhostEye(QGraphicsItem *parent = nullptr);

	void reset(const Vector2 &direction);
	void orientate(const Vector2 &direction);

private:
	Pair coordinates(const Vector2 &direction);

	QGraphicsEllipseItem *_iris;
};

#endif // GHOSTEYE_H
