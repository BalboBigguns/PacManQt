#pragma once

//#include <QKeyEvent>

#include "dynamicObject.h"

class Player : public DynamicObject
{
public:
    enum playerSpeed { stop, normalSpeed = 5};
    Direction nextDir;
    Player(QTimer* t);

    QPoint playerSpawn;

    void respawn();
};