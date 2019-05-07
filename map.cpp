#include "map.h"
#include <iostream>


Map::Map()
{
   countDots();
}


void Map::countDots()
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (maze[y][x] >= aisle) {
                dotCount++;
            }
        }
    }
}

Map::gridType Map::grid(int x, int y) const
{
    if (x < 0 || x >= 37 || y < 0 || y >= 21) {
        std::cerr << "Out of boundary maze check! x = "<< x << " y = " << y << std::endl;    // PURE DEBUG STUFF
        //throw OutOfBoundaryCheck();
        return wall;
    }

    return (gridType)maze[y][x];
}

Map::gridType Map::grid(QPoint tile) const
{
    if (tile.x() < 0 || tile.x() >= 37 || tile.y() < 0 || tile.y() >= 21) {
        std::cerr << "Out of boundary maze check! x = "<< tile.x() << " y = " << tile.y() << std::endl;    // PURE DEBUG STUFF
        throw OutOfBoundaryCheck(); 
    }
    return (gridType)maze[tile.y()][tile.x()];
}

void Map::removeDot(int x, int y)
{
    maze[y][x] = visited;
    dotCount--;
}