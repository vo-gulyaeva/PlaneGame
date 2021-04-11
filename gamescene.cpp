#include "gamescene.h"
#include <QPalette>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene()
{
    Q_UNUSED(parent);
    QBrush brush(QPixmap(":/res/sky.png"));
    this->setBackgroundBrush(brush);
}

GameScene::~GameScene()
{

}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalCursorCoordinate(event->scenePos());
}