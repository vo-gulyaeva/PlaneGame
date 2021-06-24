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
