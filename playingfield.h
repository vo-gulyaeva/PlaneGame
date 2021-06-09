//////////////////////////////////////////////////////////////////////////
//
//! \file playfield.h
//! \brief Игровое поле, унаследовано от QWidget
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QWidget>
#include <QPointF>
#include "gamescene.h"
#include "mainplane.h"
#include <QVector>
#include "bullet.h"
#include <QTimer>

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
    void slotStartBullet(QPointF);
    void slotCreateEnemy();
    void slotDeleteEnemy(QGraphicsItem*);
    void slotMeetEnemy();
public:
    explicit PlayingField(QWidget *parent = 0);
    ~PlayingField();
    void updatePosPlane();

private:
    Ui::PlayingField *ui;
    GameScene *gameScene_;
    MainPlane *plane_;
    QTimer *timerEnemy_;
    int score_;
    int life_;
};

#endif // PLAYINGFIELD_H
