#include "stdafx.h"
#include "CControl.h"
#include "Serial.h"
#include "math.h"

// Constructor initializes control state
CControl::CControl() {
    current_state = 0;
    is_count = 0;
}

// Destructor
CControl::~CControl() {}

// Initializes communication by attempting to connect on different COM ports
void CControl::init_com() {
    int temp;
    for (int i = 1; i < 100; i++) {
        std::string port = "COM" + std::to_string(i);
        _com.open(port);
        temp = i;
        if (!test()) // Test communication, break if successful
            break;
    }
    std::cout << "Com Port used: COM" << temp << "\n";
}

// Sends data to a specified type and channel with a given value
bool CControl::set_data(int type, int channel, int val) {
    std::string T = std::to_string(type), C = std::to_string(channel), V = std::to_string(val);
    std::string Total = "s " + T + " " + C + " " + V + "\n";
    test();  // Ensure communication is active
    _com.write(Total.c_str(), Total.length());
    return true;
}

// Gets data from a specified type and channel, stores result in the reference parameter
bool CControl::get_data(int type, int channel, int& result) {
    std::string T = std::to_string(type), C = std::to_string(channel);
    std::string Total = "g " + T + " " + C + " \n";
    std::string receive;
    char buff[2];

    _com.write(Total.c_str(), Total.length());
    Sleep(10); // Brief delay for data to be received

    receive = "";
    double start_time = cv::getTickCount();  // Start timeout count

    buff[0] = 0;
    // Read bytes until newline or timeout (1 second)
    while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0) {
        if (_com.read(buff, 1) > 0) {
            receive += buff[0];
        }
    }

    std::stringstream ss(receive);
    char ack;
    int receive_type = 0, receive_channel = 0, receive_value = 0, n4 = 0;

    ss >> ack >> receive_type >> receive_channel >> receive_value >> n4;

    if (receive_channel == channel) {
        result = receive_value;
    }
    return (ack != 'A');
}

// Tests if the device is communicating correctly
bool CControl::test() {
    _com.flush();
    int Test;
    bool error = get_data(0, 0, Test);
    return error;
}

// Retrieves analog data from a specified channel, scales it to a percentage, and rounds to 2 decimal places
float CControl::get_analog(int channel) {
    result = 0;
    get_data(ANALOG, channel, result);
    float percent_result = (result / 4096.0f) * 100;
    percent_result = ceilf(percent_result * 100) / 100;  // Round to 2 decimal places
    return percent_result;
}

// Checks if a button is pressed on a specified channel with debouncing
int CControl::get_button(int Channel) {
    get_data(DIGITAL, Channel, pressed);

    // If button is pressed, begin counting debounce time
    if (!pressed) {
        if (!is_count) {
            start_time = cv::getTickCount();
            is_count = true;
        }

        // Check if the debounce time is less than 10 milliseconds
        if (((cv::getTickCount() - start_time) / cv::getTickFrequency()) * 1000 <= 10) {
            is_count = false;
            get_data(DIGITAL, Channel, pressed);

            // Register button press if not pressed before
            if (!pressed && !current_state) {
                current_state = 1;
                if (current_state != Previous_state)
                    return 1;
            }
        }
    }

    // Reset count if button is not pressed
    is_count = false;
    Previous_state = current_state;

    // Update button state if released
    if (pressed)
        current_state = 0;
    return 0;
}
