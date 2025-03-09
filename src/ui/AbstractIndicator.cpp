#include "AbstractIndicator.h"
#include <QPaintEvent>
#include <QPainterPath>
#include <QPainter>

AbstractIndicator::AbstractIndicator(QWidget *parent) :
	QWidget{parent},
	_visible{true}
{

}

QPainterPath AbstractIndicator::path() const
{
	return _path;
}

void AbstractIndicator::setPath(QPainterPath path)
{
	_path = path;

	const QSize &sz{sizeHint()};
	qreal midX{0.5*(sz.width() - _path.boundingRect().width())};
	qreal midY{0.5*(sz.height() - _path.boundingRect().height())};

	_mid.setX(midX);
	_mid.setY(midY);
}

QSize AbstractIndicator::sizeHint() const
{
	int marginsWidth{contentsMargins().left() + contentsMargins().right()};
	int marginsHeight{contentsMargins().top() + contentsMargins().bottom()};
	const QSize &marginsSize{marginsWidth, marginsHeight};
	const QSize &pathSize{_path.boundingRect().size().toSize()};
	int sz{std::max(pathSize.width(), pathSize.height())};

	return QSize(sz, sz) + marginsSize;
}

void AbstractIndicator::turnOn()
{
	_visible = true;
	update();
}

void AbstractIndicator::turnOff()
{
	_visible = false;
	update();
}

void AbstractIndicator::paintEvent(QPaintEvent *event)
{
	if (!_visible)
		return;

	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(Qt::transparent));
	painter.setBrush(palette().window());
	painter.drawEllipse(rect());
	painter.translate(_mid - _path.boundingRect().topLeft());
	painter.setPen(palette().windowText().color());
	painter.setBrush(palette().button());
	painter.drawPath(_path);
}
