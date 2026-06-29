# 🚗 CAN Black Box

A **Car Black Box** (Event Data Recorder) implemented on a **PIC18F4580** microcontroller as part of the Emertxe Embedded Systems Training Program. The system logs critical vehicle events such as gear shifts and overspeed incidents in real time, with password-protected access to view and manage the logs.

---

## 📋 Table of Contents
- [About the Project](#about-the-project)
- [Hardware Used](#hardware-used)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Project Structure](#project-structure)
- [Communication Protocols](#communication-protocols)
- [How to Build and Run](#how-to-build-and-run)
- [Sample Output](#sample-output)
- [Author](#author)

---

## 📖 About the Project

The concept of a Black Box is widely known in aviation. This project brings the same idea to automobiles — recording critical driving events for later analysis. The system monitors vehicle speed and gear shifts in real time, logs overspeed events, and provides a password-protected menu to view logs and set the RTC time.

---

## 🔧 Hardware Used

| Component | Description |
|-----------|-------------|
| PIC18F4580 | Main Microcontroller |
| DS1307 | Real Time Clock (RTC) via I2C |
| AT24C02 | External EEPROM via I2C |
| 16x2 CLCD | Character LCD Display |
| Matrix Keypad | 4x3 User Input |
| MCP2551 | CAN Bus Transceiver |
| Potentiometer | Speed Simulation via ADC |

---

## ✨ Features

- **Dashboard Screen** — Displays current time, latest event and vehicle speed in real time
- **Password Protected Login** — 4-key password with 3 attempts and 15-minute lockout
- **Partial Password Timeout** — Returns to dashboard if no key press for 3 seconds
- **Main Menu** — Navigate between View Log and Set Time
- **Event Logging** — Logs gear shifts (GN, G1–G4, GR) and overspeed (OS) events with timestamp and speed
- **View Log** — Scroll through all logged events with rollover support
- **Set Time** — Adjust RTC time directly from the device with field blinking
- **Real Time Event Capture** — Events are captured regardless of which screen is active

---

## 🏗️ System Architecture

```
+------------------+       I2C Bus      +----------+
|                  |<------------------>| DS1307   |
|                  |                    | (RTC)    |
|                  |       I2C Bus      +----------+
|   PIC18F4580     |<------------------>+----------+
|                  |                    | AT24C02  |
|                  |                    | (EEPROM) |
|                  |    Parallel Bus    +----------+
|                  |<------------------>+----------+
|                  |                    | 16x2     |
|                  |                    | CLCD     |
|                  |    GPIO Poll       +----------+
|                  |<------------------>+----------+
|                  |                    | Matrix   |
|                  |                    | Keypad   |
|                  |       ADC          +----------+
|                  |<------------------>+----------+
|                  |                    | Speed    |
|                  |                    | (POT)    |
+------------------+                    +----------+
```

---

## 📁 Project Structure

```
CAN_BLACKBOX.X/
│
├── main.c              # Main application entry point
├── main.h              # Shared types and definitions
│
├── dashboard.c         # Dashboard display and event processing
├── dashboard.h
│
├── login.c             # Password login with lockout and timeout
├── login.h
│
├── menu.c              # Main menu navigation
├── menu.h
│
├── view_log.c          # View logged events
├── view_log.h
│
├── set_time.c          # RTC time setting
├── set_time.h
│
├── event.c             # Event logging to RAM
├── event.h
│
├── rtc.c               # RTC driver (DS1307)
├── rtc.h
│
├── clcd.c              # Character LCD driver (predefined)
├── clcd.h
│
├── i2c.c               # I2C driver (predefined)
├── i2c.h
│
├── adc.c               # ADC driver (predefined)
├── adc.h
│
├── matrix_keypad.c     # Matrix Keypad driver (predefined)
├── matrix_keypad.h
│
├── eeprom.c            # Internal EEPROM driver (predefined)
├── eeprom.h
│
└── Makefile
```

---

## 📡 Communication Protocols

| Protocol | Used For |
|----------|----------|
| **I2C** | DS1307 RTC and AT24C02 EEPROM |
| **Parallel** | 16x2 CLCD Display |

---

## 🛠️ How to Build and Run

### Prerequisites
- [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [XC8 Compiler](https://www.microchip.com/mplab/compilers)
- PIC18F4580 development board

### Steps
1. Clone this repository:
```
git clone https://github.com/YOUR_USERNAME/CAN_BLACKBOX.git
```
2. Open **MPLAB X IDE**
3. Open the project `CAN_BLACKBOX.X`
4. Select **Production** configuration
5. Click **Build** (or press F11)
6. Flash the `.hex` file to the PIC18F4580

---

## 📺 Sample Output

```
Dashboard Screen:
+----------------+
|10:00:00      GN|
|SP:00           |
+----------------+

Login Screen:
+----------------+
|Enter password  |
|*               |
+----------------+

Main Menu:
+----------------+
|*View Log       |
| Set Time       |
+----------------+

View Log:
+----------------+
|#0 GN 10:00:00  |
|SP:00           |
+----------------+

Set Time:
+----------------+
|TIME:           |
|00:00:00        |
+----------------+
```

---

## 👨‍💻 Author

- **Name:** Abinand V Nair
- **Program:** Emertxe Embedded Systems Training
- **Date:** June 2026

---

## 📄 License

This project was developed as part of the **Emertxe Information Technologies** training program.

---

⭐ If you found this project helpful, please give it a star on GitHub!
