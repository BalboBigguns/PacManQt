#pragma once

#include <QtCore>


/*
    GENERAL NOTES:
    getters and setters do nothing so far, consider deleting them 
*/

class GameObject : public QObject
{
    Q_OBJECT
public:
    QPoint pos;
    QSize size;
    
    GameObject(int x = 0, int y = 0, int w = 0, int h = 0) : pos(x, y), size(w, h) {};
    GameObject(GameObject& g) : QObject(g.parent()), pos(g.pos), size(g.size) {};

    // getters

    inline int x() const { return pos.x(); }
    inline int y() const { return pos.y(); }
    inline int width() const { return size.width(); }
    inline int height() const { return size.height(); }

    // setters

    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
};