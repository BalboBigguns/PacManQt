#include "gameObject.h"

void GameObject::setX(int x)
{
    if (x >= 0) {
        pos.setX(x);
    }
}

void GameObject::setY(int y)
{
    if (y >= 0) {
        pos.setY(y);
    }
}

void GameObject::setWidth(int w)
{
    if (w >= 0) {
        size.setWidth(w);
    }
}

void GameObject::setHeight(int h)
{
    if (h >= 0) {
        size.setHeight(h);
    }
}