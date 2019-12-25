#ifndef CHESSBOARDUTIL_H
#define CHESSBOARDUTIL_H
#include "chesscharacter.h"
#include "chessboard.h"
class ChessBoardUtil
{
public:    
    static Team GetBoardValue(ChessBoard* cb,int posX,int posY);
    static void SetBoardValue(ChessBoard* cb,int posX,int posY,ChessCharacter* pcc);
    static ChessBoard* CreateBoard();
    static ChessCharacter* CreateChess(Team team,CHARACTER character);
    static bool isInBlockRange(ChessBoard* cb,Direction direction,int oriPosX,int oriPosY,int movePos,CHARACTER ID);
private:
    ChessBoardUtil();
    ChessBoardUtil(const ChessBoardUtil& cptr) = delete ;
    ChessBoardUtil& operator=(const ChessBoardUtil& asop) = delete;
};

#endif // CHESSBOARDUTIL_H
