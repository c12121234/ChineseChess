# ChineseChess

## 概述

使用Qt開發的象棋對戰，有本地端對戰和網路對戰。

連線方式使用TCP，嘗試使用QGraphicsView和QGraphicsScene來開發

熟悉Qt event filter、event的收發方式。


## 操作

滑鼠點擊棋子，並移動到目標地點，若違反規則的操作則會提示警示音。

## 程式截圖

主menu

![img](https://github.com/c12121234/WorkingExperence/blob/master/%E9%97%9C%E6%96%BCQt/pic/ChineseChess_1.png)

網路對戰client端

![img](https://github.com/c12121234/WorkingExperence/blob/master/%E9%97%9C%E6%96%BCQt/pic/ChineseChess_2.png)

網路對戰client端-選擇連接port及IP

![img](https://github.com/c12121234/WorkingExperence/blob/master/%E9%97%9C%E6%96%BCQt/pic/ChineseChess_3.png)

網路對戰server端

![img](https://github.com/c12121234/WorkingExperence/blob/master/%E9%97%9C%E6%96%BCQt/pic/ChineseChess_4.png)

遊戲畫面

![img](https://github.com/c12121234/WorkingExperence/blob/master/%E9%97%9C%E6%96%BCQt/pic/ChineseChess_5.png)

## 可改良部分

棋類的設計應該使用`flyweight`來減少多餘的記憶體耗損

如果要設計悔棋系統的話，要參考`command`的設計方式

目前的設計只有儲存玩家操作的那步

要把操作的多個座標用個container儲存
