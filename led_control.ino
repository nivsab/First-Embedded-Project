#include <Arduino.h>


#define LED_PIN     5
#define BUTTON_PIN  0

//machine state
enum State { OFF = 0, SLOW_BLINK, FAST_BLINK };
State currentState = OFF;

unsigned long previousMillis = 0;
bool ledState = LOW;
int blinkDelay = 1000;

bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(115200);

    Serial.println("ESP32 is working");
}

void loop() {
    unsigned long currentMillis = millis();
    bool currentButtonState = digitalRead(BUTTON_PIN);

    
    if (currentButtonState != lastButtonState) {
        lastDebounceTime = currentMillis;
    }

    if ((currentMillis - lastDebounceTime) > debounceDelay) {
        if (lastButtonState == HIGH && currentButtonState == LOW) {
            currentState = (State)((currentState + 1) % 3);
            Serial.print("Current State: ");
            Serial.println(currentState);
            digitalWrite(LED_PIN, LOW);  
            ledState = LOW;
        }
    }

    lastButtonState = currentButtonState;

   
    if (currentState == SLOW_BLINK) {
        blinkDelay = 1000;
        if (currentMillis - previousMillis >= blinkDelay) {
            previousMillis = currentMillis;
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState);
        }
    }
    else if (currentState == FAST_BLINK) {
        blinkDelay = 300;
        if (currentMillis - previousMillis >= blinkDelay) {
            previousMillis = currentMillis;
            ledState = !ledState;
            digitalWrite(LED_PIN, ledState);
        }
    }
    else if (currentState == OFF) {
        digitalWrite(LED_PIN, LOW);
    }
}
