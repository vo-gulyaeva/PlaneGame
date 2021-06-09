// 2021 год, игра - самолет
#include "playingfield.h"
#include "ui_playingfield.h"
#include <QFile>
#include "gamescene.h"
#include "bullet.h"
#include "enemyplane.h"
#include <QRandomGenerator>
#include "spriteboom.h"

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField)
{
    ui->setupUi(this);
    setFixedHeight(900);
    setFixedWidth(900);
    life_ = 3;
    score_ = 0;
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

    gameScene_ = new GameScene();
    gameScene_->setSceneRect(0,0,969,801);

    ui->graphicsView->setScene(gameScene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setMouseTracking(true);

    plane_ = new MainPlane();
    gameScene_->addItem(plane_);
    connect(gameScene_, &GameScene::signalCursorCoordinate, this, &PlayingField::slotMovePlane);
    connect(gameScene_, &GameScene::signalClick, this, &PlayingField::slotStartBullet);

    timerEnemy_ = new QTimer(this);
    connect(timerEnemy_, &QTimer::timeout, this, &PlayingField::slotCreateEnemy);
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::slotToMenu()
{
    timerEnemy_->stop();
    this->close();
    emit goToMenu();
}

void PlayingField::slotMovePlane(QPointF pos)
{
    plane_->setPos(pos.x(),735.);
}

void PlayingField::slotStartBullet(QPointF pos)
{
    Bullet *bullet = new Bullet(plane_);
    bullet->setPos(pos.x(), 670.);
    gameScene_->addItem(bullet);
    connect(bullet, &Bullet::signalFoundEnemy, this, &PlayingField::slotDeleteEnemy);
}

void PlayingField::updatePosPlane()
{
    timerEnemy_->start(3000);
    slotCreateEnemy();
    QPoint pos = this->mapFromGlobal(QCursor::pos());
    pos = ui->graphicsView->mapFromParent(pos);
    QPointF posScene = ui->graphicsView->mapToScene(pos);
    plane_->setPos(posScene.x(), 735.);
}

void PlayingField::slotCreateEnemy()
{
    int xPoint = QRandomGenerator::global()->bounded(60, 900);
    int randNumber = QRandomGenerator::global()->bounded(1, 100);
    EnemyPlane::TypePlane typePlane = randNumber%15 == 0 ? EnemyPlane::TypePlane::typeAverage:
                                                           EnemyPlane::TypePlane::typeSimple;
    EnemyPlane *enemy = new EnemyPlane(QPointF(xPoint,-100),typePlane, plane_);
    int life = QRandomGenerator::global()->bounded(1, 3);
    enemy->setLife(life);
    gameScene_->addItem(enemy);
    connect(enemy, &EnemyPlane::signalMeetMainPlane, this, &PlayingField::slotMeetEnemy);
}

void PlayingField::slotDeleteEnemy(QGraphicsItem *item)
{
    EnemyPlane *enemy = dynamic_cast<EnemyPlane *>(item);
    if(!enemy)
        return;

    int type = enemy->typePlane();
    if(!enemy->tookHit())    //если удар оказался роковым
    {
        //Взрыв
        QPointF pos = enemy->pos();
        SpriteBoom *spriteBoom = new SpriteBoom();
        spriteBoom->setPos(pos);
        gameScene_->addItem(spriteBoom);
        score_ = type == 0? score_ + 5: score_ + 10;
        ui->spinScore->setValue(score_);
    }
}

void PlayingField::slotMeetEnemy()
{
    life_--;
    ui->spinLife->setValue(life_);
    //ОБРАБОТАТЬ КОНЕЦ ЖИЗНЕЙ
}
