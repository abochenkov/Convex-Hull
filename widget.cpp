#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    m_pClear = new QPushButton("Удалить");
    m_pCalculate = new QPushButton("Рассчитать");
    m_pField = new Field;
    m_pTxt = new QTextEdit;

    m_pGdLayout = new QGridLayout(this);

    m_pGdLayout->addWidget(m_pClear, 0,0);
    m_pGdLayout->addWidget(m_pCalculate, 0, 1);
    m_pGdLayout->addWidget(m_pTxt, 0, 2, 0, 2);
    m_pGdLayout->addWidget(m_pField, 1, 0, 1, 2);

    connect(m_pClear, SIGNAL(clicked()),
            this, SLOT(ClickBtnClear()));
    connect(m_pField, SIGNAL(updateText(QString)),
            this, SLOT(ShowText(QString)));
    connect(m_pCalculate, SIGNAL(clicked()),
            this, SLOT(ClickBtnCalculate()));
}

Widget::~Widget()
{
}

//slots
void Widget::ClickBtnClear()
{
    m_pField->OnBtnClear();
    m_pTxt->clear();
}

void Widget::ClickBtnCalculate()
{
    m_pField->OnBtnCalculate();
}

void Widget::ShowText(QString result)
{
    m_pTxt->clear();
    m_pTxt->append(result);
}
