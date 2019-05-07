#pragma once

#include "ghost.h"

class Pinky : public Ghost
{
    Q_OBJECT
public:
    Pinky(Map* m, Player* p);

private slots:
    void seekForPlayer();

public slots:
    //void enterChaseMode();
    void DEBUG();
};