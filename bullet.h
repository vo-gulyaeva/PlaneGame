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

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QTimer>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = 0);
    ~Bullet();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerMove();
private:
    QTimer *timer_move;
};

#endif // BULLET_H
