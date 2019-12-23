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
    vector<tuple<QGraphicsItem*,QPixmap*,pair<int,int>>> vTemp(32,std::make_tuple(nullptr,nullptr,std::make_pair(-1,-1)));
    m_chessArr = vTemp;
    ui->setupUi(this);
    ui->graphicsView->installEventFilter(this);
    InitScene();
    //connect(this,&MainWindow::SendMouseEventToConTroller,m_spBoardController.get(),&BoardController::HandleMouseEventFromView);
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
            ui->graphicsView->show();
            break;
        }
    }
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

    std::get<0>(m_chessArr[0])->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair = std::get<2>(m_chessArr[0]);
    TempPair.first =4;
    TempPair.second = 9;

    std::get<0>(m_chessArr[1])->setPos(ConvertCoordinate::ConverX(3),ConvertCoordinate::ConverY(9));
    pair<int,int>& TempPair1 = std::get<2>(m_chessArr[1]);
    TempPair1.first = 3;
    TempPair1.second = 9;
    /*
    m_chessArr[0].first->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(9));
    m_chessArr[1].first->setPos(ConvertCoordinate::ConverX(3),ConvertCoordinate::ConverY(9));
    m_chessArr[2].first->setPos(ConvertCoordinate::ConverX(5),ConvertCoordinate::ConverY(9));
    m_chessArr[3].first->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(9));
    m_chessArr[4].first->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(9));
    m_chessArr[5].first->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(9));
    m_chessArr[6].first->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(9));
    m_chessArr[7].first->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(9));
    m_chessArr[8].first->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(9));
    m_chessArr[9].first->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(7));
    m_chessArr[10].first->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(7));
    m_chessArr[11].first->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(6));
    m_chessArr[12].first->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(6));
    m_chessArr[13].first->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(6));
    m_chessArr[14].first->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(6));
    m_chessArr[15].first->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(6));

    m_chessArr[16].first->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(0));
    m_chessArr[17].first->setPos(ConvertCoordinate::ConverX(3),ConvertCoordinate::ConverY(0));
    m_chessArr[18].first->setPos(ConvertCoordinate::ConverX(5),ConvertCoordinate::ConverY(0));
    m_chessArr[19].first->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(0));
    m_chessArr[20].first->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(0));
    m_chessArr[21].first->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(0));
    m_chessArr[22].first->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(0));
    m_chessArr[23].first->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(0));
    m_chessArr[24].first->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(0));
    m_chessArr[25].first->setPos(ConvertCoordinate::ConverX(1),ConvertCoordinate::ConverY(2));
    m_chessArr[26].first->setPos(ConvertCoordinate::ConverX(7),ConvertCoordinate::ConverY(2));
    m_chessArr[27].first->setPos(ConvertCoordinate::ConverX(0),ConvertCoordinate::ConverY(3));
    m_chessArr[28].first->setPos(ConvertCoordinate::ConverX(2),ConvertCoordinate::ConverY(3));
    m_chessArr[29].first->setPos(ConvertCoordinate::ConverX(4),ConvertCoordinate::ConverY(3));
    m_chessArr[30].first->setPos(ConvertCoordinate::ConverX(6),ConvertCoordinate::ConverY(3));
    m_chessArr[31].first->setPos(ConvertCoordinate::ConverX(8),ConvertCoordinate::ConverY(3));
    */
}

void MainWindow::CreateChessPair(int i)
{
    QGraphicsPixmapItem* chess = new QGraphicsPixmapItem();
    QString strPicPath = "Resource/"+QString::number(i+1)+".png";
    QPixmap* pic = new QPixmap(strPicPath);
    QPixmap ptemp = pic->scaled(44,44);
    chess->setPixmap(ptemp);
    m_spScene->addItem(chess);
    //m_chessArr[i].first = chess;
    //m_chessArr[i].second = pic;
    auto tempt = std::make_tuple(std::ref(chess),std::ref(pic),std::make_pair(-1,-1));
    m_chessArr[i] = tempt;
}


