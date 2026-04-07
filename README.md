# 🌡️ aht10 - ESP-12E + AHT10 Sensor

**Latest Release:** [v1.5.0](https://github.com/adminmik7/aht10/releases/tag/v1.5.0) 🚀

Simple temperature and humidity monitor using ESP-12E (NodeMCU) and AHT10 sensor. Data is output to the Serial Console and optionally displayed on an **LCD 2004 (I2C)** screen.

## 🔌 Connection

Both the **AHT10** sensor and the **LCD 2004** (with I2C module) share the same I2C pins.

| ESP-12E (NodeMCU) | AHT10 | LCD 2004 (I2C) |
|---|---|---|
| 3V3 | VCC | VCC |
| GND | GND | GND |
| D2 (GPIO4) | SDA | SDA |
| D1 (GPIO5) | SCL | SCL |

> **Note:** Ensure your LCD module has an I2C adapter (usually a small blue board on the back). If the screen remains blank, check the I2C address in `aht10.ino` (`0x27` or `0x3F`).

## 🚀 Quick Start

1. **Install Libraries:** In Arduino IDE, install:
- `Adafruit AHTX0`
     - `Adafruit Sensor`
- `LiquidCrystal_I2C` by Frank de Brabander
2. **Upload:** Open `aht10.ino` and upload it to your ESP-12E.
3. **Monitor:** Open the Serial Monitor (Baud Rate: 9600).

## 🖥️ Output

### Serial Console
```
Temperature: 24.50 *C    Humidity: 45.20 % 
...
```

### LCD 2004 (I2C)
If you connect an I2C LCD 2004 display (address `0x27`), the device will show:

| Line | Content |
|---|---|
| 1 | `AHT10 Monitor` |
| 2 | `Temp: 24.5 C` |
| 3 | `Humidity: 45.2 %` |
| 4 | (Empty) |

> **Note:** If the screen stays black, try changing the I2C address in `aht10.ino` from `0x27` to `0x3F`.

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
   ./start.sh                     # auto-detect port (115200 baud)
   ./start.sh /dev/ttyUSB0        # specific port
   ./start.sh /dev/ttyUSB0 74880  # custom baud rate
   ```
   > Скрипт `start.sh` сам проверит наличие Python3, установит `pyserial` и запустит монитор.

   **Or manually:**
   ```bash
   python3 monitor.py /dev/ttyUSB0 74880  # port and speed
   ```

## 🧠 How it Works

1. **ESP-12E (NodeMCU)** continuously reads data from the AHT10 sensor via I2C.
2. Data is formatted as a text string (e.g., `Temperature: 24.5 *C`) and sent via USB.
3. **monitor.py** on your Linux PC detects the USB port, opens it, and displays the data in real-time.

## ❓ Troubleshooting

| Problem | Solution |
|---|---|
| **No data in console** | Ensure you uploaded the latest code to ESP. Try `./start.sh /dev/ttyUSB0 9600`. |
| **"Port not found"** | Check connection: `ls /dev/ttyUSB*`. Try a different USB cable. |
| **Garbage characters** | Wrong baud rate. Try 74880 or 115200 as an argument: `./start.sh /dev/ttyUSB0 74880`. |
| **Permission denied** | Add your user to the dialout group: `sudo usermod -a -G dialout $USER`. |

## 📦 Files

- `aht10.ino` - Main firmware for ESP-12E.
- `monitor.py` - Python script to read data on Linux.
- `start.sh` - All-in-one setup and launch script.
- `CHANGELOG.md` - Full history of project updates.
