#include "Button.h"
#include <QPaintEvent>
#include <QPainter>

Button::Button(QWidget *parent) :
	QPushButton{parent}
{
	QPalette p{palette()};
	QFont f{font()};

	f.setBold(true);
	f.setPointSize(20);

	p.setColor(QPalette::ButtonText, 0x1976D2);

	setFont(f);
	setPalette(p);
	setMinimumHeight(48);
	setMinimumWidth(250);
	setFlat(true);
}

void Button::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	int opts{Qt::AlignCenter | Qt::TextSingleLine};

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(0x1976D2);
	painter.drawText(rect(), opts, text().replace('&', ""));

	if (hasFocus())
		painter.drawRect(rect());
}
