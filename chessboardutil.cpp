#include "chessboardutil.h"
#include "boardfactory.h"

Team ChessBoardUtil::GetBoardValue(ChessBoard* cb ,int posX, int posY)
{
    return cb->GetBoardValue(posX,posY);
}

void ChessBoardUtil::SetBoardValue(ChessBoard *cb, int posX, int posY, ChessCharacter *pcc)
{
    //cb->SetBoardValue(posX,posY,pcc);
}

ChessBoard *ChessBoardUtil::CreateBoard()
{
    BoardFactory bf;
    return bf.CreateBoard();
}

ChessCharacter *ChessBoardUtil::CreateChess(Team team, CHARACTER character)
{
    ChessCharacter* pcc = nullptr;
    switch (character)
    {
        case KING :
        {
            //pcc = new ChessKing(team);
            break;
        }
        case QUEEN :
        {
            break;
        }
        case BISHOP :
        {
            break;
        }
        case KNIGHT :
        {
            break;
        }
        case TOWER :
        {
            break;
        }
        case CANNON :
        {
            break;
        }
        case MINIMON:
        {
            break;
        }
        default:
            break;
    }
    return pcc;
}

ChessBoardUtil::ChessBoardUtil()
{

}
