#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include <vector>
#include <utility>
#include "ChessID.h"
class ChessBoard;
class MainWindow;
class QMouseEvent;
class QGraphicsSceneMouseEvent;
class BoardController : public QObject
{
    Q_OBJECT
public:
    explicit BoardController(MainWindow** ppMainWindow, QObject *parent = nullptr);
    ~BoardController();
signals:
    void SendCoordinateToViewUpdate(std::pair<int,int> p1,std::pair<int,int> p2);
    void SendBeepSound();
    void SendChangedm_pCoordinate(int posX1,int posY1,int posX2,int posY2);
    void SendTurnChange(Team tTeam);
public slots:
    void HandleMouseEventFromView(QGraphicsSceneMouseEvent* event);
    void InitBoardChess();    
    void HandleSendChangedm_pCoordinate(int posX1,int posY1,int posX2,int posY2);
private:
    void ConvertCoodinateToChess(int x,int y);
    bool isOutOfRange(int x,int y);
    bool isOutOfChessRadius(int x,int y);    
    void TestVal(int x,int y);
    void ClearBoardChess();
    void DoChessMove();
    void ControlAlarm();
    void InitRedTeam();
    void InitBlackTeam();
    void ResetCoordinate();
    ChessBoard* m_pChessBoard;
    std::vector<std::pair<int,int>>* m_pCoodinate;
    MainWindow* m_pMainWindow;

    int m_nChessRadius;
    int m_nChessMoveRange;
    int m_nChessXBegin;
    int m_nChessYBegin;
    int m_nPairCoodinateIndex;
    bool m_bEnableBeepSound;
    Team m_Team;
};

#endif // BOARDCONTROLLER_H
