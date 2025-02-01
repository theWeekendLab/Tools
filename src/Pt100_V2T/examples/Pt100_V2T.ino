#include "pt100_V2T.h"

// Analog pin connected to the sensor
#define PT100_PIN 34  // GPIO 34 pin (ADC1)

// ADC and sensor system parameters
#define VOLTAGE_REF 3.3  // Reference voltage of the ADC converter in Volts
#define BIT_RESOLUTION 12  // ADC resolution in bits (12 for ESP32)

pt100 sensor(PT100_PIN, VOLTAGE_REF, BIT_RESOLUTION);  // Instantiate the pt100 object

void setup() {
    Serial.begin(115200);  // Initialize serial communication
    delay(1000);  // Wait for the serial to be ready
    Serial.println("PT100 Sensor Example with ESP32");
}

void loop() {
    // Calculate temperature using the Fourier method
    float temperatureFourier = sensor.calculateTemperature(FOURIER);
    
    // Calculate temperature using the Polynomial method (degree 3)
    float temperaturePolynomial = sensor.calculateTemperature(POLINOMIAL);
    
    // Calculate temperature using the Exponential method
    float temperatureExponential = sensor.calculateTemperature(EXPONENTIAL);

    // Print the results to the serial monitor
    Serial.println("Temperature Readings:");
    Serial.print("Fourier Method: ");
    Serial.print(temperatureFourier);
    Serial.println(" °C");

    Serial.print("Polynomial Method: ");
    Serial.print(temperaturePolynomial);
    Serial.println(" °C");

    Serial.print("Exponential Method: ");
    Serial.print(temperatureExponential);
    Serial.println(" °C");

    Serial.println("--------------------------");
    delay(1000);  // Wait 1 second before repeating
}
