#include "LifesDisplay.h"
#include "PathBuilder.h"
#include <QPainter>

LifesDisplay::LifesDisplay(QWidget *parent) :
	QWidget{parent},
	m_lifeCount{2},
	m_path{PathBuilder::playerPath(45)}
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void LifesDisplay::setLifeCount(int value)
{
	m_lifeCount = value;
	update();
}

void LifesDisplay::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setPen(Qt::transparent);
	painter.setBrush(Qt::white);
	painter.translate(width() - 48*m_lifeCount, 0.5*height());

	for (int n{0}; n < m_lifeCount; n++) {
		painter.translate(48*n, 0);
		painter.drawPath(m_path);
	}
}
