#pragma once

#include <QTimer>
#include <QObject>

#include "dynamicObject.h"
#include "player.h"
#include "map.h"
#include "dot.h"

#include "blinky.h"
#include "pinky.h"

class Level : public QObject
{
    Q_OBJECT;
private:
    Player *player;
    QTimer ghostsPhase;
    QTimer *timer;
public:
    int lives = 2;
    Map map;
    Blinky *blinky;
    Pinky *pinky;
    Ghost::ghostsMode generalPhase;

    int points = 0;

    Level(QTimer *t);
    ~Level();
    Player& getPlayer() const { return *player; }

signals:
    void scoreDot(int points);
    void scoreGhost(int);
    void ghostModeChanged();
    void lifeDown(QString);

    void gameOver();
    void youWin();

public slots:
    void isIntersectReached();
    void goBack();
    void isDotEaten();
    void switchPhase();
    void playerDies();
    void ghostScored();

};