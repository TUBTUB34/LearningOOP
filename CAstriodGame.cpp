#include "stdafx.h"
#include "CAstroidGame.h"
#include "cvui.h"

// Constructor to initialize game window and setup initial game conditions
CAstroidGame::CAstroidGame(cv::Size Dim) {
    // Initializing window dimensions and properties
    _Canvis_size = Dim;
    _canvas = cv::Mat(Dim, CV_8UC3, cv::Scalar(255, 255, 255));
    WindowName = "Astroids";
    cv::namedWindow(WindowName);
    cvui::init(WindowName);
    Control.init_com();

    // Initializing ship properties and positions
    Ship.set_pos(cv::Point((Dim.width / 2), (Dim.height - 15)));
    Temp_ship = cv::Point((Dim.width / 2), (Dim.height - 15));
    _Num_of_missle = 0;
    _lives = Ship.get_lives();

    // Setting colors for game elements
    _Ship_color = cv::Scalar(255, 0, 0);
    _Astroid_color = cv::Scalar(0, 0, 0);
    _Missle_color = cv::Scalar(0, 0, 255);

    gui_position = cv::Point(0, 0);
    _Start_Time = cv::getTickCount();

    _Score = 0;
    game_over = false;
}

// Destructor
CAstroidGame::~CAstroidGame() {}

// Updates the game state
void CAstroidGame::update() {
    CMissle Missle(Ship.get_pos());
    _Click_Reset = Control.get_button(33); // Check for reset button
    _Click_Fire = Control.get_button(32);  // Check for fire button

    // Reset the game if reset button is pressed
    if (_Click_Reset) {
        reset();
    }

    // Spawn new asteroid at random intervals
    if (((cv::getTickCount() - _Start_Time) / cv::getTickFrequency()) >= (rand() % 3 + 1)) {
        CAstroid Astroid;
        Astroides.push_back(Astroid);
        _Start_Time = cv::getTickCount();
    }

    // Update each asteroid's position and check for collisions with walls or the ship
    for (int i = 0; i < Astroides.size(); i++) {
        Astroides[i].move();
        Astroides[i].draw(_canvas, _Astroid_color);

        if (Astroides[i].collide_wall(_Canvis_size))
            Astroides[i].collide(Astroides[i]);

        // Check for collision between ship and asteroid
        if (Ship.get_pos().y < Astroides[i].get_pos().y + Astroides[i].get_radius() &&
            Ship.get_pos().y > Astroides[i].get_pos().y - Astroides[i].get_radius() &&
            Ship.get_pos().x > Astroides[i].get_pos().x - Astroides[i].get_radius() &&
            Ship.get_pos().x < Astroides[i].get_pos().x + Astroides[i].get_radius()) {
            Astroides[i].collide(Astroides[i]);
            if (Ship.collide(Ship)) game_over = true;
            restart();
        }
    }

    // Fire a missile if fire button is pressed
    if (_Click_Fire) {
        Missles.push_back(Missle);
        _Num_of_missle++;
    }

    // Update missiles' positions and check for collisions with asteroids
    for (int i = 0; i < Missles.size(); i++) {
        Missles[i].draw(_canvas, _Missle_color);
        Missles[i].move();

        // Check each missile for collision with any asteroid
        for (int a = 0; a < Astroides.size(); a++) {
            if (Missles[i].get_pos().y < Astroides[a].get_pos().y + Astroides[a].get_radius() &&
                Missles[i].get_pos().y > Astroides[a].get_pos().y - Astroides[a].get_radius() &&
                Missles[i].get_pos().x > Astroides[a].get_pos().x - Astroides[a].get_radius() &&
                Missles[i].get_pos().x < Astroides[a].get_pos().x + Astroides[a].get_radius()) {
                Astroides[a].collide(Astroides[a]);
                Missles[i].collide(Missles[i]);
                Ship.hit();
            }
        }

        // Remove missile if it moves out of bounds or loses all lives
        if (Missles[i].get_pos().y < 0 || Missles[i].get_lives() == 0) {
            Missles.erase(Missles.begin() + i);
            _Num_of_missle--;
        }
    }

    // Update ship position based on controls
    Ship_position();
    Ship.move();

    // Check if ship collides with walls and restart if it does
    if (Ship.collide_wall(_Canvis_size)) {
        Ship.collide(Ship);
        restart();
    }

    Temp_ship = Ship.get_pos();

    // Remove asteroids with no lives left
    for (int i = 0; i < Astroides.size(); i++) {
        if (Astroides[i].get_lives() == 0)
            Astroides.erase(Astroides.begin() + i);
    }

    // Update score and lives
    _Score = Ship.get_score();
    _lives = Ship.get_lives();

    // End game if lives reach zero
    if (_lives == 0) {
        game_over = true;
    }

    // Draw ship
    Ship.draw(_canvas, _Ship_color);
}

// Adjusts ship position based on control inputs
void CAstroidGame::Ship_position() {
    _Check.y = Control.get_analog(26);
    _Check.x = Control.get_analog(2);

    // Horizontal position adjustments
    if (_Check.x >= 95) Temp_ship.x += 20;
    else if (_Check.x > 90) Temp_ship.x += 15;
    else if (_Check.x >= 80 && _Check.x < 90) Temp_ship.x += 10;
    else if (_Check.x >= 70 && _Check.x < 80) Temp_ship.x += 5;
    else if (_Check.x >= 60 && _Check.x < 70) Temp_ship.x += 2;
    else if (_Check.x < 10) Temp_ship.x -= 20;
    else if (_Check.x <= 5) Temp_ship.x -= 15;
    else if (_Check.x <= 20 && _Check.x > 10) Temp_ship.x -= 10;
    else if (_Check.x <= 30 && _Check.x > 20) Temp_ship.x -= 5;
    else if (_Check.x <= 40 && _Check.x > 30) Temp_ship.x -= 2;

    // Vertical position adjustments
    if (_Check.y >= 95) Temp_ship.y -= 20;
    else if (_Check.y > 90) Temp_ship.y -= 15;
    else if (_Check.y >= 80 && _Check.y < 90) Temp_ship.y -= 10;
    else if (_Check.y >= 70 && _Check.y < 80) Temp_ship.y -= 5;
    else if (_Check.y >= 60 && _Check.y < 70) Temp_ship.y -= 2;
    else if (_Check.y <= 5) Temp_ship.y += 20;
    else if (_Check.y < 10) Temp_ship.y += 15;
    else if (_Check.y <= 20 && _Check.y > 10) Temp_ship.y += 10;
    else if (_Check.y <= 30 && _Check.y > 20) Temp_ship.y += 5;
    else if (_Check.y <= 40 && _Check.y > 30) Temp_ship.y += 2;

    Ship.set_pos(Temp_ship);
}

// Draws the game and handles game over screen
bool CAstroidGame::draw() {
    if (game_over) {
        _canvas = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(255, 255, 255));
        cv::putText(_canvas, "Play again?", cv::Point(200, 400), 2, 2, BLACKNESS, 2);
        cv::putText(_canvas, "Score:" + std::to_string(_Score), cv::Point(220, 350), 2, 2, BLACKNESS, 2);

        while (game_over) {
            if (cvui::button(_canvas, gui_position.x + 300, gui_position.y + 180, 50, 30, "Play Again")) {
                game_over = false;
                reset();
            }

            if (cvui::button(_canvas, gui_position.x + 400, gui_position.y + 180, 50, 30, "Exit")) {
                do_exit = true;
                return do_exit;
            }
            cvui::update();
            cv::imshow(WindowName, _canvas);
            cv::waitKey(14);
        }
    }
    else {
        // Display game stats in the GUI
        cvui::window(_canvas, gui_position.x, gui_position.y, _Canvis_size.width, 20, WindowName);
        cvui::text(_canvas, gui_position.x + 100, gui_position.y + 5, "Lives: " + std::to_string(_lives));
        cvui::text(_canvas, gui_position.x + 300, gui_position.y + 5, "Missles: " + std::to_string(_Num_of_missle));
        cvui::text(_canvas, gui_position.x + 500, gui_position.y + 5, "Score: " + std::to_string(_Score));
        cv::imshow(WindowName, _canvas);
        _canvas = cv::Mat(_Canvis_size, CV_8UC3, cv::Scalar(255, 255, 255));
        return false;
    }
}

// Resets the game state
void CAstroidGame::reset() {
    Ship.set_score(0);
    _Num_of_missle = 0;
    Ship.set_lives(10);
    Astroides.clear();
    Missles.clear();
    Temp_ship = cv::Point((_Canvis_size.width / 2), (_Canvis_size.height - 15));
}

// Restarts the game by resetting only missile and ship positions
void CAstroidGame::restart() {
    _Num_of_missle = 0;
    Missles.clear();
    Temp_ship = cv::Point((_Canvis_size.width / 2), (_Canvis_size.height - 15));
}
