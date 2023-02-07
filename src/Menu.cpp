//////////////////////////////////////////////
///   Author: Valerio Colantonio
///   Projecte d'interacció tangible
//////////////////////////////////////////////

#include "Menu.h"
#include "OledDisplay.h"
#include <Arduino.h>

byte selectedOption = 0;

byte getSelectedOption() { return selectedOption; }

MenuOptions getCurrentMenuOption() { return menuOption; }

const byte menuSize = 3;
static String menuOtionsStr[menuSize] = {"Calib. Max. Hum.",
                                         "Calib. Max. Sequedad", "Salir"};

byte getMenuLength() { return menuSize; }

MenuOptions menuOption = CALIB_HUMIDITY;

void resetMenu() {
  selectedOption = 0;
  menuOption = (MenuOptions)selectedOption;
}

void nextOption() {
  selectedOption++;
  if (selectedOption >= menuSize)
    selectedOption = 0;

  menuOption = (MenuOptions)selectedOption;
}

String *getMenuOptionsStr() { return &menuOtionsStr[0]; }

void ContentNavigator::setCurrentPage(Page *page) { m_currentPage = page; }

void ContentNavigator::displayCurrentPage() {
  if (m_currentPage != nullptr) {
    m_currentPage->display();
  }
}

void ContentNavigator::SetOption(Option option) {
  switch (option) {
  case RIGHT:
    m_currentPage->setRightOption();
    break;
  case LEFT:
    m_currentPage->setLeftOption();
    break;
  case BOTH:
    m_currentPage->setBothOption();
    break;
  }
}

void HomePage ::display() {
  displayMessage("Umbral:" + String(83) + "%", "Humedad:", String(50) + "%");
}

void HomePage ::setBothOption() {
  resetMenu();
  m_navigator->setCurrentPage(new SetupPage(m_navigator));
}

void SetupPage ::display() {
  displayMenu(getMenuOptionsStr(), getMenuLength(), getSelectedOption());
}

void SetupPage ::setLeftOption() {
  MenuOptions menuOption = getCurrentMenuOption();
  Serial.println("option:" + String(menuOption));
  switch (menuOption) {
  case CALIB_HUMIDITY:
    m_navigator->setCurrentPage(new CalibHumidityPage(m_navigator));

    break;
  case CALIB_DRYNESS:
    m_navigator->setCurrentPage(new CalibDrynessPage(m_navigator));
    break;
  case EXIT:
    m_navigator->setCurrentPage(new HomePage(m_navigator));
    break;
  }
}

void SetupPage ::setRightOption() { nextOption(); }

void CalibHumidityPage ::display() { displaySubMenu(menuOption, 66); }

void CalibHumidityPage ::setRightOption() {
  resetMenu();
  m_navigator->setCurrentPage(new SetupPage(m_navigator));
}

void CalibHumidityPage ::setLeftOption() {
  displayMessage("CALIBRAR", "GUARDADO",
                 ""); // In the two cases above the message of calibration saved
                      // is displayed.
  delay(1000);        // The message is displayed for 1 second.
}

void CalibDrynessPage::display() { displaySubMenu(menuOption, 77); }

void CalibDrynessPage ::setLeftOption() {
  displayMessage("CALIBRAR", "GUARDADO",
                 ""); // In the two cases above the message of calibration saved
                      // is displayed.
  delay(1000);        // The message is displayed for 1 second.
}

void CalibDrynessPage ::setRightOption() {
  resetMenu();
  m_navigator->setCurrentPage(new SetupPage(m_navigator));
}