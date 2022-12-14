
#include <Arduino.h>
// broche des bouttons
int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;  // choose the pin for the LED
int inputPin = 2; // Connect sensor to input pin 3
int val1 = digitalRead(inputPin);
int val2 = digitalRead(inputPin);
int val3 = digitalRead(inputPin);
// broche pour la RGB

#include <Adafruit_NeoPixel.h>

#define PIN_LED 1 // Control signal, connect to DI of the LED
#define NUM_LED 1 // Number of LEDs in a strip

// Custom colour1: Yellow
#define RED_VAL_1 255
#define GREEN_VAL_1 255
#define BLUE_VAL_1 0

// Custom colour2: Purple
#define RED_VAL_2 255
#define GREEN_VAL_2 0
#define BLUE_VAL_2 255

// Custom colour3: Cyan
#define RED_VAL_3 0
#define GREEN_VAL_3 255
#define BLUE_VAL_3 255

// Custom colour4: White
#define RED_VAL_4 255
#define GREEN_VAL_4 255
#define BLUE_VAL_4 255

Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    wifiConnect(); // Branchement au réseau WIFI
    MQTTConnect(); // Branchement au broker MQTT
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT); // declare LED as output
    pinMode(inputPin, INPUT); // declare pushbutton as input
    RGB_Strip.begin();
    RGB_Strip.show();
    RGB_Strip.setBrightness(128);
}

void loop()
{
    // read input value
    if (val1 == HIGH)
    {                               // check if the input is HIGH
        digitalWrite(ledPin1, LOW);
        // turn LED OFF
    }
    else
    {
        digitalWrite(ledPin1, HIGH); // turn LED ON
    }
    // read input value
    if (val2 == HIGH)
    {                               // check if the input is HIGH
        digitalWrite(ledPin2, LOW); // turn LED OFF
    }
    else
    {
        digitalWrite(ledPin2, HIGH); // turn LED ON
    }
    // read input value
    if (val3 == HIGH)
    {                               // check if the input is HIGH
        digitalWrite(ledPin3, LOW); // turn LED OFF
    }
    else
    {
        digitalWrite(ledPin3, HIGH); // turn LED ON
    }

    colorWipe(RGB_Strip.Color(255, 0, 0), 1000); // Red
    colorWipe(RGB_Strip.Color(0, 255, 0), 1000); // Green
    colorWipe(RGB_Strip.Color(0, 0, 255), 1000); // Blue

    colorWipe(RGB_Strip.Color(RED_VAL_1, GREEN_VAL_1, BLUE_VAL_1), 1000); // Custom colour1: Yellow
    colorWipe(RGB_Strip.Color(RED_VAL_2, GREEN_VAL_2, BLUE_VAL_2), 1000); // Custom colour2: Purple
    colorWipe(RGB_Strip.Color(RED_VAL_3, GREEN_VAL_3, BLUE_VAL_3), 1000); // Custom colour3: Cyan
    colorWipe(RGB_Strip.Color(RED_VAL_4, GREEN_VAL_4, BLUE_VAL_4), 1000); // Custom colour4: White

    rainbow(20); // Rainbow
    appendPayload("Bouton1", val1);
      appendPayload("Bouton2", val2);
        appendPayload("Bouton3", val3);
    sendPayload();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait)
{
    for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++)
    {
        RGB_Strip.setPixelColor(i, c);
        RGB_Strip.show();
        delay(wait);
    }
}

void rainbow(uint8_t wait)
{
    uint16_t i, j;

    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < RGB_Strip.numPixels(); i++)
        {
            RGB_Strip.setPixelColor(i, Wheel((i + j) & 255));
        }
        RGB_Strip.show();
        delay(wait);
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return RGB_Strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return RGB_Strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return RGB_Strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}