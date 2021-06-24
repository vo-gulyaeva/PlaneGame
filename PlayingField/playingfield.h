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
#include "precompiled.h"
#include "PlayingField/gamescene.h"
#include "PlayingField/mainplane.h"

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
    void slotEnemyOutsideField();
    void slotStop();
public:
    explicit PlayingField(QWidget *parent = 0);
    ~PlayingField();
public slots:
    void slotStart();
private:
    Ui::PlayingField *ui;
    GameScene *gameScene_;
    MainPlane *plane_;
    QTimer *timerEnemy_;
    int score_;
    int life_;
    QGraphicsSimpleTextItem *textGameOver;
};

#endif // PLAYINGFIELD_H
