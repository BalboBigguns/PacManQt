#pragma once

#include "ghost.h"

class Blinky : public Ghost
{
    Q_OBJECT
public:
    Blinky(Map* m, Player* p);

private slots:
    void seekForPlayer();

public slots:
    //void enterChaseMode();
    void DEBUG();
    
};