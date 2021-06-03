// 2021 год, игра - самолет
#include "bullet.h"

Bullet::Bullet(QObject *parent) : QObject(parent), QGraphicsItem()
{
    timer_move = new QTimer(this);
    connect(timer_move, &QTimer::timeout, this, &Bullet::slotTimerMove);
    timer_move->start(100);
}

Bullet::~Bullet()
{

}

QRectF Bullet::boundingRect() const
{
    return QRectF(-5.,-5.,10.,10.);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rectangle(-5.,-5.,10.,10.);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawEllipse(rectangle);
}

void Bullet::slotTimerMove()
{
    QPointF pos = this->pos();
    if(pos.y() - 20. <= 0)
        this->deleteLater();

    this->setPos(pos.x(), pos.y() - 20.);
}
