#pragma once

#include <QWidget>
#include <QLabel>

#include "levelView.h"

// contains HUD && levelView

class GameView : public QWidget
{
    Q_OBJECT
public:
    GameView(QWidget *parent = 0);

private:
    LevelView *level;
    QLabel *scores;             // use setNum SLOT to connect to the scores
    QLabel *lives;              // connects to lives
    QLabel *gameOver;
    QLabel *youWin;

public slots:


private slots:
    void exit();
};