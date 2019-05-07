#pragma once

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QKeyEvent>

#include "level.h"

class LevelView : public QWidget
{
    Q_OBJECT
private:
    QTimer timer;
    QRegion objectClip(DynamicObject& obj);
public:
    Level *lvl;
    LevelView(QWidget *parent = 0);
    ~LevelView();
    void paintEvent(QPaintEvent*);
    void paintDots(QPainter &painter);
    void paintMaze(QPainter &painter);
    void paintCharacter(QPainter &painter);

    void paintBlinky(QPainter &painter);
    void paintPinky(QPainter &painter);

    void keyPressEvent(QKeyEvent *event);

signals:
    void turnBack();

public slots:
    void playerUpdate();
    void ghostUpdate();
    //void objectUpdate(DynamicObject& obj);
};