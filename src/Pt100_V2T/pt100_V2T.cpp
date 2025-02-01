#include "pt100_V2T.h"
#include <Arduino.h> // Necessario per analogRead e funzioni di Arduino

// Macro per i nomi delle funzioni predefinite
#define FOURIER "Fourier"
#define POLINOMIAL "Polynomial"
#define EXPONENTIAL "Exponential"

// Constructor
pt100::pt100(unsigned short pin, float voltage, short bit_resolution) 
    : _pin(pin), _voltage_ref(voltage), _resolution(pow(2, bit_resolution) - 1) {
    if (_voltage_ref <= 0 || _resolution <= 0) {
        Serial.println("Error: Invalid voltage or resolution values.");
        while (1); // 
    }
}

// Converts the analog value to voltage
float pt100::voltageConverter() {
    int analogValue = analogRead(_pin);
    if (analogValue < 0 || analogValue > _resolution) {
        Serial.println("Warning: Analog value out of range.");
        return 0;
    }
    //Serial.println("voltage");
    //Serial.println((analogValue / _resolution) * _voltage_ref);
    return (analogValue / _resolution) * _voltage_ref;
}

// Default Fourier-based temperature calculation
float pt100::calculateFourierTemperatureDefault(float v) {
    return 1.545e6 + -1.545e6* cos(-0.003203* v) + -1.027e4* sin(-0.003203* v);
}

// Default polynomial temperature calculation
float pt100::calculatePoliTemperatureDefault(float v, int g) {
    switch (g) {
        case 2:
            return 7.929 * v*v + 32.89*v -8.381;
        case 3:
            return 0.9043* pow(v, 3) + 5.101* pow(v, 2) + 35.47 * v + -9.025;
        default:
            Serial.println("Warning: Invalid polynomial degree. Returning input voltage.");
            return v; // Return the input voltage if degree is invalid
    }
}

// Default exponential temperature calculation
float pt100::calculateExpTemperatureDefault(float v) {
    return 43.2* exp(0.5088* v) - 52.72 * exp(-0.2917* v);
}

// Custom Fourier-based temperature calculation
float pt100::MyCalculateFourierTemperature(float v, float a0, float a1, float b1, float w) {
    return a0 + a1 * cos(w * v) + b1 * sin(w * v);
}

// Custom polynomial-based temperature calculation
float pt100::MyCalculatePoliTemperature(float v, int g, float a0, float a1, float a2, float a3) {
    switch (g) {
        case 1:
            return a0 + a1 * v;
        case 3:
            return a0 + a1 * v + a2 * pow(v, 2) + a3 * pow(v, 3);
        default:
            Serial.println("Warning: Invalid polynomial degree. Returning input voltage.");
            return v; // Return the input voltage if degree is invalid
    }
}

// Custom exponential-based temperature calculation
float pt100::MyCalculateExpTemperature(float v, float a, float b, float c, float d) {
    return a * exp(b * v) + c * exp(d * v);
}

// Unified temperature calculation function
float pt100::calculateTemperature(const char* method) {
    // Convert the analog reading to voltage
    float voltage = voltageConverter();

    // Select the calculation method based on the input
    if (strcmp(method, FOURIER) == 0) {
        return calculateFourierTemperatureDefault(voltage);
    } else if (strcmp(method, POLINOMIAL) == 0) {
        return calculatePoliTemperatureDefault(voltage, 3); // Default to 3rd degree polynomial
    } else if (strcmp(method, EXPONENTIAL) == 0) {
        return calculateExpTemperatureDefault(voltage);
    } else {
        Serial.println("Error: Invalid temperature calculation method.");
        return 0; // Return 0 for invalid method
    }
}

