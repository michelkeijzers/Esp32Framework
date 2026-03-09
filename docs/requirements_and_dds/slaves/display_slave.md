# Display Slave

**REQ-DISP-100:** The display slave shall support LEDs directly driven via a GPIO.<br/>
**Rationale:** Allows for simple and low-cost display configurations without the need for additional hardware.<br/>
**Alternative considered:** Always using a display driver IC — rejected, would add unnecessary complexity and cost for simple use cases.

**REQ-DISP-110:** The display slave shall support LEDs driven by shift register (74HC595) for larger LED counts.<br/>
**Rationale:** Provides a scalable solution for larger LED counts while keeping GPIO usage low.<br/>
**Alternative considered:** Using multiple GPIOs for each LED — rejected, would quickly exhaust available GPIO pins on the ESP32-C3.<br/>

**REQ-DISP-120:** The display slave shall support LED matrix displays driven by MAX7219 via SPI.<br/>
**Rationale:** Allows for more complex display options while keeping GPIO usage low.<br/>
**Alternative considered:** Using GPIOs for each LED in the matrix — rejected, would exhaust available GPIO pins and be impractical.<br/>

**REQ-DISP-130:** The display slave shall support 7 (or 8) segment LEDs driven without a driver IC.<br/>
**Rationale:** Many 7-segment LED modules are designed to be driven directly without a driver IC, allowing for simple and low-cost display options.<br/>
**Alternative considered:** -

**REQ-DISP-140:** The display slave shall support seven (or 8) segment displays driven by a TM1637 driver ic.<br/>
**Rationale:** Typical way of driving seven segment displays.<br/>
**Alternatives considered:** -

**REQ-DISP-150:** The display slave shall support LEDs driven by a TM1637 or TM1638 via a 4-wire serial interface.<br/>
**Rationale:** Provides a common and widely available display option with minimal GPIO usage.<br/>
**Alternative considered:** Using GPIOs for each LED — rejected, would exhaust available GPIO pins and be impractical.<br/>

**REQ-DISP-160:** The display slave shall support LCD character displays driven by PCF8574 via I2C.<br/>
**Rationale:** Provides a common and widely available display option with minimal GPIO usage.<br/>
**Alternative considered:** Using GPIOs for LCD control — rejected, would exhaust available GPIO pins and be impractical.<br/>

**REQ-DISP-170:** The display slave shall support OLED displays driven by SSD1306 via I2C.<br/>
**Rationale:** Provides a common and widely available display option with minimal GPIO usage and more advanced display capabilities.<br/>
**Alternative considered:** Using GPIOs for OLED control — rejected, would exhaust available GPIO pins and be impractical.<br/>

**REQ-DISP-200:** The display slave shall support PWM for LED controlling.<br/>
**Rationale:** Allows for brightness control of LEDs, expanding the range of possible display effects.<br/>
**Alternative considered:** No PWM support — rejected, would limit display capabilities and effects.

\*\*# Software Organization

# Testing

# Hardware
