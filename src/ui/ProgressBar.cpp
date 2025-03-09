#include "ProgressBar.h"
#include "Game.h"
#include "GameGlobals.h"
#include "Palette.h"
#include "builders/PathBuilder.h"
#include <QPaintEvent>
#include <QPainterPath>
#include <QPainter>

ProgressBar::ProgressBar(QWidget *parent) :
	QWidget{parent},
	_value{0}
{

}

void ProgressBar::setValue(qreal value)
{
	_value = value;

	if (_value >= 1)
		_value = 0;

	update();
}

QSize ProgressBar::sizeHint() const
{
	return QSize(8, 100);
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
	if (_value <= 0)
		return;

	const QBrush &brush{Game::ref().palette()->color(CR_PlayerEnergized)};
	QPainter painter(this);
	int offset{36};
	QPainterPath p;

	p.moveTo(4, height() - offset);
	p.lineTo(4, _value*(height() - 2*offset) + offset);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(brush, 8, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(Qt::transparent);
	painter.drawPath(p);//PathBuilder::dynamicObjectPath(OBJ_Deenergizer, 600));
}
