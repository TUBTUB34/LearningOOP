#include "stdafx.h"
#include "CGameobject.h"

// Moves the game object by updating its position based on its velocity
void CGameObject::move() {
    _Position.y -= _velocity.y;
    _Position.x += _velocity.x;
}

// Handles collision with another game object and decreases lives
// Returns true if lives reach zero, indicating the object is "destroyed"
bool CGameObject::collide(CGameObject& obj) {
    _lives--;
    return (_lives == 0);
}

// Checks for collisions with the board edges
// Wraps horizontally if the object goes out of bounds on the x-axis
// Returns true if the object has hit the bottom boundary
bool CGameObject::collide_wall(cv::Size board) {
    if (_Position.x < 0) {
        _Position.x += board.width;
        return false;
    }
    if (_Position.x > board.width) {
        _Position.x -= board.width;
        return false;
    }

    // Return true if object exceeds the bottom boundary
    return (_Position.y + _radius > board.height);
}

// Increases score when the object hits a target
void CGameObject::hit() {
    _Score += 10;
}

// Draws the game object as a filled circle on the given image
void CGameObject::draw(cv::Mat& im, cv::Scalar color) {
    cv::circle(im, _Position, _radius, color, cv::FILLED);
}
