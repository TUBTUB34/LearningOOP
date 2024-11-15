#include "stdafx.h"
#include "CAstroid.h"

CAstroid::CAstroid() {
    srand(time(NULL)); // Seed the random number generator

    // Set random radius between 10 and 30
    _radius = (rand() % 20 + 10);

    // Initial position: start near the top of the screen with a random x position
    _Position.y = 0;
    _Position.x = (rand() % 700 + 50);

    // Set random velocity: y-velocity between -5 and -10 (moving downwards), x-velocity between -5 and 5
    _velocity.y = (rand() % 5 + 5) * -1;
    _velocity.x = (rand() % 10 - 5);

    // Set initial lives for the asteroid
    _lives = 1;
}

CAstroid::~CAstroid() {}
