#include "LevelState.h"
#include "GameGlobals.h"
#include <QPen>

LevelState::LevelState(AbstractGameObject *parent) :
	AbstractGameObject{parent},
	_step{0}
{
	QPainterPath p;

	p.moveTo(-6, 13);
	p.cubicTo(-9, 13, -9, 10, -9, 10);
	p.cubicTo(-15, 7, -18, 1, -18, -8);
	p.lineTo(-18, -11);
	p.cubicTo(-18, -14, -18, -14, -15, -14);
	p.lineTo(15, -14);
	p.cubicTo(18, -14, 18, -14, 18, -11);
	p.lineTo(18, -8);
	p.cubicTo(18, 1, 15, 7, 9, 10);
	p.cubicTo(9, 10, 9, 13, 6, 13);
	p.lineTo(-6, 13);

	setPath(p);
	setPos(360, 396);
	// setPos(360, 396);
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);

	// setFlags(ItemHasNoContents);
}

int LevelState::step() const
{
	return _step;
}

void LevelState::setStep(int step)
{
	_step = step;

	setVisible(mode() == WM_Scatter);
}

void LevelState::incrementStep()
{
	_step++;

	setVisible(mode() == WM_Scatter);
}

int LevelState::mode() const
{
	return _step % 2 ? WM_Chase : WM_Scatter;
}

int LevelState::objectType() const
{
	return OBJ_Npc;
}
