#include "ScoreDisplay.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay(QWidget *parent) :
	QLabel{parent}
{
	setFont(QFont("Neucha", 60, QFont::Bold, false));

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setText(tr("Your Score: 00000"));
	setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QPalette p(palette());

	p.setColor(QPalette::Window, Qt::black);
	p.setColor(QPalette::WindowText, 0x4CAF50);

	setPalette(p);
}

void ScoreDisplay::setScore(int value)
{
	setText(tr("Your Score: %1").arg(value, 5, 10, QChar('0')));
}
