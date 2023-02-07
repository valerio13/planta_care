//////////////////////////////////////////////
///   Author: Valerio Colantonio
///   Projecte d'interacció tangible
//////////////////////////////////////////////

// #include <Servo.h>  // Included the library to drive the servo motor
#include "OledDisplay.h"
// #include "Sound.h"  //Included the file to play the sound in buzzer
#include "Menu.h"
#include "MoistureState.h"
#include "Ticker.h"
#include <AceButton.h>
#include <driver/gpio.h>

using namespace ace_button;

void MonitoringButtons();
void MonitoringMoisture();

Ticker buttonsTimer(MonitoringButtons, 250);
Ticker moistureTimer(MonitoringMoisture, 1000);

// #define IN_HUM A1 //Define the analog input for sensor humidity
// #define PWR_HUM A0  //Define the analog output to power sensor humidity

// const byte servoPin = 9;  //Define the the pin for servo motor

const byte LEFT_BUTTON = GPIO_NUM_18;
const byte RIGHT_BUTTON = GPIO_NUM_19;

AceButton leftButton(LEFT_BUTTON, LOW);
AceButton rightButton(RIGHT_BUTTON, LOW);

void handleButtonsEvent(AceButton *, uint8_t, uint8_t);

uint8_t leftButtonState = AceButton::kEventReleased;
uint8_t rightButtonState = AceButton::kEventReleased;

// Servo myServo;  //Define the Servo object used to drive the servo motor

int angle = 0;

int rawHum = 0;
int maxMisuredDryness = 0;
int maxMisuredHumidity = 9999;

// int maxDrynessCalibration = 520;
// int maxHumidityCalibration = 100;

// Enum rapresenting the states of the alarm
enum AlarmState { ON, OFF };

// Enum representing the state of the aplication
enum AppState { RUN, MENU, SUBMENU };

AlarmState lastAlarmState = OFF; // Variable that stores the states of the alarm
AppState appState = RUN; // Variable that stores the states of the aplication

int alarmCount = 0; // Variable that counts the number of alarm loops

ContentNavigator contentNavigator;
MoistureContext moistureContext;

void setup() {
  Serial.begin(921600); // Setting the serial speed

  // pinMode(IN_HUM, INPUT);   //Setup input for humidity reading
  // pinMode(PWR_HUM, OUTPUT); //Setup output for humidity power

  // myServo.attach(servoPin); //Setup the pin for servo motor

  setupDisplay();
  displayInitialMessage("INICIANDO!");

  contentNavigator.setCurrentPage(new HomePage(&contentNavigator));
  contentNavigator.displayCurrentPage();

  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);

  delay(2000);
  buttonsTimer.start();

  leftButton.setEventHandler(handleButtonsEvent);
  rightButton.setEventHandler(handleButtonsEvent);

  moistureContext.setState(new RunState());
  moistureContext.setupMoisture();
  moistureTimer.start();
}

void loop() { 
  buttonsTimer.update();
  moistureTimer.update();
}

void MonitoringButtons() {
  leftButton.check();
  rightButton.check();

  Option option;

  if (leftButtonState == AceButton::kEventPressed &&
      rightButtonState == AceButton::kEventPressed) {
    option = BOTH;
  } else if (rightButtonState == AceButton::kEventPressed) {
    option = RIGHT;
  } else if (leftButtonState == AceButton::kEventPressed) {
    option = LEFT;
  } else {
    return;
  }

  contentNavigator.SetOption(option);
  contentNavigator.displayCurrentPage();

  leftButtonState = AceButton::kEventReleased;
  rightButtonState = AceButton::kEventReleased;
}

void handleButtonsEvent(AceButton *button, uint8_t eventType,
                        uint8_t /*buttonState*/) {
  if (button) {
    uint8_t pin = button->getPin();

    if (pin == LEFT_BUTTON) {
      leftButtonState = eventType;
    }
    if (pin == RIGHT_BUTTON) {
      rightButtonState = eventType;
    }
  }
}

void MonitoringMoisture(){
  moistureContext.getMoisture();
}