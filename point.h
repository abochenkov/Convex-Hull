#ifndef POINT_H
#define POINT_H

#include <QVector>
#include <QPoint>

#include <algorithm>


class Point
{
public:
    Point();
    Point(QVector<QPoint>);
    inline QPoint& operator[] (int index);
    inline void Append(QPoint);
    inline int Size();
    QVector<QPoint> ToVector();
    Point ConvexHull(QVector<QPoint>);
    double SquarePolygon();

private:
    QVector<QPoint> m_vec;

    bool HasThree();
    bool AreLastThreeNonRight();
    void RemoveMiddleOfLastThree();
    void AppendUnique(Point&);
};


bool cmp(const QPoint&, const QPoint&);


#endif // POINT_H
