#include <Arduino.h>

const int ledPin = D1; // GPIO pin where the LED is connected

void setup()
{
    pinMode(ledPin, OUTPUT);
}

void blink()
{
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(500);                // wait for a second
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500);                // wait for a second
}

void loop()
{
    blink();
}