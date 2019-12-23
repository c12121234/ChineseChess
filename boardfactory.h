#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H
#include "chessboard.h"
#include <QObject>

class BoardFactory : public QObject
{
    Q_OBJECT
public:
    explicit BoardFactory(QObject *parent = nullptr);
    ChessBoard* CreateBoard();


};

#endif // BOARDFACTORY_H
