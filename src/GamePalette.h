#ifndef GAMEPALETTE_H
#define GAMEPALETTE_H

#include <QObject>

class GamePalette : public QObject
{
	Q_OBJECT
public:
	explicit GamePalette(QObject *parent = nullptr);

	QColor color(int role) const;
	void setColor(int role, const QColor &color);

private:
	bool isInvalidRole(int role) const;

	QList<QColor> _colors;
};

#endif // GAMEPALETTE_H
