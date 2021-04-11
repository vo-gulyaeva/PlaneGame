#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QWidget>
#include "gamescene.h"

namespace Ui {
class PlayingField;
}

class PlayingField : public QWidget
{
    Q_OBJECT
signals:
    void goToMenu();
private slots:
    void slotToMenu();
public:
    explicit PlayingField(QWidget *parent = 0);
    ~PlayingField();

private:
    Ui::PlayingField *ui;
    GameScene *gameScene;
};

#endif // PLAYINGFIELD_H
