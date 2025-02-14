#ifndef COLORING_H
#define COLORING_H

#include "AbstractBehavior.h"
#include <QColor>

class Coloring : public AbstractBehavior
{
public:
	explicit Coloring(GameObject *parent = nullptr);

	QColor color() const;
	void setColor(const QColor &color);
	int type() const override;

	void reset() override;

private:
	QColor _color;
};

#endif // COLORING_H
