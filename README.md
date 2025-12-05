# Engineering Assistant Toolkit (v6.0)

## Project Overview
This project is a Command Line Interface (CLI) application developed in C, designed to assist electrical and electronic engineering students with common calculations and data analysis tasks.

The application utilizes a modular design pattern, separating the user interface logic from the core engineering algorithms. 

## Features
The toolkit provides a menu-driven interface with the following functionalities:

1.  **Resistor Colour Code Decoder**: Calculates resistance values based on standard 4-band colour codes, supporting unit scaling (kΩ, MΩ).
2.  **Circuit Analyser**: Solves for Voltage, Current, or Resistance using Ohm's Law, with built-in protection against division by zero.
3.  **Signal Statistics**: Calculates the Mean and Root Mean Square (RMS) values for a signal based on user-provided samples.
4.  **RC Filter Calculator**: Computes the cut-off frequency for a low-pass RC filter given resistance and capacitance values.
5.  **Parallel Resistor Calculator**: Calculates the equivalent resistance of $N$ resistors in parallel. This feature utilizes **dynamic memory allocation (`malloc`)** to handle a user-defined number of components at runtime.
6.  **Waveform Generator**: Generates time-domain data for a sine wave based on user parameters (frequency, amplitude, duration) and exports the data to a `.csv` file for external analysis (e.g., in Excel or MATLAB).

## Project Structure
* **`main.c`**: Contains the main application loop, menu display logic, and high-level program flow control.
* **`funcs.c`**: Implements the core engineering algorithms, input validation helpers, and mathematical computations.
* **`funcs.h`**: Header file defining function prototypes and interfaces to ensure modularity.
* **`Makefile`**: Build script to compile the project and link necessary libraries.

## How to Compile

### Prerequisites
* GCC Compiler
* Standard C Libraries (including `math.h`)

### Enjoy using this version! This is still a beta version; please understand if you encounter any bugs, and please report them to the developers. Thank you for using it!