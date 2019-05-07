#include "levelView.h"
#include <iostream>

#define LEVEL_WIDTH 740
#define LEVEL_HEIGHT 420
#define GRID_SIZE 20

LevelView::LevelView(QWidget *parent)
{
    setParent(parent);
    setGeometry((800 - LEVEL_WIDTH) / 2, 100, LEVEL_WIDTH, LEVEL_HEIGHT);
    setPalette(QPalette(QColor(0, 0, 0)));
    setAutoFillBackground(true);


    lvl = new Level(&timer);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    connect(&timer, SIGNAL(timeout()), this, SLOT(playerUpdate()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(ghostUpdate()));
    connect(this, SIGNAL(turnBack()), lvl, SLOT(goBack()));
    connect(lvl->blinky, SIGNAL(playerCaught()), this, SLOT(update()));

    timer.start(60);

    show();
}

LevelView::~LevelView()
{
    delete lvl;
}

QRegion LevelView::objectClip(DynamicObject& obj)
{
    return QRegion(obj.x() - GRID_SIZE, obj.y() - GRID_SIZE, 3 * GRID_SIZE, 3 * GRID_SIZE);
}

void LevelView::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    paintMaze(painter);
    paintDots(painter);
    paintCharacter(painter);
    paintBlinky(painter);
    paintPinky(painter);
}

void LevelView::paintDots(QPainter &painter)
{
    painter.setPen(Qt::darkYellow);
    painter.setBrush(Qt::yellow);

    for (int y = 0; y < LEVEL_HEIGHT / GRID_SIZE; y++) {
        for (int x = 0; x < LEVEL_WIDTH / GRID_SIZE; x++) {
            if (lvl->map.grid(x, y) == Map::aisle) {
                painter.drawEllipse(x * GRID_SIZE + (GRID_SIZE - Dot::normal) / 2,
                                    y * GRID_SIZE + (GRID_SIZE - Dot::normal) / 2,
                                    Dot::normal, Dot::normal);
            }
            else if (lvl->map.grid(x, y) == Map::bigDotSpawn) {
                painter.drawEllipse(x * GRID_SIZE + (GRID_SIZE - Dot::big) / 2,
                                    y * GRID_SIZE + (GRID_SIZE - Dot::big) / 2,
                                    Dot::big, Dot::big);
            }
        }
    }          
    
}

void LevelView::paintMaze(QPainter &painter)
{
    painter.setPen(Qt::darkGreen);
    painter.setBrush(Qt::green);

    for (int y = 0; y < LEVEL_HEIGHT / GRID_SIZE; y++) {
        for (int x = 0; x < LEVEL_WIDTH / GRID_SIZE; x++) {
            if (lvl->map.grid(x, y) == Map::wall) {
                painter.drawRect(GRID_SIZE * x, GRID_SIZE * y, GRID_SIZE, GRID_SIZE);
            }
            else if (lvl->map.grid(x, y) == Map::gate) {
                painter.setBrush(Qt::darkGray);
                painter.drawRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, 3);
                painter.setBrush(Qt::green);
            }
        }
    }
}


void LevelView::paintCharacter(QPainter &painter)
{
    int rotation = (int)lvl->getPlayer().d() * 90 + 45;
    static int animationState = 0;

    painter.setPen(Qt::darkYellow);
    painter.setBrush(Qt::yellow);

    if (lvl->getPlayer().v() != Player::stop) {
        animationState += Player::normalSpeed * 2;
    }
    animationState %= Player::normalSpeed * 10;
    
    if (animationState < Player::normalSpeed * 5) {
        painter.drawPie(lvl->getPlayer().x() + 1, lvl->getPlayer().y() + 1, lvl->getPlayer().width() - 2, 
                        lvl->getPlayer().height() - 2, rotation * 16, 270 * 16);
    }
    else {
        painter.drawPie(lvl->getPlayer().x() + 1, lvl->getPlayer().y() + 1, lvl->getPlayer().width() - 2, 
                        lvl->getPlayer().height() - 2, (rotation - 30) * 16, 330 * 16);
    }

    /* DEBUG RECT
    painter.setBrush(Qt::NoBrush);
    DynamicObject obj = lvl->getPlayer();
    painter.drawRect(obj.x() - GRID_SIZE, obj.y() - GRID_SIZE, 3 * GRID_SIZE, 3 * GRID_SIZE);
    */
}

void LevelView::paintBlinky(QPainter &painter)
{
    static QTimer temp;
    static bool isOn = false;
    static int counter = 0;

    painter.setBrush(Qt::red);
    painter.setPen(Qt::darkRed);

    if (lvl->blinky->currentMode == Ghost::frightened) {
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::darkBlue);
        if (!isOn) {
            temp.setSingleShot(true);
            isOn = true;
            temp.start(4000);
        }

        if (!temp.isActive()) {
            counter++;
            counter %= 20;
        }

        if (counter >= 10) {
            painter.setBrush(Qt::white);
            painter.setPen(Qt::darkGray);
        }
    }
    else {
        isOn = false;
        counter = 0;
    }

    if (lvl->blinky->currentMode == Ghost::dead) {
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::darkGray);
    }

    static QPoint points[4];
    points[0] = QPoint(lvl->blinky->x() + 3, lvl->blinky->y());
    points[1] = QPoint(lvl->blinky->x() + 17, lvl->blinky->y());
    points[2] = QPoint(lvl->blinky->x(), lvl->blinky->y() + GRID_SIZE);
    points[3] = QPoint(lvl->blinky->x() + GRID_SIZE, lvl->blinky->y() + GRID_SIZE);

    painter.drawPolygon(points, 4);
}

void LevelView::paintPinky(QPainter &painter)
{
    static QTimer temp;
    static bool isOn = false;
    static int counter = 0;

    painter.setBrush(Qt::magenta);
    painter.setPen(Qt::darkMagenta);

    if (lvl->pinky->currentMode == Ghost::frightened) {
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::darkBlue);
        if (!isOn) {
            temp.setSingleShot(true);
            isOn = true;
            temp.start(4000);
        }

        if (!temp.isActive()) {
            counter++;
            counter %= 20;
        }

        if (counter >= 10) {
            painter.setBrush(Qt::white);
            painter.setPen(Qt::darkGray);
        }
    }
    else {
        isOn = false;
        counter = 0;
    }

    if (lvl->pinky->currentMode == Ghost::dead) {
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::darkGray);
    }

    static QPoint points[4];
    points[0] = QPoint(lvl->pinky->x() + 3, lvl->pinky->y());
    points[1] = QPoint(lvl->pinky->x() + 17, lvl->pinky->y());
    points[2] = QPoint(lvl->pinky->x(), lvl->pinky->y() + GRID_SIZE);
    points[3] = QPoint(lvl->pinky->x() + GRID_SIZE, lvl->pinky->y() + GRID_SIZE);

    painter.drawPolygon(points, 4);
}

void LevelView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Left:
        if (lvl->getPlayer().d() == DynamicObject::Right){
            lvl->getPlayer().nextDir = DynamicObject::Left;
            emit turnBack();
        }
        else {
            lvl->getPlayer().nextDir = DynamicObject::Left;
        }
        break;
    case Qt::Key_Right:
        if (lvl->getPlayer().d() == DynamicObject::Left){
            lvl->getPlayer().nextDir = DynamicObject::Right;
            emit turnBack();
        }
        else {
            lvl->getPlayer().nextDir = DynamicObject::Right;
        }
        break;
    case Qt::Key_Down:
        if (lvl->getPlayer().d() == DynamicObject::Up){
            lvl->getPlayer().nextDir = DynamicObject::Down;
            emit turnBack();
        }
        else {
            lvl->getPlayer().nextDir = DynamicObject::Down;
        }
        break;
    case Qt::Key_Up:
        if (lvl->getPlayer().d() == DynamicObject::Down){
            lvl->getPlayer().nextDir = DynamicObject::Up;
            emit turnBack();
        }
        else {
            lvl->getPlayer().nextDir = DynamicObject::Up;
        }
        break;    
    }
}

void LevelView::playerUpdate()
{
    repaint(objectClip(lvl->getPlayer()));
}

void LevelView::ghostUpdate()
{
    repaint(objectClip(*(lvl->blinky)));
    repaint(objectClip(*(lvl->pinky)));
}