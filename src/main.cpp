#include <Arduino.h>

const int ledPin = D1; // GPIO pin where the LED is connected
const int buttonPin = D8; // GPIO pin where the button is connected

bool ledState = LOW;
bool lastButtonState = HIGH;

void setup()
{
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLDOWN_16);
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
    bool buttonState = digitalRead(buttonPin);
    Serial.printf("Button state: %d\n", buttonState);

    if (buttonState != lastButtonState) {
        ledState = !ledState;
        lastButtonState = buttonState;
    }

    if (ledState == HIGH)
        blink();
}