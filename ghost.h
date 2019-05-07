#pragma once

#include "dynamicObject.h"
#include "map.h"
#include "player.h"

class Ghost : public DynamicObject
{
    Q_OBJECT
public:
    enum ghostsMode {scatter, chase, frightened, dead};
    typedef QPoint Tile;

    ghostsMode currentMode;
    static ghostsMode generalMode;

    Ghost(Map* m, Player* p);
    QTimer frightenedMode;

protected:
    QTimer chaseTimer;
    QTimer frightenedTimer;
    QTimer catchCheck;
    QTimer getToTargetTimer;

    Map *maze;
    Player *player;

    // IMPORTANT NOTES: these tiles are set in grid units
    Tile escapeTile;
    Tile spawnPoint;
    Tile targetTile;
    Tile gateTile;

    Tile leftTile();
    Tile rightTile();
    Tile upperTile();
    Tile bottomTile();

    Tile tileOccupied(DynamicObject* obj);
    //!!!

    void getOut();

    Map::gridType leftTileType();
    Map::gridType rightTileType();
    Map::gridType upperTileType();
    Map::gridType bottomTileType();

    double distFromTarget(Tile t);

    void enterChaseMode();
    void enterScatterMode();

    void setVel(int v) override;

public slots:
    void restart();

    void controlModes();
    void controlDir();
    void backToDuty();

    void enterFrightenedMode();
    void randMoves();

    void isPlayerCaught();

    void respawn();
    void isTargetReached();

    void hasBeenEaten();
    void isOut();

signals:
    void playerCaught();
    void ghostEaten();

    void targetReached();
};