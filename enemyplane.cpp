// 2021 год, игра - самолет
#include "enemyplane.h"
#include <QList>
#include <QPolygonF>
#include <QGraphicsScene>

EnemyPlane::EnemyPlane(QPointF pos, EnemyPlane::TypePlane typePlane,
                       QGraphicsItem *mainPlane,QObject *parent) :
    QObject(parent), QGraphicsItem(), typePlane_(typePlane),
    screw_(true), mainPlane_(mainPlane)
{
    this->setPos(pos);
    namePix_ = typePlane_==TypePlane::typeSimple ? ":/res/enemy1_" : ":/res/enemy2_";

    timerScrew_ = new QTimer(this);
    connect(timerScrew_, &QTimer::timeout, this, &EnemyPlane::slotTimerScrew);
    timerScrew_->start(100);

    timerMove_ = new QTimer(this);
    connect(timerMove_, &QTimer::timeout, this, &EnemyPlane::slotTimerMove);
    timerMove_->start(100);

    life_ = 1;
}

EnemyPlane::~EnemyPlane()
{
}

QRectF EnemyPlane::boundingRect() const
{
    return QRectF(-60.,-60.,120.,120.);
}

void EnemyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF target(-60.,-60.,120.,120.);
    QRectF source(0.0, 0.0, 120.0, 120.0);
    QString namePix = screw_ ? namePix_ + "1.png" : namePix_ + "2.png";
    QPixmap pixmap(namePix);
    painter->drawPixmap(target, pixmap, source);
}

void EnemyPlane::slotTimerScrew()
{
    screw_ = !screw_;
    this->update(QRectF(-60.,-60.,120.,120.));
}

void EnemyPlane::slotTimerMove()
{
    QList<QGraphicsItem*> foundItems = scene()->items(QPolygonF()<<mapToScene(0,0)
                                                     <<mapToScene(0,60));
    for(auto item : foundItems)
        if(item == mainPlane_)
        {
            emit signalMeetMainPlane();
            this->deleteLater();
        }

    QPointF pos = this->pos();
    if(pos.y()+10 > 900)
    {
        emit signalMeetMainPlane();
        this->deleteLater();
    }

    this->setPos(pos.x(),pos.y()+10);
}

void EnemyPlane::setLife(int life)
{
    life_ = life;
    if(typePlane_ == TypePlane::typeAverage)
        life_ += 2;
}

bool EnemyPlane::tookHit()
{
    life_--;
    if(life_ == 0)
    {
        this->deleteLater();
        return false;
    }
    return true;
}

int EnemyPlane::typePlane()
{
    return (int)typePlane_;
}
