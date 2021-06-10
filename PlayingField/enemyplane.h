//////////////////////////////////////////////////////////////////////////
//
//! \file enemylane.h
//! \brief  Самолет противника, унаследован от QGraphicsItem
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "precompiled.h"

class EnemyPlane : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum class TypePlane
    {
        typeSimple,
        typeAverage
    };
public:
    EnemyPlane(QPointF, EnemyPlane::TypePlane, QGraphicsItem *, QObject *parent = 0);
    ~EnemyPlane();
    void setLife(int);
    bool tookHit();         //Вызывается при попадании снаряда,
                            //Возвращает true - жив, false - убит
    int typePlane();
signals:
    void signalMeetMainPlane();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerScrew();
    void slotTimerMove();
private:
    EnemyPlane::TypePlane typePlane_;
    QString namePix_;
    bool screw_;
    QTimer *timerScrew_;
    QTimer *timerMove_;
    QGraphicsItem *mainPlane_;
    int life_;
};

#endif // ENEMYPLANE_H
