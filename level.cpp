#include "level.h"

Level::Level(QTimer *t)
{
    timer = t;
    player = new Player(timer);
    blinky = new Blinky(&map, player);
    pinky = new Pinky(&map, player);

    connect(timer, SIGNAL(timeout()), this, SLOT(isIntersectReached()));
    connect(timer, SIGNAL(timeout()), this, SLOT(isDotEaten()));

    connect(timer, SIGNAL(timeout()), blinky, SLOT(move()));
    connect(timer, SIGNAL(timeout()), blinky, SLOT(controlDir()));
    connect(blinky, SIGNAL(playerCaught()), this, SLOT(playerDies()));
    connect(blinky, SIGNAL(ghostEaten()), this, SLOT(ghostScored()));

    connect(timer, SIGNAL(timeout()), pinky, SLOT(move()));
    connect(timer, SIGNAL(timeout()), pinky, SLOT(controlDir()));
    connect(pinky, SIGNAL(playerCaught()), this, SLOT(playerDies()));
    connect(pinky, SIGNAL(ghostEaten()), this, SLOT(ghostScored()));

    ghostsPhase.start(7000);

    connect(&ghostsPhase, SIGNAL(timeout()), this, SLOT(switchPhase()));

    generalPhase = Ghost::ghostsMode::scatter;

    connect(this, SIGNAL(ghostModeChanged()), blinky, SLOT(controlModes()));
    connect(this, SIGNAL(ghostModeChanged()), pinky, SLOT(controlModes()));
}

Level::~Level()
{
    delete player;
    delete blinky;
    delete pinky;
}

void Level::isIntersectReached()
{
    if (player->x()%20 == 0 && player->y()%20 == 0) {
        switch (player->d()) {
        case DynamicObject::Up:
            if ((map.grid(player->x() / 20 ,player->y() / 20 - 1)) == Map::wall) {
                player->setVel(Player::stop);
            }
            break;
        case DynamicObject::Down:
            if ((map.grid(player->x() / 20 ,player->y() / 20 + 1)) == Map::wall) {
                player->setVel(Player::stop);
            }
            break;
        case DynamicObject::Left:
            if ((map.grid(player->x() / 20 - 1,player->y() / 20)) == Map::wall) {
                player->setVel(Player::stop);
            }
            break;
        case DynamicObject::Right:
            if ((map.grid(player->x() / 20 + 1,player->y() / 20)) == Map::wall) {
                player->setVel(Player::stop);
            }
            break;
        }

        switch (player->nextDir) {
        case DynamicObject::Up:
            if ((map.grid(player->x() / 20 ,player->y() / 20 - 1)) >= Map::aisle) {
                player->setDir(DynamicObject::Up);
                player->setVel(Player::normalSpeed);
            }
            break;
        case DynamicObject::Down:
            if ((map.grid(player->x() / 20 ,player->y() / 20 + 1)) >= Map::aisle) {
                player->setDir(DynamicObject::Down);
                player->setVel(Player::normalSpeed);
            }
            break;
        case DynamicObject::Left:
            if ((map.grid(player->x() / 20 - 1,player->y() / 20)) >= Map::aisle) {
                player->setDir(DynamicObject::Left);
                player->setVel(Player::normalSpeed);
            }
            break;
        case DynamicObject::Right:
            if ((map.grid(player->x() / 20 + 1,player->y() / 20)) >= Map::aisle) {
                player->setDir(DynamicObject::Right);
                player->setVel(Player::normalSpeed);
            }
            break;
        }  
    }
}

void Level::goBack()
{
    player->setDir((DynamicObject::Direction)((player->d() + 2) % 4));
}

void Level::isDotEaten()
{
    if (player->x()%20 == 0 && player->y()%20 == 0) {
        switch (map.grid(player->x() / 20, player->y() / 20)) {
        case Map::aisle:
            map.removeDot(player->x() / 20, player->y() / 20);
            points += 10;
            emit scoreDot(points);
            break;
        case Map::bigDotSpawn:
            map.removeDot(player->x() / 20, player->y() / 20);
            points += 50;
            emit scoreDot(points);
            emit blinky->enterFrightenedMode();
            emit pinky->enterFrightenedMode();
            break;
        }

        if (map.dotCount == 0) {
            timer->stop();
            emit youWin();
        }

        //printf("Dots remaining: %d\n", map.dotCount);
    }
}

void Level::switchPhase()
{
    if (generalPhase == Ghost::ghostsMode::scatter) {
        generalPhase = Ghost::ghostsMode::chase;
        emit ghostModeChanged();
        ghostsPhase.start(20000);
    }
    else {
        generalPhase = Ghost::ghostsMode::scatter;
        emit ghostModeChanged();
        ghostsPhase.start(7000);
    }
}

void Level::playerDies()
{
    if (--lives == -1) {
        timer->stop();
        emit gameOver();
    }

    QString temp(" up");
    temp.prepend(lives + '0');
    emit lifeDown(temp);

    player->respawn();
}

void Level::ghostScored()
{
    //static int multiplayer = 0;
    points += 200;

    emit scoreGhost(points);
}