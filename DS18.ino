// https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/

#include <OneWire.h>
#include <DallasTemperature.h>

// DS18 data wire is connected to GPIO-2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication
  Serial.begin(115200);
  // Start the DallasTemperature library
  sensors.begin();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Use "getTempCByIndex" as there can be more than one IC on the same bus: 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
    
  Serial.print("Celsius temperature: ");
  Serial.println(sensors.getTempCByIndex(0)); 
  // Serial.print("Fahrenheit temperature: ");
  // Serial.println(sensors.getTempFByIndex(0));
  delay(1000);
}
