#include "PathBuilder.h"
#include "GameGlobals.h"
#include <QPainterPath>

PathBuilder::PathBuilder(QObject *parent) :
	QObject{parent}
{

}

QPainterPath PathBuilder::tilePath(TileType type)
{
	switch (type) {
	case TT_ShortLineLowLeft:
		return shortLineLowLeft();
	case TT_ShortLineLowRight:
		return shortLineLowRight();
	case TT_ShortLineHighLeft:
		return shortLineHighLeft();
	case TT_ShortLineHighRight:
		return shortLineHighRight();
	case TT_HLineLow:
		return hLineLow();
	case TT_HLineHigh:
		return hLineHigh();
	case TT_VLineLeft:
		return vLineLeft();
	case TT_VLineRight:
		return vLineRight();
	case TT_BigCircleUpLeft:
		return bigCircleUpLeft();
	case TT_BigCircleUpRight:
		return bigCircleUpRight();
	case TT_BigCircleDownLeft:
		return bigCircleDownLeft();
	case TT_BigCircleDownRight:
		return bigCircleDownRight();
	case TT_SmallCircleUpLeft:
		return smallCircleUpLeft();
	case TT_SmallCircleUpRight:
		return smallCircleUpRight();
	case TT_SmallCircleDownLeft:
		return smallCircleDownLeft();
	case TT_SmallCircleDownRight:
		return smallCircleDownRight();
	case TT_Dot:
		return dot();
	case TT_Door:
		return door();
	default:
		return QPainterPath();
	}
}

QPainterPath PathBuilder::animatedObjectPath(int type, qreal value)
{
	switch (type) {
	case OBJ_Player:
		return pacman(value);
	case OBJ_Enemy:
		return ghost(value);
	case OBJ_Energizer:
		return energizer(value);
	case OBJ_Teleporter:
		return teleporter(value);
	default:
		return QPainterPath();
	}
}

QPainterPath PathBuilder::shortLineLowLeft()
{
	QPainterPath p;

	p.moveTo(0, 2);
	p.lineTo(10, 2);

	return p;
}

QPainterPath PathBuilder::shortLineLowRight()
{
	QPainterPath p;

	p.moveTo(-10, 2);
	p.lineTo(0, 2);

	return p;
}

QPainterPath PathBuilder::shortLineHighLeft()
{
	QPainterPath p;

	p.moveTo(0, -2);
	p.lineTo(10, -2);

	return p;
}

QPainterPath PathBuilder::shortLineHighRight()
{
	QPainterPath p;

	p.moveTo(-10, -2);
	p.lineTo(0, -2);

	return p;
}

QPainterPath PathBuilder::hLineLow()
{
	QPainterPath p;

	p.moveTo(-10, 2);
	p.lineTo(10, 2);

	return p;
}

QPainterPath PathBuilder::hLineHigh()
{
	QPainterPath p;

	p.moveTo(-10, -2);
	p.lineTo(10, -2);

	return p;
}

QPainterPath PathBuilder::vLineLeft()
{
	QPainterPath p;

	p.moveTo(-2, -10);
	p.lineTo(-2, 10);

	return p;
}

QPainterPath PathBuilder::vLineRight()
{
	QPainterPath p;

	p.moveTo(2, -10);
	p.lineTo(2, 10);

	return p;
}

QPainterPath PathBuilder::bigCircleUpLeft()
{
	QPainterPath p;

	p.moveTo(10, -2);
	p.arcTo(-2, -2, 18, 18, 90, 90);
	p.lineTo(-2, 10);

	return p;
}

QPainterPath PathBuilder::bigCircleUpRight()
{
	QPainterPath p;

	p.moveTo(2, 10);
	p.arcTo(-16, -2, 18, 18, 0, 90);
	p.lineTo(-10, -2);

	return p;
}

QPainterPath PathBuilder::bigCircleDownLeft()
{
	QPainterPath p;

	p.moveTo(-2, -10);
	p.arcTo(-2, -16, 18, 18, 180, 90);
	p.lineTo(10, 2);

	return p;
}

QPainterPath PathBuilder::bigCircleDownRight()
{
	QPainterPath p;

	p.moveTo(-10, 2);
	p.arcTo(-16, -16, 18, 18, 270, 90);
	p.lineTo(2, -10);

	return p;
}

QPainterPath PathBuilder::smallCircleUpLeft()
{
	QPainterPath p;

	p.moveTo(10, 2);
	p.arcTo(2, 2, 16, 16, 90, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleUpRight()
{
	QPainterPath p;

	p.moveTo(-2, 10);
	p.arcTo(-18, 2, 16, 16, 0, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleDownLeft()
{
	QPainterPath p;

	p.moveTo(2, -10);
	p.arcTo(2, -18, 16, 16, 180, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleDownRight()
{
	QPainterPath p;

	p.moveTo(-10, -2);
	p.arcTo(-18, -18, 16, 16, 270, 90);

	return p;
}

QPainterPath PathBuilder::dot()
{
	QPainterPath p;

	p.addEllipse(-5, -5, 10, 10);

	return p;
}

QPainterPath PathBuilder::door()
{
	QPainterPath p;

	p.moveTo(-8, 2);
	p.lineTo(8, 2);

	return p;
}

QPainterPath PathBuilder::pacman(qreal angle)
{
	qreal startAngle{180 - angle};
	qreal sweepLength{-2*startAngle};
	QPainterPath p;

	p.arcTo(-20, -20, 40, 40, startAngle, sweepLength);

	return p;
}

QPainterPath PathBuilder::ghost(qreal d)
{
	QPainterPath p;

	p.moveTo(-20, 20);
	p.quadTo(-17, -7, -8, -16);
	p.cubicTo(-6, -18, -3, -20, 0, -20);
	p.cubicTo(3, -20, 6, -18, 8, -16);
	p.quadTo(17, -7, 20, 20);
	p.quadTo(16, 16, 14, 16);
	p.cubicTo(12, 16, 10 + d, 19, 8 + d, 19);
	p.cubicTo(5 + d, 19, 3, 16, 0, 16);
	p.cubicTo(-3, 16, -5, 19, -8 + d, 19);
	p.cubicTo(-10 + d, 19, -12 + d, 16, -14, 16);
	p.quadTo(-16, 16, -20, 20);

	return p;
}

QPainterPath PathBuilder::energizer(qreal d)
{
	QPainterPath p;
	qreal w{d + 8};

	p.addEllipse(-0.5*w, -0.5*w, w, w);

	return p;
}

QPainterPath PathBuilder::teleporter(qreal angle)
{
	QPainterPath p;

	p.moveTo(-16, -12);
	p.cubicTo(-2, -30, 20, -14, 16, 2);
	p.cubicTo(18, -2, 20, -8, 12, -16);
	p.cubicTo(30, -2, 14, 20, -2, 16);
	p.cubicTo(2, 18, 8, 20, 16, 12);
	p.cubicTo(2, 30, -20, 14, -16, -2);
	p.cubicTo(-18, 2, -20, 8, -12, 16);
	p.cubicTo(-30, 2, -14, -20, 2, -16);
	p.cubicTo(-2, -18, -8, -20, -16, -12);

	rotate(p, angle);

	return p;
}

void PathBuilder::rotate(QPainterPath &path, qreal angle)
{
	for (int n{0}; n < path.elementCount(); n++) {
		qreal x{path.elementAt(n).x};
		qreal y{path.elementAt(n).y};
		qreal sina{sin(angle)};
		qreal cosa{cos(angle)};

		path.setElementPositionAt(n, x*cosa - y*sina, x*sina + y*cosa);
	}
}
