// 2021 год, игра - самолет
#include "PlayingField/spriteboom.h"

SpriteBoom::SpriteBoom(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    spriteImage_ = new QPixmap(":/res/PlayingField/boom.png");
    xPix_ = 0, yPix_ = 0;
    frame_ = 1;

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &SpriteBoom::slotTimer);
    timer_->start(70);
}

SpriteBoom::~SpriteBoom()
{
}

QRectF SpriteBoom::boundingRect() const
{
    return QRectF(-60.,-60.,120.,120.);
}

void SpriteBoom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(-60,-60, *spriteImage_,xPix_,yPix_,120,120);
}

void SpriteBoom::slotTimer()
{
    if(frame_ == 17)
        this->deleteLater();
    xPix_ = ((frame_ - 1)%4)*120;
    yPix_ = (frame_%5)==0? yPix_ + 120 : yPix_;
    frame_++;
    this->update(QRectF(-60.,-60.,120.,120.));
}
