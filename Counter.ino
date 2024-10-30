#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include <YoutubeApi.h>
#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>

// LED MATRIX DISPLAY DEFINITION
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  4
#define CLK_PIN   D6  // or SCK
#define DATA_PIN  D8  // or MOSI
#define CS_PIN    D7  // or SS

#define PIN   D4
#define LED_NUM 3 //CHANGE this to the number of LEDs you have
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const char* WIFI_SSID = ""; //ADD YOUR SSID HERE
const char* WIFI_PASSWORD = ""; //ADD YOUR PASS HERE

#define CHANNEL_ID "" //ADD YOUR CHANNEL ID HERE

#define API_KEY "" //ADD YOUR API KEY HERE
WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

void setup() {
  Serial.begin(115200);

  leds.begin();

  //initialize the LED MAtrix 4, 8x8
  myDisplay.begin();
  myDisplay.setIntensity(10);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setPause(2000);
  myDisplay.setSpeed(40);
  myDisplay.displayClear();
  myDisplay.print("Hello");


  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  auto status = WiFi.status();
  while ( (status != WL_CONNECTED) && (status != WL_CONNECT_FAILED) ) {
    delay(300);
    status = WiFi.status();
    myDisplay.print(".");
    delay(300);
    myDisplay.print("..");
    delay(300);
    myDisplay.print("...");
    delay(300);
    myDisplay.displayClear();
  }
  myDisplay.displayClear();
  myDisplay.print("Done!");
  client.setInsecure();
}

void led_set(uint8 R, uint8 G, uint8 B) {
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, leds.Color(R, G, B));
    leds.show();
    delay(66);
  }
}


String formatSubscriberCount(long int count) {
  if (count < 1000) {
     return String(count);
  }
  else if (count < 10000) { // Less than 10K
     return String(count);
  } else if (count < 100000) { // Less than 100K
     int thousands = count / 1000;
     int remainder = (count % 1000) / 10; // First two digits after the comma
     return String(thousands) + "," + (remainder < 10 ? "0" : "") + String(remainder) + "K";
  }
  else if (count < 1000000) { // Less than 1M
     int thousands = count / 1000;
     int remainder = (count % 1000) / 100; // First one digits after the comma
     return String(thousands) + "," + (remainder < 1 ? "0" : "") + String(remainder) + "K";
  } else if (count < 10000000) { // Less than 10M
    int millions = count / 1000000;
    int remainder = (count % 1000000) / 100000; // First two digits after the comma
    return String(millions) + "," + (remainder < 1 ? "0" : "") + String(remainder) + "M";
  } else { // More than 10M
    int millions = count / 1000000;
    return String(millions) + "M";
  }
}



String getSubscriberCount() {
  if(api.getChannelStatistics(CHANNEL_ID)) {
    return String(api.channelStats.subscriberCount);
  }
  return "Error";
}


void handleFetchSubscribers() {
  String rawSubscriberCountString = getSubscriberCount();
  long int rawSubscriberCount = rawSubscriberCountString.toInt();
  String formattedSubscriberCount = formatSubscriberCount(rawSubscriberCount);
  
  myDisplay.displayClear();
  myDisplay.print(formattedSubscriberCount);
}


int loops = 0;
int max_loops = 60*1000;

void loop() {
  //run every second
  led_set(50, 50, 50);
  led_set(80, 80, 100);

  led_set(50, 50, 50);
  led_set(100, 80, 80);

  led_set(50, 50, 50);
  led_set(80, 100, 80);
  loops = loops + 1;

  if (loops >= max_loops) {
    handleFetchSubscribers();
    loops = 0;
  }
}
