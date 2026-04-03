# 🌡️ aht10 — ESP-12E + AHT10 Sensor

**Latest Release:** [v1.4.0](https://github.com/adminmik7/aht10/releases/tag/v1.4.0) 🚀

Simple temperature and humidity monitor using ESP-12E (NodeMCU) and AHT10 sensor. Data is output to the Serial Console.

## 🔌 Connection

| ESP-12E (NodeMCU) | AHT10 |
|---|---|
| 3V3 | VCC |
| GND | GND |
| D2 (GPIO4) | SDA |
| D1 (GPIO5) | SCL |

> **Note:** AHT10 uses I2C communication. Make sure to use pull-up resistors if your module doesn't have them built-in (though most AHT10 breakout boards do).

## 🚀 Quick Start (Wi-Fi & MQTT Mode)

1. **Install Libraries:** In Arduino IDE, install:
   - `Adafruit AHTX0`
   - `Adafruit Sensor`
   - `PubSubClient` (by Nick O'Leary)
   - `ArduinoJson` (by Benoit Blanchon)

2. **Configure:** Open `aht10.ino` and fill in your details:
   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASS";
   const char* mqtt_server = "192.168.0.67"; // Your HA IP
   ```

3. **Upload & Enjoy:** Flash the code. Home Assistant will automatically discover the sensor via MQTT! 🏠

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

- `aht10.ino` — Main firmware for ESP-12E.
- `monitor.py` — Python script to read data on Linux.
- `start.sh` — All-in-one setup and launch script.
- `CHANGELOG.md` — Full history of project updates.
