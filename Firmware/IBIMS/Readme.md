# 🔧 IBIMS Firmware Configuration

This directory contains the C++ source code for the ESP8266 (NodeMCU) edge node. The firmware is optimized for **Signal-to-Noise Ratio (SNR)** management and cloud telemetry resilience.

## 📍 Pinout Mapping
| Component | ESP8266 Pin | GPIO | Role |
| :--- | :--- | :--- | :--- |
| **Piezo Transducer** | A0 | ADC0 | Kinetic Impulse Detection |
| **Digital LDR** | D2 | GPIO 4 | Optical State Verification |
| **Red LED** | D0 | GPIO 16 | Inventory Occupied Indicator |
| **Green LED** | D1 | GPIO 5 | Inventory Empty Indicator |

## ⚙️ Logic Calibration
- **Placement Threshold:** Triggered at ADC values > 60.
- **Pick-up Threshold:** Triggered at ADC values > 4 (relative to baseline) + LDR High-to-Low transition.
- **Hysteresis:** A 3000ms lockout is active after every event to prevent mechanical bounce triggers.

## 🚀 Installation
1. Install the **ESP8266 Board Core** in the Arduino IDE.
2. Install the following native libraries: `ESP8266WiFi`, `ESP8266HTTPClient`, `WiFiClientSecure`.
3. Open `IBIMS.ino`.
4. Update the `ssid`, `password`, `URL` and `DeploymentID` variables.
5. Set the Upload Speed to **115200**.
