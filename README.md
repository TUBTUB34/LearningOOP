# LearningOOP - ELEX4618 Labs

This repository contains labs, assignments, and projects completed in **ELEX4618**, focusing on Object-Oriented Programming (OOP) principles and applications in C++. Each lab demonstrates practical programming skills, including graphics, games, hardware communication, and more.

# Update
#### Since i updated opencv to the latest version, this code does not work. you will need opencv 3.14 

# Table of Contents
- [Project Overview](#project-overview)
- [Installation and Setup](#installation-and-setup)
- [Labs and Projects](#labs-and-projects)
  - [Lab 4: Etch-A-Sketch](#lab-4-etch-a-sketch)
  - [Lab 5: Pong Game](#lab-5-pong-game)
  - [Lab 6: Classic Arcade Game Simulation](#lab-6-classic-arcade-game-simulation)
- [Dependencies](#dependencies)
- [License](#license)

[![View Documentation](https://img.shields.io/badge/View%20Documentation-blue)](https://github.com/yourusername/LearningOOP)

## Project Overview
This repository serves as a record of labs and exercises to apply and solidify my understanding of OOP concepts. Each lab builds upon C++ fundamentals and introduces new topics like real-time graphics, multithreading, serial communication, and basic client-server networking. Labs primarily use the **Tiva BoosterPack Joystick** as the input device.

## Installation and Setup
1. **Clone the repository**:
   ```bash
   git clone https://github.com/TUBTUB34/LearningOOP.git
   cd LearningOOP
2. **Install dependencies**
   Make sure you have OpenCV and other necessary libraries installed
   
3. **Build the project**
   Use your preferred C++ IDE or a compiler like g++ to compile and link the project files.
   
# Labs and Projects
Each lab is accessible from the main menu. Here’s a summary of the available labs and projects:

## Lab 4: Etch-A-Sketch
**Description:**
A digital "Etch-A-Sketch" drawing program controlled by the Tiva BoosterPack Joystick, simulating an Etch-A-Sketch experience. This lab demonstrates basic graphics and user interaction using OpenCV.

Key Files: CSketch.h, CSketch.cpp

## Lab 5: Pong Game
**Description:**
A classic Pong game built with OpenCV. The game is controlled using the Tiva BoosterPack Joystick, allowing movement for paddle control. This lab explores basic game development concepts, multithreading, and real-time graphics rendering in C++.

Key Files: CPong.h, CPong.cpp, CPaddle.h, CPaddle.cpp, CBall.h, CBall.cpp

## Lab 6: Classic Arcade Game Simulation
**Description:** 
A simple simulation of an arcade game using the Tiva BoosterPack Joystick for input. This lab focuses on user interaction, control structures, and basic game mechanics.

## Dependencies
- C++ Compiler: Compatible with C++11 or higher
- OpenCV: Required for graphics and image processing
- Windows Libraries: Certain labs depend on Windows-specific libraries (e.g., Serial communication).
- Other libraries: Ensure libraries for threading and networking (e.g., Winsock2) are installed as needed.

## License
This project is for educational purposes. You are welcome to use and modify it.
