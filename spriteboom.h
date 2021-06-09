//////////////////////////////////////////////////////////////////////////
//
//! \file spriteboom.h
//! \brief Взрыв
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef SPRITEBOOM_H
#define SPRITEBOOM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QRectF>

class SpriteBoom : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit SpriteBoom(QObject *parent = 0);
    ~SpriteBoom();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimer();
private:
    QTimer *timer_;
    QPixmap *spriteImage_;
    int xPix_, yPix_;
    int frame_;
};

#endif // SPRITEBOOM_H
