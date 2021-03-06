#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <memory>
#include "ChessID.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QGraphicsView;
class QGraphicsScene;
class QGraphicsItem;
class QGraphicsTextItem;
class QMouseEvent;
class QGraphicsSceneMouseEvent;
class BoardController;
class MyGraphicsScene;
using std::shared_ptr;
using std::vector;
using std::pair;
using std::tuple;
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void SendMouseEventToConTroller(QGraphicsSceneMouseEvent* event);        
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject* obj,QEvent* event) override;
public slots:
    void HandleCoordinateToViewUpdate(pair<int,int> p1,pair<int,int> p2);
    void HandleBeepSound();
    void HandleNewGame();
    void HandleChangeTurn(Team tTeam);
protected:
    BoardController* m_pBoardController;
private:
    void InitScene();
    void InitChess();
    void InitTurnIcon();
    void CreateChessPair(int i);
    void ShowAllChess();
    void BindingRedTeam();
    void BindingBlackTeam();
    void BindingRedKing();
    void BindingRedQueen();
    void BindingRedBishop();
    void BindingRedKnight();
    void BindingRedTower();
    void BindingRedCannon();
    void BindingRedMinion();
    void BindingBlackKing();
    void BindingBlackQueen();
    void BindingBlackBishop();
    void BindingBlackKnight();
    void BindingBlackTower();
    void BindingBlackCannon();
    void BindingBlackMinion();
    Ui::MainWindow *ui;
    shared_ptr<MyGraphicsScene> m_spScene;
    shared_ptr<QImage> m_spBoardImage;
    shared_ptr<QGraphicsTextItem> m_spTextItem;
    //shared_ptr<BoardController> m_spBoardController;    
    vector<tuple<QGraphicsItem*,QPixmap*,pair<int,int>>> m_chessArr;

};
#endif // MAINWINDOW_H
