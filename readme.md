
## M5Stick-WLED 
This repository to show how to modify WLED source code to install WLED on M5Stick. Below are the steps needed: 

- **Change the platformio.ini**
  Pleaase modify the env:m5atom file and add the library dependency as shown below
  ```ini
  [env:m5atom]
  board = esp32dev
  build_unflags = ${common.build_unflags}
  build_flags = ${common.build_flags_esp32} -D LEDPIN=26 -D BTNPIN=37
  lib_ignore =
	ESPAsyncTCP
	ESPAsyncUDP
  platform = espressif32@2.0
  lib_deps = 
    adafruit/Adafruit NeoPixel @ ^1.8.0
    https://github.com/m5stack/M5StickC-Plus.git
  ```
- **Modify the WLED00.ino header**
  Pleaase modify the WLED00.ino file and add the library dependency as shown below
  ```cpp
  #include "wled.h"
  #include <Adafruit_NeoPixel.h>

  #ifdef __AVR__
  #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
  #endif

  #include <M5StickCPlus.h>
  #include "AXP192.h"
  TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);
  
  // Which pin on the Arduino is connected to the NeoPixels?
  // On a Trinket or Gemma we suggest changing this to 1:
  #define LED_PIN    26
  
  // How many NeoPixels are attached to the Arduino?
  #define LED_COUNT 240
  ```
- **Modify the WLED00.ino body**
  Pleaase modify the WLED00.ino file and add the library dependency as shown below
  ```cpp
  void setup() {
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
    #endif
    // END of Trinket-specific code.

    M5.begin();
    M5.Lcd.setRotation(1);
    
    tftSprite.createSprite(160, 80);
    tftSprite.setRotation(3);

    M5.Axp.EnableCoulombcounter();
  
    strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip2.show();            // Turn OFF all pixels ASAP
    strip2.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
    M5.Lcd.fillScreen(BLACK); 
      
    WLED::instance().setup();
  }
  
  void loop() {  
   
    M5.Lcd.setCursor(62, 10);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("Thank you\r\n");
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setCursor(60, 30);
    M5.Lcd.printf("Aircoookie\r\n");
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.setTextColor(ORANGE);
    M5.Lcd.printf("Greet from Singapore");
  
    tftSprite.pushSprite(25, 70);
    tftSprite.setCursor(0, 0);  
  
    tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
    tftSprite.setCursor(0, 10);
    tftSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(),   M5.Axp.GetBatCurrent());
    tftSprite.setCursor(0, 30);  
    tftSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage()  , M5.Axp.GetVBusCurrent());
    tftSprite.setCursor(0, 50);    
    tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
    tftSprite.pushSprite(25, 70);
  
    M5.update();
  
    WLED::instance().loop();
  }
  ```
----------

<p align="center">
  <img src="/images/wled_logo_akemi.png">
  <a href="https://github.com/Aircoookie/WLED/releases"><img src="https://img.shields.io/github/release/Aircoookie/WLED.svg?style=flat-square"></a>
  <a href="https://raw.githubusercontent.com/Aircoookie/WLED/master/LICENSE"><img src="https://img.shields.io/github/license/Aircoookie/wled?color=blue&style=flat-square"></a>
  <a href="https://wled.discourse.group"><img src="https://img.shields.io/discourse/topics?colorB=blue&label=forum&server=https%3A%2F%2Fwled.discourse.group%2F&style=flat-square"></a>
  <a href="https://discord.gg/KuqP7NE"><img src="https://img.shields.io/discord/473448917040758787.svg?colorB=blue&label=discord&style=flat-square"></a>
  <a href="https://github.com/Aircoookie/WLED/wiki"><img src="https://img.shields.io/badge/quick_start-wiki-blue.svg?style=flat-square"></a>
  <a href="https://github.com/Aircoookie/WLED-App"><img src="https://img.shields.io/badge/app-wled-blue.svg?style=flat-square"></a>
  <a href="https://gitpod.io/#https://github.com/Aircoookie/WLED"><img src="https://img.shields.io/badge/Gitpod-ready--to--code-blue?style=flat-square&logo=gitpod"></a>

  </p>
  
# Welcome to my project WLED! ✨

A fast and feature-rich implementation of an ESP8266/ESP32 webserver to control NeoPixel (WS2812B, WS2811, SK6812) LEDs or also SPI based chipsets like the WS2801 and APA102!

## ⚙️ Features
- WS2812FX library integrated for over 100 special effects  
- FastLED noise effects and 50 palettes  
- Modern UI with color, effect and segment controls  
- Segments to set different effects and colors to parts of the LEDs  
- Settings page - configuration over network  
- Access Point and station mode - automatic failsafe AP  
- Support for RGBW strips  
- Up to 250 user presets to save and load colors/effects easily, supports cycling through them.  
- Presets can be used to automatically execute API calls  
- Nightlight function (gradually dims down)  
- Full OTA software updatability (HTTP + ArduinoOTA), password protectable  
- Configurable analog clock + support for the Cronixie kit by Diamex  
- Configurable Auto Brightness limit for safer operation  
- Filesystem-based config for easier backup of presets and settings  

## 💡 Supported light control interfaces
- WLED app for [Android](https://play.google.com/store/apps/details?id=com.aircoookie.WLED) and [iOS](https://apps.apple.com/us/app/wled/id1475695033)
- JSON and HTTP request APIs  
- MQTT  
- Blynk IoT  
- E1.31, Art-Net, DDP and TPM2.net
- [Hyperion](https://github.com/hyperion-project/hyperion.ng)
- UDP realtime  
- Alexa voice control (including dimming and color)  
- Sync to Philips hue lights  
- Adalight (PC ambilight via serial) and TPM2  
- Sync color of multiple WLED devices (UDP notifier)  
- Infrared remotes (24-key RGB, receiver required)  
- Simple timers/schedules (time from NTP, timezones/DST supported)  

## 📲 Quick start guide and documentation

See the [wiki](https://github.com/Aircoookie/WLED/wiki)!

[On this page](https://github.com/Aircoookie/WLED/wiki/Learning-the-ropes) you can find excellent tutorials made by the community and helpful tools to help you get your new lamp up and running!

## 🖼️ Images
<img src="/images/macbook-pro-space-gray-on-the-wooden-table.jpg" width="50%"><img src="/images/walking-with-iphone-x.jpg" width="50%">

## 💾 Compatible LED Strips
Type | Voltage | Comments
|---|---|---|
WS2812B | 5v |
WS2813 | 5v | 
SK6812 | 5v | RGBW
APA102 | 5v | C/D
WS2801 | 5v | C/D
LPD8806 | 5v | C/D
TM1814 | 12v | RGBW
WS2811 | 12v | 3-LED segments
WS2815 | 12v | 
GS8208 | 12v |
Analog/non-addressable | any | Requires additional circuitry

## 🧊 Compatible PC RGB Fans and ARGB accessories
Brand | Model | Comments
|---|---|---|
Corsair | HD120 Fan | Uses WS2812B, data-in only
PCCOOLER | Moonlight 5-pack Fans | Uses WS2812B, includes Data-out connector to keep each fan uniquely addressable if wired in series like traditional LED strips
Any | 5v 3-pin ARGB for PC | Any PC RGB device that supports the 5v 3-pin ARGB motherboard header should work fine with WLED. All the major motherboard vendors support the Corsair HD120 and PCCOOLER fans listed, so we can safely assume any device that supports motherboard ARGB 5V 3-Pin standard will work with WLED.


## ✌️ Other

Licensed under the MIT license  
Credits [here](https://github.com/Aircoookie/WLED/wiki/Contributors-&-About)!

Uses Linearicons by Perxis!

Join the Discord server to discuss everything about WLED!

<a href="https://discord.gg/KuqP7NE"><img src="https://discordapp.com/api/guilds/473448917040758787/widget.png?style=banner2" width="25%"></a>

Check out the WLED [Discourse forum](https://wled.discourse.group)!  
You can also send me mails to [dev.aircoookie@gmail.com](mailto:dev.aircoookie@gmail.com), but please only do so if you want to talk to me privately.  
If WLED really brightens up your every day, you can [![](https://img.shields.io/badge/send%20me%20a%20small%20gift-paypal-blue.svg?style=flat-square)](https://paypal.me/aircoookie)


*Disclaimer:*   
If you are sensitive to photosensitive epilepsy it is not recommended that you use this software.  
In case you still want to try, don't use strobe, lighting or noise modes or high effect speed settings.
As per the MIT license, I assume no liability for any damage to you or any other person or equipment.  

