#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
signals:
    void signalCursorCoordinate(QPointF pos);
public:
    explicit GameScene(QObject *parent = 0);
    ~GameScene();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GAMESCENE_H
