//////////////////////////////////////////////
///   Author: Valerio Colantonio
///   Projecte d'interacció tangible
//////////////////////////////////////////////

#include <Arduino.h> //Includes the Arduino's standard library

// This file defines the methods and variables that are developed in the
// menu.cpp. Without this definitions the .ino file can not use it.
#ifndef MENU_H_ // Preprocessor instruction, that it will be executed before
                // compiling the application if the menu.h is not defined.
#define MENU_H_ // It is defined just once.

void resetMenu(); // Method that reset the menu options.

enum MenuOptions // Enum that defines the menu options
{
  CALIB_HUMIDITY,
  CALIB_DRYNESS,
  EXIT
};

extern MenuOptions
    menuOption; // Variable that stores the selected menu option. Is mark as
                // extern so it can be used in the other files.

String *getMenuOptionsStr(); // Method that returns the menu options array.

byte getMenuLength(); // Method that gets the menu length.

void nextOption(); // Method that select the next menu option.

byte getSelectedOption(); // Method that returns the index of the present
                          // selected option.

MenuOptions
getCurrentMenuOption(); // Method that returns the the present selected option.

enum Option { LEFT, RIGHT, BOTH };

class Page {
public:
  virtual void display() = 0;
  virtual void setBothOption(){};
  virtual void setLeftOption(){};
  virtual void setRightOption(){};
};

class ContentNavigator {
public:
  ContentNavigator() : m_currentPage(nullptr) {}

  void setCurrentPage(Page *page);

  void displayCurrentPage();

  void SetOption(Option option);

private:
  Page *m_currentPage;
};

class HomePage : public Page {
public:
  HomePage(ContentNavigator *navigator) : m_navigator(navigator) {}

  virtual void display();
  virtual void setBothOption();

private:
  ContentNavigator *m_navigator;
};

class SetupPage : public Page {
public:
  SetupPage(ContentNavigator *navigator) : m_navigator(navigator) {}

  virtual void display();
  virtual void setLeftOption();
  virtual void setRightOption();

private:
  ContentNavigator *m_navigator;
};

class CalibHumidityPage : public Page {
public:
  CalibHumidityPage(ContentNavigator *navigator) : m_navigator(navigator) {}

  virtual void display();
  virtual void setLeftOption();
  virtual void setRightOption();

private:
  ContentNavigator *m_navigator;
};

class CalibDrynessPage : public Page {
public:
  CalibDrynessPage(ContentNavigator *navigator) : m_navigator(navigator) {}

  virtual void display();
  virtual void setLeftOption();
  virtual void setRightOption();

private:
  ContentNavigator *m_navigator;
};
#endif // End of define instruction.