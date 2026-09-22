/*
 * Session 2 — FINAL: tilt switches, knob dims.
 * --------------------------------------------------------------------------
 * 1. My chosen axis and threshold:
 *    Z axis, threshold +3.0 m/s^2. LED is enabled only when az > +3.0.
 * 2. The readings I observed in the three poses (held still):
 *    up ~ +9.6, sideways ~ +0.1, down ~ -9.5   <-- REPLACE with YOUR measured values
 * 3. One thing that surprised me when testing:
 *    Even held "still," the Z reading wobbled by a few tenths, I set the
 *    threshold at +3.0 instead of near 0 to avoid flicker near sideways.
 *    <-- REPLACE with what actually surprised YOU
 *
 * WIRING:
 *   pot outer leg 1 -> 3V3, pot outer leg 2 -> GND, pot middle leg -> GPIO4
 *   GPIO40 -> 220-330 ohm resistor -> LED long leg (anode)
 *   LED short leg (cathode) -> GND
 *   MPU-6050: VCC -> 3V3, GND -> GND, SDA -> GPIO8, SCL -> GPIO9
 */
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>

#define POT_PIN 4
#define LED_PIN 40
#define TILT_THRESHOLD 3.0f   // m/s^2 — LED on only when az is clearly "up"

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(300);
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(8, 9);                  // SDA 8, SCL 9

  if (!mpu.begin()) {
    Serial.println("MPU-6050 not found — run the I2C scanner first.");
    while (true) delay(1000);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.println("Tilt switches, knob dims — hold the board still.");
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);          // acceleration in m/s^2

  int raw  = analogRead(POT_PIN);    // 0 .. 4095
  int duty = raw / 16;               // 0 .. 255
  if (duty > 255) duty = 255;

  // Tilt switch: only enable the LED while the Z axis points up.
  bool enabled = (a.acceleration.z > TILT_THRESHOLD);
  analogWrite(LED_PIN, enabled ? duty : 0);   // disabled -> off at every knob setting

  Serial.printf("az %+6.2f | raw %4d -> duty %3d | %s\n",
                a.acceleration.z, raw, duty, enabled ? "ON " : "OFF");
  delay(50);
}