#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <QPushButton>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QList>
#include <QLabel>
#include <QMainWindow>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <sling.h>
#include <pig.h>
#include <barrier.h>
#include <yellowbird.h>
#include <blackbird.h>
#include <bluebird.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void deleteitem();
    void restartgame();
    void endgame();
    void playgame();
    void button();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<Pig *> PigList;
    QList<Barrier *> BarrierList;
    QList<Bird *> BirdList;
    QTimer timer;
    QLabel *Score;
    QPushButton *end, *restart;
    float piggy1,piggy2,piggy3;
    float bar1,bar2,bar3,bar4,bar5,bar6,bar7;
    int num[10]={0};
    Pig *pig1,*pig2,*pig3;
    Bird *birdie1,*birdie2,*birdie3,*birdie4;
    Barrier *barrier1,*barrier2,*barrier3,*barrier4,*barrier5,*barrier6,*barrier7;
    int birdplay=0;
    int play=0;
    int birdnum =4;
    int score=0;
    Sling *sling;
    int s=0;

    //int numberofenemy;
};

#endif // MAINWINDOW_H
