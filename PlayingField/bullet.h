//////////////////////////////////////////////////////////////////////////
//
//! \file bullet.h
//! \brief Снаряд игрового самолета
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef BULLET_H
#define BULLET_H

#include "precompiled.h"

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Bullet(QGraphicsItem*,QObject *parent = 0);
    ~Bullet();
signals:
    void signalFoundEnemy(QGraphicsItem*);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerMove();
private:
    QTimer *timerMove_;
    QGraphicsItem *mainPlane_;
};

#endif // BULLET_H
