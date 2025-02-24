#include "ScoreDisplay.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay(QWidget *parent) :
	QLabel{parent}
{
	QPalette p(palette());

	p.setColor(QPalette::Window, Qt::black);
	p.setColor(QPalette::WindowText, 0x757575);

	setPalette(p);
	setScore(0);
	setFont(QFont("Neucha", 28, QFont::Bold, false));
	setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void ScoreDisplay::setScore(int value)
{
	setText(tr("Your Score: %1").arg(value, 5, 10, QChar('0')));
}
