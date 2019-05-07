#include <QPushButton>


#include "gameView.h"
#include "mainWindow.h"

#include "gameObject.h"

GameView::GameView(QWidget *parent)
{
    setParent(parent);
    setPalette(QPalette(Qt::black));              // TEMP
    setAutoFillBackground(true);

    level = new LevelView(this);

    QPushButton* quit = new QPushButton(tr("Exit"), this);
    quit->setGeometry(688, 548, 80, 32);

    connect(quit, SIGNAL(clicked()), this, SLOT(exit()));

    scores = new QLabel("0", this, 0);
    scores->setGeometry(32, 32, 200, 32);
    QPalette temp;
    temp.setColor(QPalette::WindowText, Qt::blue);
    scores->setPalette(temp);
    scores->setFont(QFont("Times", 24));

    connect(level->lvl, SIGNAL(scoreDot(int)), scores, SLOT(setNum(int)));
    connect(level->lvl, SIGNAL(scoreGhost(int)), scores, SLOT(setNum(int)));

    lives = new QLabel("2 up", this, 0);
    lives->setGeometry(710, 32, 100, 32);
    lives->setPalette(temp);
    lives->setFont(QFont("Times", 24));

    connect(level->lvl, SIGNAL(lifeDown(QString)), lives, SLOT(setText(QString)));

    gameOver = new QLabel("GAME OVER", this);
    gameOver->setGeometry(185, 200, 430, 200);
    temp.setColor(QPalette::WindowText, Qt::red);
    gameOver->setPalette(temp);
    gameOver->setFont(QFont("Times", 52));
    gameOver->hide();

    connect(level->lvl, SIGNAL(gameOver()), gameOver, SLOT(show()));

    youWin = new QLabel("YOU WIN!!!", this);
    youWin->setGeometry(185, 200, 430, 200);
    temp.setColor(QPalette::WindowText, Qt::red);
    youWin->setPalette(temp);
    youWin->setFont(QFont("Times", 52));
    youWin->hide();

    connect(level->lvl, SIGNAL(youWin()), youWin, SLOT(show()));

    show();
}

void GameView::exit()
{
    delete level;
    emit ((MainWindow*)parentWidget())->backToMenu(this);
    //hide();
}