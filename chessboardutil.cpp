#include "chessboardutil.h"
#include "boardfactory.h"
#include "ChessID.h"
Team ChessBoardUtil::GetBoardValue(ChessBoard* cb ,int posX, int posY)
{
    return cb->GetBoardTeamValue(posX,posY);
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

bool ChessBoardUtil::isInBlockRange(ChessBoard *cb, Direction direction, int oriPosX, int oriPosY, int movePos,CHARACTER ID)
{
    int nBlock = 0;
    bool bBlock = false;
    switch (static_cast<int>(direction))
    {
        case PLUSX:
        {
            for(int i = oriPosX+1; i<cb->GetBoardSizeCoordinateX();++i)
            {
                Team tBlock = cb->GetBoardTeamValue(i,oriPosY);
                if(tBlock != ZERO)
                {
                    nBlock = i;
                    if(ID == TOWER)
                        bBlock = movePos>nBlock ?true:false;
                    if(ID == CANNON)
                        bBlock = movePos>=nBlock ?true:false;
                    break;
                }
            }
            break;
        }
        case MINUSX:
        {
            for(int i = oriPosX-1; i>=0;--i)
            {
                Team tBlock = cb->GetBoardTeamValue(i,oriPosY);
                if(tBlock != ZERO)
                {
                    nBlock = i;
                    if(ID == TOWER)
                        bBlock = movePos<nBlock ?true:false;
                    if(ID == CANNON)
                        bBlock = movePos<=nBlock ?true:false;
                    break;
                }
            }
            break;
        }
        case PLUSY:
        {
            for(int i = oriPosY+1; i<cb->GetBoardSizeCoordinateY();++i)
            {
                Team tBlock = cb->GetBoardTeamValue(oriPosX,i);
                if(tBlock != ZERO)
                {
                    nBlock = i;
                    if(ID == TOWER)
                        bBlock = movePos>nBlock ?true:false;
                    if(ID == CANNON)
                        bBlock = movePos>=nBlock ?true:false;
                    break;
                }
            }
            break;
        }
        case MINUSY:
        {
            for(int i = oriPosY-1; i>=0;--i)
            {
                Team tBlock = cb->GetBoardTeamValue(oriPosX,i);
                if(tBlock != ZERO)
                {
                    nBlock = i;
                    if(ID == TOWER)
                        bBlock = movePos<nBlock ?true:false;
                    if(ID == CANNON)
                        bBlock = movePos<=nBlock ?true:false;
                    break;
                }
            }
            break;
        }
        default:
            break;
    }
    return bBlock;
}

ChessBoardUtil::ChessBoardUtil()
{

}
