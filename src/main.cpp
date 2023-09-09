//rel_battery LOW TRIGGER


#include <Arduino.h>

#define sen_voltage A0
#define sen_temperature A1
#define rel_battery 5
#define but_power 6

const byte interruptPin = 2;



int voltage = 0;
int temperature = 0;

int readVoltage() {
  voltage = analogRead(sen_voltage);
  return voltage;
}

int readTemperature() {
  temperature = analogRead(sen_temperature);
  return temperature;
}
void powerOff()
{
  Serial.println("power off");
  digitalWrite(rel_battery, HIGH);
  delay(1000);
}

void (*resetFunc)(void) = 0;

void setup()
{
  pinMode(sen_voltage, INPUT);
  pinMode(sen_temperature, INPUT);
  pinMode(rel_battery, OUTPUT);
  pinMode(but_power, INPUT);


  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), powerOff, CHANGE);
  digitalWrite(rel_battery, LOW);

  Serial.begin(9600);
}

void loop()
{
  Serial.print("Voltage ");
  Serial.println(readVoltage());
  delay(1000);
  Serial.print("Temperature ");
  Serial.println(readTemperature());

  if (readVoltage() < 569)
  {
    powerOff();
    delay(10000);
    resetFunc();
  }
  if (readTemperature() > 250)
  {
    powerOff();
    delay(300000);
    resetFunc();
  }
  
  
}