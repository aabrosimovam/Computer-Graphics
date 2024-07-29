#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,500,500);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(scene);
    obj = new arrow();
    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(Draw()));
    animationTimer->start(10);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Draw()
{
    scene->clear();
    for(int i =0;i<6;i++)
    {
        QLineF temp = obj->getLine(i);
        scene->addLine( temp.x1(), temp.y1(), temp.x2(), temp.y2());
    }
    obj->updateLines();

}
