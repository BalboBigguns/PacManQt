#include "blinky.h"
#include <iostream>

Blinky::Blinky(Map* m, Player* p) : Ghost(m, p)
{
    escapeTile = Tile(34, 2);
    spawnPoint = Tile(18, 9);
    targetTile = Tile(34, 2); // top-right corner
    pos = spawnPoint * 20;
    currentMode = scatter;
    velocity = 4;

    connect( &chaseTimer, SIGNAL(timeout()), this, SLOT(seekForPlayer()));

    getOut();

    /**/
    QTimer* debug = new QTimer();
    debug->start(1000);
    connect(debug, SIGNAL(timeout()), this, SLOT(DEBUG()));
    
}

void Blinky::seekForPlayer()
{
    targetTile = player->pos / 20;
}

void Blinky::DEBUG()
{
    std::cout << "#BLINKY" << std::endl;
    std::cout << "Position: x = " << pos.x() << " y = " << pos.y() << std::endl;
    std::cout << "Target: x = " << targetTile.x() << " y = " << targetTile.y() << std::endl;
    std::cout << "Current mode: ";
    switch(currentMode) {
        case dead:
            std::cout << "dead";
        break;
        case chase:
            std::cout << "chase";
            break;
        case frightened:
            std::cout << "frightened";
            break;
        case scatter:
            std::cout << "scatter";
    }
    std::cout << std::endl << std::endl;
}