# Web-Controlled-RC-Car

A WiFi-controlled RC car built using the ESP8266 microcontroller. Control the car from any browser on your phone or laptop — no app needed.

---

## 🚗 Features

- Control via browser over WiFi (no internet required)
- Forward, Backward, Left, Right, Stop
- Manual horn button
- Ultrasonic obstacle detection — auto-beeps when object is within 10cm

---

## 🛠️ Components Used

| Component | Purpose |
|---|---|
| ESP8266 (NodeMCU) | WiFi + main controller |
| L298N Motor Driver | Controls DC motors |
| 2x DC Motors | Drive the wheels |
| HC-SR04 Ultrasonic Sensor | Obstacle detection |
| Buzzer | Horn / obstacle alert |
| Li-ion Battery Pack | Power supply |

---

## 📡 How It Works

1. ESP8266 creates its own WiFi hotspot named **"WiFiCar"**
2. Connect your phone/laptop to that WiFi
3. Open browser and go to **192.168.4.1**
4. Use the buttons to control the car in real time

---

## 🔌 Pin Connections

| ESP8266 Pin | Connected To |
|---|---|
| D1 (enA) | L298N ENA |
| D2 (in1) | L298N IN1 |
| D3 (in2) | L298N IN2 |
| D4 (in3) | L298N IN3 |
| D5 (in4) | L298N IN4 |
| D6 (enB) | L298N ENB |
| D7 | Buzzer |
| D8 (trig) | HC-SR04 Trig |
| D0 (echo) | HC-SR04 Echo |

---

## 💻 Software

- Arduino IDE
- ESP8266 Board Package
- Libraries: `ESP8266WiFi`, `ESP8266WebServer`

---

## 🚀 Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP8266 board: `File → Preferences → Additional Board Manager URLs`
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Install board via `Tools → Board → Board Manager → ESP8266`
4. Open the `.ino` file and upload to your NodeMCU
5. Connect to **WiFiCar** hotspot and open **192.168.4.1**

---

## 👨‍💻 Made By

Made as a mini project to demonstrate IoT and embedded systems using ESP8266.
