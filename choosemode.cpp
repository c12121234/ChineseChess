#include "choosemode.h"
#include "ui_choosemode.h"
#include "netgamewindow.h"
#include <QtNetwork>
#include <QPainter>
ChooseMode::ChooseMode(QWidget *parent) :
    QDialog(parent),
    m_nChoose(0),ui(new Ui::ChooseMode),m_pLocalGame(nullptr),m_pNetworkGame(nullptr)
{
    ui->setupUi(this);
    SettingPageButton();
    SettingPage2Button();
    SettingPage3Button();
    SettingPage4Button();
    ui->page->show();
}

ChooseMode::~ChooseMode()
{
    delete ui;
    if(m_pLocalGame)
        delete m_pLocalGame;
    if(m_pNetworkGame)
        delete m_pNetworkGame;
}

void ChooseMode::on_btnLocalGame_clicked()
{
    m_nChoose = 1;
    if(!m_pLocalGame)
    {
        m_pLocalGame = new MainWindow;
        connect(m_pLocalGame,&MainWindow::destroyed,m_pLocalGame,&MainWindow::deleteLater);
        connect(m_pLocalGame,&MainWindow::destroyed,this,&ChooseMode::ClearLocalGame);
        m_pLocalGame->setWindowModality(Qt::ApplicationModal);
        m_pLocalGame->show();
    }
    //ui->stackedWidget->setCurrentIndex(0);
    //accept();
}

void ChooseMode::on_btnNetworkGame_clicked()
{
    m_nChoose = 2;
    ui->stackedWidget->setCurrentIndex(CLIENT_SERVER_SELECTPAGE);

    //accept();
}

void ChooseMode::ClearLocalGame()
{
    if(m_pLocalGame)
        m_pLocalGame = nullptr;
}

void ChooseMode::ClearNetworkGame()
{
    if(m_pNetworkGame)
        m_pNetworkGame = nullptr;
}

void ChooseMode::ShowNetGameView()
{
    if(m_pNetworkGame)
    {
        //m_pNetworkGame->setWindowModality(Qt::ApplicationModal);
        m_pNetworkGame->show();
    }
}

void ChooseMode::on_btnQuit_clicked()
{
    m_nChoose = 3;
    this->close();
}

void ChooseMode::on_btnCancelConnect_clicked()
{
    ui->stackedWidget->setCurrentIndex(TOPMENU);
}

void ChooseMode::on_btnEnterConnect_clicked()
{
    int nSelect = ui->comboBox->currentIndex();
    if(nSelect == CLIENT)
        ui->stackedWidget->setCurrentIndex(CLIENT_PAGE);
    else
        ui->stackedWidget->setCurrentIndex(SERVER_PAGE);
}

void ChooseMode::on_btnClientEnterConnect_clicked()
{
    if(!m_pNetworkGame)
    {
        m_pNetworkGame = new NetGameWindow(CLIENT,ui->ConnectIPtextEdit->toPlainText(),
                                           ui->ConnectPorttextEdit->toPlainText());
        connect(m_pNetworkGame,&NetGameWindow::ConnectEachOther,this,&ChooseMode::ShowNetGameView);
        connect(m_pNetworkGame,&NetGameWindow::destroyed,m_pNetworkGame,&NetGameWindow::deleteLater);
        connect(m_pNetworkGame,&NetGameWindow::destroyed,this,&ChooseMode::ClearNetworkGame);

    }
}

void ChooseMode::on_btnClientCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(CLIENT_SERVER_SELECTPAGE);
}

void ChooseMode::on_btnServerEnter_clicked()
{
    if(!m_pNetworkGame)
    {
        m_pNetworkGame = new NetGameWindow(SERVER,"",
                                           ui->ServerPorttextEdit->toPlainText());
        connect(m_pNetworkGame,&NetGameWindow::ConnectEachOther,this,&ChooseMode::ShowNetGameView);
        connect(m_pNetworkGame,&NetGameWindow::destroyed,m_pNetworkGame,&NetGameWindow::deleteLater);
        connect(m_pNetworkGame,&NetGameWindow::destroyed,this,&ChooseMode::ClearNetworkGame);
    }
}

void ChooseMode::on_btnServerCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(CLIENT_SERVER_SELECTPAGE);
}

void ChooseMode::on_comboBox_currentIndexChanged(int index)
{
    if(index == CLIENT)
        ui->labelConnection->setText("as client and BLACK team.");
    else
        ui->labelConnection->setText("as server and RED team.");
}

void ChooseMode::SettingPageButton()
{
    ui->page->setStyleSheet(
                "QPushButton{background-color:rgb(75,152,210);color: black;border-radius: 15px;"
                "border-style: outset;}"
                "QPushButton:hover{background-color:rgb(73,90,104); color: white;border-radius: 15px}"
                "QPushButton:pressed{background-color:rgb(67, 203, 208);border-radius: 15px;"
                "border-style: inset; }");
}

void ChooseMode::SettingPage2Button()
{
    ui->page_2->setStyleSheet(
                "QPushButton{background-color:rgb(75,152,210);color: black;border-radius: 15px;"
                "border-style: outset;}"
                "QPushButton:hover{background-color:rgb(73,90,104); color: white;border-radius: 15px}"
                "QPushButton:pressed{background-color:rgb(67, 203, 208);border-radius: 15px;"
                "border-style: inset; }");
}

void ChooseMode::SettingPage3Button()
{
    ui->page_3->setStyleSheet(
                "QPushButton{background-color:rgb(75,152,210);color: black;border-radius: 15px;"
                "border-style: outset;}"
                "QPushButton:hover{background-color:rgb(73,90,104); color: white;border-radius: 15px}"
                "QPushButton:pressed{background-color:rgb(67, 203, 208);border-radius: 15px;"
                "border-style: inset; }");
}

void ChooseMode::SettingPage4Button()
{
    ui->page_4->setStyleSheet(
                "QPushButton{background-color:rgb(75,152,210);color: black;border-radius: 15px;"
                "border-style: outset;}"
                "QPushButton:hover{background-color:rgb(73,90,104); color: white;border-radius: 15px}"
                "QPushButton:pressed{background-color:rgb(67, 203, 208);border-radius: 15px;"
                "border-style: inset; }");
}
