// 2021 год, игра - самолет
#include "playingfield.h"
#include "ui_playingfield.h"
#include <QFile>
#include "gamescene.h"
#include "bullet.h"

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField)
{
    ui->setupUi(this);
    setFixedHeight(900);
    setFixedWidth(900);
    //фоновое изображение
    QBrush brush(QPixmap(":/res/sky.png"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
    ui->graphicsView->setPalette(palette);
    //установка стилей кнопок
    QFile btnSetting(":/res/styleButton.css");
    if(btnSetting.open(QFile::ReadOnly))
        ui->phbToMenu->setStyleSheet(btnSetting.readAll());
    btnSetting.exists();

    connect(ui->phbToMenu,SIGNAL(clicked()),this,SLOT(slotToMenu()));

    gameScene = new GameScene();
    gameScene->setSceneRect(0,0,969,801);

    ui->graphicsView->setScene(gameScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setMouseTracking(true);

    plane = new MainPlane();
    gameScene->addItem(plane);
    connect(gameScene, &GameScene::signalCursorCoordinate, this, &PlayingField::slotMovePlane);
    connect(gameScene, &GameScene::signalClick, this, &PlayingField::slotStartBullet);
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::slotToMenu()
{
    this->close();
    emit goToMenu();
}

void PlayingField::slotMovePlane(QPointF pos)
{
    plane->setPos(pos.x(),735.);
}

void PlayingField::slotStartBullet(QPointF pos)
{
    Bullet *bullet = new Bullet();
    bullet->setPos(pos.x(), 670.);
    gameScene->addItem(bullet);
}

void PlayingField::updatePosPlane()
{
    QPoint pos = this->mapFromGlobal(QCursor::pos());
    pos = ui->graphicsView->mapFromParent(pos);
    QPointF posScene = ui->graphicsView->mapToScene(pos);
    plane->setPos(posScene.x(), 735.);
}
