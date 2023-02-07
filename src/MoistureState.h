//////////////////////////////////////////////
///   Author: Valerio Colantonio
///   Projecte d'interacció tangible
//////////////////////////////////////////////

#include <iostream>

struct moisture {
  int moisturePercent;
  int thersholdPercen;
  int maxRawDryness;
  int maxRawHumidity;
};

class State {
public:
  virtual moisture getMoisture() = 0;
};

class RunState : public State {
public:
  virtual moisture getMoisture() override;
};

class CalibHumidityState : public State {
public:
  virtual moisture getMoisture() override;
};

class CalibDrynessState : public State {
public:
  virtual moisture getMoisture() override;
};

class MoistureContext {
public:
  MoistureContext();
  void setState(State *state);
  moisture getMoisture();
  void setupMoisture();

private:
  State *m_state;
};