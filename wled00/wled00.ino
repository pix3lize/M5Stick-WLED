/*
 * WLED Arduino IDE compatibility file.
 * 
 * Where has everything gone?
 * 
 * In April 2020, the project's structure underwent a major change. 
 * Global variables are now found in file "wled.h"
 * Global function declarations are found in "fcn_declare.h"
 * 
 * Usermod compatibility: Existing wled06_usermod.ino mods should continue to work. Delete usermod.cpp.
 * New usermods should use usermod.cpp instead.
 */
#include "wled.h"
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <M5StickCPlus.h>
#include "AXP192.h"
TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 * 
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    26

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 240

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

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
  // for(int i=0; i<5; i++) { // For each pixel in strip...
  //   strip2.setPixelColor(i, strip2.Color(255,   0,   0));         //  Set pixel's color (in RAM)
  //   strip2.show();                          //  Update strip to match
  //   delay(50);                           //  Pause for a moment
  // }

  WLED::instance().setup();
}

void loop() {

    // text print  
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
  tftSprite.printf("Bat:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
  tftSprite.setCursor(0, 30);  
  tftSprite.printf("USB:\r\n  V: %.3fv  I: %.3fma\r\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
  tftSprite.setCursor(0, 50);    
  tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
  tftSprite.pushSprite(25, 70);

  // tftSprite.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
  // //M5.Lcd.printf("AXP Temp: %.1fC \r\n", M5.Axp.GetTempInAXP192());
  // tftSprite.setCursor(0, 20);   
  // tftSprite.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
  // tftSprite.pushSprite(25, 90);

  //M5.Lcd.printf("Bat power %.3fmw", M5.Axp.GetBatPower());
  M5.update();

  WLED::instance().loop();
}
