#include "ScoreDisplay.h"
#include <QPainter>

ScoreDisplay::ScoreDisplay(QWidget *parent) :
	QLabel{parent}
{
	// setAutoFillBackground(true);

	setFont(QFont("Neucha", 72, QFont::Bold, false));

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setText("SCORE: 0000");
	setAlignment(Qt::AlignCenter);

	QPalette p(palette());

	p.setColor(QPalette::Window, Qt::black);
	p.setColor(QPalette::WindowText, Qt::green);

	setPalette(p);
}
