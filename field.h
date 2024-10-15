#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QVector>
#include <QPolygon>
#include <QGridLayout>

#include "point.h"


class Field : public QWidget
{
    Q_OBJECT
public:
    enum action {DrawPoint, DrawConture};
    enum text_edit {Square, Points};
    explicit Field(QWidget *parent = nullptr);
    ~Field();

    void DrawPoints(QPainter *painter);
    void DrawConvexHull(QPainter *painter);



signals:
    void updateText(QString);

protected:
    void paintEvent(QPaintEvent* pe);
    virtual void mousePressEvent(QMouseEvent* pe);

public slots:
    void SetAction(action action);
    void OnBtnClear();
    void OnBtnCalculate();

private:
    action m_action = action(DrawPoint);
    QVector<QPoint> m_Points;
    Point m_ConvexHullPoints;

    QString TextSquare();
    QString TextPoints();
    QString ResultTextForTextEditor(text_edit);
};

#endif // FIELD_H
