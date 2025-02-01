#ifndef PT100_V2T_H
#define PT100_V2T_H

#include <math.h> 
#include <Arduino.h> // Required for analogRead and similar functions

// Macros for default calculation methods
#define FOURIER "Fourier"
#define POLINOMIAL "Polynomial"
#define EXPONENTIAL "Exponential"

class pt100 {
  
public:
    /**
     * @brief Constructor to initialize the pt100 object.
     * @param pin The analog pin to read from.
     * @param voltage The reference voltage of the ADC.
     * @param bit_resolution The bit resolution of the ADC (e.g., 12 for ESP32).
     */
    pt100(unsigned short pin, float voltage, short bit_resolution);

    /**
     * @brief Converts the analog value read from the pin to voltage.
     * @return The voltage corresponding to the analog reading.
     */
    float voltageConverter();

    /**
     * @brief Calculates temperature using the default Fourier-based function.
     * @param v The voltage input.
     * @return The calculated temperature.
     */
    float calculateFourierTemperatureDefault(float v);

    /**
     * @brief Calculates temperature using a default polynomial function of degree g.
     * @param v The voltage input.
     * @param g The degree of the polynomial (1 or 3 supported).
     * @return The calculated temperature.
     */
    float calculatePoliTemperatureDefault(float v, int g);

    /**
     * @brief Calculates temperature using the default exponential function.
     * @param v The voltage input.
     * @return The calculated temperature.
     */
    float calculateExpTemperatureDefault(float v);

    /**
     * @brief Custom Fourier-based temperature calculation.
     * @param v The voltage input.
     * @param a0 Constant term.
     * @param a1 Cosine coefficient.
     * @param b1 Sine coefficient.
     * @param w Frequency term.
     * @return The calculated temperature.
     */
    float MyCalculateFourierTemperature(float v, float a0, float a1, float b1, float w);

    /**
     * @brief Custom polynomial-based temperature calculation.
     * @param v The voltage input.
     * @param g The degree of the polynomial (e.g., 1 or 3).
     * @param a0, a1, a2, a3 Polynomial coefficients.
     * @return The calculated temperature.
     */
    float MyCalculatePoliTemperature(float v, int g, float a0, float a1, float a2, float a3);

    /**
     * @brief Custom exponential-based temperature calculation.
     * @param v The voltage input.
     * @param a, b, c, d Exponential coefficients.
     * @return The calculated temperature.
     */
    float MyCalculateExpTemperature(float v, float a, float b, float c, float d);

    /**
     * @brief Calculates temperature using a selected default method (Fourier, Polynomial, or Exponential).
     * @param method The method name (use macros: FOURIER, POLINOMIAL, EXPONENTIAL).
     * @return The calculated temperature.
     */
    float calculateTemperature(const char* method);

private:
    unsigned short _pin;      ///< Analog pin connected to the sensor.
    float _voltage_ref;       ///< Reference voltage of the ADC.
    float _resolution;        ///< Maximum ADC resolution value (2^bit_resolution - 1).
};

#endif // PT100_V2T_H
