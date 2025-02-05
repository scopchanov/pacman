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

QPainterPath PathBuilder::playerPath(qreal angle)
{
	return player(angle);
}

QPainterPath PathBuilder::enemyPath()
{
	return enemy();
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

QPainterPath PathBuilder::player(qreal angle)
{
	qreal startAngle{180 - angle};
	qreal sweepLength{-2*startAngle};
	QPainterPath p;

	p.arcTo(-20, -20, 40, 40, startAngle, sweepLength);

	return p;
}

QPainterPath PathBuilder::enemy()
{
	QPainterPath p;

	p.addEllipse(-15, -15, 30, 30);

	return p;
}

QPainterPath PathBuilder::teleporter()
{
	QPainterPath p;

	p.addRect(-6, -6, 12, 12);

	return p;
}
