#ifndef CHESSCHARACTER_H
#define CHESSCHARACTER_H

#include <QObject>
#include "ChessID.h"

class ChessBoard;

class ChessCharacter : public QObject
{
    Q_OBJECT
public:
    explicit ChessCharacter(Team Team,int x,int y,QObject *parent = nullptr);
    virtual ~ChessCharacter();
    virtual bool Move(ChessBoard* cb,int posX,int posY);
    virtual bool CantMoveCondition(ChessBoard* cb,int posX,int posY);
    Team GetChessTeam();
    void ChessTest();
    int GetChessPosX();
    void SetChessPosX(int x);
    int GetChessPosY();
    void SetChessPosY(int y);
protected:
    Team m_Team;
    int m_posX;
    int m_posY;
};

class ChessKing : public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessKing(Team team,int x,int y,QObject* parent = nullptr);
    ~ChessKing() override;
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
};

class ChessQueen:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessQueen(Team team,int x,int y,QObject* parent = nullptr);
    ~ChessQueen() override;
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
};

#endif // CHESSCHARACTER_H
