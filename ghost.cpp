#include "ghost.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <time.h>

Ghost::ghostsMode Ghost::generalMode = scatter;

Ghost::Ghost(Map* m, Player* p)
{
    maze = m;
    player = p;
    currentMode = dead;
    velocity = 0;
    setDir(DynamicObject::Up);
    gateTile = Tile(18, 7);

    frightenedTimer.setInterval(20);
    chaseTimer.setInterval(20);
    catchCheck.start(30);
    getToTargetTimer.setInterval(20);

    connect(&frightenedTimer, SIGNAL(timeout()), this, SLOT(randMoves()));
    connect(&frightenedMode, SIGNAL(timeout()), this, SLOT(backToDuty()));
    connect(&frightenedTimer, SIGNAL(timeout()), this, SLOT(isOut()));
    connect(&catchCheck, SIGNAL(timeout()), this, SLOT(isPlayerCaught()));
    connect(this, SIGNAL(ghostEaten()), this, SLOT(hasBeenEaten()));
    connect(&getToTargetTimer, SIGNAL(timeout()), this, SLOT(isTargetReached()));
    connect(this, SIGNAL(targetReached()), this, SLOT(respawn()));
    connect(this, SIGNAL(targetReached()), this, SLOT(backToDuty()));
    connect(this, SIGNAL(playerCaught()), this, SLOT(restart()));

    srand(time(NULL));
}

Ghost::Tile Ghost::tileOccupied(DynamicObject* obj)
{
    return Tile((obj->x() + 10) / 20 , (obj->y() + 10) / 20);
}

void Ghost::getOut()
{
    currentMode = generalMode;
    pos.setX(18 * 20);
    pos.setY(7 * 20);
    setDir(DynamicObject::Left);
}

void Ghost::setVel(int v)
{
    DynamicObject::setVel(0);
    pos = tileOccupied(this) * 20;
    DynamicObject::setVel(v);
}

// HELPERS

Map::gridType Ghost::leftTileType()
{
    return maze->grid(x() / 20 - 1,y() / 20);
}

Map::gridType Ghost::rightTileType()
{
    return maze->grid(x() / 20 + 1,y() / 20);
}

Map::gridType Ghost::upperTileType()
{
    return maze->grid(x() / 20,y() / 20 - 1);
}

Map::gridType Ghost::bottomTileType()
{
    return maze->grid(x() / 20,y() / 20 + 1);
}

Ghost::Tile Ghost::leftTile()
{
    return Tile(x() / 20 - 1,y() / 20);
}

Ghost::Tile Ghost::rightTile()
{
    return Tile(x() / 20 + 1,y() / 20);
}

Ghost::Tile Ghost::upperTile()
{
    return Tile(x() / 20,y() / 20 - 1);
}

Ghost::Tile Ghost::bottomTile()
{
    return Tile(x() / 20,y() / 20 + 1);
}

double Ghost::distFromTarget(Tile t)
{
    return std::sqrt(std::pow(targetTile.x() - t.x(), 2) + std::pow(targetTile.y() - t.y(), 2));
}

// END OF HELPERS


// arbitrary order UP > LEFT > DOWN
void Ghost::controlDir()
{
    double minDist;
    bool hasChoice = false;

    if (x() % 20 == 0 && y() % 20 == 0) {
        
        /* DEBUG 
        std::cout << "Current dist from target: " << distFromTarget(pos) << std::endl;
        std::cout << "Up dist from target: " << distFromTarget(upperTile()) << std::endl;
        std::cout << "Down dist from target: " << distFromTarget(bottomTile()) << std::endl;
        std::cout << "Left dist from target: " << distFromTarget(leftTile()) << std::endl;
        std::cout << "Right dist from target: " << distFromTarget(rightTile()) << std::endl;
        */

        switch (d()) {
        case DynamicObject::Up:
            if (rightTileType() == Map::wall && leftTileType() == Map::wall) {
                return;     // no direction change in case of straight aisle
            }

            if (upperTileType() >= Map::aisle || (currentMode == dead ? (upperTileType() < Map::wall) : 0 )) {
                minDist = distFromTarget(upperTile());
                hasChoice = true;
            }

            if (leftTileType() >= Map::aisle || (currentMode == dead ? (leftTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(leftTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Left);
                    }
                }
                else {
                    minDist = distFromTarget(leftTile());
                    hasChoice = true;
                    setDir(DynamicObject::Left);
                }
            }

            if (rightTileType() >= Map::aisle || (currentMode == dead ? (rightTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(rightTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Right);
                    }
                }
                else {
                    setDir(DynamicObject::Right);
                }
            }
            break;
        case DynamicObject::Down:
            if (rightTileType() == Map::wall && leftTileType() == Map::wall) {
                return;     // no direction change in case of straight aisle
            }

            if (leftTileType() >= Map::aisle || (currentMode == dead ? (leftTileType() < Map::wall) : 0 )) {
                minDist = distFromTarget(leftTile());
                hasChoice = true;
                setDir(DynamicObject::Left);
            }

            if (bottomTileType() >= Map::aisle || (currentMode == dead ? (bottomTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(bottomTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Down);
                    }
                }
                else {
                    minDist = distFromTarget(bottomTile());
                    hasChoice = true;
                    setDir(DynamicObject::Down);
                }
            }

            if (rightTileType() >= Map::aisle || (currentMode == dead ? (rightTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(rightTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Right);
                    }
                }
                else {
                    setDir(DynamicObject::Right);
                }
            }
            break;
        case DynamicObject::Left:
            if (upperTileType() == Map::wall && bottomTileType() == Map::wall) {
                return;     // no direction change in case of straight aisle
            }

            if (upperTileType() >= Map::aisle || (currentMode == dead ? (upperTileType() < Map::wall) : 0 )) {
                minDist = distFromTarget(upperTile());
                hasChoice = true;
                setDir(DynamicObject::Up);
            }

            if (leftTileType() >= Map::aisle || (currentMode == dead ? (leftTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(leftTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Left);
                    }
                }
                else {
                    minDist = distFromTarget(leftTile());
                    hasChoice = true;
                    setDir(DynamicObject::Left);
                }
            }

            if (bottomTileType() >= Map::aisle || (currentMode == dead ? (bottomTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(bottomTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Down);
                    }
                }
                else {
                    setDir(DynamicObject::Down);
                }
            }
            break;
        case DynamicObject::Right:
            if (upperTileType() == Map::wall && bottomTileType() == Map::wall) {
                return;     // no direction change in case of straight aisle
            }

            if (upperTileType() >= Map::aisle || (currentMode == dead ? (upperTileType() < Map::wall) : 0 )) {
                minDist = distFromTarget(upperTile());
                hasChoice = true;
                setDir(DynamicObject::Up);
            }

            if (bottomTileType() >= Map::aisle || (currentMode == dead ? (bottomTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(bottomTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Down);
                    }
                }
                else {
                    minDist = distFromTarget(bottomTile());
                    hasChoice = true;
                    setDir(DynamicObject::Down);
                }
            }

            if (rightTileType() >= Map::aisle || (currentMode == dead ? (rightTileType() < Map::wall) : 0 )) {
                if (hasChoice) {
                    double temp = distFromTarget(rightTile());
                    if (temp < minDist) {
                        minDist = temp;
                        setDir(DynamicObject::Right);
                    }
                }
                else {
                    setDir(DynamicObject::Right);
                }
            }
            break;
        } 
    }
}

void Ghost::enterScatterMode()
{
    chaseTimer.stop();
    frightenedTimer.stop();

    targetTile = escapeTile;

    if (currentMode == chase) {
        setDir(Direction((d() + 2) % 4));
    }

    currentMode = scatter;
}

void Ghost::enterChaseMode()
{
    frightenedTimer.stop();
    currentMode = chase;
    chaseTimer.start(20);
}

void Ghost::enterFrightenedMode()
{
    if (currentMode == dead) {
        return;
    }

    currentMode = frightened;

    chaseTimer.stop();

    frightenedMode.setSingleShot(true);
    frightenedMode.start(7060);

    setVel(2);
}

void Ghost::restart()
{   
    pos = spawnPoint * 20;

    getToTargetTimer.start();

    respawn();
}

void Ghost::controlModes()
{
    // it changes general phase and specific behaviours unless 
    // the ghost is in special state (dead or frightened)
    if (generalMode == chase) {
        generalMode = scatter;
        if (currentMode == chase) {
            enterScatterMode();
        }
    }
    else if (generalMode == scatter){
        generalMode = chase;
        if (currentMode == scatter) {
            enterChaseMode();
        }
    }
}

void Ghost::backToDuty()
{
    if (getToTargetTimer.isActive()) {
        return;
    }

    if (currentMode == dead) {
        currentMode = scatter;
    }

    setVel(4);

    if (generalMode == scatter) {
        enterScatterMode();
    }
    else {
        enterChaseMode();
    }
}

void Ghost::randMoves()
{
    targetTile = Tile(rand() % 37, rand() % 21);
}

void Ghost::isPlayerCaught()
{
    if (tileOccupied(this) == tileOccupied(player)) {
        if (currentMode == frightened) {
            emit ghostEaten();
        }
        else if (currentMode != dead){
            emit playerCaught();
        }
    }
}

void Ghost::hasBeenEaten()
{
    frightenedTimer.stop();
    currentMode = dead;
    targetTile = spawnPoint;
    getToTargetTimer.start();
    setVel(10);
}

void Ghost::respawn()
{
    targetTile = gateTile;
    setDir(DynamicObject::Up);
    setVel(4);
}

void Ghost::isTargetReached()
{
    if (pos / 20 == targetTile) {
        getToTargetTimer.stop();
        emit targetReached();
    }
}

void Ghost::isOut()
{
    if (tileOccupied(this).x() <= 0 || tileOccupied(this).x() >= 36 || 
        tileOccupied(this).y() <= 0 || tileOccupied(this).x() >= 20) {
        emit ghostEaten();
    }
}