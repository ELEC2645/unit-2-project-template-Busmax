# Engineering Assistant Toolkit (v7.0)

## Project Overview
**Engineering Assistant Toolkit** is a comprehensive software solution designed to assist electrical and electronic engineering students with common calculations and data analysis tasks. 

The project adopts a **Hybrid Programming Architecture**, leveraging the performance and precision of **C** for backend algorithms and the versatility of **Python** for a modern Graphical User Interface (GUI). This approach demonstrates industry-standard practices in software modularity and cross-language interoperability.

## Key Features

### Core Engineering Modules (C-Backend)
The application core is built in C for efficiency and robustness, providing the following functionalities:

1.  **Resistor Colour Code Decoder**: Deciphers standard 4-band resistor codes with automatic unit scaling (kΩ, MΩ).
2.  **Circuit Analyser**: A robust Ohm's Law solver for Voltage, Current, and Resistance, featuring error handling for division by zero.
3.  **Signal Statistics Engine**: Performs statistical analysis on datasets to calculate Mean and Root Mean Square (RMS) values, essential for signal processing.
4.  **RC Filter Calculator**: Computes the cut-off frequency for low-pass RC filters.
5.  **Parallel Resistor Calculator**: Solves for the total resistance of $N$ parallel components using **dynamic memory allocation (`malloc`)**, allowing for runtime-defined circuit complexity.
6.  **Waveform Generator**: Simulates a signal generator, calculating time-domain sine wave data and exporting it to CSV format for external analysis.

### Advanced Features
* **System Self-Diagnostic**: An integrated unit-testing module that verifies mathematical logic, memory allocation safety, and file system permissions at runtime.
* **Hybrid GUI (Python)**: A user-friendly desktop interface built with `tkinter`, which dynamically loads the C library (`.dll`/`.so`) to perform calculations.
* **Data Visualization**: Integrated plotting using `matplotlib` to visualize generated waveforms directly within the application.

## Project Structure
* **`main.c`**: The CLI Presentation Layer. Handles the command-line menu interface and user input validation.
* **`funcs.c` / `funcs.h`**: The Logic Layer. Contains all engineering algorithms and exposed API functions.
* **`app.py`**: The GUI Presentation Layer (Python). Interfaces with the compiled C shared library.
* **`libeng.dll` / `libeng.so`**: The compiled shared object serving as the bridge between C and Python.
* **`Makefile`**: Automation script for compiling the project.

## Installation & Usage Guide

### Prerequisites
* GCC Compiler (MinGW for Windows, or standard GCC for Linux/Mac).
* Python 3.x with `matplotlib` and `numpy` installed.

### Option 1: Command Line Interface (CLI)
To run the traditional text-based interface:

1.  Compile the project:
    ```bash
    make
    # OR manually: gcc main.c funcs.c -o main.out -lm
    ```
2.  Run the executable:
    ```bash
    ./main.out
    ```

### Option 2: Graphical User Interface (GUI)
To experience the modern desktop application:

1.  Compile the C code into a shared library:
    * **Windows**: `gcc -shared -o libeng.dll funcs.c -fPIC -lm`

2.  Run the Python app:
    ```bash
    python app.py
    ```

## Testing
A shell script `test.sh` is provided for automated build verification. Additionally, the application includes a built-in **Self-Diagnostic** tool (Option 7 in CLI) to validate internal logic.

## References
* Standard C Library documentation.
* *ELEC2645 Unit 2 Application Ideas* 
### Enjoy using this version! This is still a beta version; please understand if you encounter any bugs, and please report them to the developers. Thank you for using it!