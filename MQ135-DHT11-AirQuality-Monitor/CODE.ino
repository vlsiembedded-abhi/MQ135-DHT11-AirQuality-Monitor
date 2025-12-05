#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

/* ------------ OLED Config ------------ */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED on address 0x3C (most common)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ------------ Sensor & IO Pins ------------ */

#define DHTPIN    2
#define DHTTYPE   DHT11
DHT dht(DHTPIN, DHTTYPE);

const int mq135Pin = A0;

#define GREEN_LED 3
#define RED_LED   4
#define BUZZER    5

/* ------------ MQ135 Thresholds (RAW) ------------ */
/*
 * Tune these after watching mqRaw values.
 * For now:
 *  0   - 100  : GOOD
 *  101 - 300  : MODERATE
 *  >300       : BAD
 */
const int MQ_GOOD_MAX     = 100;
const int MQ_MODERATE_MAX = 300;

void setup() {
  // LED + Buzzer pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Start DHT
  dht.begin();

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // If OLED init fails, stay here
    while (true) {
      digitalWrite(RED_LED, HIGH);
      delay(200);
      digitalWrite(RED_LED, LOW);
      delay(200);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Simple splash screen
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");
  display.println("MQ135 + DHT11 + OLED");
  display.display();
  delay(2000);
}

void loop() {
  // ---- Read sensors ----
  int mqRaw = analogRead(mq135Pin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // deg C

  // ---- DHT11 Error Handling ----
  if (isnan(humidity) || isnan(temperature)) {
    // Show error on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("DHT11 ERROR!");
    display.println("Check wiring");
    display.display();

    // Indicate error with red LED
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    delay(1000);
    return; // skip rest of loop
  }

  // ---- Classify Air Quality ----
  int airStatus = 0;        // 0 = GOOD, 1 = MODERATE, 2 = BAD
  const char *airText = ""; // text for OLED

  if (mqRaw <= MQ_GOOD_MAX) {
    airStatus = 0;
    airText = "GOOD";
  } else if (mqRaw <= MQ_MODERATE_MAX) {
    airStatus = 1;
    airText = "MODERATE";
  } else {
    airStatus = 2;
    airText = "BAD";
  }

  // ---- Control LEDs & Buzzer ----
  if (airStatus == 0) {
    // GOOD: Green ON solid, others OFF
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else if (airStatus == 1) {
    // MODERATE: only GREEN fast blink, no red, no buzzer
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    digitalWrite(GREEN_LED, HIGH);
    delay(50);
    digitalWrite(GREEN_LED, LOW);
    delay(50);
  }
  else {
    // BAD: Red ON, Green OFF, buzzer beeps
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    // remaining delay at end of loop
  }

  // ---- Show values on OLED ----
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.print("Hum : ");
  display.print(humidity, 1);
  display.println(" %");

  display.print("AQI: ");
  display.println(mqRaw);

  display.print("Air : ");
  display.println(airText);

  display.display();

  // ---- Delay between updates ----
  // For GOOD/MODERATE we already used some delay; here we add a bit more
  delay(300);
}

