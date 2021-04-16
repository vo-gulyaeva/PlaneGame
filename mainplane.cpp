#include "mainplane.h"

MainPlane::MainPlane(QObject *parent) : QObject(parent), QGraphicsItem(),
    screw(true)
{
    timer_screw = new QTimer(this);

    connect(timer_screw,&QTimer::timeout,this,&MainPlane::slotTimerScrew);
    timer_screw->start(100);
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
    QString nameFile = screw ? ":/res/plane1.png" : ":/res/plane2.png";
    QPixmap pixmap(nameFile);
    painter->drawPixmap(target, pixmap, source);
}

void MainPlane::slotTimerScrew()
{
    screw = !screw;
    this->update(QRectF(-60.,-60.,120.,120.));
}
