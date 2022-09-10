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
const char *device_id = "esp32test";

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
const char *private_key_str = "ee:65:de:f8:65:8a:18:bb:02:9e:e5:f0:81:c7:81:"
    "28:3f:46:6e:18:6d:1f:2b:f3:fa:87:e8:cc:f6:e5:"
    "82:89";
    
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
    "MIIFdzCCBF+gAwIBAgIRAMtWVBP6211QCg9c79Q6T+0wDQYJKoZIhvcNAQELBQAw\n"
    "RjELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM\n"
    "TEMxEzARBgNVBAMTCkdUUyBDQSAxQzMwHhcNMjIwODIyMDgyNTM1WhcNMjIxMTE0\n"
    "MDgyNTM0WjAeMRwwGgYDVQQDExNtcXR0Lmdvb2dsZWFwaXMuY29tMIIBIjANBgkq\n"
    "hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAp8flr808U2bayzO4K4pNuxql7pYjwE2p\n"
    "R2yODo+qqqZF4rO2j51UpBQZMx2BX/ai1uINTvHBGDo2BDcMaqgb84mJF2fVBDuO\n"
    "XnNYHBrd9C2us4qYBppS4flhmZEZLuI7trsoAOzz+H1EE8eTRnl3ZQFAeM4MfM1A\n"
    "dpurw298K9TCZv7lYZ5KgLTXgHO9zvP507SENOQXnsJg/STKsLl4lhfEcmVha6d/\n"
    "+Odaoft+mFv1Mo7Tduk1tTWp7+cnpKFdOWjEl76c796pl7bdd4XtozfpRIMODS5I\n"
    "LniEKxwBIhHoMUvPpdk+vIWRUv0QP9jytTnSAPFA5eq0faC+SSCdewIDAQABo4IC\n"
    "hjCCAoIwDgYDVR0PAQH/BAQDAgWgMBMGA1UdJQQMMAoGCCsGAQUFBwMBMAwGA1Ud\n"
    "EwEB/wQCMAAwHQYDVR0OBBYEFKFkC5Km+Yk3ay8EluYkuZ0GfQpvMB8GA1UdIwQY\n"
    "MBaAFIp0f6+Fze6VzT2c0OJGFPNxNR0nMGoGCCsGAQUFBwEBBF4wXDAnBggrBgEF\n"
    "BQcwAYYbaHR0cDovL29jc3AucGtpLmdvb2cvZ3RzMWMzMDEGCCsGAQUFBzAChiVo\n"
    "dHRwOi8vcGtpLmdvb2cvcmVwby9jZXJ0cy9ndHMxYzMuZGVyMDgGA1UdEQQxMC+C\n"
    "E21xdHQuZ29vZ2xlYXBpcy5jb22CGG1xdHQtbXRscy5nb29nbGVhcGlzLmNvbTAh\n"
    "BgNVHSAEGjAYMAgGBmeBDAECATAMBgorBgEEAdZ5AgUDMDwGA1UdHwQ1MDMwMaAv\n"
    "oC2GK2h0dHA6Ly9jcmxzLnBraS5nb29nL2d0czFjMy96ZEFUdDBFeF9Gay5jcmww\n"
    "ggEEBgorBgEEAdZ5AgQCBIH1BIHyAPAAdwApeb7wnjk5IfBWc59jpXflvld9nGAK\n"
    "+PlNXSZcJV3HhAAAAYLE3ytYAAAEAwBIMEYCIQC5Z4zu0brXPoO1g+LBxKFhBpwY\n"
    "oevaDTQTCyGpMvk8xwIhALbDZkOOv5aMBl/W7W1CmE1HJYPKAnVBYBdlVsCco8XL\n"
    "AHUABZwB0yDgB4QTlYBJjRF8kDJmr69yULWvO0akPhGEDUoAAAGCxN8rhgAABAMA\n"
    "RjBEAiBQHYM8vYym5x38RBIe45kywAjsxwrGShqgduNuelVovgIgQSOLF5toKez4\n"
    "8SyBIMjEQJkR83WAoe9itEs8g31ozwQwDQYJKoZIhvcNAQELBQADggEBAB2qJB2k\n"
    "JDiHpk12LGCMRiajm/5if3tsXQXSpmyqLldAQMIfPlPtV3RoVbC0OQSyKLmpfoRB\n"
    "jcrq1HShcW0bRzBVl/8upEGEy3g5pE4VAB2mHl2zYTmj4d8+mc81Hl9px/wE85Xe\n"
    "J895MS1NELjydPCP/kYnqvAl0kZtGjFBWt/o3UJ9vyBGd2HMvB2jPm+oNJJzV9FQ\n"
    "LkoSYj45gz5x4mIGN8OOyhxvoHoLBFLt08Cp3/bhMehr85Qg3huslxZhix8ECCtf\n"
    "puXVcpCwz/O0R3tSqDpl6XTU2bg7mPcG0SgqzBNHVLfmQMMucNp0mGgPggN6eAtD\n"
    "aIbUmbr20Jnjlg8=\n"
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

