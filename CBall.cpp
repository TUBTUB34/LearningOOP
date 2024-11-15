#include "stdafx.h"
#include "CBall.h"

CBall::CBall() {
    _pos.x = 400;
    _pos.y = 300;
    direction = 0;
}

CBall::~CBall() {}

void CBall::reset() {
    _position = _pos;
    direction = STOP;
}

int CBall::rand_dir() {
    direction = (rand() % 6) + 1;
    return direction;
}

void CBall::move(int speed) {
    switch (direction) {
    case STOP:
        break;
    case Left:
        _position.x -= speed;
        break;
    case Right:
        _position.x += speed;
        break;
    case UpLeft:
        _position.x -= speed;
        _position.y -= speed;
        break;
    case DownLeft:
        _position.x -= speed;
        _position.y += speed;
        break;
    case UpRight:
        _position.x += speed;
        _position.y -= speed;
        break;
    case DownRight:
        _position.x += speed;
        _position.y += speed;
        break;
    default:
        break;
    }
}
