# 📦 IBIMS V2: IoT-Based Real-Time Inventory Management System

**IBIMS V2** is an ultra-reliable, industrial-grade **Industry 5.0** cyber-physical system designed for real-time asset tracking. By merging hardware telemetry with a **Sensor Fusion Dual-Verification Gate** (Piezoelectric + LDR), it completely eliminates the issue of "Ghost Inventory" caused by signal decay and localized mechanical noise. 

Version 2 upgrades the architecture from a simple transactional logger to a fully synchronized, low-latency **Digital Twin Shadow Model** protected by a non-blocking network connection watchdog.

---

## 📺 Live Demonstration
<p align="center">
  <img src="Media/DemoV2gif" width="45%" alt="Hardware Demo V2" />
</p>

*Watch the IBIMS system detect an item placement, trigger the physical state indicators, and synchronize the event to the Cloud-hosted Digital Twin Ledger in real time.*

---

## 🚀 The Engineering Challenge
In dense industrial warehousing, piezoelectric sensors are highly prone to **Signal Decay**—where the generated electrical charge "leaks" away over time even if an object remains physically seated on the sensor. This leakage historically causes standard edge nodes to register a "False Pick" error. 

**IBIMS V2 solves this using a deterministic Dual-Verification State Machine:**
1. **Kinetic Gate:** Captures the high-frequency voltage impulse (>95 ADC) generated during the mechanical impact of an item being placed.
2. **Optical Gate:** Employs a stabilized LDR to continuously verify physical presence, blocking unauthorized state-changes triggered by transient electrical noise, voltage drops, or long-term signal decay.

---

## 🛠️ Tech Stack & Architecture
* **Edge Hardware:** ESP8266 (NodeMCU), High-Sensitivity Piezoelectric Transducer, Digital LDR Gate.
* **Firmware Framework:** Embedded C++ / Arduino Core (Built with non-blocking state loops).
* **Cloud Infrastructure:** Google Apps Script Execution Engine (REST API Gateway), Google Sheets (Dual-Engine: Live Digital Twin Shadow + Historic Data Lake Log).
* **Communication Security:** HTTPS with TLS/SSL Encryption.

---

## 🧠 Key Technical Innovations (V2 Upgrades)

### 1. Real-Time Digital Twin Shadowing
Unlike traditional batch-logging IoT nodes, V2 implements a localized physical state machine (`SYSTEM_EMPTY` vs. `SYSTEM_OCCUPIED`). Any state transition on the physical rack instantly streams to the cloud backend, overwriting a dedicated tracking row to maintain a perfect 1:1 virtual twin of the warehouse layout.

### 2. Connection-Time Watchdog Protocol
To handle the unpredictable wireless environments of factories, the firmware incorporates a non-blocking **Hardware/Software Watchdog Protocol**. If an SSL handshake hangs or a network drop occurs, the system monitors connection duration. If it exceeds a strict 10-second timeout window, the system automatically forces a network interface reset to prevent system freeze-ups.

### 3. Edge Resilience (ARQ Recursive Retry Logic)
To bypass **TCP Connection -1 Errors** (Connection Refused) common during sudden mechanical or electromagnetic events, the firmware utilizes an **Automatic Repeat Request (ARQ)** pattern. If a cloud sync is rejected, the edge node automatically executes up to 3 recursive stabilization retries backed by a 1000ms delay window.

### 4. Power Integrity & Inrush Current Mitigation
A rapid drop in LDR resistance during a pick event causes localized transient voltage dips on the power rails, which can trigger ESP8266 WiFi "brownouts." This is mitigated using **Software-Defined Stabilization Delays** within the firmware, ensuring that power-heavy SSL handshakes only fire once the rail voltages have completely normalized.

---

## 📂 Repository Structure
* **`/Firmware`**: Upgraded, non-blocking C++ source code optimized for the ESP8266 node.
* **`/Cloud-Backend`**: Google Apps Script V2 middleware supporting dual-sheet logging (Twin Shadow + Log Archive).
* **`/Documentation`**: Comprehensive analytical breakdowns of the **TCP -1 Error** resolutions and **Signal Decay** mitigation math.
* **`/Media`**: High-resolution demonstrations showing hardware interaction and cloud ledger synchronization.

---

## 📈 Roadmap & Future Scope
* **Latency Optimization:** Transitioning edge-to-cloud communication from HTTP REST to an **MQTT (Pub/Sub)** broker architecture to drop synchronization latency from ~5s down to <200ms.
* **Power Optimization:** Implementing hardware-interrupt-driven **Deep Sleep** states to allow long-term, battery-powered cluster deployment.
* **Industrial Scaling:** Designing a modular, multi-channel PCB shield to connect multi-rack inventory clusters to a single master edge gateway.

---
**Developed by Karthik V S** *Mechanical Engineering Student | Government Engineering College, Thrissur* [LinkedIn Profile](https://www.linkedin.com/in/karthik-v-s-4335k)
