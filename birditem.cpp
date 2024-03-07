#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>
BirdItem::BirdItem(QPixmap pixmap):
    wingPosition(WingPosition::Up),
    wingDirection(0)

{
    setPixmap(pixmap);


    QTimer *birdWingsTimer = new QTimer(this);

    connect(birdWingsTimer, &QTimer::timeout, this, [=]() {
        updatePixmap();
    });


    birdWingsTimer->start(80);
    groundPosition=scenePos().y()+290;

    yAnimation=new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);
    rotationAnimation=new QPropertyAnimation(this,"rotation",this);
}



void BirdItem::updatePixmap() {
    QString imagePath;

    switch (wingPosition) {
    case WingPosition::Middle:
        if (wingDirection) {
            // up
            imagePath = ":/Images/bird_red_up.png";
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        } else {
            // down
            imagePath = ":/Images/bird_red_down.png";
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }
        break;
    case WingPosition::Up:
        // middle
        imagePath = ":/Images/bird_red_middle.png";
        wingPosition = WingPosition::Middle;
        break;
    case WingPosition::Down:
        // middle
        imagePath = ":/Images/bird_red_middle.png";
        wingPosition = WingPosition::Middle;
        break;
    }

    setPixmap(QPixmap(imagePath));
}


qreal BirdItem::rotation() const
{
    return m_rotation;
}



void BirdItem::setRotation(qreal newRotation)
{
    if (m_rotation != newRotation) {
        m_rotation = newRotation;

        // Yeni döndürme matrisini oluştur
        QTransform transform;
        transform.rotate(m_rotation);

        setTransform(transform);
    }
}


qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::setY(qreal newY)
{
    moveBy(0,newY-m_y);
    m_y = newY;
}

void BirdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();
    //y() QGraphicsItem sınıfın y koordinatını döndüren fonksiyondur.
    qreal curPosY=y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY-scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fallToGroundNecessary();
    });
    yAnimation->start();
    rotateTo(-20,200,QEasingCurve::OutCubic);

}


void BirdItem::fallToGroundNecessary()
{
    if(y()<groundPosition){

        rotationAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);
        yAnimation->start();
        rotateTo(90,1100,QEasingCurve::InCubic);
    }
}



void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

void BirdItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}
