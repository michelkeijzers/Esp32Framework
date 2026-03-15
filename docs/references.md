# REFERENCES

<!-- TOC tocDepth:2..3 chapterDepth:2..6 -->
<!-- /TOC -->

# Role Summary

| Role             | Wi-Fi        | Watchdog             | Heartbeat | Webserver | OTA | Common      |
| ---------------- | ------------ | -------------------- | --------- | --------- | --- | ----------- |
| `ROLE_MASTER`    | ESP-NOW only | Own cluster + remote | —         | —         | —   | Always      |
| `ROLE_REMOTE`    | ESP-NOW only | Own cluster          | To master | —         | —   | Always      |
| `ROLE_SLAVE`     | ESP-NOW only | —                    | To master | —         | —   | Always      |
| `ROLE_WEBSERVER` | AP or router | —                    | To master | Yes       | Yes | Per project |

# Antenna Reference

| Role           | Variant | Antenna        |
| -------------- | ------- | -------------- |
| ROLE_MASTER    | U.FL    | FPC flexible   |
| ROLE_REMOTE    | U.FL    | FPC flexible   |
| ROLE_WEBSERVER | U.FL    | FPC flexible   |
| ROLE_SLAVE     | PCB     | Built-in trace |
| OSC slave      | U.FL    | FPC flexible   |

Note: Slaves in metal enclosures may require U.FL + FPC — OTA proxy via ESP-NOW is the preferred long term solution for these cases.

# OTA Reference

| Approach              | Applies to      | Wi-Fi on slave  | Status            |
| --------------------- | --------------- | --------------- | ----------------- |
| USB cable via idf.py  | All ESPs        | No              | Always available  |
| Wi-Fi OTA             | Webserver slave | Yes (own Wi-Fi) | Implemented       |
| Temporary Wi-Fi OTA   | Slaves          | Yes (temporary) | To be implemented |
| OTA proxy via ESP-NOW | Slaves          | No              | Deferred          |

## OTA Proxy — ESP-NOW Chunk Protocol

```
Webserver downloads firmware binary (~500KB) to LittleFS via Wi-Fi
Webserver calculates CRC32 of full binary
Webserver sends MSG_OTA_START to master → routed to target slave
  payload: total_chunks, total_size, binary_crc32, firmware_version

Slave receives MSG_OTA_START
Slave sends MSG_OTA_STARTED to master
Slave opens second flash partition for writing

For each chunk:
  Webserver sends MSG_OTA_CHUNK
    payload: chunk_index, total_chunks, chunk_size, chunk_crc16, data[200]
  Slave receives chunk
  Slave verifies chunk_crc16 — mismatch → sends NACK → webserver resends
  Slave writes chunk to flash partition
  Slave sends ACK with chunk_index

Webserver receives last ACK
Webserver sends MSG_OTA_COMPLETE

Slave verifies full binary CRC32
  Mismatch → abort → rollback to previous partition → notify master
  Match → reboot into new partition
  Failed boot → automatic rollback via ESP-IDF bootloader
```

Estimated transfer time: 30-60 seconds for ~500KB binary at ~2500 chunks.

## Message Structure

```c
typedef struct {
    uint8_t  msg_type;      // message type identifier
    uint8_t  version;       // protocol version
    uint16_t sequence;      // sequence number — detect lost/duplicate
    uint16_t crc16;         // CRC16 of full message including payload
    uint8_t  payload[];     // message specific data
} espnow_msg_t;
```

CRC functions from ESP-IDF — no external library needed:

```
include "esp_crc.h"
include "esp_crc.h"
include "esp_crc.h"
include "esp_crc.h"

uint16_t crc = esp_crc16_le(0, data, length); // per message, per chunk
uint32_t crc = esp_crc32_le(0, data, length); // full OTA binary
```

# Slave Hardware

## UART — pick one per slave

| Define             | Hardware           | Baud     |
| ------------------ | ------------------ | -------- |
| `SLAVE_UART_MIDI`  | 6N138, 220R, DIN-5 | 31250    |
| `SLAVE_UART_DMX`   | MAX3485, XLR, 120R | 250000   |
| `SLAVE_UART_CO2`   | MH-Z19             | 9600     |
| `SLAVE_UART_GPS`   | NEO-6M             | 9600     |
| `SLAVE_UART_RS232` | MAX3232            | variable |
| `SLAVE_UART_PZEM`  | PZEM-004T          | 9600     |

## I2C — any combination

| Define                   | IC       | Address   |
| ------------------------ | -------- | --------- |
| `SLAVE_I2C_DISPLAY_LCD`  | PCF8574  | 0x27/0x3F |
| `SLAVE_I2C_DISPLAY_TM`   | TM1637   | GPIO      |
| `SLAVE_I2C_DISPLAY_TM38` | TM1638   | GPIO      |
| `SLAVE_I2C_DISPLAY_OLED` | SSD1306  | 0x3C      |
| `SLAVE_I2C_MCP23017`     | MCP23017 | 0x20      |
| `SLAVE_I2C_ADS1115`      | ADS1115  | 0x48/0x49 |
| `SLAVE_I2C_PCA9685`      | PCA9685  | 0x40+     |
| `SLAVE_I2C_SHT31`        | SHT31    | 0x44      |
| `SLAVE_I2C_BH1750`       | BH1750   | 0x23      |
| `SLAVE_I2C_VL53L0X`      | VL53L0X  | 0x29      |
| `SLAVE_I2C_DS3231`       | DS3231   | 0x68      |
| `SLAVE_I2C_INA219`       | INA219   | 0x40      |

## SPI, RMT, GPIO

| Define                | Hardware                  | Max                     |
| --------------------- | ------------------------- | ----------------------- |
| `SLAVE_SPI_595`       | 74HC595 + ULN2803         | 128 outputs (16 ICs)    |
| `SLAVE_SPI_165`       | 74HC165                   | 64 inputs (8 ICs)       |
| `SLAVE_SPI_MAX7219`   | MAX7219                   | 128 outputs (2 ICs)     |
| `SLAVE_RMT_WS2812`    | WS2812B / WS2813 / SK6812 | 2 strips, 600 LEDs each |
| `SLAVE_GPIO_ENCODERS` | Direct GPIO + interrupt   | 2 encoders              |
| `SLAVE_GPIO_PIR`      | HC-SR501 / RCWL-0516      | 1 pin                   |
| `SLAVE_GPIO_IR_RECV`  | TSOP38238                 | 1 pin                   |
| `SLAVE_GPIO_IR_SEND`  | TSAL6200                  | 1 pin                   |
| `SLAVE_GPIO_AUDIO`    | MCP6004 + ADS1115         | 4 bands                 |

## MAX7219 Brightness Reference

| RSET   | Current per output | Brightness                     |
| ------ | ------------------ | ------------------------------ |
| 47kΩ   | ~3mA               | Dim                            |
| 20kΩ   | ~7mA               | Medium                         |
| 9.53kΩ | ~10mA              | Bright                         |
| 4.7kΩ  | ~20mA              | Very bright                    |
| 3.3kΩ  | ~25mA              | Maximum (safe practical limit) |

Maximum absolute per datasheet: 40mA — do not exceed 25mA in practice.
TM1637 brightness: software controlled via `tm1637_set_brightness(0-7)`.

# Project Structure

```

project/
main/
main.c ← app_main, role selection via #ifdef
CMakeLists.txt
sdkconfig.defaults ← CONFIG_FREERTOS_HZ=1000, flash size, CPU freq
partitions.csv ← dual partition layout for all roles
components/
common/
espnow/
watchdog/
messages/
nvs/
master/
routing.c/h
webserver/
webserver.c
ota.c
littlefs.c
slaves/
dmx/
display/
tm1637/
max7219/
input/
gpio/
hc165/
a1324/
midi/
audio/
osc/
sensor/
led/
ws2812/

```

# Latency Reference

| Path                               | Latency | Notes                              |
| ---------------------------------- | ------- | ---------------------------------- |
| Button → webserver                 | ~8ms    | Input slave → master → webserver   |
| Webserver → DMX                    | ~5ms    | Webserver → master → DMX slave     |
| Button → DMX (full chain)          | ~31ms   | Includes 22ms DMX frame            |
| MIDI note → OSC UDP                | ~6ms    | Direct routing, bypasses webserver |
| MIDI note → webserver (monitoring) | ~6ms    | Parallel copy, non-blocking        |

# Power Reference

| Project        | Total current | Recommended PSU | Headroom |
| -------------- | ------------- | --------------- | -------- |
| DMX Controller | ~491mA        | 5V 2A           | ~1509mA  |
| FCB1010        | ~710mA        | 5V 2A           | ~1290mA  |

Note: DMX fixtures and LED strips are powered by their own PSUs — not included above.
