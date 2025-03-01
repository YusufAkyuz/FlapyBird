#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird();
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool newGameOn);

    void incrementScore();
    int getScore() const;
    void setScore(int newScore);

signals:
private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();

    QTimer * timer;
    BirdItem *bird;

    bool gameOn;

    int score;
    int bestScore;

    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem * scoreTextItem;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
