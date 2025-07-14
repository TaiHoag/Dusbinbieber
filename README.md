# DUSBINBIEBER: Smart Dustbin Image Classification

![Alt tex](src/iot.png?raw=true)

This repository contains two Arduino sketches for an ESP32-CAM based IoT project:

1. **Collect_Images_for_EdgeImpulse**  
   Turn your ESP32-CAM into a web-based image collection server—captures labeled samples for training on Edge Impulse.

2. **updated_as_robo_smart_dustbin**  
   Deploy a trained Edge Impulse object detection model on the ESP32-CAM.  
   Display inference results on an SSD1306 OLED and actuate a servo to sort detected items (e.g., `battery` vs. `paper`).

---

## Repository Structure

```
Code/
├── Collect_Images_for_EdgeImpulse/
│   └── Collect_Images_for_EdgeImpulse.ino   # Image-collection server sketch
├── updated_as_robo_smart_dustbin/
│   └── updated_as_robo_smart_dustbin.ino    # Inference, OLED display & servo control
└── README.md                                # Project overview and setup
```

## Prerequisites

- **Hardware:**

  - AI-Thinker ESP32-CAM module
  - SSD1306 I²C OLED display
  - SG90 (or similar) servo motor
  - Breadboard wires and power supply

- **Software:**
  - Arduino IDE (or PlatformIO)
  - Installed libraries:
    - `EloquentESP32CAM`
    - `ESP32Servo`
    - `Adafruit SSD1306` & `Adafruit GFX`
    - `Wire`
    - Edge Impulse Arduino SDK (as provided by Edge Impulse)

## Setup & Usage

### 1. Collect Training Images

1. Open `Collect_Images_for_EdgeImpulse/Collect_Images_for_EdgeImpulse.ino` in Arduino IDE.
2. Fill in your Wi-Fi credentials:
   ```cpp
   #define WIFI_SSID "<your-SSID>"
   #define WIFI_PASS "<your-password>"
   ```
3. Upload to your ESP32-CAM and open Serial Monitor at 115200 baud.
4. Note the printed URL (e.g., `http://192.168.1.42:8080`), then open it in a browser.
5. Capture labeled images (e.g., `battery`, `paper`) and download for Edge Impulse training.

### 2. Train & Export Model

1. On [Edge Impulse](https://www.edgeimpulse.com), create a new project and upload your captured images.
2. Design and train an object detection impulse.
3. Export the Arduino library and copy it into this repo under `updated_as_robo_smart_dustbin/lib/`.

### 3. Deploy Inference Sketch

1. Open `updated_as_robo_smart_dustbin/updated_as_robo_smart_dustbin.ino`.
2. Ensure the Edge Impulse SDK and model headers are included correctly:
   ```cpp
   #include <dusbin_inferencing.h>
   ```
3. Wire your OLED (SDA → GPIO15, SCL → GPIO14) and servo (signal → GPIO12).
4. Upload to the ESP32-CAM and watch the OLED and servo respond to detected classes.
