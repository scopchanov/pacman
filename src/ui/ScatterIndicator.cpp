#include "ScatterIndicator.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include <QPaintEvent>
#include <QPainterPath>
#include <QPainter>

ScatterIndicator::ScatterIndicator(QWidget *parent) :
	QWidget{parent}
{

}

void ScatterIndicator::turnOn()
{

}

void ScatterIndicator::turnOff()
{

}

QSize ScatterIndicator::sizeHint() const
{
	return QSize(40, 40);
}

void ScatterIndicator::paintEvent(QPaintEvent *event)
{
	const QBrush &brush{Game::ref().palette()->color(CR_PlayerEnergized)};
	QPainter painter(this);
	// int offset{36};
	// QPainterPath p;

	// p.moveTo(4, height() - offset);
	// p.lineTo(4, _value*(height() - 2*offset) + offset);

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

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::Antialiasing);
	// painter.setPen(QPen(brush, 8, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(Qt::white);
	painter.translate(20, 20);
	painter.drawPath(p);
	// painter.fillRect(rect(), Qt::red);
	// painter.drawPath(p);//PathBuilder::dynamicObjectPath(OBJ_Deenergizer, 600));
}
