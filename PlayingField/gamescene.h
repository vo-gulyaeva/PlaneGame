//////////////////////////////////////////////////////////////////////////
//
//! \file gamescene.h
//! \brief Игровая сцена, унаследована от QGraphicsScene
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "precompiled.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
signals:
    void signalCursorCoordinate(QPointF pos);
    void signalClick(QPointF pos);
public:
    explicit GameScene(QObject *parent = 0);
    ~GameScene();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GAMESCENE_H
