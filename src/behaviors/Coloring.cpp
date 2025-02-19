#include "Coloring.h"
#include "GameGlobals.h"
#include "GameObject.h"
#include <QBrush>

Coloring::Coloring(GameObject *parent) :
	AbstractBehavior(parent)
{

}

QColor Coloring::color() const
{
	return _color;
}

void Coloring::setColor(const QColor &color)
{
	_color = color;
}

int Coloring::type() const
{
	return BT_Coloring;
}

void Coloring::reset()
{
	parent()->setBrush(_color);
}
