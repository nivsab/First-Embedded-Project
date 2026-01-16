# STM32 Bare Metal GPIO Driver & LED State Machine

This project demonstrates a custom, **Bare Metal C++** implementation of a GPIO driver for STM32 microcontrollers. It features a complete hardware abstraction layer (HAL) written from scratch without relying on vendor libraries (like HAL or LL), and implements a robust State Machine application.

## 🚀 Key Features

* **Custom GPIO Driver (OOP):** Object-Oriented driver providing direct register access.
    * Full configuration control: Clock Enable, Mode, Output Type, Speed, and Pull-Up/Down resistors.
    * **Direct Register Manipulation:** Efficient control of `ODR` (Output) and `IDR` (Input) registers using standard bitwise operators (`|=`, `&= ~`) for Read-Modify-Write logic.
* **Finite State Machine (FSM):** Structured logic controlling system states (`OFF` -> `ON` -> `BLINK`).
* **Software Debouncing:** Robust input handling mechanism including **Falling Edge Detection** and signal stabilization delays to filter mechanical switch noise.
* **Non-Blocking Logic:** The "Blink" state is implemented using a cycle-counter approach, ensuring the main loop remains responsive to button presses at all times (no blocking `delay` inside logic states).

## 🛠️ Hardware Configuration

The code is configured for standard **STM32 Nucleo** pinouts but is portable to other boards.

| Component | Pin | Configuration | Logic |
| :--- | :--- | :--- | :--- |
| **User LED** | `PA5` | Output (Push-Pull) | Active High |
| **User Button** | `PC13`| Input | **Internal Pull-Up** (Active Low) |

## 💡 System Logic & Flow

The application runs inside an infinite `while(1)` loop handling two main tasks:

1.  **Input Processing:**
    * Polls the button state.
    * Detects a **Falling Edge** (Transition from `1` to `0`).
    * Applies a debounce delay and re-verifies the state.
    * Triggers a state transition upon valid press.

2.  **State Execution:**
    * **STATE_OFF:** LED is driven low.
    * **STATE_ON:** LED is driven high.
    * **STATE_BLINK:** LED toggles at a fixed interval without blocking the CPU.

## 📂 File Structure

* `GpioDriver.h` / `GpioDriver.cpp`: The driver class implementation. Handles all direct register manipulation (RCC, MODER, ODR, IDR, etc.).
* `main.cpp`: System initialization, State Machine logic, and main application loop.

---

### 👨‍💻 Author
Developed as part of a Low-Level Embedded Systems portfolio, demonstrating proficiency in Register-Level programming and C++.
