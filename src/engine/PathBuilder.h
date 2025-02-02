#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <QObject>

class QPainterPath;

class PathBuilder : public QObject
{
	Q_OBJECT
public:
	enum PathType : int {
		PT_ShortLineLowLeft = 0,
		PT_HLineLow,
		PT_ShortLineLowRight,
		PT_ShortLineHighLeft,
		PT_HLineHigh,
		PT_ShortLineHighRight,
		PT_BigCircleUpLeft,
		PT_BigCircleUpRight,
		PT_VLineLeft,
		PT_BigCircleDownLeft,
		PT_BigCircleDownRight,
		PT_VLineRight,
		PT_SmallCircleUpLeft,
		PT_SmallCircleUpRight,
		PM_15,
		PT_SmallCircleDownLeft,
		PT_SmallCircleDownRight,
		PT_Dot,
		PT_PlayerFrame1,
		PT_PlayerFrame2
	};

	explicit PathBuilder(QObject *parent = nullptr);

	static QPainterPath build(PathType type);

private:
	static QPainterPath shortLineLowLeft();
	static QPainterPath shortLineLowRight();
	static QPainterPath shortLineHighLeft();
	static QPainterPath shortLineHighRight();
	static QPainterPath hLineLow();
	static QPainterPath hLineHigh();
	static QPainterPath vLineLeft();
	static QPainterPath vLineRight();
	static QPainterPath bigCircleUpLeft();
	static QPainterPath bigCircleUpRight();
	static QPainterPath bigCircleDownLeft();
	static QPainterPath bigCircleDownRight();
	static QPainterPath smallCircleUpLeft();
	static QPainterPath smallCircleUpRight();
	static QPainterPath smallCircleDownLeft();
	static QPainterPath smallCircleDownRight();
	static QPainterPath dot();
	static QPainterPath playerFrame1();
	static QPainterPath playerFrame2();
};

#endif // PATHBUILDER_H
