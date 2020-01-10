/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 by Andreas Loeffler
 *
 * oled code based on work by (ESP8266_and_ESP32_Oled_Driver_for_SSD1306_display)
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */


#define DEBUG_ESP_SSL 1
#define DEBUG 1

#include "debug_print.h"
#include "wifi_mqtt_creds.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include "server_mqtt.crt.h"
#include "client.crt.h"
#include "client.key.h"

String ipAddr;
String dnsAddr;
String rssi;


const unsigned max_wifi_wait_seconds = 30;
const char* mqtt_device_id = "wemosD1_oled";
const int maxMqttRetry = 5;
bool mqttConnected = false;

const char* VERSION = "1.2.3";


BearSSL::X509List   server_cert(server_crt_str);
BearSSL::X509List   client_crt(client_crt_str);
BearSSL::PrivateKey client_key(client_key_str);

BearSSL::WiFiClientSecure net;
PubSubClient mqttClient(net);



#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
// Include custom images
//#include "images.h"
#include "mqtt_img.h"
// Initialize the OLED display using Wire library
// D3 -> SDA
// D5 -> SCL
SSD1306Wire display(0x3c, D3, D5);
//OLEDDisplayUi ui(&display);


void rssiOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(WiFi.RSSI()));
}

void drawLogo() {
  display.clear();
  //display.drawXbm(34, 12, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.drawXbm(40, 2, mqtt_width, mqtt_height, mqtt_bits);
  display.display();
}

void drawInfo() {
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 50, "v" + String(VERSION) + ", ip: " + ipAddr);
  display.display();
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_16);

  // The coordinates define the left starting point of the text
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0 + x, 16 + y, "IP:   " + ipAddr);

  // The coordinates define the right end of the text
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  //  display->drawString(0 + x, 32 + y, "mqtt: " + mqtt_val);
}


int setupWifi() {
  DEBUG_PRINTLN();
  DEBUG_PRINTLN("Connecting to wifi");

  WiFi.begin(wifi_ssid, wifi_pass);

  unsigned retry_counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_PRINT(".");
    retry_counter++;
    if (retry_counter > max_wifi_wait_seconds) {
      DEBUG_PRINTLN(" TIMEOUT!");
      return 1;
    }
  }
  ipAddr  = WiFi.localIP().toString();
  dnsAddr = WiFi.dnsIP().toString();

  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(ipAddr);
  DEBUG_PRINTLN("DNS address: ");
  DEBUG_PRINTLN(dnsAddr);

  return 0;
}

void mqttConnect()
{
  DEBUG_PRINT("Attempting MQTT connection...");
  String connect_msg = "CONNECTED ";
  connect_msg += VERSION;

  // Attempt to connect
  if (mqttClient.connect(mqtt_device_id, mqtt_user, mqtt_pass, "/wemos/oled/state", 1, 1, "OFFLINE")) {
    DEBUG_PRINTLN("connected");
    // Once connected, publish an announcement...
    mqttClient.publish("/wemos/oled/state", connect_msg.c_str(), true);
    mqttClient.subscribe("/wemos/oled/set");
  }
  else {
    DEBUG_PRINT("failed, mqttClient.state = ");
    DEBUG_PRINTLN(mqttClient.state());
    DEBUG_PRINTLN(state2str(mqttClient.state()));
  }
}


void mqttCallback(char* topic, byte* payload, unsigned int length)
{
  DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("] ");

  char value[length+1];
  memcpy(value, payload, length);
  value[length] = '\0';

  DEBUG_PRINTLN(value);

  if (0 == strcmp("/wemos/oled/set", topic)) {
    // String oled_text((char*)payload);
    // oled_text[length] = '\0';

    DEBUG_PRINTLN("wemos set");

    if (0 == memcmp("logo", payload, 4)) {
      DEBUG_PRINTLN("wemos set logo");
      drawLogo();
    }
    else {
      // Align text vertical/horizontal center
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      //display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      display.setFont(ArialMT_Plain_16);
      //display.drawString(display.getWidth()/2, display.getHeight()/2, value);
      display.drawString(1, display.getHeight()/2, value);
      display.display();
    }
  }
}


void setup() {

  DEBUG_BEGIN(115200);
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("setup begin...");
  DEBUG_PRINTLN( ESP.getChipId() );

  // oled setup
  display.init();
  display.flipScreenVertically();
  display.setContrast(200);
  display.clear();

  drawLogo();

  DEBUG_PRINTLN("starting setupWifi()");
  setupWifi();
  drawInfo();

  // Use WiFiClientSecure class to create TLS connection ****
  DEBUG_PRINTLN("setTrustAnchors()");
  net.setTrustAnchors(&server_cert);
  //  DEBUG_PRINTLN("allowSelfSignedCerts()");
  //  net.allowSelfSignedCerts();
  DEBUG_PRINTLN("setClientRSACert() client cert and key");
  net.setClientRSACert(&client_crt, &client_key);

  DEBUG_PRINTLN("set mqtt host/port and callback");
  mqttClient.setServer(mqtt_host, mqtt_port);
  mqttClient.setCallback(mqttCallback);

  DEBUG_PRINTLN("calling mqttConnect()");
  mqttConnect();

}


void loop() {

  if (!mqttClient.connected()) {
    DEBUG_PRINTLN("no mqtt connection!!!");
    mqttConnect();
  }
  else {
    mqttClient.loop();
  }

}
