#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent},gameOn(false),score(0),bestScore(0)
{
    setUpPillarTimer();
}

void Scene::addBird()
{

    bird=new BirdItem(QPixmap(":/Images/bird_red_up.png"));
    addItem(bird);
}

void Scene:: setUpPillarTimer(){

    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        PillarItem * pillarItem=new PillarItem();
        connect(pillarItem,&PillarItem::collideFail,[=](){
            timer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(pillarItem);
    });
}

void Scene::startGame()
{
    //Bird
    bird->startFlying();

    //Pillars
    if(!timer->isActive()){
        cleanPillars();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        timer->start(800);
    }

}


void Scene::freezeBirdAndPillarsInPlace()
{   //freeze bird
    bird->freezeInPlace();
    //freeze pillars
    QList<QGraphicsItem *>sceneItems=items();
    foreach (QGraphicsItem * item, sceneItems) {
        PillarItem * pillar=dynamic_cast<PillarItem*>(item);
        if(pillar){
            pillar->freezeInPlace();
        }

    }
}

int Scene::getScore() const
{
    return score;
}

void Scene::setScore(int newScore)
{
    score = newScore;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::incrementScore()
{
    score++;
    if(score>bestScore){
        bestScore=score;

        qDebug() <<"Score :" << score;
        qDebug() <<"Best Score :" <<bestScore;
    }
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/Images/gameOver.png"));
    addItem(gameOverPix);

    const QPointF offset(100, 120);

    gameOverPix->setPos(QPointF(0, 0) - offset);

    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = QString("<p> Score: %1 </p><p> Best Score: %2 </p>").arg(score).arg(bestScore);
    QFont mFont("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::red);
    addItem(scoreTextItem);

    const QPointF textItemPos = QPointF(0, 0) - QPointF(scoreTextItem->boundingRect().width() / 2, scoreTextItem->boundingRect().height() / 2);
    scoreTextItem->setPos(textItemPos);
}


void Scene::hideGameOverGraphics()
{
    if (gameOverPix && items().contains(gameOverPix)) {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if (scoreTextItem && items().contains(scoreTextItem)) {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}


void Scene::cleanPillars()
{
    QList<QGraphicsItem*>sceneItems=items();
    foreach (QGraphicsItem * item, sceneItems) {
        PillarItem *pillar=dynamic_cast<PillarItem*>(item);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }

    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){

        if(gameOn){
            bird->shootUp();
        }

    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);

}
