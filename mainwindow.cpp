#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QToolTip>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDir>
#include <QTimer>
#include <QToolTip>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "boardcontroller.h"
#include "mygraphicsscene.h"
#include "convertcoordinate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_spScene(std::make_shared<MyGraphicsScene>())
    , m_spBoardImage(std::make_shared<QImage>())
    //, m_spBoardController(std::make_shared<BoardController>(this))
{
    MainWindow* pTemp = this;
    m_pBoardController = new BoardController(&pTemp);
    connect(m_pBoardController,&BoardController::SendBeepSound,this,&MainWindow::HandleBeepSound);
    vector<tuple<QGraphicsItem*,QPixmap*,pair<int,int>>> vTemp(32,std::make_tuple(nullptr,nullptr,std::make_pair(-1,-1)));
    m_chessArr = vTemp;
    ui->setupUi(this);
    connect(ui->ActionNewGame,&QAction::triggered,this,&MainWindow::HandleNewGame);
    connect(ui->ActionNewGame,&QAction::triggered,m_pBoardController,&BoardController::InitBoardChess);
    ui->graphicsView->installEventFilter(this);
    InitScene();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pBoardController;
    for(auto i :m_chessArr)
    {
        delete std::get<0>(i);
        delete std::get<1>(i);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->graphicsView)
    {
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
            qDebug()<<"MainWindow::eventFilter :"<<QString("%1,%2").arg(me->pos().x()).arg(me->pos().y());

            //emit SendMouseEventToConTroller(me);
        }
    }
    return QMainWindow::eventFilter(obj,event);
}

void MainWindow::HandleCoordinateToViewUpdate(pair<int, int> p1, pair<int, int> p2)
{
    for(auto& TempTuple :m_chessArr)
    {
        if(std::get<2>(TempTuple) == p2)
        {
            std::get<0>(TempTuple)->hide();
            std::get<2>(TempTuple).first = -1;
            std::get<2>(TempTuple).second = -1;
        }
    }

    for(auto& TempTuple :m_chessArr)
    {
        if(std::get<2>(TempTuple) == p1)
        {
            std::get<0>(TempTuple)->setPos(ConvertCoordinate::ConverX(p2.first),ConvertCoordinate::ConverY(p2.second));
            std::get<2>(TempTuple) = p2;
            //ui->graphicsView->show();
            ui->graphicsView->update();
            break;
        }
    }
}

void MainWindow::HandleBeepSound()
{
    QApplication::beep();
}

void MainWindow::HandleNewGame()
{
    BindingRedTeam();
    BindingBlackTeam();
    ShowAllChess();
    //ui->graphicsView->show();
    ui->graphicsView->update();
}

void MainWindow::InitScene()
{
    ui->graphicsView->setScene(m_spScene.get());
    m_spScene->installEventFilter(m_spScene.get());
    connect(m_spScene.get(),&MyGraphicsScene::SentSceneMouseEventToController,
            m_pBoardController,&BoardController::HandleMouseEventFromView);
    ui->graphicsView->setBackgroundBrush(QColor(255,255,0,100));
    m_spBoardImage->load("Resource/Board.png");
    m_spScene->addPixmap(QPixmap::fromImage(*m_spBoardImage));        
    InitChess();
    //connect(ui->ActionNewGame,&QAction::triggered,this,&MainWindow::HandleNewGame);
    ui->graphicsView->show();
}

void MainWindow::InitChess()
{
    //must after init m_chessArr
    ConvertCoordinate::m_nChessImgWidth = 44;
    ConvertCoordinate::m_nChessImgHeigh = 44;
    for(int i = 0; i<16;++i)
    {
        //red chess
        CreateChessPair(i);
        //black chess
        CreateChessPair(i+16);
    }
    BindingRedTeam();
    BindingBlackTeam();
}

void MainWindow::CreateChessPair(int i)
{
    QGraphicsPixmapItem* chess = new QGraphicsPixmapItem();
    QString strPicPath = "Resource/"+QString::number(i+1)+".png";
    QPixmap* pic = new QPixmap(strPicPath);
    QPixmap ptemp = pic->scaled(44,44);
    chess->setPixmap(ptemp);
    m_spScene->addItem(chess);
    auto tempt = std::make_tuple(std::ref(chess),std::ref(pic),std::make_pair(-1,-1));
    m_chessArr[i] = tempt;
}

void MainWindow::ShowAllChess()
{
    for(auto& TempTuple :m_chessArr)
        std::get<0>(TempTuple)->show();
}

void MainWindow::BindingRedTeam()
{
    BindingRedKing();
    BindingRedQueen();
    BindingRedBishop();
    BindingRedKnight();
    BindingRedTower();
    BindingRedCannon();
    BindingRedMinion();
}

void MainWindow::BindingBlackTeam()
{
    BindingBlackKing();
    BindingBlackQueen();
    BindingBlackBishop();
    BindingBlackKnight();
    BindingBlackTower();
    BindingBlackCannon();
    BindingBlackMinion();
}

void MainWindow::BindingRedKing()
{
    std::get<0>(m_chessArr[0])->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[0]);
    TempPair.first =4;
    TempPair.second = 9;
}

void MainWindow::BindingRedQueen()
{
    std::get<0>(m_chessArr[1])->setPos(ConvertCoordinate::ConverX(3),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[1]);
    TempPair.first = 3;
    TempPair.second = 9;

    std::get<0>(m_chessArr[2])->setPos(ConvertCoordinate::ConverX(5),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[2]);
    TempPair2.first = 5;
    TempPair2.second = 9;
}

void MainWindow::BindingRedBishop()
{
    std::get<0>(m_chessArr[3])->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[3]);
    TempPair.first = 2;
    TempPair.second = 9;

    std::get<0>(m_chessArr[4])->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[4]);
    TempPair2.first = 6;
    TempPair2.second = 9;
}

void MainWindow::BindingRedKnight()
{
    std::get<0>(m_chessArr[5])->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[5]);
    TempPair.first = 1;
    TempPair.second = 9;

    std::get<0>(m_chessArr[6])->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[6]);
    TempPair2.first = 7;
    TempPair2.second = 9;
}

void MainWindow::BindingRedTower()
{
    std::get<0>(m_chessArr[7])->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[7]);
    TempPair.first = 0;
    TempPair.second = 9;

    std::get<0>(m_chessArr[8])->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[8]);
    TempPair2.first = 8;
    TempPair2.second = 9;
}

void MainWindow::BindingRedCannon()
{
    std::get<0>(m_chessArr[9])->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(7));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[9]);
    TempPair.first = 1;
    TempPair.second = 7;

    std::get<0>(m_chessArr[10])->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(7));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[10]);
    TempPair2.first = 7;
    TempPair2.second = 7;
}

void MainWindow::BindingRedMinion()
{
    std::get<0>(m_chessArr[11])->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(6));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[11]);
    TempPair.first = 0;
    TempPair.second = 6;

    std::get<0>(m_chessArr[12])->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(6));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[12]);
    TempPair2.first = 2;
    TempPair2.second = 6;

    std::get<0>(m_chessArr[13])->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(6));
    pair<int,int>& TempPair3 = std::get<2>(m_chessArr[13]);
    TempPair3.first = 4;
    TempPair3.second = 6;

    std::get<0>(m_chessArr[14])->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(6));
    pair<int,int>& TempPair4 = std::get<2>(m_chessArr[14]);
    TempPair4.first = 6;
    TempPair4.second = 6;

    std::get<0>(m_chessArr[15])->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(6));
    pair<int,int>& TempPair5 = std::get<2>(m_chessArr[15]);
    TempPair5.first = 8;
    TempPair5.second = 6;

}

void MainWindow::BindingBlackKing()
{
    std::get<0>(m_chessArr[16])->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[16]);
    TempPair.first =4;
    TempPair.second = 0;
}

void MainWindow::BindingBlackQueen()
{
    std::get<0>(m_chessArr[17])->setPos(ConvertCoordinate::ConverX(3),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[17]);
    TempPair.first = 3;
    TempPair.second = 0;

    std::get<0>(m_chessArr[18])->setPos(ConvertCoordinate::ConverX(5),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[18]);
    TempPair2.first = 5;
    TempPair2.second = 0;
}

void MainWindow::BindingBlackBishop()
{
    std::get<0>(m_chessArr[19])->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[19]);
    TempPair.first = 2;
    TempPair.second = 0;

    std::get<0>(m_chessArr[20])->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[20]);
    TempPair2.first = 6;
    TempPair2.second = 0;
}

void MainWindow::BindingBlackKnight()
{
    std::get<0>(m_chessArr[21])->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[21]);
    TempPair.first = 1;
    TempPair.second = 0;

    std::get<0>(m_chessArr[22])->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[22]);
    TempPair2.first = 7;
    TempPair2.second = 0;
}

void MainWindow::BindingBlackTower()
{
    std::get<0>(m_chessArr[23])->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[23]);
    TempPair.first = 0;
    TempPair.second = 0;

    std::get<0>(m_chessArr[24])->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(0));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[24]);
    TempPair2.first = 8;
    TempPair2.second = 0;
}

void MainWindow::BindingBlackCannon()
{
    std::get<0>(m_chessArr[25])->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(2));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[25]);
    TempPair.first = 1;
    TempPair.second = 2;

    std::get<0>(m_chessArr[26])->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(2));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[26]);
    TempPair2.first = 7;
    TempPair2.second = 2;
}

void MainWindow::BindingBlackMinion()
{
    std::get<0>(m_chessArr[27])->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(3));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[27]);
    TempPair.first = 0;
    TempPair.second = 3;

    std::get<0>(m_chessArr[28])->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(3));
    pair<int,int>& TempPair2 = std::get<2>(m_chessArr[28]);
    TempPair2.first = 2;
    TempPair2.second = 3;

    std::get<0>(m_chessArr[29])->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(3));
    pair<int,int>& TempPair3 = std::get<2>(m_chessArr[29]);
    TempPair3.first = 4;
    TempPair3.second = 3;

    std::get<0>(m_chessArr[30])->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(3));
    pair<int,int>& TempPair4 = std::get<2>(m_chessArr[30]);
    TempPair4.first = 6;
    TempPair4.second = 3;

    std::get<0>(m_chessArr[31])->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(3));
    pair<int,int>& TempPair5 = std::get<2>(m_chessArr[31]);
    TempPair5.first = 8;
    TempPair5.second = 3;
}
