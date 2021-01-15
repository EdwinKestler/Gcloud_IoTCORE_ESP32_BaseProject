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
const char *password = "M!n!g3r2019";

// Cloud iot details.
const char *project_id = "flatbox-serverless-demos";
const char *location = "us-central1";
const char *registry_id = "atest-registry";
const char *device_id = "atest-dev";

// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

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
    "f7:5e:03:71:00:9e:9c:d9:c7:29:a0:df:a6:72:9f:"
    "1e:91:32:42:4c:12:e7:b9:77:65:bb:ae:04:b6:51:"
    "01:7b";
    
// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

const char *root_cert =
    "-----BEGIN CERTIFICATE-----\n"
    "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\n"
    "dzeUaFF4PZYvB5on3IW8vx1Szsk9ohk6hVI=\n"
    "-----END CERTIFICATE-----\n";

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};