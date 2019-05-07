#pragma once

#include <QWidget>

#include "gameView.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
private:
    QWidget menu;                       //TODO: add scores
    QWidget creditsView;
    GameView *game;
    //here it should be placed the game view class

private slots:
    void exitFromCredits();

public slots:
    void showCredits();
    void startGame();   
    void backToMenu(QWidget *src);
};