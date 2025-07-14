
// 1st file to do: include the library of ESP32-CAM and import the port to connect with the machine.

// WiFi Configuration - Replace with your network credentials
#define WIFI_SSID ""        // Your WiFi network name (SSID)
#define WIFI_PASS ""        // Your WiFi password
#define HOSTNAME "esp32cam" // Device hostname on the network

// Include the main EloquentESP32cam library for camera functionality
#include <eloquent_esp32cam.h>
// Include WiFi station mode functionality
#include <eloquent_esp32cam/extra/esp32/wifi/sta.h>
// Include the image collection server for web interface
#include <eloquent_esp32cam/viz/image_collection.h>

// Using declarations to simplify namespace usage
using eloq::camera;           // Camera control object
using eloq::wifi;             // WiFi management object
using eloq::viz::collectionServer; // Image collection web server

void setup() {
    // Initial delay to allow system stabilization
    delay(3000);
    
    // Initialize serial communication at 115200 baud rate
    Serial.begin(115200);
    Serial.println("___IMAGE COLLECTION SERVER___");

    // CAMERA CONFIGURATION
    // Set camera pinout configuration for AI-Thinker ESP32-CAM board
    // This configures the GPIO pins for the specific camera module
    camera.pinout.aithinker();
    
    // Disable brownout detector to prevent random resets
    // Brownout can occur when camera draws too much current
    camera.brownout.disable();
    
    // Set camera resolution to 240x240 pixels (face detection optimized)
    // Edge Impulse models typically work best with square images
    // This resolution is specifically chosen for face detection applications
    camera.resolution.face();
    
    // Set image quality to high for better image clarity
    // Trade-off: higher quality = larger file size, slower processing
    camera.quality.high();

    // CAMERA INITIALIZATION
    // Attempt to initialize the camera with error handling
    // Keep trying until camera is successfully initialized
    while (!camera.begin().isOk()) {
        Serial.println(camera.exception.toString());
        // This will print any camera initialization errors
        // Common issues: wrong pinout, hardware problems, power issues
    }

    // WIFI CONNECTION
    // Attempt to connect to WiFi network
    // Uses the SSID and password defined at the top
    while (!wifi.connect().isOk()) {
        Serial.println(wifi.exception.toString());
        // This will print WiFi connection errors
        // Common issues: wrong credentials, network not found, weak signal
    }

    // IMAGE COLLECTION SERVER INITIALIZATION
    // Start the HTTP server for image collection interface
    // This creates a web interface accessible via browser
    while (!collectionServer.begin().isOk()) {
        Serial.println(collectionServer.exception.toString());
        // This will print server initialization errors
        // Common issues: port conflicts, memory issues
    }

    // SUCCESS MESSAGES
    Serial.println("Camera OK");                    // Camera initialized successfully
    Serial.println("WiFi OK");                     // WiFi connected successfully
    Serial.println("Image Collection Server OK");   // Server started successfully
    
    // Print the server address where you can access the web interface
    // Format: http://[IP_ADDRESS]:[PORT]
    Serial.println(collectionServer.address());
}

void loop() {
    // The image collection server runs in a separate thread/task
    // No additional code needed in the main loop
    // The server handles HTTP requests automatically in the background
    
    // You could add additional functionality here such as:
    // - LED status indicators
    // - Button handling
    // - Additional sensors
    // - Periodic tasks
}