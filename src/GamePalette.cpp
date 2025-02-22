#include "GamePalette.h"
#include <QColor>

GamePalette::GamePalette(QObject *parent) :
	QObject(parent)
{
	for (int n{0}; n < 13; n++)
		_colors.append(QColor());
}

QColor GamePalette::color(int role) const
{
	if (isInvalidRole(role))
		return QColor();

	return _colors.at(role);
}

void GamePalette::setColor(int role, const QColor &color)
{
	if (isInvalidRole(role))
		return;

	_colors[role] = color;
}

bool GamePalette::isInvalidRole(int role) const
{
	return role < 0 || role >= _colors.length();
}
