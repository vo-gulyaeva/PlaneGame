#ifndef MAINPLANE_H
#define MAINPLANE_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QTimer>

class MainPlane : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit MainPlane(QObject *parent = 0);
    ~MainPlane();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void slotTimerScrew();
private:
    QTimer *timer_screw;
    bool screw;
};

#endif // MAINPLANE_H
