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
    QBrush brush(QPixmap(":/res/plane.jpg"));
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

    playing_field = new PlayingField();
    connect(ui->phbPlay,SIGNAL(clicked()),this,SLOT(slotsShowField()));
    connect(playing_field,&PlayingField::goToMenu,this,&MainMenu::show);
    connect(ui->phbExit, &QPushButton::clicked,this, &MainMenu::close);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::slotsShowField()
{
    playing_field->show();
    this->close();
}
