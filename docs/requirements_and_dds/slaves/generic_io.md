# GENERIC I/O SLAVE

## Input

**REQ-GPIO-100:** The generic I/O slave shall support direct GPIO button inputs for simple single-button use cases (e.g. foot switches) without requiring an expander IC.<br/>
**Rationale:** Allows for simple and low-cost input configurations without the need for additional hardware.<br/>
**Alternative considered:** Always using an expander IC for button inputs — rejected, would add unnecessary complexity and cost for simple use cases.

**REQ-GPIO-110:** The generic I/O slave shall support shift register button input via 74HC165 for larger button counts.<br/>
**Rationale:** Provides a scalable solution for larger button counts while keeping GPIO usage low.<br/>
**Alternative considered:** Using multiple GPIOs for each button — rejected, would quickly exhaust available GPIO pins on the ESP32-C3.<br/>
**Status:**: Deferred until project FCB1010.

**REQ-GPIO-200:** Debouncing shall be implemented in software for all button inputs, with a configurable debounce time in NVS.<br/>
**Rationale:** Ensures reliable button input without false triggers due to mechanical bounce.<br/>
**Alternative considered:** No debouncing or hardware debouncing — rejected, would lead to unreliable button inputs.

**REQ-GPIO-210:** Long press detection shall be implemented in software for all button inputs, with a configurable long press time in NVS.<br/>
**Rationale:** Allows for additional functionality based on long presses without requiring additional hardware.<br/>
**Alternative considered:** No long press detection — rejected, would limit functionality and user interaction options.

**REQ-GPIO-300:** The input slave shall support potentiometer input via ADS1115 ADC expander.<br/>
**Rationale:** Allows for continuous control via potentiometers, expanding the range of possible interactions.<br/>
**Alternative considered:** No potentiometer input support — rejected, would limit functionality and user interaction options.

**REQ-GPIO-310:** The input slave shall support Hall effect pedal input via A1324 sensor read through ADS1115.<br/>
**Rationale:** Allows for expression control via a pedal, expanding the range of possible interactions.<br/>
**Alternative considered:** No pedal input support — rejected, would limit functionality and user interaction options.

**REQ-GPIO-320:** All boolean inputs can be configured as normally open or normaly closed. This configuration is stored in NVM.<br/>
**Rationale**: Switches can have two states.
**Alternative considered:** Handled by webserver, rejected because it is input configuration.

## Output

**REQ-GPIO-400:** The generic I/O slave shall support direct GPIO outputs for simple use cases (e.g. non dimmable LEDs) without requiring an expander IC.<br/>
**Rationale:** Allows for simple and low-cost output configurations without the need for additional hardware.<br/>
**Alternative considered:** Always using an expander IC for outputs — rejected, would add unnecessary complexity and cost for simple use cases.

**REQ-GPIO-410:** The generic I/O slave shall support shift register output via 74HC595 for larger output counts.<br/>
**Rationale:** Provides a scalable solution for larger output counts while keeping GPIO usage low.<br/>
**Alternative considered:** Using multiple GPIOs for each output — rejected, would quickly exhaust available GPIO pins on the ESP32-C3.<br/>

## Communication

**REQ-GPIO-500:** The input slave shall send events to master on change — not on polling interval. Also, values are only sent when changing a minimum value (see REQ-GPIO-320).<br/>
**Rationale:** Reduces unnecessary message traffic and ensures timely updates based on actual input changes.<br/>
**Alternative considered:** Sending events on a fixed polling interval — rejected, would result in unnecessary message traffic and potential latency in event handling.

**REQ-GPIO-520:** For outputs, a message shall be defined to set a specified output of a slave to a specified value — e.g. set output 3 to 255.<br/>
**Rationale:** Provides a clear and flexible way to control outputs from the master or webserver slave.<br/>
**Alternative considered:** No defined message for setting outputs — rejected, would limit control options and require custom implementation for each output type.

# Software Organization

# Testing

# Hardware
