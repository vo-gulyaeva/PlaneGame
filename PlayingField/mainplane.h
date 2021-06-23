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
signals:
    void signalGameOver();      // Испускается при столкновении с самолетом противником
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerScrew();
    void slotSearchEnemy();
private:
    QTimer *timerScrew_;
    QTimer *timerSearchEnemy_;
    bool screw_;
};

#endif // MAINPLANE_H
