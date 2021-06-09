//////////////////////////////////////////////////////////////////////////
//
//! \file mainmenu.h
//! \brief Главное меню
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "playingfield.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT
private slots:
    void slotsShowField();
public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private:
    Ui::MainMenu *ui;
    PlayingField *playingField_;
};

#endif // MAINMENU_H
