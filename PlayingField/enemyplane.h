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
    enum class DepartureSide
    {
        top,
        left,
        right
    };
public:
    EnemyPlane(EnemyPlane::TypePlane, QObject *parent = 0);
    ~EnemyPlane();
    void setLife(int);
    bool tookHit();         //Вызывается при попадании снаряда,
                            //Возвращает true - жив, false - убит
    int typePlane();
    void setStartPos();     //ВЫЗОВ ПОСЛЕ ДОБАВЛЕНИЯ НА СЦЕНУ!
signals:
    void signalGettingOutField();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int generateCourse();
private slots:
    void slotTimerScrew();
    void slotTimerMove();
private:
    EnemyPlane::TypePlane typePlane_;
    QString namePix_;
    bool screw_;
    QTimer *timerScrew_;
    QTimer *timerMove_;
    int life_;
    EnemyPlane::DepartureSide side_;
    int course_;
    int width_, height_;        //параметры сцены
};

#endif // ENEMYPLANE_H
