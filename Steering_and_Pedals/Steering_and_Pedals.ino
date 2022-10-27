#include <Joystick.h>
#include <SimRacing.h>

const int Pin_Gas = A2;
const int Pin_Brake = A1;
const int Pin_Steering = A0;

SimRacing::TwoPedals pedals(Pin_Gas, Pin_Brake);

// Create Joystick
Joystick_ Joystick(
    JOYSTICK_DEFAULT_REPORT_ID,                // default report (no additional pages)
    JOYSTICK_TYPE_JOYSTICK,                    // so that this shows up in Windows joystick manager
    0,                                         // number of buttons (none)
    0,                                         // number of hat switches (none)
    true, false,                               // X and no Y axes
    pedals.hasPedal(SimRacing::Clutch),        // include Z axis for the clutch pedal
    pedals.hasPedal(SimRacing::Brake),         // include Rx axis for the brake pedal
    pedals.hasPedal(SimRacing::Gas),           // include Ry axis for the gas pedal
    false, false, false, false, false, false); // no other axes

const int ADC_Max = 1023;      // max value of the analog inputs, 10-bit on AVR boards
const bool AlwaysSend = false; // override the position checks, *always* send data constantly

void setup()
{
  pedals.begin();

  Joystick.begin(false);

  Joystick.setZAxisRange(0, ADC_Max);
  Joystick.setRxAxisRange(0, ADC_Max);
  Joystick.setRyAxisRange(0, ADC_Max);

  Joystick.setXAxisRange(0, 1023);
  pinMode(Pin_Steering, INPUT_PULLUP);

  updateJoystick(); // set initial state
  Joystick.begin();
}

void loop()
{
  pedals.update();

  if (pedals.positionChanged() || AlwaysSend)
  {
    updateJoystick();
  }

  int steering = analogRead(Pin_Steering);
  Joystick.setXAxis(steering);
}

void updateJoystick()
{

  if (pedals.hasPedal(SimRacing::Gas))
  {
    int gasPedal = pedals.getPosition(SimRacing::Gas, 0, ADC_Max);
    Joystick.setRyAxis(gasPedal);
  }

  if (pedals.hasPedal(SimRacing::Brake))
  {
    int brakePedal = pedals.getPosition(SimRacing::Brake, 0, ADC_Max);
    Joystick.setRxAxis(brakePedal);
  }

  Serial.println();
  delay(100);
}
