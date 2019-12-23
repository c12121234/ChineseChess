#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent):
    QGraphicsScene(parent)
{

}

bool MyGraphicsScene::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
            qDebug()<<"MyGraphicsScene::eventFilter :"<<QString("%1,%2").arg(me->scenePos().x()).arg(me->scenePos().y());
            emit SentSceneMouseEventToController(me);
        }
    }
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"MyGraphicsScene::mousePressEvent:"<<QString("%1,%2").arg(event->scenePos().x()).arg(event->scenePos().y());
    qDebug()<<event->type();
    QGraphicsScene::mousePressEvent(event);
}

//void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QString strText = QString("%1,%2").arg(event->scenePos().x()).arg(event->scenePos().y());
//    qDebug()<<strText;
//    QGraphicsScene::mouseMoveEvent(event);
//}
