# Retro Computer for Arduino Nano Every

This project turns an Arduino Nano Every into a retro-style computer, complete
 with a command-line interface (CLI) and a feature-rich BASIC interpreter. You
 can interact with the computer through the Arduino IDE's serial monitor.

## Features

*   **Command-Line Interface**: A simple CLI for interacting with the system.
*   **BASIC Interpreter**: A powerful BASIC interpreter based on Sinclair BASIC,
 with support for variables, arrays, loops, and more.
*   **GPIO Access**: Control the Arduino's pins directly from the CLI or from w
ithin the BASIC interpreter.

## Setup

1.  **Install the Arduino IDE**: If you don't have it already, download and ins
tall the Arduino IDE from the [official website](https://www.arduino.cc/en/soft
ware).
2.  **Configure for Arduino Nano Every**: In the Arduino IDE, go to **Tools > B
oard** and select **Arduino Nano Every**.
3.  **Open the Project**: Download this project as a ZIP file and unzip it. Ope
n the `RetroComputer.ino` file in the Arduino IDE.

    *Note on Project Structure:* This is a multi-file Arduino project. When you
 open `RetroComputer.ino`, the Arduino IDE should automatically open the other
 `.h` and `.cpp` files in tabs. This is the standard way to organize larger Ardu
ino sketches and makes the code easier to navigate and maintain.
4.  **Upload the Code**: Connect your Arduino Nano Every to your computer and u
pload the sketch.

## Usage

Once the code is uploaded, open the Serial Monitor (**Tools > Serial Monitor**)
 with the baud rate set to 9600. You should see the welcome message and the CLI
 prompt `>`.

### Command-Line Interface

The following commands are available in the main CLI:

*   `HELP`: Show a list of available commands.
*   `CLEAR`: Clear the serial monitor screen.
*   `BASIC`: Enter the BASIC interpreter.
*   `PINMODE <pin> <mode>`: Set a pin to a specific mode.
    *   `<pin>`: The pin number.
    *   `<mode>`: `0` for `INPUT`, `1` for `OUTPUT`, `2` for `INPUT_PULLUP`.
*   `DOUT <pin> <value>`: Write a digital value to a pin.
    *   `<pin>`: The pin number.
    *   `<value>`: `0` for `LOW`, `1` for `HIGH`.
*   `DIN <pin>`: Read the digital value from a pin.
*   `AOUT <pin> <value>`: Write an analog value (PWM) to a pin.
*   `AIN <pin>`: Read the analog value from a pin.

### BASIC Interpreter

To enter the BASIC interpreter, type `BASIC` in the main CLI. You will see a we
lcome message for the BASIC interpreter. You can type `EXIT` to leave the inter
preter and return to the main CLI.

The BASIC interpreter is very powerful. Here are some of the things you can do:

*   **Standard BASIC commands**: `PRINT`, `LET`, `IF`, `THEN`, `FOR`, `NEXT`, `G
OTO`, `GOSUB`, `RETURN`, `REM`, `STOP`, `CONT`, `NEW`, `LIST`, `RUN`.
*   **Variables and Arrays**: Support for numeric and string variables, and mul
ti-dimensional arrays (`DIM`).
*   **GPIO Access**: You can control the pins from within BASIC:
    *   `PIN <pin>, <state>`
    *   `PINMODE <pin>, <mode>`
    *   `PINREAD(<pin>)`
    *   `ANALOGRD(<pin>)`
*   **File Storage**: `SAVE` and `LOAD` programs to and from the Arduino's inte
rnal EEPROM.

For a full list of commands and functions, please refer to the source code and
 the documentation of the original `ArduinoBASIC` project.

## Credits

This project would not have been possible without the excellent `ArduinoBASIC`
 interpreter created by Robin Edwards. You can find the original project [here]
(https://github.com/robinhedwards/ArduinoBASIC).
