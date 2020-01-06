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
, m_bEnableBeepSound(true)
, m_Team(RED)
{    
    connect(this,&BoardController::SendCoordinateToViewUpdate,m_pMainWindow,&MainWindow::HandleCoordinateToViewUpdate);
    QTimer::singleShot(50,this,&BoardController::InitBoardChess);    
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
        m_bEnableBeepSound = true;
        DoChessMove();
        m_nPairCoodinateIndex %= 2;
    }
}

void BoardController::ConvertCoodinateToChess(int x, int y)
{
    if(isOutOfRange(x,y))
    {
        ControlAlarm();
    }
    else
    {
        if(isOutOfChessRadius(x,y))
        {
            ControlAlarm();
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
    Team chess1 = m_pChessBoard->GetBoardTeamValue(m_pCoodinate->operator[](0).first,m_pCoodinate->operator[](0).second);
    if(chess1 == ZERO)
    {
        if(m_bEnableBeepSound)
            ControlAlarm();
        return;
    }
    if(chess1 != m_Team)
    {
        qDebug()<<"not your chess.";
        ControlAlarm();
        return;
    }
    bool bRet = m_pChessBoard->MoveChess(m_pCoodinate->operator[](0).first,m_pCoodinate->operator[](0).second,
                             m_pCoodinate->operator[](1).first,m_pCoodinate->operator[](1).second);
    if(bRet)
    {
        //emit updateboard.
        m_Team = (m_Team == RED)?BLACK:RED;
        emit SendCoordinateToViewUpdate(m_pCoodinate->operator[](0),m_pCoodinate->operator[](1));
        emit SendTurnChange(m_Team);
    }
    else
    {
        //emit alarm.
        ControlAlarm();
    }
            qDebug()<<"BoardController::DoChessMove-";
}

void BoardController::HandleSendChangedm_pCoordinate(int posX1, int posY1, int posX2, int posY2)
{
    m_pCoodinate->operator[](0).first = posX1;
    m_pCoodinate->operator[](0).second = posY1;
    m_pCoodinate->operator[](1).first = posX2;
    m_pCoodinate->operator[](1).second = posY2;
    m_bEnableBeepSound = false;
    DoChessMove();
}

void BoardController::TestVal(int x, int y)
{
    m_pChessBoard->TestChessValueByCoor(x,y);
}

void BoardController::ClearBoardChess()
{
    m_pChessBoard->ClearChessBoard();
}

void BoardController::ControlAlarm()
{
    ResetCoordinate();
    emit SendBeepSound();
}

void BoardController::InitRedTeam()
{
    ChessCharacter* pRedKing = new ChessKing(RED,4,9);
    m_pChessBoard->SetBoardValue(pRedKing->GetChessPosX(),pRedKing->GetChessPosY(),&pRedKing);
    ChessCharacter* pRedQueen = new ChessQueen(RED,3,9);
    m_pChessBoard->SetBoardValue(pRedQueen->GetChessPosX(),pRedQueen->GetChessPosY(),&pRedQueen);
    ChessCharacter* pRedQueen2 = new ChessQueen(RED,5,9);
    m_pChessBoard->SetBoardValue(pRedQueen2->GetChessPosX(),pRedQueen2->GetChessPosY(),&pRedQueen2);
    ChessCharacter* pRedBishop = new ChessBishop(RED,2,9);
    m_pChessBoard->SetBoardValue(pRedBishop->GetChessPosX(),pRedBishop->GetChessPosY(),&pRedBishop);
    ChessCharacter* pRedBishop2 = new ChessBishop(RED,6,9);
    m_pChessBoard->SetBoardValue(pRedBishop2->GetChessPosX(),pRedBishop2->GetChessPosY(),&pRedBishop2);
    ChessCharacter* pRedKnight = new ChessKnight(RED,1,9);
    m_pChessBoard->SetBoardValue(pRedKnight->GetChessPosX(),pRedKnight->GetChessPosY(),&pRedKnight);
    ChessCharacter* pRedKnight2 = new ChessKnight(RED,7,9);
    m_pChessBoard->SetBoardValue(pRedKnight2->GetChessPosX(),pRedKnight2->GetChessPosY(),&pRedKnight2);
    ChessCharacter* pRedTower = new ChessTower(RED,0,9);
    m_pChessBoard->SetBoardValue(pRedTower->GetChessPosX(),pRedTower->GetChessPosY(),&pRedTower);
    ChessCharacter* pRedTower2 = new ChessTower(RED,8,9);
    m_pChessBoard->SetBoardValue(pRedTower2->GetChessPosX(),pRedTower2->GetChessPosY(),&pRedTower2);
    ChessCharacter* pRedCannon = new ChessCannon(RED,1,7);
    m_pChessBoard->SetBoardValue(pRedCannon->GetChessPosX(),pRedCannon->GetChessPosY(),&pRedCannon);
    ChessCharacter* pRedCannon2 = new ChessCannon(RED,7,7);
    m_pChessBoard->SetBoardValue(pRedCannon2->GetChessPosX(),pRedCannon2->GetChessPosY(),&pRedCannon2);
    ChessCharacter* pRedMinion = new ChessMinion(RED,0,6);
    m_pChessBoard->SetBoardValue(pRedMinion->GetChessPosX(),pRedMinion->GetChessPosY(),&pRedMinion);
    ChessCharacter* pRedMinion2 = new ChessMinion(RED,2,6);
    m_pChessBoard->SetBoardValue(pRedMinion2->GetChessPosX(),pRedMinion2->GetChessPosY(),&pRedMinion2);
    ChessCharacter* pRedMinion3 = new ChessMinion(RED,4,6);
    m_pChessBoard->SetBoardValue(pRedMinion3->GetChessPosX(),pRedMinion3->GetChessPosY(),&pRedMinion3);
    ChessCharacter* pRedMinion4 = new ChessMinion(RED,6,6);
    m_pChessBoard->SetBoardValue(pRedMinion4->GetChessPosX(),pRedMinion4->GetChessPosY(),&pRedMinion4);
    ChessCharacter* pRedMinion5 = new ChessMinion(RED,8,6);
    m_pChessBoard->SetBoardValue(pRedMinion5->GetChessPosX(),pRedMinion5->GetChessPosY(),&pRedMinion5);
}

void BoardController::InitBlackTeam()
{
    ChessCharacter* pBlackKing = new ChessKing(BLACK,4,0);
    m_pChessBoard->SetBoardValue(pBlackKing->GetChessPosX(),pBlackKing->GetChessPosY(),&pBlackKing);
    ChessCharacter* pBlackQueen = new ChessQueen(BLACK,3,0);
    m_pChessBoard->SetBoardValue(pBlackQueen->GetChessPosX(),pBlackQueen->GetChessPosY(),&pBlackQueen);
    ChessCharacter* pBlackQueen2 = new ChessQueen(BLACK,5,0);
    m_pChessBoard->SetBoardValue(pBlackQueen2->GetChessPosX(),pBlackQueen2->GetChessPosY(),&pBlackQueen2);
    ChessCharacter* pBlackBishop = new ChessBishop(BLACK,2,0);
    m_pChessBoard->SetBoardValue(pBlackBishop->GetChessPosX(),pBlackBishop->GetChessPosY(),&pBlackBishop);
    ChessCharacter* pBlackBishop2 = new ChessBishop(BLACK,6,0);
    m_pChessBoard->SetBoardValue(pBlackBishop2->GetChessPosX(),pBlackBishop2->GetChessPosY(),&pBlackBishop2);
    ChessCharacter* pBlackKnight = new ChessKnight(BLACK,1,0);
    m_pChessBoard->SetBoardValue(pBlackKnight->GetChessPosX(),pBlackKnight->GetChessPosY(),&pBlackKnight);
    ChessCharacter* pBlackKnight2 = new ChessKnight(BLACK,7,0);
    m_pChessBoard->SetBoardValue(pBlackKnight2->GetChessPosX(),pBlackKnight2->GetChessPosY(),&pBlackKnight2);
    ChessCharacter* pBlackTower = new ChessTower(BLACK,0,0);
    m_pChessBoard->SetBoardValue(pBlackTower->GetChessPosX(),pBlackTower->GetChessPosY(),&pBlackTower);
    ChessCharacter* pBlackTower2 = new ChessTower(BLACK,8,0);
    m_pChessBoard->SetBoardValue(pBlackTower2->GetChessPosX(),pBlackTower2->GetChessPosY(),&pBlackTower2);
    ChessCharacter* pBlackCannon = new ChessCannon(BLACK,1,2);
    m_pChessBoard->SetBoardValue(pBlackCannon->GetChessPosX(),pBlackCannon->GetChessPosY(),&pBlackCannon);
    ChessCharacter* pBlackCannon2 = new ChessCannon(BLACK,7,2);
    m_pChessBoard->SetBoardValue(pBlackCannon2->GetChessPosX(),pBlackCannon2->GetChessPosY(),&pBlackCannon2);
    ChessCharacter* pBlackMinion = new ChessMinion(BLACK,0,3);
    m_pChessBoard->SetBoardValue(pBlackMinion->GetChessPosX(),pBlackMinion->GetChessPosY(),&pBlackMinion);
    ChessCharacter* pBlackMinion2 = new ChessMinion(BLACK,2,3);
    m_pChessBoard->SetBoardValue(pBlackMinion2->GetChessPosX(),pBlackMinion2->GetChessPosY(),&pBlackMinion2);
    ChessCharacter* pBlackMinion3 = new ChessMinion(BLACK,4,3);
    m_pChessBoard->SetBoardValue(pBlackMinion3->GetChessPosX(),pBlackMinion3->GetChessPosY(),&pBlackMinion3);
    ChessCharacter* pBlackMinion4 = new ChessMinion(BLACK,6,3);
    m_pChessBoard->SetBoardValue(pBlackMinion4->GetChessPosX(),pBlackMinion4->GetChessPosY(),&pBlackMinion4);
    ChessCharacter* pBlackMinion5 = new ChessMinion(BLACK,8,3);
    m_pChessBoard->SetBoardValue(pBlackMinion5->GetChessPosX(),pBlackMinion5->GetChessPosY(),&pBlackMinion5);
}

void BoardController::ResetCoordinate()
{
    m_nPairCoodinateIndex = 0;
    m_bEnableBeepSound = true;
    m_pCoodinate->operator[](0).first = 0;
    m_pCoodinate->operator[](0).second = 0;
    m_pCoodinate->operator[](1).first = 0;
    m_pCoodinate->operator[](1).second = 0;
}

void BoardController::InitBoardChess()
{
    qDebug()<<"BoardController::InitBoardChess+";
    ResetCoordinate();
    ClearBoardChess();
    InitRedTeam();
    InitBlackTeam();
    qDebug()<<"BoardController::InitBoardChess-";
}
