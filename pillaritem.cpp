#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include<QGraphicsScene>
#include <birditem.h>
#include "scene.h"
PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/Images/pillar.png"))),
    pastBird(false)
{
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    topPillar->setPos(QPointF(0,0)-QPointF(topPillar->boundingRect().width()/2,
                                              topPillar->boundingRect().height()+80));

    bottomPillar->setPos(QPointF(0,0)+QPointF(-bottomPillar->boundingRect().width()/2,60));

    yPosition=QRandomGenerator::global()->bounded(150);
    int xRandomizer=QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0)+QPoint(260+xRandomizer,yPosition));


    xAnimation =new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260+xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    xAnimation->start();

    connect(xAnimation,&QPropertyAnimation::finished,[=](){

        scene()->removeItem(this);
        delete this;

    });

}

PillarItem::~PillarItem()
{

    delete topPillar;
    delete bottomPillar;
}



qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();

}

void PillarItem::setX(qreal x){

    m_x=x;

    if(x<0 && !pastBird ){
        pastBird=true;
        QGraphicsScene * mScene=scene();
        Scene * myScene =dynamic_cast<Scene * >(mScene);

        if(myScene){
            myScene->incrementScore();
        }

    }

    if(collidesWithBird()){
        emit collideFail();

    }
    setPos(QPointF(0,0)+QPointF(x,yPosition));
}

bool PillarItem::collidesWithBird()
{

    QList<QGraphicsItem*> collidingItems= topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach (QGraphicsItem * item, collidingItems) {
        BirdItem * birdItem=dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;

}



