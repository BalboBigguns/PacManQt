#include "player.h"

#include <QWidget>

Player::Player(QTimer* t)
{
    playerSpawn = QPoint(18 * 20, 13 * 20);
    pos = playerSpawn;
    setWidth(20);
    setHeight(20);
    setVel(stop);
    nextDir = Up;

    connect(t, SIGNAL(timeout()), this, SLOT(move()));          // could be moved to dynamicObject maybe?
}

void Player::respawn()
{
    pos = playerSpawn;
    setVel(stop);
    nextDir = Up;
}