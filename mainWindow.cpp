#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

#include "mainWindow.h"
//#define DEBUG

MainWindow::MainWindow(QWidget *parent) 
    : QWidget(parent)
{
    setFont(QFont("Times", 18, QFont::Bold));
    QPalette temp;
    temp.setColor(QPalette::Window, Qt::darkBlue);
    setPalette(QPalette(temp));
    setAutoFillBackground(true);

    //menu setting
    menu.setParent(this);
    menu.setGeometry(240, 100, 320, 400);                                    //TODO: Find some fancy font

    QPushButton *play = new QPushButton(tr("Play!"), &menu);             
    QPushButton *credits = new QPushButton(tr("Credits"), &menu);
    QPushButton *quit = new QPushButton(tr("Quit"), &menu);

    connect(play, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(credits, SIGNAL(clicked()), this, SLOT(showCredits()));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(play);
    layout->addWidget(credits);
    layout->addWidget(quit);
    menu.setLayout(layout);

    //credits setting
    creditsView.setParent(this);
    creditsView.setGeometry(240, 100, 320, 400);

    QLabel *creditsText = new QLabel(&creditsView);
    creditsText->setText(tr("Creator: Michal Okrasa\nDate: 11.01.19\nVersion: 1.0.1")); 

    QPushButton *back = new QPushButton(tr("Back"), &creditsView);

    connect(back, SIGNAL(clicked()), this, SLOT(exitFromCredits()));

    QVBoxLayout *creditsLayout = new QVBoxLayout;
    creditsLayout->addWidget(creditsText);
    creditsLayout->addWidget(back);
    creditsView.setLayout(creditsLayout);

    creditsView.hide();
}

void MainWindow::showCredits()
{
    menu.hide();
    creditsView.show();
}

void MainWindow::backToMenu(QWidget *src)
{
    if (src->isVisible()) {
        src->hide();
    }
    menu.show();
}

void MainWindow::startGame()
{
    game = new GameView(this);
    menu.hide();
}

void MainWindow::exitFromCredits()
{
    emit backToMenu(&creditsView);
}
