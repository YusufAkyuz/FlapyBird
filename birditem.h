#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BirdItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    explicit BirdItem(QPixmap pixmap);

    qreal rotation() const;
    void setRotation(qreal newRotation);

    qreal y() const;
    void setY(qreal newY);

    void shootUp();
    void fallToGroundNecessary();

    void startFlying();

    void freezeInPlace();
signals:

public slots:
    void rotateTo(const qreal &end, const int& duration,const QEasingCurve&curve);
private:
    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    WingPosition wingPosition;
        bool wingDirection;

    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation *yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;


};

#endif // BIRDITEM_H
