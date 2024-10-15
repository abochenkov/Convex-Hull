#include "field.h"

Field::Field(QWidget *parent) : QWidget(parent)
{
}

Field::~Field()
{
}

void Field::mousePressEvent(QMouseEvent* pe)
{
    QPoint point = pe->pos();
    m_Points.append(point);
    update();
}

void Field::DrawPoints(QPainter *painter)
{
    painter->drawPoints(QPolygon(m_Points));

    text_edit text = text_edit(Points);
    QString result = ResultTextForTextEditor(text);
    emit updateText(result);
}

void Field::DrawConvexHull(QPainter *painter)
{
    Point Tmp;
    m_ConvexHullPoints = Tmp.ConvexHull(m_Points);

    text_edit text = text_edit (Square);
    QString result = ResultTextForTextEditor(text);
    emit updateText(result);

    painter->drawPoints(QPolygon(m_Points));
    painter->drawPolygon(QPolygon(m_ConvexHullPoints.ToVector()));
}

void Field::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
    switch (m_action)
    {
        case DrawPoint:
            DrawPoints(&painter);
            break;
        case DrawConture:
            DrawConvexHull(&painter);
            break;
    }
}

QString Field::TextSquare()
{
    QString square = QString::number(m_ConvexHullPoints.SquarePolygon());
    return QString("Площадь: " + square + "\n");
}

QString Field::TextPoints()
{
    if (m_Points.empty())
    {
        return QString("");
    }
    QString result = "Точки: \n";
    for (int i = 0; i < m_Points.size(); ++i)
    {
        QString x = QString::number(m_Points[i].x());
        QString y = QString::number(m_Points[i].y());
        QString statement = x + " " + y + "\n";
        result+= statement;
    }
    return result;
}

QString Field::ResultTextForTextEditor(text_edit text)
{
    QString result;
    switch (text)
    {
        case Square:
            result += TextSquare();

        case Points:
            result += TextPoints();
        break;

    }

    return result;
}

//slots
void Field::SetAction(action action)
{
    this->m_action = action;
    update();
}

void Field::OnBtnClear()
{
    m_Points.clear();
    SetAction(action(DrawPoint));
}

void Field::OnBtnCalculate()
{
    if (this->m_action == action(DrawPoint))
    {
        SetAction(action(DrawConture));
    }
    else
    {
        SetAction(action(DrawPoint));
    }
}
