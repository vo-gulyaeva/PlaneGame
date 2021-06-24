// 2021 год, игра - самолет
#include "PlayingField/enemyplane.h"
#include <QList>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <math.h>

EnemyPlane::EnemyPlane(EnemyPlane::TypePlane typePlane, QObject *parent) :
    QObject(parent), QGraphicsItem(), typePlane_(typePlane), screw_(true)
{
    namePix_ = typePlane_==TypePlane::typeSimple ? ":/res/PlayingField/enemy1_" : ":/res/PlayingField/enemy2_";

    timerScrew_ = new QTimer(this);
    connect(timerScrew_, &QTimer::timeout, this, &EnemyPlane::slotTimerScrew);
    timerScrew_->start(100);

    timerMove_ = new QTimer(this);
    connect(timerMove_, &QTimer::timeout, this, &EnemyPlane::slotTimerMove);
    timerMove_->start(150);

    life_ = 1;

    side_ = DepartureSide(QRandomGenerator::global()->bounded(0, 2));
    course_ = generateCourse();
    this->setRotation(course_);
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
    //сдвиг
    QPointF pos = this->pos();
    double newX, newY;
    double alpha = (180 - course_)*M_PI/180;
    newX = pos.x() - 20*sin(alpha);
    newY = pos.y() - 20*cos(alpha);
    this->setPos(newX,newY);
    //проверка на выход за границы
    if(newX<0 || newX >width_ || newY<0 || newY>height_)
    {
        this->scene()->removeItem(this);
        emit signalGettingOutField();
        this->deleteLater();
        return;
    }
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

int EnemyPlane::generateCourse()
{
    switch (side_) {
    case DepartureSide::top:
        return QRandomGenerator::global()->bounded(-75, 75);
    case DepartureSide::left:
        return QRandomGenerator::global()->bounded(-75, -15);
    case DepartureSide::right:
        return QRandomGenerator::global()->bounded(15, 75);
    default:
        return 0;
    }
}

void EnemyPlane::setStartPos()
{
    if(!this->scene())
        return;
    width_ = this->scene()->width();
    height_ = this->scene()->height();
    double x = 0, y = 0;
    switch (side_) {
    case DepartureSide::top:
        if(course_ < 0)
            x = QRandomGenerator::global()->bounded(0, (int)width_/2);
        else
            x = QRandomGenerator::global()->bounded((int)width_/2, width_);
        break;
    case DepartureSide::left:
        y = QRandomGenerator::global()->bounded(0, (int)height_/2);
        break;
    case DepartureSide::right:
        x = width_;
        y = QRandomGenerator::global()->bounded(0, (int)height_/2);
        break;
    default:
        break;
    }
    this->setPos(x,y);
}
