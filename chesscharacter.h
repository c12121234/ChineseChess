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
    bool isEatSelfTeam(ChessBoard* cb,int posX,int posY);
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
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
};

class ChessQueen:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessQueen(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
};

class ChessBishop:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessBishop(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
private:
    bool isCorrectMoveForm(int posX,int posY);//是否走田字
    bool isBlock(ChessBoard* cb,int posX,int posY);//是否堵象眼
};

class ChessKnight:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessKnight(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
private:
    bool isCorrectMoveForm(int posX,int posY); //是否走日字
    bool isBlock(ChessBoard* cb,int posX,int posY);//是否拐馬腳
};

class ChessTower:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessTower(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
private:
    bool isBlock(ChessBoard* cb,int posX,int posY);
};

class ChessCannon:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessCannon(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
private:
    bool isBlock(ChessBoard* cb,int posX,int posY);
    bool CanAttack(ChessBoard* cb,int posX,int posY);
};

class ChessMinion:public ChessCharacter
{
    Q_OBJECT
public:
    explicit ChessMinion(Team team,int x,int y,QObject* parent = nullptr);
    bool CantMoveCondition(ChessBoard* cb,int posX,int posY) override;
};
#endif // CHESSCHARACTER_H
