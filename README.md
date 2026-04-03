# 🌡️ aht10 — ESP-12E + AHT10 Sensor

Simple temperature and humidity monitor using ESP-12E (NodeMCU) and AHT10 sensor. Data is output to the Serial Console.

## 🔌 Connection

| ESP-12E (NodeMCU) | AHT10 |
|---|---|
| 3V3 | VCC |
| GND | GND |
| D2 (GPIO4) | SDA |
| D1 (GPIO5) | SCL |

> **Note:** AHT10 uses I2C communication. Make sure to use pull-up resistors if your module doesn't have them built-in (though most AHT10 breakout boards do).

## 🚀 Quick Start

1. **Install Libraries:** In Arduino IDE, install:
   - `Adafruit AHTX0`
   - `Adafruit Sensor`
2. **Upload:** Open `aht10.ino` and upload it to your ESP-12E.
3. **Monitor:** Open the Serial Monitor (Baud Rate: 115200).

## 🖥️ Console Output

```
Temperature: 24.50 *C    Humidity: 45.20 %
Temperature: 24.52 *C    Humidity: 45.15 %
...
```

## 📥 Installation & Download

### Download Files
You can download the project using Git:
```bash
git clone https://github.com/adminmik7/aht10.git
cd aht10
```
Or download the ZIP archive from the [Releases page](https://github.com/adminmik7/aht10/releases).

## 🖥️ PC Monitor (Linux)

You can use `monitor.py` to read data on your Linux computer.

1. **Install dependencies:**
   ```bash
   pip3 install pyserial
   ```
2. **Run (Recommended):**
   ```bash
   chmod +x start.sh
   ./start.sh              # auto-detect port
   ./start.sh /dev/ttyUSB0 # specific port
   ```
   > Скрипт `start.sh` сам проверит наличие Python3, установит `pyserial` и запустит монитор.

   **Or manually:**
   ```bash
   python3 monitor.py
   ```

## 📦 Files

- `aht10.ino` — Main firmware for ESP-12E.
- `monitor.py` — Python script to read data on Linux.
