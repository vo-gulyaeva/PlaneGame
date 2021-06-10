//////////////////////////////////////////////////////////////////////////
//
//! \file mainplane.h
//! \brief Игровой самолет, унаследован от QGraphicsItem
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef MAINPLANE_H
#define MAINPLANE_H

#include "precompiled.h"

class MainPlane : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit MainPlane(QObject *parent = 0);
    ~MainPlane();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerScrew();
private:
    QTimer *timerScrew_;
    bool screw_;
};

#endif // MAINPLANE_H
