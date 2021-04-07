#include "playingfield.h"
#include "ui_playingfield.h"
#include <QFile>

PlayingField::PlayingField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayingField)
{
    ui->setupUi(this);
    setFixedHeight(800);
    setFixedWidth(800);
    //фоновое изображение
    QBrush brush(QPixmap(":/res/sky.png"));
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);
    //установка стилей кнопок
    QFile btnSetting(":/res/styleButton.css");
    if(btnSetting.open(QFile::ReadOnly))
        ui->phbToMenu->setStyleSheet(btnSetting.readAll());
    btnSetting.exists();

    connect(ui->phbToMenu,SIGNAL(clicked()),this,SLOT(slotToMenu()));
}

PlayingField::~PlayingField()
{
    delete ui;
}

void PlayingField::slotToMenu()
{
    this->close();
    emit goToMenu();
}
