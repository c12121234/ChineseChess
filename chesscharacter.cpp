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
    qDebug()<<"ChessCharacter::GetChessPosX+ :" <<m_posX;
    return m_posX;
}

void ChessCharacter::SetChessPosX(int x)
{
    m_posX = x;
}

int ChessCharacter::GetChessPosY()
{
    qDebug()<<"ChessCharacter::GetChessPosY+ :"<<m_posY;
    return m_posY;
}

void ChessCharacter::SetChessPosY(int y)
{
    m_posY = y;
}

bool ChessCharacter::isEatSelfTeam(ChessBoard *cb, int posX, int posY)
{
    Team Temp = cb->GetBoardTeamValue(posX,posY);
    return Temp == m_Team ? true :false;
}

ChessKing::ChessKing(Team team,int x,int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{
    qDebug()<<"ChessKing::ChessKing+";
    qDebug()<<"ChessKing::ChessKing-";
}


bool ChessKing::CantMoveCondition(ChessBoard* cb,int posX, int posY)
{
    if(posX>5 || posX< 3 )
        return true;
    if(m_Team == RED && (posY<7))
        return true;
    if(m_Team == BLACK && posY>3)
        return true;
    if(isEatSelfTeam(cb,posX,posY))
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

bool ChessQueen::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(posX>5 || posX< 3 )
        return true;
    if(m_Team == RED && (posY<7))
        return true;
    if(m_Team == BLACK && posY>3)
        return true;
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    return (abs(m_posX-posX)==1 && abs(m_posY-posY)==1)? false:true;
}

ChessBishop::ChessBishop(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

bool ChessBishop::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(m_Team == RED && posY<5)
        return true;
    if(m_Team == BLACK && posY>4)
        return true;
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    if(isBlock(cb,posX,posY))
        return true;
    return !isCorrectMoveForm(posX,posY);
}

bool ChessBishop::isCorrectMoveForm(int posX, int posY)
{
    return (abs(m_posX-posX)==2 && abs(m_posY-posY)==2)?true:false;
}

bool ChessBishop::isBlock(ChessBoard *cb, int posX, int posY)
{
    bool bBlock = false;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionX = (moveX>0)? 1:-1;
    int directionY = (moveY>0)? 1:-1;

    if(directionX>0 && directionY>0)
    {
        Team tBlock = cb->GetBoardTeamValue(m_posX+1,m_posY+1);
        bBlock = (tBlock == ZERO) ? false :true;
    }
    else if(directionX>0 && directionY<0)
    {
        Team tBlock = cb->GetBoardTeamValue(m_posX+1,m_posY-1);
        bBlock = (tBlock == ZERO) ? false :true;
    }
    else if(directionX<0 && directionY>0)
    {
        Team tBlock = cb->GetBoardTeamValue(m_posX-1,m_posY+1);
        bBlock = (tBlock == ZERO) ? false :true;
    }
    else if(directionX<0 && directionY<0)
    {
        Team tBlock = cb->GetBoardTeamValue(m_posX-1,m_posY-1);
        bBlock = (tBlock == ZERO) ? false :true;
    }
}

ChessKnight::ChessKnight(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

bool ChessKnight::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    bool bCorrectForm = isCorrectMoveForm(posX,posY);
    bool bBlock = isBlock(cb,posX,posY);
    return (bCorrectForm == true && bBlock == false)?false:true;
}

bool ChessKnight::isCorrectMoveForm(int posX, int posY)
{
    return (abs(m_posX-posX)==2 && abs(m_posY-posY) == 1) || (abs(m_posX-posX)==1 && abs(m_posY-posY) == 2) ? true:false;
}

bool ChessKnight::isBlock(ChessBoard *cb, int posX, int posY)
{
    bool bBlock = false;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionX = (moveX>0)? 1:-1;
    int directionY = (moveY>0)? 1:-1;
    if(abs(moveX) == 2)
    {
        if(directionX == 1)
        {
            Team tBlock = cb->GetBoardTeamValue(m_posX+1,m_posY);
            bBlock = tBlock == ZERO ? false :true;
        }
        else if(directionX == -1)
        {
            Team tBlock = cb->GetBoardTeamValue(m_posX-1,m_posY);
            bBlock = tBlock == ZERO ? false :true;
        }
    }
    else if(abs(moveY) == 2)
    {
        if(directionY == 1)
        {
            Team tBlock = cb->GetBoardTeamValue(m_posX,m_posY+1);
            bBlock = tBlock == ZERO ? false :true;
        }
        else if(directionY == -1)
        {
            Team tBlock = cb->GetBoardTeamValue(m_posX,m_posY-1);
            bBlock = tBlock == ZERO ? false :true;
        }
    }
    return bBlock;
}

ChessTower::ChessTower(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

bool ChessTower::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    if(abs(moveX)>0 && abs(moveY)>0)
        return true;
    return isBlock(cb,posX,posY);
}

bool ChessTower::isBlock(ChessBoard *cb, int posX, int posY)
{
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionX = (moveX>0)? 1:-1;
    int directionY = (moveY>0)? 1:-1;
    int bBlock = false;
    if(abs(moveX)>0)
    {
        if(directionX == 1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,PLUSX,m_posX,m_posY,posX,TOWER);
        }
        else if(directionX == -1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,MINUSX,m_posX,m_posY,posX,TOWER);
        }
    }
    else if(abs(moveY)>0)
    {
        if(directionY == 1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,PLUSY,m_posX,m_posY,posY,TOWER);
        }
        else if(directionY == -1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,MINUSY,m_posX,m_posY,posY,TOWER);
        }
    }
    return bBlock;
}

ChessCannon::ChessCannon(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

bool ChessCannon::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    if(abs(moveX)>0 && abs(moveY)>0)
        return true;
    if(CanAttack(cb,posX,posY))
        return false;
    return isBlock(cb,posX,posY);
}

bool ChessCannon::isBlock(ChessBoard *cb, int posX, int posY)
{
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionX = (moveX>0)? 1:-1;
    int directionY = (moveY>0)? 1:-1;
    int bBlock = false;
    if(abs(moveX)>0)
    {
        if(directionX == 1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,PLUSX,m_posX,m_posY,posX,CANNON);
        }
        else if(directionX == -1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,MINUSX,m_posX,m_posY,posX,CANNON);
        }
    }
    else if(abs(moveY)>0)
    {
        if(directionY == 1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,PLUSY,m_posX,m_posY,posY,CANNON);
        }
        else if(directionY == -1)
        {
            bBlock = ChessBoardUtil::isInBlockRange(cb,MINUSY,m_posX,m_posY,posY,CANNON);
        }
    }
    return bBlock;
}

bool ChessCannon::CanAttack(ChessBoard *cb, int posX, int posY)
{
    if(isEatSelfTeam(cb,posX,posY))
        return false;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionX = (moveX>0)? 1:-1;
    int directionY = (moveY>0)? 1:-1;
    int bAttack = false;
    int nBlockNum = 0;
    Team tAttack = ZERO;
    if(abs(moveX)>0)
    {
        if(directionX == 1)
        {
            for(int i = m_posX+1;i<=posX;++i)
            {
                tAttack = cb->GetBoardTeamValue(i,m_posY);
                if(tAttack == ZERO)
                    continue;
                nBlockNum++;
            }
        }
        else if(directionX == -1)
        {
            for(int i = m_posX-1;i>=posX;--i)
            {
                tAttack = cb->GetBoardTeamValue(i,m_posY);
                if(tAttack == ZERO)
                    continue;
                nBlockNum++;
            }
        }
    }
    else if(abs(moveY)>0)
    {
        if(directionY == 1)
        {
            for(int i = m_posY+1;i<=posY;++i)
            {
                tAttack = cb->GetBoardTeamValue(m_posX,i);
                if(tAttack == ZERO)
                    continue;
                nBlockNum++;
            }
        }
        else if(directionY == -1)
        {
            for(int i = m_posY-1;i>=posY;--i)
            {
                tAttack = cb->GetBoardTeamValue(m_posX,i);
                if(tAttack == ZERO)
                    continue;
                nBlockNum++;
            }
        }
    }
    bAttack = (m_Team!=tAttack && nBlockNum == 2)?true:false;
    return bAttack;
}

ChessMinion::ChessMinion(Team team, int x, int y, QObject *parent):
    ChessCharacter(team,x,y,parent)
{

}

bool ChessMinion::CantMoveCondition(ChessBoard *cb, int posX, int posY)
{
    if(isEatSelfTeam(cb,posX,posY))
        return true;
    int moveX = posX-m_posX;
    int moveY = posY-m_posY;
    int directionY = 0;
    if(moveY>0)
        directionY =1;
    else if(moveY<0)
        directionY = -1;
    else
        directionY = 0;
    if((m_Team == RED && directionY == 1) || (m_Team == RED && m_posY >=5 && moveX !=0))
        return true;
    if((m_Team == BLACK && directionY == -1) || (m_Team == BLACK && m_posY <=4 && moveX!=0))
        return true;
    bool bRet = true;
    if(abs(moveX)==1 || abs(moveY)==1)
        bRet = false;
    if(abs(moveX)==1 && abs(moveY)==1)
        bRet = true;
    return bRet;
}
