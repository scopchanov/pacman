#include "GamePalette.h"
#include <QColor>

GamePalette::GamePalette(QObject *parent) :
	QObject(parent)
{
	for (int n{0}; n < 12; n++)
		_colors.append(QColor());
}

QColor GamePalette::color(int role) const
{
	if (isFoo(role))
		return QColor();

	return _colors.at(role);
}

void GamePalette::setColor(int role, const QColor &color)
{
	if (isFoo(role))
		return;

	_colors[role] = color;
}

bool GamePalette::isFoo(int role) const
{
	return role < 0 || role >= _colors.length();
}
