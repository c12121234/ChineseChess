#include "boardcontroller.h"
#include "chessboard.h"
#include "chesscharacter.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>
#include "mainwindow.h"
using std::vector;
using std::pair;

BoardController::BoardController(MainWindow** ppMainWindow,QObject *parent) : QObject(parent),
  m_pChessBoard(new ChessBoard()),
  m_pCoodinate(new vector<pair<int,int>>(2,std::make_pair(0,0))),
  m_pMainWindow(*ppMainWindow)
, m_nChessRadius(15)
, m_nChessMoveRange(60)
, m_nChessXBegin(40)
, m_nChessYBegin(39)
, m_nPairCoodinateIndex(0)
{
    //m_pChessBoard = ChessBoardUtil::CreateBoard();
    connect(this,&BoardController::SendCoordinateToViewUpdate,m_pMainWindow,&MainWindow::HandleCoordinateToViewUpdate);
    QTimer::singleShot(50,this,&BoardController::ResetBoardChess);
}

BoardController::~BoardController()
{
    delete m_pChessBoard;
}

void BoardController::HandleMouseEventFromView(QGraphicsSceneMouseEvent *event)
{
    ConvertCoodinateToChess(event->scenePos().x(),event->scenePos().y());
    qDebug()<<"BoardController"<<m_pCoodinate->operator[](m_nPairCoodinateIndex).first<<": x "
            <<m_pCoodinate->operator[](m_nPairCoodinateIndex).second<<": y"<<"\n";
    m_nPairCoodinateIndex++;
    if(m_nPairCoodinateIndex == 2)
    {
        DoChessMove();
        m_nPairCoodinateIndex %= 2;
    }
}

void BoardController::ConvertCoodinateToChess(int x, int y)
{
    if(isOutOfRange(x,y))
    {

    }
    else
    {
        if(isOutOfChessRadius(x,y))
        {

        }
        else
        {
            int TempX = (x-m_nChessXBegin)%m_nChessMoveRange<=m_nChessRadius ?
                        (x-m_nChessXBegin)/m_nChessMoveRange : (x-m_nChessXBegin)/m_nChessMoveRange +1;
            int TempY = (y-m_nChessYBegin)%m_nChessMoveRange<=m_nChessRadius ?
                        (y-m_nChessYBegin)/m_nChessMoveRange : (y-m_nChessYBegin)/m_nChessMoveRange +1 ;
            m_pCoodinate->operator[](m_nPairCoodinateIndex).first = TempX;
            m_pCoodinate->operator[](m_nPairCoodinateIndex).second = TempY;
        }
    }
}

bool BoardController::isOutOfRange(int x, int y)
{
    if(x<m_nChessXBegin-m_nChessRadius || x >m_nChessXBegin+m_nChessMoveRange*8+m_nChessRadius ||
            y < m_nChessYBegin-m_nChessRadius || y>m_nChessYBegin+m_nChessMoveRange*9+m_nChessRadius)
    {
        qDebug()<<"out of range.\n";
        return true;
    }
    return false;
}

bool BoardController::isOutOfChessRadius(int x, int y)
{
    if(((x-m_nChessXBegin)%m_nChessMoveRange<=m_nChessRadius ||
        (x-m_nChessXBegin)%m_nChessMoveRange>=m_nChessMoveRange-m_nChessRadius) &&
            ((y-m_nChessYBegin)%m_nChessMoveRange <=m_nChessRadius ||
             (y-m_nChessYBegin)%m_nChessMoveRange>=m_nChessMoveRange-m_nChessRadius))
        return false;
    qDebug()<<"click is empty\n";
    return true;
}

void BoardController::DoChessMove()
{
    qDebug()<<"BoardController::DoChessMove+";
    bool bRet = m_pChessBoard->MoveChess(m_pCoodinate->operator[](0).first,m_pCoodinate->operator[](0).second,
                             m_pCoodinate->operator[](1).first,m_pCoodinate->operator[](1).second);
    if(bRet)
    {
        //emit updateboard.
        emit SendCoordinateToViewUpdate(m_pCoodinate->operator[](0),m_pCoodinate->operator[](1));
        TestVal(m_pCoodinate->operator[](1).first,m_pCoodinate->operator[](1).second);
        TestVal(m_pCoodinate->operator[](0).first,m_pCoodinate->operator[](0).second);
    }
    else
    {
        //emit alarm.
    }
    qDebug()<<"BoardController::DoChessMove-";
}

void BoardController::TestVal(int x, int y)
{
    m_pChessBoard->TestChessValueByCoor(x,y);
}

void BoardController::ResetBoardChess()
{
    qDebug()<<"BoardController::ResetBoardChess+";
    ChessCharacter* pRedKing = new ChessKing(RED,4,9);
    m_pChessBoard->SetBoardValue(pRedKing->GetChessPosX(),pRedKing->GetChessPosY(),&pRedKing);
    ChessCharacter* pRedQueen = new ChessQueen(RED,3,9);
    m_pChessBoard->SetBoardValue(pRedQueen->GetChessPosX(),pRedQueen->GetChessPosY(),&pRedQueen);
    ChessCharacter* pRedQueen2 = new ChessQueen(RED,5,9);
    m_pChessBoard->SetBoardValue(pRedQueen2->GetChessPosX(),pRedQueen2->GetChessPosY(),&pRedQueen2);
    qDebug()<<"BoardController::ResetBoardChess-";
}
