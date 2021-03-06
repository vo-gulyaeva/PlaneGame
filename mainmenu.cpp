// 2021 год, игра - самолет
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QFile>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setFixedHeight(800);
    setFixedWidth(800);
    //фоновое изображение
    QBrush brush(QPixmap(":/res/mainmenu.jpg"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
    //установка стилей кнопок
    QFile file(":/res/styleButton.css");
    if(file.open(QFile::ReadOnly))
    {
        QString settings = file.readAll();
        ui->phbPlay->setStyleSheet(settings);
        ui->phbRecords->setStyleSheet(settings);
        ui->phbSettings->setStyleSheet(settings);
        ui->phbExit->setStyleSheet(settings);
    }
    file.exists();

    playingField_ = new PlayingField();
    connect(ui->phbPlay,SIGNAL(clicked()),this,SLOT(slotsShowField()));
    connect(playingField_,&PlayingField::goToMenu,this,&MainMenu::show);
    connect(ui->phbExit, &QPushButton::clicked,this, &MainMenu::close);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::slotsShowField()
{
    playingField_->show();
    playingField_->slotStart();
    this->close();
}
