#include "stdafx.h"
#include "CPong.h"
#include "CBase4618.h"
#include "CPaddle.h"
#include "cvui.h"

CPong::CPong() {
    // Initializing 
    srand(time(NULL));
    _width = 800;
    _height = 600;
    _direction = STOP;
    _Size = 5;
    _Speed = 100;
    gui_position = cv::Point(300, 10);
    game_over = false;

    // Initializing the paddles in the middle of the screen, 50 from the edges
    CPaddle.y = (_height / 2);
    PPaddle.y = (_height / 2);
    PPaddle.x = (_width - 50);
    CPaddle.x = 50;

    _Player_paddle_variable = 50;
    _Player_Score = 0;
    _Cmp_Score = 0;

    _Dim = cv::Size(_width, _height);
    WindowName = "Pong";
    cv::namedWindow(WindowName);
    cvui::init(WindowName);

    _BallColor = cv::Scalar(0, 0, 0);
    Control.init_com();
}

CPong::~CPong() {
    _thread_exit = true;
}

bool CPong::draw() {
    if (game_over) {
        _canvas = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(255, 255, 255));
        cv::putText(_canvas, "Play again?", cv::Point(200, 400), 2, 2, BLACKNESS, 2);
        cv::putText(_canvas, Winner, cv::Point(220, 350), 2, 2, BLACKNESS, 2);

        while (game_over) {
            if (cvui::button(_canvas, gui_position.x + 25, gui_position.y + 180, 50, 30, "Play Again")) {
                game_over = false;
            }

            if (cvui::button(_canvas, gui_position.x + 125, gui_position.y + 180, 50, 30, "Exit")) {
                game_over = false;
                do_exit = true;
                return do_exit;
            }
            cvui::update();
            cv::imshow(WindowName, _canvas);
            cv::waitKey(14);
        }
    }
    else {
        auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(30);

        freq = cv::getTickFrequency();
        start_tic = cv::getTickCount();

        _canvas = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(255, 255, 255));

        // Drawing the GUI
        cvui::window(_canvas, gui_position.x, gui_position.y, 220, 220, WindowName);
        cvui::text(_canvas, gui_position.x + 55, gui_position.y + 5, "FPS: " + std::to_string(_FPS_AVE));
        cvui::text(_canvas, gui_position.x + 25, gui_position.y + 30, "CMP Score: " + std::to_string(_Cmp_Score));
        cvui::text(_canvas, gui_position.x + 25, gui_position.y + 55, "Player Score: " + std::to_string(_Player_Score));
        cvui::text(_canvas, gui_position.x + 25, gui_position.y + 80, "Ball Size");
        cvui::trackbar(_canvas, gui_position.x + 100, gui_position.y + 70, 100, &_Size, 5, 100);
        cvui::text(_canvas, gui_position.x + 25, gui_position.y + 130, "Ball Speed");
        cvui::trackbar(_canvas, gui_position.x + 100, gui_position.y + 120, 100, &_Speed, 100, 500);
        if (cvui::button(_canvas, gui_position.x + 25, gui_position.y + 180, 50, 30, "Reset")) {
            Reset();
        }

        if (cvui::button(_canvas, gui_position.x + 125, gui_position.y + 180, 50, 30, "Exit")) {
            do_exit = true;
            return do_exit;
        }
        cvui::update();

        // Draw paddles and ball
        cv::rectangle(_canvas, cv::Point(PPaddle.x, PPaddle.y - 60), cv::Point(PPaddle.x + 20, PPaddle.y + 60), cv::Scalar(0, 0, 0), cv::FILLED);
        cv::rectangle(_canvas, cv::Point(CPaddle.x, CPaddle.y - 60), cv::Point(CPaddle.x - 20, CPaddle.y + 60), cv::Scalar(0, 0, 0), cv::FILLED);
        cv::circle(_canvas, cv::Point(ball.x, ball.y), _Size, _BallColor, cv::FILLED);
        cv::imshow(WindowName, _canvas);

        std::this_thread::sleep_until(end_time);

        elapsed_time = (cv::getTickCount() - start_tic) / freq;
        _FPS3 = _FPS2;
        _FPS2 = _FPS;
        _FPS = 1 / elapsed_time;
        _FPS_AVE = (_FPS + _FPS2 + _FPS3) / 3;
    }
    return do_exit;
}

void CPong::update() {
    auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(33);

    // Reset with the pushbuttons
    _Click_Reset1 = Control.get_button(33);
    if (_Click_Reset1 == 1) Reset();

    UpdateBall();
    UpdatePaddle();
    UpdateScore();

    if ((_Player_Score == 5 || _Cmp_Score == 5) && !game_over) {
        Winner = (_Player_Score == 5) ? "You win" : "Computer Wins";
        game_over = true;
        Reset();
    }

    std::this_thread::sleep_until(end_time);
}

void CPong::UpdateBall() {
    if (_direction == STOP) {
        Ball.reset();
        _direction = Ball.rand_dir();
    }
    Ball.move(0.053333333333 * (_Speed - 100) + 3.33333333333);

    ball = Ball.GetPos();

    // Ball hitting the bottom wall
    if (ball.y >= (_height - _Size)) {
        _direction = (Ball.GetDirection() == DownRight) ? UpRight : UpLeft;
        Ball.changeDir(_direction);
    }

    // Ball hitting the top wall
    if (ball.y <= _Size) {
        _direction = (Ball.GetDirection() == UpRight) ? DownRight : DownLeft;
        Ball.changeDir(_direction);
    }
}

void CPong::UpdatePaddle() {
    _Player_paddle_variable = Control.get_analog(26);

    // Move player paddle
    if (_Player_paddle_variable > 80 && PPaddle.y > 60) PPaddle.y -= 20;
    if (_Player_paddle_variable < 20 && PPaddle.y < (_height - 60)) PPaddle.y += 20;

    // Move computer paddle
    if (CPaddle.y < ball.y && CPaddle.y < (_height - 60)) CPaddle.y += 10;
    if (CPaddle.y > ball.y && CPaddle.y > 60) CPaddle.y -= 10;

    // Check ball hitting player paddle
    if (ball.x >= (PPaddle.x - _Size) && ball.x <= (PPaddle.x + 20 - _Size)) {
        if ((ball.y + _Size >= PPaddle.y - 60) && (ball.y - _Size <= PPaddle.y + 60)) {
            _direction = (Ball.GetDirection() == DownRight) ? DownLeft : (Ball.GetDirection() == UpRight) ? UpLeft : (Ball.changeDir((rand() % 3) + 4), _direction);
            Ball.changeDir(_direction);
        }
    }

    // Check ball hitting computer paddle
    if (ball.x >= (CPaddle.x - 20 + _Size) && ball.x <= (CPaddle.x + _Size)) {
        if ((ball.y + _Size >= CPaddle.y - 60) && (ball.y - _Size <= CPaddle.y + 60)) {
            _direction = (Ball.GetDirection() == UpLeft) ? UpRight : (Ball.GetDirection() == DownLeft) ? DownRight : (Ball.changeDir((rand() % 3) + 1), _direction);
            Ball.changeDir(_direction);
        }
    }
}

void CPong::UpdateScore() {
    // Computer scoring
    if (ball.x >= _width - _Size) {
        _Cmp_Score++;
        Ball.reset();
        SoftReset();
    }

    // Player scoring on left side
    if (ball.x <= _Size) {
        _Player_Score++;
        Ball.reset();
        SoftReset();
    }
}

void CPong::SoftReset() {
    CPaddle.y = _height / 2;
    PPaddle.y = _height / 2;
    _direction = STOP;
}

void CPong::Reset() {
    Ball.reset();
    CPaddle.y = _height / 2;
    PPaddle.y = _height / 2;
    _Cmp_Score = 0;
    _Player_Score = 0;
    SoftReset();
}

void CPong::update_thread(CBase4618* ptr) {
    std::cout << "in thread 1";
    while (!ptr->_thread_exit) ptr->update();
}

void CPong::draw_thread(CBase4618* ptr) {
    std::cout << "in thread 2";
    while (!ptr->_thread_exit) ptr->draw();
}
