#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

class Tile : public GameObject
{
public:
    explicit Tile(QGraphicsItem *parent = nullptr);
};

#endif // TILE_H
