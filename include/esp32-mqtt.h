/******************************************************************************
 * Copyright 2018 Google
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
// This file contains static methods for API requests using Wifi / MQTT
#include <Client.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <MQTT.h>

#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>
#include "ciotc_config.h"                       // Update this file with your configuration
#include <Arduino.h>
#include <ArduinoJson.h>
#include "SevSeg.h"

#define CLR 16
#define NUM_DIGITS 6

//Create an instance of the object.
SevSeg NSA1166Display;

//Create global variables
unsigned long timer;
int deciSecond = 0;


String id_de_operacion, Display_Coin_name_json, Display_CoinPrice_json;

void ESPreboot(){
  Serial.println(F("este dispositivo se reiniciara en 5 segundos..."));                                                   //imprimir mensaje de Aviso sobre reinicio remoto de unidad.
  ESP.restart();              
}

void commands(String &payload){
  Serial.println(F("mensaje recibido de topico commandos"));
  const int capacity = JSON_OBJECT_SIZE(3);
  StaticJsonDocument<capacity> edin_operation_json;
  
  DeserializationError err = deserializeJson(edin_operation_json, payload);
  
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
    return;
  }

  id_de_operacion = edin_operation_json["idOperation"] | "idOperation";
  
  Serial.print("idOperation: ");
  Serial.println(id_de_operacion);
  if (id_de_operacion == "reboot"){
    ESPreboot();
  }else{
    Serial.println(F("toro ese JSON por nara"));
  }
}

void clear_display () {
    char CLR_String[NUM_DIGITS+1] = {CLR,CLR,CLR,CLR,CLR,CLR};

    NSA1166Display.DisplayString(CLR_String, 0);
  
}

void ChainPriceDisplay(String &payload){
  Serial.println(F("mensaje recibido de topico commandos"));
  const int capacity = JSON_OBJECT_SIZE(8);
  StaticJsonDocument<capacity> ChainCoinDisplay_json;
  
  DeserializationError err = deserializeJson(ChainCoinDisplay_json, payload);
  
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
    return;
  }

  Display_Coin_name_json = ChainCoinDisplay_json["Coin"]| "Coin_Name";
  Display_CoinPrice_json = ChainCoinDisplay_json["CoinPrice"]| "Coin_Coinprice";

  Serial.print(F("Coin= "));
  Serial.print(Display_Coin_name_json);
  Serial.print(F(" : "));
  Serial.print(F("Price= "));
  Serial.print(Display_CoinPrice_json);

 int str_len_Coin_price = Display_CoinPrice_json.length() + 1;
 char char_array_CoinPrice[str_len_Coin_price];
 Display_CoinPrice_json.toCharArray(char_array_CoinPrice, str_len_Coin_price);

 int str_len_Coin_name = Display_Coin_name_json.length() + 1;
 char char_array_Coin_Name[str_len_Coin_name]; 
 Display_Coin_name_json.toCharArray(char_array_Coin_Name, str_len_Coin_name);

 char tempString[7] = {'0','0','0','0','0','0'}; //Used for sprintf
 
 for(int i =0;i<100;i++) {

    tempString[0] = char_array_Coin_Name[0];
    tempString[1] = char_array_Coin_Name[1];
    tempString[2] = char_array_Coin_Name[2];
    tempString[3] = char_array_Coin_Name[3];
    tempString[4] = char_array_Coin_Name[4];
    tempString[5] = char_array_Coin_Name[5];
   
   NSA1166Display.DisplayString(tempString, 0); //(numberToDisplay, decimal point location)
   delay(10);
 }
 clear_display (); //clears display
 memset(tempString, 0, sizeof(tempString)); 

 for(int i =0;i<100;i++) {
   tempString[0] = char_array_CoinPrice[0];
   tempString[1] = char_array_CoinPrice[1];
   tempString[2] = char_array_CoinPrice[2];
   tempString[3] = char_array_CoinPrice[3];
   tempString[4] = char_array_CoinPrice[4];
   tempString[5] = char_array_CoinPrice[5];
   
   NSA1166Display.DisplayString(tempString, 0);
   delay(10);
 }
 clear_display (); //clears display
 delay(1000);
}

// !!REPLACEME!!
// The MQTT callback function for commands and configuration updates
// Place your message handler code here.
void messageReceived(String &topic, String &payload){
  Serial.println("incoming: " + topic + " - " + payload);
  
  if (topic == commadsTopic)
  {
    Serial.println(F("Remote Device commnad received"));                                                                    //imprimir mensaje de Aviso sobre reinicio remoto de unidad.
    commands(payload);
  }
  if (topic== ChainCoinTopic)
  {
    Serial.println(F("Remote Display massage received"));
    ChainPriceDisplay(payload);
  }
  
}
///////////////////////////////

// Initialize WiFi and MQTT for this board
Client *netClient;
CloudIoTCoreDevice *device;
CloudIoTCoreMqtt *mqtt;
MQTTClient *mqttClient;
unsigned long iat = 0;
String jwt;

///////////////////////////////
// Helpers specific to this board
///////////////////////////////
String getDefaultSensor(){
  return "Wifi: " + String(WiFi.RSSI()) + "db";
}

String getDeviceState(){

  uint32_t chipId = 0;

  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  
  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getSdkVersion(), ESP.getChipRevision());
  Serial.printf("This chip has %d cores\n", ESP.getFlashChipSpeed());
  Serial.print("Chip ID: "); Serial.println(chipId);

  const int capacity = JSON_OBJECT_SIZE(5);
  StaticJsonDocument<capacity> edin_json_config_doc;
  // create an object
  JsonObject object = edin_json_config_doc.to<JsonObject>();
    
  char buf[16];
  sprintf(buf, "IP:%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );
  Serial.println(String(buf));
  object["chipID"]         = chipId ;
  object["IpNodo"]         = String (buf);
  object["State"]          = "ON";
    
  String output;
  serializeJson(object, output);                                                                  //SAve CPU cycles by calculatinf the size.
  Serial.println(F("publishing device manageTopic metadata:"));
  Serial.println(output);
  return output;
}

String getJwt(){
  iat = time(nullptr);
  Serial.println("Refreshing JWT");
  jwt = device->createJWT(iat, jwt_exp_secs);
  return jwt;
}

void setupWifi(){
  Serial.println("Starting wifi");

  WiFi.mode(WIFI_STA);
  // WiFi.setSleep(false); // May help with disconnect? Seems to have been removed from WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
  }

  configTime(0, 0, ntp_primary, ntp_secondary);
  Serial.println("Waiting on time sync...");
  while (time(nullptr) < 1510644967){
    delay(10);
  }
}

void connectWifi(){
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
}

///////////////////////////////
// Orchestrates various methods from preceeding code.
///////////////////////////////
bool publishTelemetry(String data){
  return mqtt->publishTelemetry(data);
}

bool publishTelemetry(const char *data, int length){
  return mqtt->publishTelemetry(data, length);
}

bool publishTelemetry(String subfolder, String data){
  return mqtt->publishTelemetry(subfolder, data);
}

bool publishTelemetry(String subfolder, const char *data, int length){
  return mqtt->publishTelemetry(subfolder, data, length);
}

bool publishState(String data){
  return mqtt->publishState(data);
}

void connect(){
  connectWifi();
  mqtt->mqttConnect();
}

void setupCloudIoT(){
  device = new CloudIoTCoreDevice(
      project_id, location, registry_id, device_id,
      private_key_str);

  setupWifi();
  netClient = new WiFiClientSecure();
  ((WiFiClientSecure*)netClient)->setCACert(primary_cert);
  mqttClient = new MQTTClient(512);
  mqttClient->setOptions(180, true, 1000); // keepAlive, cleanSession, timeout
  mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
  mqtt->setUseLts(true);
  mqtt->startMQTT();
}

