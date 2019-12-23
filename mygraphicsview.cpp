#include "mygraphicsview.h"
#include <QToolTip>
#include <QMouseEvent>
#include <QDebug>
MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{

}

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene,parent)
{

}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    //QString strText = QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
    //QToolTip::showText(event->pos(),strText,this);
    //qDebug()<<strText<<"\n";
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"MyGraphicsView::mousePressEvent"<<QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
    qDebug()<<event->type();
    QGraphicsView::mousePressEvent(event);
}
