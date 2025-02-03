#ifndef VECTOR2_H
#define VECTOR2_H

#include <QtGlobal>

class QPoint;
class QPointF;

class Vector2
{
public:
    explicit Vector2();
    explicit Vector2(qreal x, qreal y);
    explicit Vector2(const QPoint &p);
    explicit Vector2(const QPointF &p);

    qreal x() const;
    qreal y() const;
    qreal magnitude() const;
    qreal sqrMagnitude() const;
    Vector2 normalized() const;
    Vector2 reflected() const;
    Vector2 perpendicular() const;
    Vector2 movedTowards(const Vector2 &target, qreal maxDistanceDelta) const;

    void set(qreal x, qreal y);
    void set(const Vector2 &other);
    void normalize();
    void reflect();
    void makePerpendicular();
    void moveTowards(const Vector2 &target, qreal maxDistanceDelta);

    qreal angleFrom(const Vector2 &vector) const;
    qreal angleTo(const Vector2 &vector) const;
    qreal distanceTo(const Vector2 &vector) const;
    qreal dotProduct(const Vector2 &vector) const;
    Vector2 min(const Vector2 &vector) const;
    Vector2 max(const Vector2 &vector) const;

    void clampMagnitude(qreal maxLength);
    Vector2 clampedMagnitude(qreal maxLength) const;

    QPoint toPoint() const;
    QPointF toPointF() const;
    QString toString() const;

    static qreal angle(const Vector2 &vectorFrom, const Vector2 &vectorTo);
    static qreal distanceBetween(const Vector2 &vectorFrom, const Vector2 &vectorTo);
    static qreal dotProduct(const Vector2 &vectorL, const Vector2 &vectorR);
    static Vector2 min(const Vector2 &vectorA, const Vector2 &vectorB);
    static Vector2 max(const Vector2 &vectorA, const Vector2 &vectorB);
    static Vector2 clampedMagnitude(const Vector2 &vector, qreal maxLength);
    static Vector2 perpendicular(const Vector2 &inDirection);
    static Vector2 movedTowards(const Vector2 &source, const Vector2 &target, qreal maxDistanceDelta);

    bool operator==(const Vector2 &other) const;
    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
	Vector2 operator*(const Vector2 &other) const;
	Vector2 operator/(const Vector2 &other) const;
	Vector2 operator+(const QPointF &other) const;
	Vector2 operator-(const QPointF &other) const;
	Vector2 operator*(const QPointF &other) const;
	Vector2 operator/(const QPointF &other) const;
	Vector2 operator+(qreal k) const;
	Vector2 operator-(qreal k) const;
	Vector2 operator*(qreal k) const;
	Vector2 operator/(qreal k) const;
    void operator+=(const Vector2 &other);
    void operator-=(const Vector2 &other);
	void operator*=(const Vector2 &other);
	void operator/=(const Vector2 &other);
	void operator+=(qreal k);
	void operator-=(qreal k);
	void operator*=(qreal k);
	void operator/=(qreal k);
    operator QString() const;

private:
    static qreal moveNumberTowards(qreal source, qreal target, qreal maxDistanceDelta);

    qreal m_x;
    qreal m_y;
};

#endif // VECTOR2_H
