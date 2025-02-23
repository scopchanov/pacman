#ifndef GAMEPALETTE_H
#define GAMEPALETTE_H

#include <QObject>
#include <QHash>

class GamePalette : public QObject
{
	Q_OBJECT
public:
	explicit GamePalette(QObject *parent = nullptr);

	QColor color(int role) const;
	void setColor(int role, const QColor &color);

private:
	QHash<int, QColor> _colors;
};

#endif // GAMEPALETTE_H
