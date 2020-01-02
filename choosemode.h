#ifndef CHOOSEMODE_H
#define CHOOSEMODE_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class ChooseMode;
}
enum PageNum
{
    TOPMENU = 0,
    CLIENT_SERVER_SELECTPAGE = 1,
    CLIENT_PAGE = 2,
    SERVER_PAGE = 3
};

enum SIDE
{
    CLIENT = 0,
    SERVER = 1
};

class NetGameWindow;
class ChooseMode : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseMode(QWidget *parent = nullptr);
    ~ChooseMode();
    int m_nChoose;
private slots:
    void on_btnLocalGame_clicked();
    void on_btnQuit_clicked();
    void on_btnNetworkGame_clicked();
    void ClearLocalGame();
    void ClearNetworkGame();
    void ShowNetGameView();
    void on_btnCancelConnect_clicked();
    void on_btnEnterConnect_clicked();
    void on_btnClientEnterConnect_clicked();
    void on_btnClientCancel_clicked();
    void on_btnServerEnter_clicked();
    void on_btnServerCancel_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ChooseMode *ui;
    MainWindow* m_pLocalGame;
    NetGameWindow* m_pNetworkGame;
};

#endif // CHOOSEMODE_H
