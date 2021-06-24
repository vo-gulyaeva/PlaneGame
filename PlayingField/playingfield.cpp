// 2021 год, игра - самолет
#include "PlayingField/playingfield.h"
#include "ui_playingfield.h"
#include <QFile>
#include "bullet.h"
#include "PlayingField/enemyplane.h"
#include <QRandomGenerator>
#include "PlayingField/spriteboom.h"
#include "PlayingField/bullet.h"

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField)
{
    ui->setupUi(this);
    setFixedHeight(900);
    setFixedWidth(900);
    //фоновое изображение
    QBrush brush(QPixmap(":/res/PlayingField/sky.png"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
    ui->graphicsView->setPalette(palette);
    //установка стилей кнопок
    QFile btnSetting(":/res/styleButton.css");
    if(btnSetting.open(QFile::ReadOnly))
    {
        QString styleButton = btnSetting.readAll();
        ui->phbToMenu->setStyleSheet(styleButton);
        ui->phbToStart->setStyleSheet(styleButton);
    }
    btnSetting.exists();

    connect(ui->phbToMenu,&QPushButton::clicked,this,&PlayingField::slotStop);
    connect(ui->phbToMenu,&QPushButton::clicked,this,&PlayingField::slotToMenu);
    connect(ui->phbToStart, &QPushButton::clicked,this,&PlayingField::slotStart);

    gameScene_ = new GameScene();
    gameScene_->setSceneRect(0,0,969,801);

    ui->graphicsView->setScene(gameScene_);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setMouseTracking(true);

    timerEnemy_ = new QTimer(this);
    connect(timerEnemy_, &QTimer::timeout, this, &PlayingField::slotCreateEnemy);

    plane_ = new MainPlane();
    gameScene_->addItem(plane_);
    connect(plane_, &MainPlane::signalGameOver, this, &PlayingField::slotStop);

    connect(gameScene_, &GameScene::signalCursorCoordinate, this, &PlayingField::slotMovePlane);

    textGameOver = new QGraphicsSimpleTextItem("Конец игры");
    QFont font("Times", 70, QFont::Cursive);
    textGameOver->setFont(font);
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::slotStart()
{
    ui->phbToStart->setEnabled(false);
    gameScene_->removeItem(textGameOver);

    life_ = 3;
    score_ = 0;
    ui->spinLife->setValue(life_);
    ui->spinScore->setValue(score_);

    connect(gameScene_, &GameScene::signalClick, this, &PlayingField::slotStartBullet);

    timerEnemy_->start(3000);
    slotCreateEnemy();
    QPoint pos = this->mapFromGlobal(QCursor::pos());
    pos = ui->graphicsView->mapFromParent(pos);
    QPointF posScene = ui->graphicsView->mapToScene(pos);
    plane_->setPos(posScene.x(), 735.);
}

void PlayingField::slotStop()
{
    life_ = 0;
    ui->spinLife->setValue(life_);
    gameScene_->addItem(textGameOver);
    textGameOver->setPos(gameScene_->width()/2 - 250, gameScene_->height()/2);

    timerEnemy_->stop();
    disconnect(gameScene_, &GameScene::signalClick, this, &PlayingField::slotStartBullet);
    ui->phbToStart->setEnabled(true);

    for(auto item : gameScene_->items())
        if(item!=plane_ && item!=textGameOver)
        {
            gameScene_->removeItem(item);
            delete item;
        }
}

void PlayingField::slotToMenu()
{
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

void PlayingField::slotCreateEnemy()
{
    int randNumber = QRandomGenerator::global()->bounded(1, 100);
    EnemyPlane::TypePlane typePlane = randNumber%15 == 0 ? EnemyPlane::TypePlane::typeAverage:
                                                           EnemyPlane::TypePlane::typeSimple;
    EnemyPlane *enemy = new EnemyPlane(typePlane);
    int life = QRandomGenerator::global()->bounded(1, 3);
    enemy->setLife(life);
    gameScene_->addItem(enemy);
    enemy->setStartPos();
    connect(enemy,&EnemyPlane::signalGettingOutField,this,&PlayingField::slotEnemyOutsideField);
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

void PlayingField::slotEnemyOutsideField()
{
    life_--;
    ui->spinLife->setValue(life_);
    if(life_ == 0)
        slotStop();
}
