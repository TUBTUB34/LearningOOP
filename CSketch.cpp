#include "stdafx.h"
#include "Serial.h" 
#include "CControl.h"
#include "CSketch.h"
#include "cvui.h"

// Destructor: Closes all windows and resets control data to 0
CSketch::~CSketch() {
    cv::destroyAllWindows();
    Control.set_data(0, 37, 0);
    Control.set_data(0, 38, 0);
    Control.set_data(0, 39, 0);
}

// Constructor: Initializes the canvas and control parameters
CSketch::CSketch(cv::Size Dim) {
    _canvas = cv::Mat(Dim, CV_8UC3, cv::Scalar(255, 255, 255));
    WindowName = "Etch a Sketch";
    cv::namedWindow(WindowName);
    cvui::init(WindowName);
    Control.init_com();

    // Initial position and settings
    Position.x = 400;
    Position.y = 300;
    accelerometer = 23;
    Button_count = 0;
    gui_position = cv::Point(10, 10);
}

// Updates the game state, including controls, position, and color changes
void CSketch::update(void) {
    Control.test();  // Test control connection

    Prev_position = Position;  // Store previous position for drawing lines

    // Get control inputs for position and clearing canvas
    _Check.y = Control.get_analog(26);
    _Check.x = Control.get_analog(2);
    clear = Control.get_analog(accelerometer);

    // Clear canvas if accelerometer input exceeds threshold
    if (clear > 96) {
        _canvas = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(255, 255, 255));
    }

    // Update button count if the specified button is pressed
    if (Control.get_button(32)) Button_count++;

    // Color selection logic based on button count modulus
    if ((Button_count % 10) == 0) {
        line_Color = cv::Scalar(255, 0, 0); // Blue
        Color = "Blue";
        Control.get_data(0, 37, Real_colorB);
        if (!Real_colorB) {
            Control.set_data(0, 37, 1);
            Control.set_data(0, 39, 0);
        }
    }
    else if ((Button_count % 10) == 1) {
        line_Color = cv::Scalar(0, 255, 0); // Green
        Color = "Green";
        Control.get_data(0, 38, Real_colorG);
        if (!Real_colorG) {
            Control.set_data(0, 38, 1);
            Control.set_data(0, 37, 0);
        }
    }
    else if ((Button_count % 10) == 2) {
        line_Color = cv::Scalar(0, 0, 255); // Red
        Color = "Red";
        Control.get_data(0, 39, Real_colorR);
        if (!Real_colorR) {
            Control.set_data(0, 39, 1);
            Control.set_data(0, 38, 0);
        }
    }
    else if ((Button_count % 10) == 3) {
        line_Color = cv::Scalar(255, 153, 255); // Pink
        Color = "Pink";
        if (Real_colorR || Real_colorG || Real_colorB) {
            Control.set_data(0, 39, 0);
            Control.set_data(0, 38, 0);
            Control.set_data(0, 37, 0);
        }
    }
    else if ((Button_count % 10) == 4) {
        line_Color = cv::Scalar(0, 255, 255); // Yellow
        Color = "Yellow";
    }
    else if ((Button_count % 10) == 5) {
        line_Color = cv::Scalar(0, 128, 255); // Orange
        Color = "Orange";
    }
    else if ((Button_count % 10) == 6) {
        line_Color = cv::Scalar(255, 204, 153); // Light Blue
        Color = "Light Blue";
    }
    else if ((Button_count % 10) == 7) {
        line_Color = cv::Scalar(76, 0, 153); // Dark Red
        Color = "Dark Red";
    }
    else if ((Button_count % 10) == 8) {
        line_Color = cv::Scalar(0, 102, 0); // Dark Green
        Color = "Dark Green";
    }
    else if ((Button_count % 10) == 9) {
        line_Color = cv::Scalar(255, 204, 255); // Light Pink
        Color = "Light Pink";
    }

    // Limit and update X position based on control input
    if (Position.x < 0) Position.x = 0;
    else if (Position.x > 800) Position.x = 800;
    else if (_Check.x >= 95) Position.x += 20;
    else if (_Check.x > 90) Position.x += 15;
    else if (_Check.x >= 80 && _Check.x < 90) Position.x += 10;
    else if (_Check.x >= 70 && _Check.x < 80) Position.x += 5;
    else if (_Check.x >= 60 && _Check.x < 70) Position.x += 2;
    else if (_Check.x < 10) Position.x -= 15;
    else if (_Check.x <= 5) Position.x -= 20;
    else if (_Check.x <= 20 && _Check.x > 10) Position.x -= 10;
    else if (_Check.x <= 30 && _Check.x > 20) Position.x -= 5;
    else if (_Check.x <= 40 && _Check.x > 30) Position.x -= 2;

    // Limit and update Y position based on control input
    if (Position.y < 0) Position.y = 0;
    else if (Position.y > 600) Position.y = 600;
    else if (_Check.y >= 95) Position.y -= 20;
    else if (_Check.y > 90) Position.y -= 15;
    else if (_Check.y >= 80 && _Check.y < 90) Position.y -= 10;
    else if (_Check.y >= 70 && _Check.y < 80) Position.y -= 5;
    else if (_Check.y >= 60 && _Check.y < 70) Position.y -= 2;
    else if (_Check.y <= 5) Position.y += 20;
    else if (_Check.y < 10) Position.y += 15;
    else if (_Check.y <= 20 && _Check.y > 10) Position.y += 10;
    else if (_Check.y <= 30 && _Check.y > 20) Position.y += 5;
    else if (_Check.y <= 40 && _Check.y > 30) Position.y += 2;
}

// Draws the canvas and GUI controls, including color display and reset/exit buttons
bool CSketch::draw() {
    cvui::window(_canvas, gui_position.x, gui_position.y, 200, 110, WindowName);
    cvui::text(_canvas, gui_position.x + 25, gui_position.y + 35, "Color: " + Color);

    // Reset canvas if "Reset" button is clicked
    if (cvui::button(_canvas, gui_position.x + 25, gui_position.y + 60, 50, 30, "Reset")) {
        _canvas = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(255, 255, 255));
    }

    // Exit application if "Exit" button is clicked
    if (cvui::button(_canvas, gui_position.x + 125, gui_position.y + 60, 50, 30, "Exit")) {
        do_exit = true;
        return do_exit;
    }

    cvui::update();
    cv::imshow(WindowName, _canvas);

    // Draws line from previous position to current position with the selected color
    cv::line(_canvas, Prev_position, Position, line_Color, 10);

    return false;
}
