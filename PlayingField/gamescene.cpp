// 2021 год, игра - самолет
#include "PlayingField/gamescene.h"
#include <QPalette>
#include "PlayingField/enemyplane.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene()
{
    Q_UNUSED(parent);
    QBrush brush(QPixmap(":/res/PlayingField/sky.png"));
    this->setBackgroundBrush(brush);

    timerClear_ = new QTimer(this);
    connect(timerClear_, &QTimer::timeout, this, &GameScene::slotClear);
    timerClear_->start(1000);
}

GameScene::~GameScene()
{

}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalCursorCoordinate(event->scenePos());
}

 void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
 {
     emit signalClick(mouseEvent->scenePos());
 }

 void GameScene::slotClear()
 {
     int width = this->width();
     int height = this->height();
     for(auto item : items())
     {
         EnemyPlane *enemy = dynamic_cast<EnemyPlane *>(item);
         if(!enemy)
             continue;
         QPointF pos = enemy->pos();
         if(pos.x()<0 || pos.x()>width || pos.y()<0 || pos.y()>height)
         {
             removeItem(item);
             delete item;
             emit signalEnemyAbaftField();
             return;
         }
     }
 }
