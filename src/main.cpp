/******************************************************************************
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <Arduino.h>
#include "esp32-mqtt.h"
#include "SevSeg.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  setupCloudIoT();
  //Start the Display 
  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode
    
  //This pinout is for a bubble dispaly
  //Declare what pins are connected to the GND pins (cathodes)
  int digit1 = 26; //- 4;  //Pin D2
  int digit2 = 18; //- 13; //Pin D3
  int digit3 = 19; //- 16; //Pin D4
  int digit4 = 23; //- 17; //Pin D5
  int digit5 = 22; //- 18; //Pin D6
  int digit6 = 21; //-   19; //Pin D7
       
  //Declare what pins are connected to the segments (anodes)
  int segA = 27;// - 21; //Pin D8
  int segB = 25;// - 22; //Pin D9
  int segC = 32;// - 23; //Pin D11
  int segD = 4;//  - 25; //Pin D13
  int segE = 17;// - 26; //Pin D12
  int segF = 16;// - 27; //Pin A4
  int segG = 2;// - 13 - TCK; //A5
  int segDP= 33;//  - 27 - RXD; //RX0
  int numberOfDigits = 6; //Do you have a 6 digit display?

  NSA1166Display.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, digit5, digit6, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  NSA1166Display.SetBrightness(100); //Set the display to 100% brightness level

  timer = millis();
}

unsigned long last_Telemetry_Millis = 0;
unsigned long last_State_Millis = 0;
unsigned long last_LEDState_Millis = 0;



void loop() {
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!mqttClient->connected()) {
    connect();
  }
  

  // TODO: replace with your code
  // publish a message roughly every second.
  if (millis() - last_Telemetry_Millis > telemetry_publish_interval) {
    last_Telemetry_Millis = millis();
    Serial.println(F("sending Telemetry data"));
    publishTelemetry(getDefaultSensor());
  }
  
  if (millis() - last_State_Millis > device_state_publish_interval) {
    last_State_Millis = millis();
    Serial.println(F("Sending Device State Data"));
    publishState(getDeviceState());
  }
}
