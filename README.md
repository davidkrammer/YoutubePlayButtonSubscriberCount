
# Getting Started


## 1. Fill in your WIFI Credentials
`const char* WIFI_SSID = "";`
`const char* WIFI_PASSWORD = "";`

&nbsp;


## 2. Fill in your Channel ID ([*How to find Channel ID*](https://support.google.com/youtube/answer/3250431?hl=en))
`#define CHANNEL_ID ""`

&nbsp;


## 3. Obtain an API KEY
Step 1: Create a project on *console.cloud.google.com*
Step 2: Go into your newly created Project and open the left Menu
Step 3: Open "**API & Services**" and select "**Enabled APIs & services**"
Step 4: Click on "**+ ENABLE APIS AND SERVICES**"
Step 5: Search for "**Youtube Data API v3**" and click on it
Step 6: Enable the API and wait for you being redirected
Step 7: Click on "**Credentials**" on the newly opened page
Step 8: Click on "**+ CREATE CREDENTIALS**" and select "**API key**"
Step 9: Copy the key and paste it into the code `#define  API_KEY  ""`

&nbsp;


## 4. Install Arduino Libraries
- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- [WiFiClientSecure](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure)
- [MD_Parola](https://github.com/MajicDesigns/MD_Parola)
- [MD_MAX72xx](https://github.com/MajicDesigns/MD_MAX72XX)
- [YoutubeApi](https://github.com/witnessmenow/arduino-youtube-api)
- [ArduinoJson](https://www.arduino.cc/reference/en/libraries/arduinojson/)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- 
&nbsp;


## 5. Upload the Script and have fun 🎉
