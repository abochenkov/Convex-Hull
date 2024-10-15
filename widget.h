#ifndef WIDGET_H
#define WIDGET_H

#include "field.h"

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void ClickBtnClear();
    void ClickBtnCalculate();
    void ShowText(QString);


private:
    Field *m_pField;
    QGridLayout *m_pGdLayout;
    QPushButton *m_pClear;
    QPushButton *m_pCalculate;
    QTextEdit *m_pTxt;
};

#endif // WIDGET_H
