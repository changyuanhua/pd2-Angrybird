#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    ui->graphicsView->setBackgroundBrush(QPixmap(":/background").scaled(960, 540));
    qApp->installEventFilter(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,960,540);
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    Score= new QLabel(this);
    Score->setStyleSheet("color:blue;font:bold 30px;background-color:transparent");
    Score->setText("Score:0");
    Score->setGeometry(10,0,200,60);
    Score->show();
    playgame();
    button();
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(deleteitem()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}
void MainWindow::playgame()
{
    // Create ground (You can edit here)
    itemList.push_back(new Land(16.0f,1.5f,32.0f,3.0f,QPixmap(":/ground.png").scaled(960,90),world,scene));
    // create sling
    sling = new Sling(3.0, 4.5, 2.0, 2.0, QPixmap(":/sling").scaled(50, 105), world, scene);
    itemList.push_back(sling);
    // Create bird (You can edit here)
    birdie1 = new bluebird(4.0f,4.5f,1.0f,&timer,QPixmap(":/bluebird.png").scaled(60,60),world,scene);
    BirdList.push_back(birdie1);
    birdie2 = new yellowbird(5.0f,4.5f,1.0f,&timer,QPixmap(":/yellowbird.png").scaled(60,60),world,scene);
    BirdList.push_back(birdie2);
    birdie3 = new blackbird(6.0f,4.5f,1.0f,&timer,QPixmap(":/blackbird.png").scaled(60,60),world,scene);
    BirdList.push_back(birdie3);  
    birdie4 = new Bird(3.0f,8.5f,1.0f,&timer,QPixmap(":/redbird.png").scaled(60,60),world,scene);
    BirdList.push_back(birdie4);
    // creat barrier
    barrier1 = new Barrier(20.0f,5.5f,1.0f,4.0f,&timer,QPixmap(":/verticalwood.png").scaled(30,120),world,scene);
    BarrierList.push_back(barrier1);
    barrier2 = new Barrier(24.0f,5.5f,1.0f,4.0f,&timer,QPixmap(":/verticalwood.png").scaled(30,120),world,scene);
    BarrierList.push_back(barrier2);
    barrier3 = new Barrier(22.0f,8.0f,4.0f,1.0f,&timer,QPixmap(":/horizontalwood.png").scaled(120,30),world,scene);
    BarrierList.push_back(barrier3);
    barrier4 = new Barrier(18.0f,3.0f,3.0f,3.0f,&timer,QPixmap(":/squarewood.png").scaled(90,90),world,scene);
    BarrierList.push_back(barrier4);
    barrier5 = new Barrier(26.0f,3.0f,3.0f,3.0f,&timer,QPixmap(":/squarewood.png").scaled(90,90),world,scene);
    BarrierList.push_back(barrier5);
    barrier6 = new Barrier(22.0f,5.5f,1.0f,4.0f,&timer,QPixmap(":/verticalwood.png").scaled(30,120),world,scene);
    BarrierList.push_back(barrier6);
    barrier7 = new Barrier(28.0f,5.5f,1.0f,4.0f,&timer,QPixmap(":/verticalwood.png").scaled(30,120),world,scene);
    BarrierList.push_back(barrier7);
    // create pig
    pig1 = new Pig(18.0f,5.5f,1.0f,&timer,QPixmap(":/pig.png").scaled(60,60),world,scene);
    PigList.push_back(pig1);
    pig2 = new Pig(26.0f,5.5f,1.0f,&timer,QPixmap(":/pig.png").scaled(60,60),world,scene);
    PigList.push_back(pig2);
    pig3 = new Pig(16.0f,4.5f,1.0f,&timer,QPixmap(":/pig.png").scaled(60,60),world,scene);
    PigList.push_back(pig3);   
}
void MainWindow::button()
{
    // create end
    end = new QPushButton;
    end->setStyleSheet("background-image: url(:/end.png);");
    end->setGeometry(850, 10, 80, 80);
    scene->addWidget(end);
    //create restart
    restart = new QPushButton;
    restart->setStyleSheet("background-image: url(:/restart.png);");
    restart->setGeometry(770, 10, 80, 80);
    scene->addWidget(restart);
    connect(end,SIGNAL(clicked(bool)), this, SLOT(endgame()));
    connect(restart,SIGNAL(clicked(bool)), this, SLOT(restartgame()));
}

void MainWindow::deleteitem()
{
    if (num[0]==0)
    {
        piggy1=pig1->linearvelocity().x + pig1->linearvelocity().y;
        if (piggy1>=1.8)
        {
            delete pig1;
            num[0]=1;
            score=score+2000;
        }
    }
    if (num[1]==0)
    {
        piggy2=pig2->linearvelocity().x +pig2->linearvelocity().y;
        if (piggy2>=1.8)
        {
            delete pig2;
            num[1]=1;
            score=score+2000;
        }
    }
    if (num[2]==0)
    {
        piggy3=pig3->linearvelocity().x + pig3->linearvelocity().y;
        if (piggy3>=1.8)
        {
            delete pig3;
            num[2]=1;
            score=score+2000;
        }
    }
    if (num[3]==0)
    {
        bar1=barrier1->linearvelocity().x + barrier1->linearvelocity().y;
        if (bar1>=2.3)
        {
            delete barrier1;
            num[3]=1;
            score=score+500;
        }
    }
    if (num[4]==0)
    {
        bar2=barrier2->linearvelocity().x + barrier2->linearvelocity().y;
        if (bar2>=2.3)
        {
            delete barrier2;
            num[4]=1;
            score=score+500;
        }
    }
    if (num[5]==0)
    {
        bar3=barrier3->linearvelocity().x + barrier3->linearvelocity().y;
        if (bar3>=2.3)
        {
            delete barrier3;
            num[5]=1;
            score=score+500;
        }
    }
    if (num[6]==0)
    {
        bar4=barrier4->linearvelocity().x + barrier4->linearvelocity().y;
        if (bar4>=2.3)
        {
            delete barrier4;
            num[6]=1;
            score=score+500;
        }
    }
    if (num[7]==0)
    {
        bar5=barrier5->linearvelocity().x + barrier5->linearvelocity().y;
        if (bar5>=2.3)
        {
            delete barrier5;
            num[7]=1;
            score=score+500;
        }
    }
    if (num[8]==0)
    {
        bar6=barrier6->linearvelocity().x + barrier6->linearvelocity().y;
        if (bar6>=2.3)
        {
            delete barrier6;
            num[8]=1;
            score=score+500;
        }
    }
    if (num[9]==0)
    {
        bar7=barrier7->linearvelocity().x + barrier7->linearvelocity().y;
        if (bar7>=2.3)
        {
            delete barrier7;
            num[9]=1;
            score=score+500;
        }
    }
    Score->setText("SCORE :  " + QString::number(score));
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouse;
    Bird *birdie;
    QKeyEvent* key;
    if (event->type()==QEvent::KeyPress)
    {
        key=static_cast<QKeyEvent *>(event);
        if (key->key()==Qt::Key_S)
        {
            static_cast<Bird *>(BirdList.last())->special();
            return true;
        }
    }
    if(birdnum>=1)
    {
        // Hint: Notice the Number of every event!
        if(event->type()==QEvent::MouseButtonPress || event->type()==QEvent::MouseMove || event->type()==QEvent::MouseButtonRelease)
        {
            mouse = static_cast<QMouseEvent*>(event);
            birdie = static_cast<Bird*>(BirdList.last());
        }
        if(mouse->pos().rx()<=120 && mouse->pos().ry()<=400 && mouse->pos().ry()>=300)
        {
            if(event->type() == QEvent::MouseButtonPress)
            {
                //TODO : add your code here
                //std::cout << "Press !" << std::endl ;                
                birdie->setsleep(false);
                if(birdplay==0&&play==1)
                {
                    BirdList.pop_back();
                    birdie->deleteLater();
                }
                s=0;

                return true;
            }
            if(event->type() == QEvent::MouseMove)
            {
                // TODO : add your code here
                //std::cout << "Move !" << std::endl ;

                if (birdplay==1)
                {
                    birdie->setsleep(false);
                    birdie->setposition(mouse->pos().rx(),mouse->pos().ry());
                }
                s=0;
                return true;
            }
            if(event->type() == QEvent::MouseButtonRelease)
            {
                // TODO : add your code here
                //std::cout << "Release !" << std::endl ;
                birdplay=(birdplay==0)?1:0;
                play=1;              
                if (birdplay==1)
                {
                     birdie->setposition(120,350);
                     birdie->setsleep(false);
                }
                else
                {
                     birdie->setsleep(true);
                     birdie->setposition(120,350);
                     birdie->setLinearVelocity(mouse->pos().rx(),mouse->pos().ry());
                     birdnum=birdnum-1;
                     s=1;
                }
                return true;
            }
        }
    }
    return false;
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::restartgame()
{
        timer.stop();   
        birdnum=4;
        birdplay=0;
        play=0;
        score=0;
        int i;
        for(i=0;i<=9;i++)
        {
            if(num[i]==0)
            {
                switch (i)
                {
                case 0:
                    delete pig1;
                    break;
                case 1:
                    delete pig2;
                    break;
                case 2:
                    delete pig3;
                    break;
                case 3:
                    delete barrier1;
                    break;
                case 4:
                    delete barrier2;
                    break;
                case 5:
                    delete barrier3;
                    break;
                case 6:
                    delete barrier4;
                    break;
                case 7:
                    delete barrier5;
                    break;
                case 8:
                    delete barrier6;
                    break;
                case 9:
                    delete barrier7;
                    break;
                }
            }
            if(num[i]==1)
            {
                num[i]=0;
            }
        }
        for(i=0;i<PigList.size();i++)
        {
            if( PigList[i]!=NULL)
            {
                PigList[i]=NULL;              
            }
        }
        for(i=0;i<BarrierList.size();i++)
        {
            if( BarrierList[i]!=NULL)
            {               
                BarrierList[i]=NULL;
            }
        }
        for(i=0;i<BirdList.size();i++)
        {
            if(BirdList[i]!=NULL)
            {
                delete BirdList[i];
                BirdList[i]=NULL;
            }
        }
        PigList.clear();
        BarrierList.clear();
        BirdList.clear();
        playgame();
        button();
        timer.start(100/6);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}
void MainWindow::endgame()
{
    emit quitGame();
    exit(0);
}
void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

