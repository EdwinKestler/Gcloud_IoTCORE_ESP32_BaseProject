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
// This file contains your configuration used to connect to Cloud IoT Core

// Wifi network details.
const char *ssid = "MANAGER";
const char *password = "M@n@g3r2022#";

// Cloud iot details.
const char *project_id = "flatbox-serverless-demos";
const char *location = "us-central1";
const char *registry_id = "esp32registry";
const char *device_id = "esp32s8display";

// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

//subscription Topics

const char commadsTopic[]    = "projects/flatbox-serverless-demos/topics/esp32PublishTopic";                           //Topico del cual se reciben los mensajes de re-inicio
const char ChainCoinTopic[]  = "projects/flatbox-serverless-demos/topics/esp32PublishTopic";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char *private_key_str = 
    "00:2d:6d:f9:aa:2c:93:46:c6:c2:bd:de:00:6f:36:"
    "3b:00:6c:63:22:80:d2:21:88:45:10:8f:00:60:38:"
    "cf:00";
    
// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

const char *primary_cert = "-----BEGIN CERTIFICATE-----\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"0000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000\n"
"-----END CERTIFICATE-----\n";

const char *secondary_cert = 
        "-----BEGIN CERTIFICATE-----\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "Y000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000\n"
        "0000000000000000000000000000000000000000000000000000000000000000n"
        "00000000\n"
        "-----END CERTIFICATE-----\n";
   
// In case we ever need extra topics
//const int ex_num_topics = 0;
//const char* ex_topics[ex_num_topics];
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];

//timer intervals 

unsigned long telemetry_publish_interval = 62000;
unsigned long device_state_publish_interval = 300000;
unsigned long device_LEDstate_publish_interval = 18000;

