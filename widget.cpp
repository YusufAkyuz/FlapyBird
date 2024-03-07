#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene=new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap(":/Images/backgroundGame.jpg"));
    scene->addItem(item);
    item->setPos(-item->boundingRect().center());

    ui->graphicsView->setScene(scene);
    scene->addBird();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startGameButton_clicked()
{
    scene->startGame();

}




