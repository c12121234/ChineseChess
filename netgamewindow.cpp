#include "netgamewindow.h"
#include "boardcontroller.h"
#include <QtNetwork>
#include <QMessageBox>
NetGameWindow::NetGameWindow(bool bServer, QString strIP, QString strPort):
    MainWindow(),m_pServer(nullptr),m_pClient(nullptr),m_bServer(bServer)
{        
    if(bServer)
    {

        m_pServer = new QTcpServer(this);
        bool bListen = m_pServer->listen(QHostAddress::Any,strPort.toInt());
        if(!bListen)
        {
            QMessageBox::critical(this, tr("Server problem"),
                                  tr("Unable to start the server."));
            close();
            return;
        }
        //正在監聽的訊息要顯示
        connect(m_pServer,&QTcpServer::newConnection,this,&NetGameWindow::ConnectEachOther);
        connect(m_pServer,&QTcpServer::newConnection,this,&NetGameWindow::HandleNewConnection);
    }
    else
    {
        m_pClient = new QTcpSocket(this);
        m_pClient->connectToHost(strIP,strPort.toInt());
        connect(m_pClient,&QAbstractSocket::connected,this,&NetGameWindow::ConnectEachOther);
        connect(m_pClient,&QAbstractSocket::readyRead,this,&NetGameWindow::HandleReceiveData);
        connect(m_pClient,&QAbstractSocket::disconnected,m_pClient,&QAbstractSocket::deleteLater);

    }
    connect(this->m_pBoardController,&BoardController::SendCoordinateToViewUpdate,
            this,&NetGameWindow::HandleWriteData);
    connect(this->m_pBoardController,&BoardController::SendChangedm_pCoordinate,
            this->m_pBoardController,&BoardController::HandleSendChangedm_pCoordinate);
}

NetGameWindow::~NetGameWindow()
{

}

void NetGameWindow::HandleNewConnection()
{
    m_pClient = m_pServer->nextPendingConnection();
    connect(m_pClient,&QAbstractSocket::readyRead,this,&NetGameWindow::HandleReceiveData);

}

void NetGameWindow::HandleReceiveData()
{
    QByteArray data;
    data = m_pClient->readAll();
    QDataStream in(&data,QIODevice::ReadWrite);
    in.setVersion(QDataStream::Qt_5_9);
    vector<int> vTemp(4,0);
    in >>vTemp[0]>>vTemp[1]>>vTemp[2]>>vTemp[3];
    emit this->m_pBoardController->SendChangedm_pCoordinate(vTemp[0],vTemp[1],vTemp[2],vTemp[3]);
}

void NetGameWindow::HandleWriteData(std::pair<int, int> p1, std::pair<int, int> p2)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_9);
    out <<p1.first<<p1.second<<p2.first<<p2.second;
    m_pClient->write(data);
}
