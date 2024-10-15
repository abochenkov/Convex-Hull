#include "point.h"

Point::Point()
{

}

Point::Point(QVector<QPoint> vec)
{
    m_vec = vec;
}

QPoint& Point::operator[] (int index)
{
    return m_vec[index];
}
void Point::Append(QPoint point)
{
    m_vec.append(point);
}

int Point::Size()
{
    m_vec.size();
}

QVector<QPoint> Point::ToVector()
{
    return m_vec;
}

bool cmp(const QPoint &p1, const QPoint &p2)
{
    return p1.x() < p2.x() || ( p1.x() == p2.x() && p1.y() < p2.y() );
}

bool Point::HasThree()
{
    if (m_vec.size() >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Point::AreLastThreeNonRight()
{
    /*
     * Lmo - L minus one
     * p - новая точка добавленная в конец массива
     *
     * Последние три точки в массиве [... , L, Lmo, p]
     *
     * Матрица для определения того,
     * как соотносятся последние три точки
     *
     *           Matrix 3x3
     *       |Lmo.x, Lmo.y, 1|
     *       |               |
     * cp  = |L.x,   L.y,   1|
     *       |               |
     *       |p.x,   p.y,   1|
     *
     * cp = (L.x - Lmo.x)(p.y - Lmo.y) - (L.y - Lmo.y)(p.x - Lmo.x)
     *
     * Если cp < 0, то последние три точки образуют правый поворот.
     * Мы включаем точку p и продолжаем сканирование.
     *
     * Если cp => 0, то тогда мы должны исключить среднюю Lmo точку
     * и продолжить сканирование.
     *
     */
    int n = m_vec.size();
    QPoint p = m_vec[n-1];
    QPoint L = m_vec[n-2];
    QPoint Lmo = m_vec[n-3];

    int cp = (L.x() - Lmo.x()) * (p.y() - Lmo.y()) - (L.y() - Lmo.y()) * (p.x() - Lmo.x());
    if (cp >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Point::RemoveMiddleOfLastThree()
{
    int n = m_vec.size();
    m_vec.remove(n-2);
}

void Point::AppendUnique(Point &points)
{
    for (int i=0 ; i < points.Size(); ++i)
    {
        if (!m_vec.contains(points[i]))
        {
            m_vec.append(points[i]);
        }
    }
}

// Convex Hull Scan (Algorithm Andrew)
Point Point::ConvexHull(QVector<QPoint> points)
{
    int n = points.size();
    std::sort(points.begin(), points.end(), cmp);
    if (points.size() < 3)
    {
        return points;
    }

    Point Upper = QVector<QPoint>{points[0], points[1]};
    for (int i = 2; i < n; ++i)
    {
       Upper.Append(points[i]);
       while (Upper.HasThree() && Upper.AreLastThreeNonRight())
       {
            Upper.RemoveMiddleOfLastThree();
       }
    }

    Point Lower = QVector<QPoint>{points[n-1], points[n-2]};
    for (int i = n-3; i >= 0; --i)
    {
        Lower.Append(points[i]);
        while (Lower.HasThree() && Lower.AreLastThreeNonRight())
        {
            Lower.RemoveMiddleOfLastThree();
        }
    }

    Point Hull = Upper;
    Hull.AppendUnique(Lower);
    return Hull;

}

// Алгоритм нахождения площади многоугольника на основе трапеций
double Point::SquarePolygon()
{
    int n = m_vec.size();
    double square = 0;
    for (int i = 0; i < n; ++i) {
        QPoint p1 = m_vec[i];
        QPoint p2;
        if (i != n-1)
        {
            p2 = m_vec[i+1];
        }
        else
        {
            p2 = m_vec[0];
        }
       square += (p2.x() - p1.x()) * (p1.y() + p2.y());
    }
    return square/2;
}
