ESP32 LED Control

This is my first embedded systems project, developed during self-learning of embedded systems and real-time operating system (RTOS) principles. The project controls an LED using a button on an ESP32 microcontroller, implementing a state machine for three states: OFF, slow blink, and fast blink.

Project Overview:
Platform: ESP32 microcontroller
Language: C/C++ (Arduino framework)
Hardware: LED (connected to GPIO 5), push button (connected to GPIO 0)

Features:
  * State machine to manage LED states (OFF, slow blink, fast blink).
  * Non-blocking timing using millis() for real-time operation.
  * Button debouncing to handle input noise.
  * Clean and documented code for maintainability.

Purpose:
This project was created to:
  1. Gain hands-on experience with embedded programming and hardware interfacing.
  2. Understand real-time programming concepts, such as non-blocking execution and state management, relevant to RTOS.
