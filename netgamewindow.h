#ifndef NETGAMEWINDOW_H
#define NETGAMEWINDOW_H
#include "mainwindow.h"

class QTcpServer;
class QTcpSocket;

class NetGameWindow : public MainWindow
{
    Q_OBJECT
public:
    NetGameWindow(bool bServer,QString strIP,QString strPort);
    ~NetGameWindow();
signals:
    void ConnectEachOther();
public slots:
    void HandleNewConnection();
    void HandleReceiveData();
    void HandleWriteData(std::pair<int,int> p1,std::pair<int,int> p2);
private:
    QTcpServer* m_pServer;
    QTcpSocket* m_pClient;
    bool m_bServer;
};

#endif // NETGAMEWINDOW_H
