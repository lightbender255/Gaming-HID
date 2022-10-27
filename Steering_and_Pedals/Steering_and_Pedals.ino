#include <Joystick.h>
#include <SimRacing.h>

// Create Joystick
Joystick_ Joystick;

const int Pin_Gas = A2;
const int Pin_Brake = A1;
const int Pin_Steering = A0;

SimRacing::TwoPedals pedals(Pin_Gas, Pin_Brake);

void setup()
{
  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);  
  pinMode(Pin_Steering, INPUT_PULLUP);
  pinMode(Pin_Gas, INPUT_PULLUP);
  pinMode(Pin_Brake, INPUT_PULLUP);

  Serial.begin(115200);
  while (!Serial)
    ; // wait for connection to open

  Serial.println("Starting...");
  Serial.print("setup complete");
}

void loop()
{

  int steering = analogRead(Pin_Steering);
  int gas = analogRead(Pin_Gas);
  int brake = analogRead(Pin_Brake);
  Joystick.setXAxis(steering);
  
  Serial.print("Pedals:");

  Serial.print("\tSteering: [ ");
  Serial.print(steering);
  Serial.print(" ]");

  Serial.print("\tGas: [ ");
  Serial.print(gas);
  Serial.print(" ]");

  Serial.print("\tBrake: [ ");
  Serial.print(brake);
  Serial.print(" ]");

  Serial.println();
  delay(100);
}
