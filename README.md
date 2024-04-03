**Keyboard and Backlight Controller**

This Arduino project creates a customizable keyboard controller and backlight manager for F-keys (F13-F18). It offers features like:

- **Function Key Mapping:** Assign custom actions to F-keys for convenient control.
- **Brightness Adjustment:** Adjust the backlight intensity using dedicated buttons.
- **Permanent Backlight:** Toggle a permanent backlight mode independent of button presses.
- **Debouncing:** Ensures reliable button presses by ignoring rapid fluctuations.
- **Safety Check:** Detects a grounded RX pin (pin #1) to prevent unintended keyboard interference.

**Hardware Requirements**

- Arduino board (any model)
- 6 pushbuttons for function and mode control
- LEDs (quantity depends on desired backlight configuration)
- (Optional) Resistors (if using LEDs without built-in resistors)

**Software Requirements**

- Arduino IDE ([https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE))
- Keyboard library ([https://github.com/arduino-libraries/Keyboard](https://github.com/arduino-libraries/Keyboard))

**Connections**

1. Connect pushbuttons to pins `BUTTON_PIN1` to `BUTTON_PIN6` (pins 2-7 in your code).
2. Connect LEDs for backlight to `LED_BACKLIGHT` (pin 9).
3. If using separate LEDs and resistors, connect resistors appropriately based on LED voltage and current requirements.
4. Connect a wire to ground (GND) if using a safety check (optional).

**Installation**

1. Download the Keyboard library from [https://github.com/arduino-libraries/Keyboard](https://github.com/arduino-libraries/Keyboard) and install it in your Arduino IDE library manager.
2. Download or copy the code provided in this README.md.
3. Open the Arduino IDE and create a new sketch.
4. Paste the code into the sketch.
5. Connect your Arduino board to your computer.
6. Select the appropriate board and serial port in the Arduino IDE.
7. Upload the code to your Arduino board.

**Usage**

- Press function buttons (F-keys) to trigger their assigned actions.
- Press the brightness button to adjust backlight intensity (multiple presses might be needed).
- Press the light style button to toggle between temporary (activated on button press) and permanent backlight modes.

**Customization**

- Modify the `BUTTON_KEYx` definitions (lines 4-9) to map F-keys to different keyboard shortcuts or actions using the Keyboard library functions (refer to the library documentation for available functions).
- Adjust the `brightness_step` value (line 18) to control the brightness change per button press.
- Change the `number_steps_of_brightness` value (line 17) to modify the total number of brightness levels.

**Code Breakdown**

The code is well-structured, with clear function definitions and comments explaining key sections. Here's a brief overview:

- **`failsafe()`:** Handles safety check by halting program execution if RX pin is grounded.
- **`light_background(boolean state)`:** Controls backlight based on button press state and permanent light mode.
- **`change_brightness()`:** Increases backlight brightness within limits.
- **`toggle_permanent_light()`:** Switches between temporary and permanent backlight modes.
- **`btn` class:** Base class for buttons, providing pin handling and basic press detection.
- **`function_btn` class:** Extends `btn` for F-key buttons, handling debouncing and sending keyboard presses/releases.
- **`mode_btn` class:** Extends `btn` for mode buttons (brightness and light style), handling debouncing and mode-specific actions.
- **`setup()`:** Initializes pins, LEDs, and debounce timer.
- **`loop()`:** Continuously scans function and mode buttons for presses, updating their states.

**Additional Notes**

- Consider adding comments within the code to further enhance readability and maintainability.
- Explore advanced features of the Keyboard library for more complex keyboard actions.
- Experiment with different backlight configurations (single LED, multiple LEDs) based on your hardware setup.
