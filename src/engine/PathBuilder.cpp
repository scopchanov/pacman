#include "PathBuilder.h"
#include <QPainterPath>

PathBuilder::PathBuilder(QObject *parent) :
	QObject{parent}
{

}

QPainterPath PathBuilder::build(PathType type)
{
	switch (type) {
	case PT_ShortLineLowLeft:
		return shortLineLowLeft();
	case PT_ShortLineLowRight:
		return shortLineLowRight();
	case PT_ShortLineHighLeft:
		return shortLineHighLeft();
	case PT_ShortLineHighRight:
		return shortLineHighRight();
	case PT_HLineLow:
		return hLineLow();
	case PT_HLineHigh:
		return hLineHigh();
	case PT_VLineLeft:
		return vLineLeft();
	case PT_VLineRight:
		return vLineRight();
	case PT_BigCircleUpLeft:
		return bigCircleUpLeft();
	case PT_BigCircleUpRight:
		return bigCircleUpRight();
	case PT_BigCircleDownLeft:
		return bigCircleDownLeft();
	case PT_BigCircleDownRight:
		return bigCircleDownRight();
	case PT_SmallCircleUpLeft:
		return smallCircleUpLeft();
	case PT_SmallCircleUpRight:
		return smallCircleUpRight();
	case PT_SmallCircleDownLeft:
		return smallCircleDownLeft();
	case PT_SmallCircleDownRight:
		return smallCircleDownRight();
	case PT_Dot:
		return dot();
	case PT_PlayerFrame1:
		return playerFrame1();
	default:
		return QPainterPath();
	}
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

	p.addEllipse(7, 7, 10, 10);;

	return p;
}

QPainterPath PathBuilder::playerFrame1()
{
	QPainterPath p;

	p.addEllipse(16, 16, 40, 40);;

	return p;
}
