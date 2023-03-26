/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLJxoMgMaz"
#define BLYNK_TEMPLATE_NAME "DS18 Temperature Template"
#define BLYNK_AUTH_TOKEN "zG3W5RwkgY1Ix8llri-RHc-eQNB4zprq"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define LED_PIN D4

//#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//libraries for DS18 temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 GPIO pin
const int oneWireBus = D3;
// WiFi credentials.
char ssid[] = "PLUSNET-62C3JJ";
char pass[] = "xeav4bnMgJX7GV";

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass the oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// set up a Blynk timer to handle timed event (measure temp and send to Blynk)
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // turn on-board LED on or off via Blynk switch (LOW = on, hence 'not value')
  digitalWrite(LED_PIN, not value);

  // Update state back to Blync.console
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Blynk.virtualWrite(V2, temperatureC);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

  // Start the DS18B20 sensor
  sensors.begin();

  // set up onboard LED
  pinMode(LED_PIN, OUTPUT);  
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
