// 2021 год, игра - самолет
#include "mainplane.h"

MainPlane::MainPlane(QObject *parent) : QObject(parent), QGraphicsItem(),
    screw_(true)
{
    timerScrew_ = new QTimer(this);

    connect(timerScrew_,&QTimer::timeout,this,&MainPlane::slotTimerScrew);
    timerScrew_->start(100);
}

MainPlane::~MainPlane()
{
}

QRectF MainPlane::boundingRect() const
{
    return QRectF(-60.,-60.,120.,120.);
}

void MainPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF target(-60.,-60.,120.,120.);
    QRectF source(0.0, 0.0, 120.0, 120.0);
    QString nameFile = screw_ ? ":/res/plane1.png" : ":/res/plane2.png";
    QPixmap pixmap(nameFile);
    painter->drawPixmap(target, pixmap, source);
}

void MainPlane::slotTimerScrew()
{
    screw_ = !screw_;
    this->update(QRectF(-60.,-60.,120.,120.));
}
