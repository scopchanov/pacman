#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <QObject>

class QPainterPath;

class PathBuilder : public QObject
{
	Q_OBJECT
public:
	enum TileType : int {
		TT_ShortLineLowLeft = 0,
		TT_HLineLow = 1,
		TT_ShortLineLowRight = 2,
		TT_ShortLineHighLeft = 3,
		TT_HLineHigh = 4,
		TT_ShortLineHighRight = 5,
		TT_BigCircleUpLeft = 6,
		TT_BigCircleUpRight = 7,
		TT_VLineLeft = 8,
		TT_BigCircleDownLeft = 9,
		TT_BigCircleDownRight = 10,
		TT_VLineRight = 11,
		TT_SmallCircleUpLeft = 12,
		TT_SmallCircleUpRight = 13,
		TT_SmallCircleDownLeft = 15,
		TT_SmallCircleDownRight = 16,
		TT_Dot = 17,
		TT_Door = 18
	};

	explicit PathBuilder(QObject *parent = nullptr);

	static QPainterPath tilePath(TileType type);
	static QPainterPath animatedObjectPath(int type, qreal value);

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
	static QPainterPath door();
	static QPainterPath pacman(qreal d);
	static QPainterPath ghost(qreal d);
	static QPainterPath energizer(qreal d);
	static QPainterPath teleporter(qreal d);
};

#endif // PATHBUILDER_H
