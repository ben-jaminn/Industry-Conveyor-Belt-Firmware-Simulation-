# Industrial Conveyor Belt Firmware (Simulation)

## Project Overview
This project simulates the firmware control logic for an industrial conveyor belt system. It demonstrates **Bare-Metal C** concepts including state machine architecture, bitwise register manipulation, and non-blocking task scheduling.

## Key Features
* **Finite State Machine (FSM):** Manages system states (IDLE, RUNNING, FAULT) with safety interlocks.
* **Bitwise HAL:** Direct register manipulation using bitmasks for Motor Control, Overheat Errors, and Emergency Stops.
* **Non-Blocking Scheduler:** Uses a timer-based loop to handle status reporting without freezing CPU cycles.
* **Safety Logic:** Automated fault detection that instantly overrides motor control during error states.

## Tech Stack
* **Language:** C (C99 Standard)
* **Concepts:** Pointers, Structs, Enum, Volatile Memory, Bit-Masking.
