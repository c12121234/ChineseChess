#include "chessboard.h"
#include "chesscharacter.h"
#include <QDebug>
ChessBoard::ChessBoard(QObject *parent) : QObject(parent)
  ,m_pBoard(new vector<vector<ChessCharacter*>>(9,vector<ChessCharacter*>(10,nullptr)))
{

}

ChessBoard::~ChessBoard()
{
    for(int i = 0; i<9;++i)
    {
        for(int j =0;j<10;++j)
        {
            if(m_pBoard->operator[](i)[j]!=nullptr)
                delete m_pBoard->operator[](i)[j];
        }
    }
    delete m_pBoard;
}

Team ChessBoard::GetBoardValue(int x, int y)
{
    ChessCharacter* pcc = m_pBoard->operator[](x).operator[](y);
    return pcc ? pcc->GetChessTeam() : ZERO;
}

void ChessBoard::SetBoardValue(int x, int y, ChessCharacter **character)
{
    m_pBoard->operator[](x)[y] = *character;
}

bool ChessBoard::MoveChess(int x0, int y0, int x1, int y1)
{
    bool bRet = m_pBoard->operator[](x0)[y0]->Move(this,x1,y1);
    if(bRet)
    {
        if(m_pBoard->operator[](x1)[y1] != nullptr)
        {
            SetChessCoordinate(x1,y1,-1,-1);
            m_pBoard->operator[](x1)[y1] = m_pBoard->operator[](x0)[y0];
            m_pBoard->operator[](x0)[y0] = nullptr;
        }
        else
        {
            m_pBoard->operator[](x1)[y1] = m_pBoard->operator[](x0)[y0];
            m_pBoard->operator[](x0)[y0] = nullptr;
        }
    }

    return bRet;
}

void ChessBoard::SetChessCoordinate(int x, int y, int Valx, int Valy)
{
    m_pBoard->operator[](x)[y]->SetChessPosX(Valx);
    m_pBoard->operator[](x)[y]->SetChessPosY(Valy);
}

void ChessBoard::TestChessValueByCoor(int x, int y)
{
    if(m_pBoard->operator[](x)[y])
    {
        qDebug()<<"chess x val: "<<m_pBoard->operator[](x)[y]->GetChessPosX();
        qDebug()<<"chess y val: "<<m_pBoard->operator[](x)[y]->GetChessPosY();
    }
    else
    {
        qDebug()<<"chess null";
    }
}

int ChessBoard::GetBoardSizeCoordinateX()
{
    return m_pBoard->size();
}

int ChessBoard::GetBoardSizeCoordinateY()
{
    return m_pBoard->operator[](0).size();
}

