#include "PathBuilder.h"
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
	default:
		return QPainterPath();
	}
}

QPainterPath PathBuilder::animatedObjectPath(GameObjectType type, qreal value)
{
	switch (type) {
	case GO_Player:
		return pacman(value);
	case GO_Enemy:
		return ghost(value);
	case GO_Energizer:
		return energizer(value);
	default:
		return QPainterPath();
	}
}

QPainterPath PathBuilder::teleporterPath()
{
	return teleporter();
}

QPainterPath PathBuilder::shortLineLowLeft()
{
	QPainterPath p;

	p.moveTo(12, 14);
	p.lineTo(22, 14);

	return p;
}

QPainterPath PathBuilder::shortLineLowRight()
{
	QPainterPath p;

	p.moveTo(2, 14);
	p.lineTo(12, 14);

	return p;
}

QPainterPath PathBuilder::shortLineHighLeft()
{
	QPainterPath p;

	p.moveTo(12, 10);
	p.lineTo(22, 10);

	return p;
}

QPainterPath PathBuilder::shortLineHighRight()
{
	QPainterPath p;

	p.moveTo(2, 10);
	p.lineTo(12, 10);

	return p;
}

QPainterPath PathBuilder::hLineLow()
{
	QPainterPath p;

	p.moveTo(2, 14);
	p.lineTo(22, 14);

	return p;
}

QPainterPath PathBuilder::hLineHigh()
{
	QPainterPath p;

	p.moveTo(2, 10);
	p.lineTo(22, 10);

	return p;
}

QPainterPath PathBuilder::vLineLeft()
{
	QPainterPath p;

	p.moveTo(10, 2);
	p.lineTo(10, 22);

	return p;
}

QPainterPath PathBuilder::vLineRight()
{
	QPainterPath p;

	p.moveTo(14, 2);
	p.lineTo(14, 22);

	return p;
}

QPainterPath PathBuilder::bigCircleUpLeft()
{
	QPainterPath p;

	p.moveTo(22, 10);
	p.arcTo(10, 10, 18, 18, 90, 90);
	p.lineTo(10, 22);

	return p;
}

QPainterPath PathBuilder::bigCircleUpRight()
{
	QPainterPath p;

	p.moveTo(14, 22);
	p.arcTo(-4, 10, 18, 18, 0, 90);
	p.lineTo(2, 10);

	return p;
}

QPainterPath PathBuilder::bigCircleDownLeft()
{
	QPainterPath p;

	p.moveTo(10, 2);
	p.arcTo(10, -4, 18, 18, 180, 90);
	p.lineTo(22, 14);

	return p;
}

QPainterPath PathBuilder::bigCircleDownRight()
{
	QPainterPath p;

	p.moveTo(2, 14);
	p.arcTo(-4, -4, 18, 18, 270, 90);
	p.lineTo(14, 2);

	return p;
}

QPainterPath PathBuilder::smallCircleUpLeft()
{
	QPainterPath p;

	p.moveTo(22, 14);
	p.arcTo(14, 14, 16, 16, 90, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleUpRight()
{
	QPainterPath p;

	p.moveTo(10, 22);
	p.arcTo(-6, 14, 16, 16, 0, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleDownLeft()
{
	QPainterPath p;

	p.moveTo(14, 2);
	p.arcTo(14, -6, 16, 16, 180, 90);

	return p;
}

QPainterPath PathBuilder::smallCircleDownRight()
{
	QPainterPath p;

	p.moveTo(2, 10);
	p.arcTo(-6, -6, 16, 16, 270, 90);

	return p;
}

QPainterPath PathBuilder::dot()
{
	QPainterPath p;

	p.addEllipse(7, 7, 10, 10);

	return p;
}

QPainterPath PathBuilder::pacman(qreal d)
{
	qreal startAngle{180 - d};
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

	p.addEllipse(-0.5*d, -0.5*d, d, d);

	return p;
}

QPainterPath PathBuilder::teleporter()
{
	QPainterPath p;

	p.addRect(-6, -6, 12, 12);

	return p;
}
