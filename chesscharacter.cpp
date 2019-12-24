#include "chesscharacter.h"
#include "chessboardutil.h"
#include <QDebug>
#include <stdlib.h>
ChessCharacter::ChessCharacter(Team Team, int x, int y, QObject *parent) : QObject(parent)
  ,m_Team(Team),m_posX(x),m_posY(y)
{

}

ChessCharacter::~ChessCharacter()
{

}

bool ChessCharacter::Move(ChessBoard* cb,int posX, int posY)
{
    bool bMove = false;
    if(!CantMoveCondition(cb,posX,posY))
    {
        m_posX = posX;
        m_posY = posY;
        bMove = true;
    }
    return bMove;
}

bool ChessCharacter::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    return false;
}

Team ChessCharacter::GetChessTeam()
{
    return m_Team;
}

void ChessCharacter::ChessTest()
{
    qDebug()<<"test";
}

int ChessCharacter::GetChessPosX()
{
    qDebug()<<"ChessKing::GetChessPosX+ :" <<m_posX;
    return m_posX;
}

void ChessCharacter::SetChessPosX(int x)
{
    m_posX = x;
}

int ChessCharacter::GetChessPosY()
{
    qDebug()<<"ChessKing::GetChessPosY+ :"<<m_posY;
    return m_posY;
}

void ChessCharacter::SetChessPosY(int y)
{
    m_posY = y;
}

ChessKing::ChessKing(Team team,int x,int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{
    qDebug()<<"ChessKing::ChessKing+";
    qDebug()<<"ChessKing::ChessKing-";
}

ChessKing::~ChessKing()
{

}

bool ChessKing::CantMoveCondition(ChessBoard* cb,int posX, int posY)
{
    if(posX>5 || posX< 3 )
        return true;
    if(m_Team == RED && (posY<7))
        return true;
    if(m_Team == BLACK && posY>3)
        return true;
    Team Temp = cb->GetBoardValue(posX,posY);
    if(Temp == m_Team)
        return true;
    if(abs(m_posX-posX)>1 || abs(m_posY-posY)>1)
        return true;
    if(abs(m_posX-posX)+abs(m_posY-posY)>1)
        return true;
    return false;
}

ChessQueen::ChessQueen(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

ChessQueen::~ChessQueen()
{

}

bool ChessQueen::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(posX>5 || posX< 3 )
        return true;
    if(m_Team == RED && (posY<7))
        return true;
    if(m_Team == BLACK && posY>3)
        return true;
    Team Temp = cb->GetBoardValue(posX,posY);
    if(Temp == m_Team)
        return true;
    return (abs(m_posX-posX)==1 && abs(m_posY-posY)==1)? false:true;
}
