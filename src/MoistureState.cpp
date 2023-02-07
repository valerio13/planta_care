//////////////////////////////////////////////
/// Author : Valerio Colantonio ///
//////////////////////////////////////////////

#include "MoistureState.h"
#include <Arduino.h>
#include <driver/gpio.h>

const byte IN_HUM = GPIO_NUM_4;
const byte PWR_HUM = GPIO_NUM_0;

int maxDrynessCalibration;
int maxHumidityCalibration;
int moistureThersholdPercen;

int readMoisture();

MoistureContext::MoistureContext() : m_state(new RunState()) {}

void MoistureContext::setState(State *state) { m_state = state; }

moisture MoistureContext::getMoisture() { return m_state->getMoisture(); }

void MoistureContext::setupMoisture() {
  pinMode(IN_HUM, INPUT);
  pinMode(PWR_HUM, OUTPUT);

  maxDrynessCalibration = 520;
  maxHumidityCalibration = 100;
  moistureThersholdPercen = 50;
}

moisture RunState::getMoisture() {
  moisture myMoisture;
  myMoisture.moisturePercent = readMoisture();
  myMoisture.thersholdPercen = moistureThersholdPercen;
  myMoisture.maxRawDryness = maxDrynessCalibration;
  myMoisture.maxRawHumidity = maxHumidityCalibration;

  return myMoisture;
}

moisture CalibHumidityState::getMoisture() {
  moisture myMoisture;
  return myMoisture;
}

moisture CalibDrynessState::getMoisture() {
  moisture myMoisture;
  return myMoisture;
}

int readMoisture() {
  digitalWrite(PWR_HUM, HIGH); // Apply power to the soil moisture sensor.
  delay(10);
  int rawHumidity = analogRead(IN_HUM);
  Serial.println("Humedad: " + String(rawHumidity));

  digitalWrite(PWR_HUM, LOW); // Turn off the sensor to reduce metal corrosion

  int humidityPercent =
      map(rawHumidity, maxDrynessCalibration, maxHumidityCalibration, 0, 100);

  return humidityPercent;
}