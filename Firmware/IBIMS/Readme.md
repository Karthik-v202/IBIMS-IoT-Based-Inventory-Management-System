# 🔧 IBIMS Firmware Configuration (Digital Twin Edition)

This directory contains the upgraded C++ source code for the ESP8266 (NodeMCU) edge node. As demonstrated in `WhatsApp Video 2026-03-27 at 10.29.01 PM.mp4`, the firmware has been updated to support real-time **3D Digital Twin Synchronization** alongside Signal-to-Noise Ratio (SNR) management and cloud telemetry resilience.

## 📍 Pinout Mapping
| Component | ESP8266 Pin | GPIO | Role |
| :--- | :--- | :--- | :--- |
| **Piezo Transducer** | A0 | ADC0 | Kinetic Impulse Detection |
| **Digital LDR** | D2 | GPIO 4 | Optical State Verification |
| **Red LED** | D0 | GPIO 16 | Inventory Empty / Absent Indicator |
| **Green LED** | D1 | GPIO 5 | Inventory Item Present Indicator |

## ⚙️ Logic & Digital Twin Calibration
- **Placement Threshold:** Triggered at ADC values > 60. As shown in `demo`, placing an item onto the physical structure instantly illuminates the **Green LED** and updates the Web Dashboard state to **ITEM PRESENT**, rendering the item on the 3D model canvas.
- **Pick-up Threshold:** Triggered at ADC values > 4 (relative to baseline) + LDR High-to-Low transition. This action clears the object from the 3D canvas, reverts the dashboard status to **EMPTY / ABSENT**, and illuminates the **Red LED**.
- **Hysteresis:** A 3000ms lockout is active after every event to prevent mechanical bounce triggers from sending duplicate telemetry to the web application.

## 🚀 Installation
1. Install the **ESP8266 Board Core** in the Arduino IDE.
2. Install the following native libraries required for backend updates: `ESP8266WiFi`, `ESP8266HTTPClient`, `WiFiClientSecure`.
3. Open `IBIMS.ino`.
4. Update the `ssid`, `password`, `URL` (Your Digital Twin API endpoint), and `DeploymentID` variables.
5. Set the Upload Speed to **115200**.
