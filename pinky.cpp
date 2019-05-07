#include "pinky.h"
#include <iostream>

Pinky::Pinky(Map* m, Player* p) : Ghost(m, p)
{
    escapeTile = Tile(2, 2);
    spawnPoint = Tile(17, 10);
    targetTile = Tile(2, 2); // top-left corner
    pos = spawnPoint * 20;
    currentMode = scatter;
    velocity = 4;

    connect( &chaseTimer, SIGNAL(timeout()), this, SLOT(seekForPlayer()));

    getOut();

    
    QTimer* debug = new QTimer();
    debug->start(1000);
    connect(debug, SIGNAL(timeout()), this, SLOT(DEBUG()));
    /**/
    
}

void Pinky::seekForPlayer()
{
    targetTile = player->pos / 20;

    switch (player->d()) {
        case Up:
            targetTile += Tile(0, 4);
            break;
        case Down:
            targetTile += Tile(0, -4);
            break;
        case Left:
            targetTile += Tile(-4, 0);
            break;
        case Right:
            targetTile += Tile(4, 0);
            break;
    }
}

void Pinky::DEBUG()
{
    std::cout << "#PINKY" << std::endl;
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
