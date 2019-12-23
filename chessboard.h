#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <vector>
#include "ChessID.h"

using std::vector;
class ChessCharacter;

class ChessBoard : public QObject
{
    Q_OBJECT
public:
    explicit ChessBoard(QObject *parent = nullptr);
    ~ChessBoard();
    Team GetBoardValue(int x,int y);
    void SetBoardValue(int x,int y,ChessCharacter** character);
    bool MoveChess(int x0,int y0,int x1,int y1);
    void SetChessCoordinate(int x,int y,int Valx,int Valy);
    void TestChessValueByCoor(int x,int y);
    int GetBoardSizeCoordinateX();
    int GetBoardSizeCoordinateY();
//signals:

private:
    vector<vector<ChessCharacter*>>* m_pBoard;
};

#endif // CHESSBOARD_H
