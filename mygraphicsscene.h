#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

class QGraphicsSceneMouseEvent;
class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void SentSceneMouseEventToController(QGraphicsSceneMouseEvent* event);
protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYGRAPHICSSCENE_H
