#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QWidget>
#include <QPointF>
#include "gamescene.h"
#include "mainplane.h"

namespace Ui {
class PlayingField;
}

class PlayingField : public QWidget
{
    Q_OBJECT
signals:
    void goToMenu();
private slots:
    void slotToMenu();
    void slotMovePlane(QPointF);
public:
    explicit PlayingField(QWidget *parent = 0);
    ~PlayingField();

private:
    Ui::PlayingField *ui;
    GameScene *gameScene;
    MainPlane *plane;
};

#endif // PLAYINGFIELD_H
