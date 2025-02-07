#include "Vector2.h"
#include <QPoint>
#include <QDebugStateSaver>

Vector2::Vector2() :
	Vector2(0, 0)
{

}

Vector2::Vector2(qreal x, qreal y) :
	m_x{x},
	m_y{y}
{

}

Vector2::Vector2(const QPoint &p) :
	Vector2(p.x(), p.y())
{

}

Vector2::Vector2(const QPointF &p) :
	Vector2(p.x(), p.y())
{

}

qreal Vector2::x() const
{
	return m_x;
}

qreal Vector2::y() const
{
	return m_y;
}

qreal Vector2::magnitude() const
{
	return sqrt(pow(m_x, 2) + pow(m_y, 2));
}

Vector2 Vector2::normalized() const
{
	return *this/magnitude();
}

Vector2 Vector2::reflected() const
{
	// Reflects a vector off the surface defined by a normal.

	// This method calculates a reflected vector using the following
	// formula: v = inDirection - 2 * inNormal * dot(inDirection inNormal).
	// The inNormal vector defines a surface. A surface's normal is the vector
	// that is perpendicular to its surface. The inDirection vector is treated
	//as a directional arrow coming into the surface. The returned value is a
	//vector of equal magnitude to inDirection but with its direction reflected.

	return Vector2();
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(-m_y, m_x);
}

Vector2 Vector2::reversed() const
{
	return Vector2(-m_x, -m_y);
}

Vector2 Vector2::rotated(qreal angle) const
{
	qreal cosAngle{cos(angle)};
	qreal sinAngle{sin(angle)};
	qreal x{m_x*cosAngle - m_y*sinAngle};
	qreal y{m_x*sinAngle + m_y*cosAngle};

	return Vector2(x, y);
}

Vector2 Vector2::movedTowards(const Vector2 &target, qreal maxDistanceDelta) const
{
	return movedTowards(*this, target, maxDistanceDelta);
}

void Vector2::normalize()
{
	set(normalized());
}

void Vector2::reflect()
{
	set(reflected());
}

void Vector2::makePerpendicular()
{
	set(perpendicular());
}

void Vector2::reverse()
{
	set(reversed());
}

void Vector2::rotate(qreal angle)
{
	set(rotated(angle));
}

void Vector2::moveTowards(const Vector2 &target, qreal maxDistanceDelta)
{
	set(movedTowards(*this, target, maxDistanceDelta));
}

qreal Vector2::angleFrom(const Vector2 &vector) const
{
	return 0;
}

qreal Vector2::angleTo(const Vector2 &vector) const
{
	return 0;
}

qreal Vector2::distanceTo(const Vector2 &vector) const
{
	return sqrt(pow(vector.x() - m_x, 2) + pow(vector.y() - m_y, 2));
}

qreal Vector2::distanceTo(const QPointF &point) const
{
	return distanceTo(Vector2(point));
}

qreal Vector2::distanceTo(const QPoint &point) const
{
	return distanceTo(Vector2(point));
}

qreal Vector2::dotProduct(const Vector2 &vector) const
{
	return 0;
}

Vector2 Vector2::min(const Vector2 &vector) const
{
	return min(*this, vector);
}

Vector2 Vector2::max(const Vector2 &vector) const
{
	return max(*this, vector);
}

void Vector2::clampMagnitude(qreal maxLength)
{

}

Vector2 Vector2::clampedMagnitude(qreal maxLength) const
{
	return Vector2();
}

QPoint Vector2::toPoint() const
{
	return toPointF().toPoint();
}

QPointF Vector2::toPointF() const
{
	return QPointF(m_x, m_y);
}

QString Vector2::toString() const
{
	return QString("Vector2(%1, %2)").arg(m_x).arg(m_y);
}

qreal Vector2::angle(const Vector2 &vectorFrom, const Vector2 &vectorTo)
{
	return 0;
}

qreal Vector2::distanceBetween(const Vector2 &vectorFrom, const Vector2 &vectorTo)
{
	return 0;
}

qreal Vector2::dotProduct(const Vector2 &vectorL, const Vector2 &vectorR)
{
	return 0;
}

Vector2 Vector2::min(const Vector2 &vectorA, const Vector2 &vectorB)
{
	qreal minX{qMin(vectorA.x(), vectorB.x())};
	qreal minY{qMin(vectorA.y(), vectorB.y())};

	return Vector2(minX, minY);
}

Vector2 Vector2::max(const Vector2 &vectorA, const Vector2 &vectorB)
{
	qreal maxX{qMax(vectorA.x(), vectorB.x())};
	qreal maxY{qMax(vectorA.y(), vectorB.y())};

	return Vector2(maxX, maxY);
}

Vector2 Vector2::clampedMagnitude(const Vector2 &vector, qreal maxLength)
{
	return Vector2();
}

Vector2 Vector2::perpendicular(const Vector2 &inDirection)
{
	return inDirection.perpendicular();
}

Vector2 Vector2::movedTowards(const Vector2 &source, const Vector2 &target, qreal maxDistanceDelta)
{
	qreal x{moveNumberTowards(source.x(), target.x(), maxDistanceDelta)};
	qreal y{moveNumberTowards(source.y(), target.y(), maxDistanceDelta)};

	return Vector2(x, y);
}

Vector2 Vector2::operator =(const QPoint &point)
{
	m_x = point.x();
	m_y = point.y();

	return *this;
}

Vector2 Vector2::operator=(const QPointF &point)
{
	m_x = point.x();
	m_y = point.y();

	return *this;
}

bool Vector2::operator==(const Vector2 &other) const
{
	return m_x == other.x() && m_y == other.y();
}

Vector2 Vector2::operator+(const Vector2 &other) const
{
	return Vector2(m_x + other.x(), m_y + other.y());
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
	return Vector2(m_x - other.x(), m_y - other.y());
}

Vector2 Vector2::operator*(const Vector2 &other) const
{
	return Vector2(m_x*other.x(), m_y*other.y());
}

Vector2 Vector2::operator/(const Vector2 &other) const
{
	try {
		return Vector2(m_x/other.x(), m_y/other.y());
	} catch (...) {
		qCritical() << "Division by zero!";
	}

	return Vector2();
}

Vector2 Vector2::operator+(const QPointF &other) const
{
	return Vector2(m_x + other.x(), m_y + other.y());
}

Vector2 Vector2::operator-(const QPointF &other) const
{
	return Vector2(m_x - other.x(), m_y - other.y());
}

Vector2 Vector2::operator*(const QPointF &other) const
{
	return Vector2(m_x*other.x(), m_y*other.y());
}

Vector2 Vector2::operator/(const QPointF &other) const
{
	try {
		return Vector2(m_x/other.x(), m_y/other.y());
	} catch (...) {
		qCritical() << "Division by zero!";
	}

	return Vector2();
}

Vector2 Vector2::operator+(qreal k) const
{
	return Vector2(m_x + k, m_y + k);
}

Vector2 Vector2::operator-(qreal k) const
{
	return Vector2(m_x - k, m_y - k);
}

Vector2 Vector2::operator*(qreal k) const
{
	return Vector2(m_x*k, m_y*k);
}

Vector2 Vector2::operator/(qreal k) const
{
	try {
		return Vector2(m_x/k, m_y/k);
	} catch (...) {
		qCritical() << "Division by zero!";
	}

	return Vector2();
}

void Vector2::operator+=(const Vector2 &other)
{
	set(*this + other);
}

void Vector2::operator-=(const Vector2 &other)
{
	set(*this - other);
}

void Vector2::operator*=(const Vector2 &other)
{
	set(*this*other);
}

void Vector2::operator/=(const Vector2 &other)
{
	set(*this/other);
}

void Vector2::operator+=(qreal k)
{
	set(*this + k);
}

void Vector2::operator-=(qreal k)
{
	set(*this - k);
}

void Vector2::operator*=(qreal k)
{
	set(*this*k);
}

void Vector2::operator/=(qreal k)
{
	set(*this/k);
}

Vector2::operator QString() const
{
	return toString();
}

Vector2::operator QPoint() const
{
	return toPoint();
}

Vector2::operator QPointF() const
{
	return toPointF();
}

void Vector2::set(const Vector2 &other)
{
	m_x = other.x();
	m_y = other.y();
}

qreal Vector2::moveNumberTowards(qreal source, qreal target, qreal maxDistanceDelta)
{
	qreal delta{target - source};

	return abs(delta) < maxDistanceDelta
			   ? target
			   : source + (delta > 0 ? maxDistanceDelta : -maxDistanceDelta);
}
