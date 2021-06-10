// 2021 год, игра - самолет
#include "PlayingField/bullet.h"
#include <QList>
#include <QPolygonF>
#include <QGraphicsScene>

Bullet::Bullet(QGraphicsItem *mainPlane, QObject *parent) :
    QObject(parent), QGraphicsItem(), mainPlane_(mainPlane)
{
    timerMove_ = new QTimer(this);
    connect(timerMove_, &QTimer::timeout, this, &Bullet::slotTimerMove);
    timerMove_->start(100);
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

    QList<QGraphicsItem*> foundItems = scene()->items(QPolygonF()<<mapToScene(0,0)
                                                     <<mapToScene(0,-1));
    for(auto item : foundItems)
    {
        if(item == this || item == mainPlane_)
            continue;

        emit signalFoundEnemy(item);
        this->deleteLater();
    }
}
