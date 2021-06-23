// 2021 год, игра - самолет
#include "PlayingField/mainplane.h"
#include "PlayingField/enemyplane.h"

MainPlane::MainPlane(QObject *parent) : QObject(parent), QGraphicsItem(),
    screw_(true)
{
    timerScrew_ = new QTimer(this);
    connect(timerScrew_,&QTimer::timeout,this,&MainPlane::slotTimerScrew);
    timerScrew_->start(100);

    timerSearchEnemy_ = new QTimer(this);
    connect(timerSearchEnemy_,&QTimer::timeout,this,&MainPlane::slotSearchEnemy);
    timerSearchEnemy_->start(300);
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
    QString nameFile = screw_ ? ":/res/PlayingField/plane1.png" : ":/res/PlayingField/plane2.png";
    QPixmap pixmap(nameFile);
    painter->drawPixmap(target, pixmap, source);
}

void MainPlane::slotTimerScrew()
{
    screw_ = !screw_;
    this->update(QRectF(-60.,-60.,120.,120.));
}

void MainPlane::slotSearchEnemy()
{
    QList<QGraphicsItem*> foundItems = scene()->items(QPolygonF()<<mapToScene(0,0)
                                                     <<mapToScene(0,-60));
    for(auto item : foundItems)
    {
        EnemyPlane *enemy = dynamic_cast<EnemyPlane *>(item);
        if(!enemy || item == this)
            continue;
        this->scene()->removeItem(item);
        delete item;
        emit signalGameOver();
        return;
    }
}
