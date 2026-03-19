# 📦 IBIMS: IoT-Based Inventory Management System

**IBIMS** is a high-reliability **Industry 5.0** solution for real-time warehouse tracking. By using **Sensor Fusion** (Piezo + LDR), it eliminates "Ghost Inventory" caused by signal decay and mechanical noise. Features include a **Recursive Retry Protocol** for 100% cloud data integrity and a timestamped **Digital Twin** ledger via Google Cloud.

---

## 📺 Live Demonstration
![Hardware Demo](./Media/demo.gif)

*Watch the IBIMS system detect an item placement, trigger the Red Status LED, and synchronize the event to the Cloud Ledger in under 5 seconds.*

---

## 🚀 The Engineering Challenge
In industrial environments, piezoelectric sensors are prone to **Signal Decay**—where the electrical charge "leaks" over time even if an object is present. This often leads to "False Pick" errors in standard IoT racks. 

**IBIMS solves this using a Dual-Verification Gate:**
1. **Kinetic Gate:** Captures the high-frequency impulse (>95 ADC) of an item being placed.
2. **Optical Gate:** Uses an LDR to confirm physical presence, preventing state-changes caused by electronic noise or voltage drops during pick events.

---

## 🛠️ Tech Stack
* **Hardware:** ESP8266 (NodeMCU), Piezoelectric Transducer, Digital LDR.
* **Firmware:** C++ / Arduino Framework.
* **Cloud Architecture:** Google Apps Script (REST API), Google Sheets (Data Lake).
* **Protocols:** HTTPS with SSL/TLS Encryption.

---

## 🧠 Key Technical Innovations

### 1. Sensor Fusion & Temporal Hysteresis
To prevent "Double-Logging" and false triggers from mechanical bounce, I implemented a 3000ms **Software Lockout**. This allows mechanical vibrations to settle before the system returns to an "Active Listening" state.

### 2. Edge Resilience (Recursive Retry Logic)
Faced with **TCP Connection -1 Errors** (Connection Refused) during high-vibration events, I engineered an **Automatic Repeat Request (ARQ)** protocol. If the initial Cloud Sync fails, the system automatically retries 3 times with a 1000ms stabilization delay.

### 3. Power Integrity & Inrush Current Mitigation
Picking up an object causes a sudden drop in LDR resistance, creating a transient voltage dip. I resolved the resulting WiFi "brownouts" by implementing **Software-Defined Stabilization Delays** in the firmware, ensuring the SSL handshake occurs only when the power rail is stable.

---

## 📂 Repository Structure
* **`/Firmware`**: Optimized C++ source code for the ESP8266.
* **`/Cloud-Backend`**: Google Apps Script middleware for spreadsheet integration.
* **`/Documentation`**: Detailed breakdown of the **-1 Error** and **Signal Decay** solutions.
* **`/Media`**: High-resolution GIFs of hardware interaction and Cloud synchronization.

---

## 📈 Roadmap & Future Scope
* **Latency Optimization:** Migrating from HTTPS to **MQTT (Pub/Sub)** to reduce latency from ~5s to <200ms.
* **Power Management:** Implementing **Deep Sleep** modes for battery-powered, long-term deployment.
* **Scalability:** Designing a modular PCB shield for multi-rack industrial clusters.

---
**Developed by Karthik V S** *Mechanical Engineering Student | Government Engineering College, Thrissur* [LinkedIn Profile](https://www.linkedin.com/in/karthik-v-s-4335k)
