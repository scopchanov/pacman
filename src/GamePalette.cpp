#include "GamePalette.h"
#include <QColor>

GamePalette::GamePalette(QObject *parent) :
	QObject(parent)
{

}

QColor GamePalette::color(int role) const
{
	return _colors.value(role, QColor());
}

void GamePalette::setColor(int role, const QColor &color)
{
	_colors.insert(role, color);
}
