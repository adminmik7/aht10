#!/usr/bin/env python3
"""AHT10 Monitor for Linux. Reads data from ESP-12E via USB Serial."""

import sys
import glob
import time
import os
import subprocess

BAUD = 115200

# ─── Auto-install dependencies ───────────────────────────
def _pip_install(package):
    print(f"[!] {package} not found, installing...")
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package, "--quiet"])
        return True
    except Exception as e:
        print(f"[✗] Failed: {e}")
        return False

try:
    import serial
except ImportError:
    if not _pip_install("pyserial"):
        sys.exit(1)
    import serial
    print("[✓] pyserial installed successfully")

# ─── Port detection ──────────────────────────────────────
def find_port():
    """Find available USB-Serial port (ESP8266/ESP32)."""
    for dev in sorted(glob.glob("/dev/ttyUSB*") + glob.glob("/dev/ttyACM*")):
        if os.path.exists(dev):
            return dev
    return None

# ─── Main ────────────────────────────────────────────────
def main():
    port = sys.argv[1] if len(sys.argv) > 1 else find_port()
    if not port:
        print("Error: No USB-Serial port found. Use: python3 monitor.py /dev/ttyUSB0")
        sys.exit(1)

    print(f"Connecting to ESP-12E on {port} @ {BAUD} baud...")
    
    try:
        with serial.Serial(port, BAUD, timeout=1) as ser:
            # Force ESP reset (DTR/RTS toggle like in Arduino IDE)
            ser.setDTR(False) 
            ser.setRTS(False)
            time.sleep(0.5)
            ser.setDTR(True) 
            ser.setRTS(True)
            time.sleep(2)  # Wait for boot
            
            ser.reset_input_buffer()
            print(f"✅ Connected! Waiting for data (Ctrl+C to stop)...\n")

            while True:
                if ser.in_waiting:
                    try:
                        line = ser.readline().decode("utf-8", errors="replace").strip()
                        if line:
                            # Simple formatting for console
                            if "Temperature" in line:
                                print(f"  🌡️  {line}")
                            else:
                                print(f"  📄  {line}")
                    except Exception as e:
                        print(f"Read error: {e}")
                
                time.sleep(0.1)

    except serial.SerialException as e:
        print(f"Serial Error: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\n👋 Stopped.")

if __name__ == "__main__":
    main()
