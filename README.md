# 🏫 Smart Multi-Zone Classroom Appliance Control System

An ESP32-based smart classroom energy management system that automatically controls lights and fans using **PIR-based occupancy detection** and **temperature-adaptive decision logic**. The system divides a classroom into multiple zones and powers only the occupied areas, reducing energy consumption while maintaining occupant comfort.

---

## 📌 Features

* Multi-zone occupancy detection using PIR sensors
* Independent relay control for each classroom zone
* Temperature and humidity monitoring using DHT22
* Adaptive fan shut-off delay based on room temperature
* Automatic light and fan control
* Real-time LCD status display
* ESP32-based embedded control system
* Designed for energy-efficient classroom automation

---

## 🛠 Hardware Components

* ESP32 WROOM Development Board
* PIR Motion Sensors (3 Zones)
* DHT22 Temperature & Humidity Sensor
* 3-Channel Relay Module
* 16×2 I2C LCD Display
* LED Lamps
* DC Fan
* 12V Power Supply
* NPN Transistor Driver Circuit
* Flyback Protection Diodes

---

## 💻 Software & Tools

* Embedded C
* Arduino IDE
* ESP32 Framework
* Proteus (Circuit Simulation)

---

## ⚙ Working Principle

The classroom is divided into **Front**, **Middle**, and **Back** zones.

Each zone contains a PIR sensor that continuously monitors human presence.

When movement is detected within a zone:

* The corresponding relay activates.
* Lights and fans in that zone turn ON.
* Empty zones remain OFF to reduce unnecessary energy consumption.

A DHT22 sensor continuously measures the classroom temperature and humidity.

Instead of using a fixed timer, the controller adjusts the fan OFF delay according to the measured temperature:

* **Above 30°C** → Longer delay
* **27–30°C** → Medium delay
* **Below 27°C** → Short delay

This improves user comfort while minimizing electricity usage.

---

## 📂 Repository Structure

```text
smart-multi-zone-power-control/
│
├── main.ino
├── README.md
├── LICENSE
├── images/
│   ├── prototype.jpg
│   ├── block_diagram.png
│   └── circuit_diagram.png
│
├── docs/
│   └── Project_Report.pdf
│
└── proteus/
```

---

## 🔄 System Workflow

```text
        PIR Sensors
             │
             ▼
     Detect Occupancy
             │
             ▼
     ESP32 Controller
             │
     Read DHT22 Sensor
             │
             ▼
 Temperature-Based Logic
             │
             ▼
      Relay Controller
             │
             ▼
 Lights & Fans (Zone-wise)
```

---

## 🎯 Project Highlights

* Zone-wise classroom appliance automation
* Temperature-aware fan control
* Privacy-friendly occupancy detection
* Low-cost embedded hardware implementation
* Scalable architecture for larger classrooms
* Energy-efficient relay switching

---

## 📊 Applications

* Smart Classrooms
* Educational Institutions
* Office Buildings
* Conference Rooms
* Libraries
* Laboratories
* Smart Building Automation

---

## 🚀 Future Improvements

* IoT dashboard for remote monitoring
* Occupancy data logging
* Mobile application integration
* Predictive scheduling based on classroom timetable
* AI-based occupancy prediction
* Energy consumption analytics
* Cloud database integration

---

## 📷 Demonstration

Project photographs, circuit diagrams, simulation files, and demonstration videos are available in the repository.

---

## 📚 Skills Demonstrated

* Embedded Systems Programming
* ESP32 Firmware Development
* Sensor Interfacing
* Relay Driver Design
* PIR Motion Detection
* Temperature & Humidity Monitoring
* Embedded Control Systems
* Energy Management
* Hardware Integration

---


---

### ⭐ If you found this project useful, consider giving it a star.
