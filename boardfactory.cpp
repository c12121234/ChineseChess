#include "boardfactory.h"

BoardFactory::BoardFactory(QObject *parent) : QObject(parent)
{

}

ChessBoard *BoardFactory::CreateBoard()
{
    return new ChessBoard();
}
