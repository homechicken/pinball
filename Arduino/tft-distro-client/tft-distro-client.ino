#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/* I had to change the Adafruit_ST7735.cpp's initR() function where BLACKTAB was executed and add 
 *  
 _colstart = 2;
 _rowstart = 1;

to fix a weird display issue on the DF_ROBOT 1.8" TFT LCD screen. initR(GREENTAB) worked, but the colors were weird.
 */

#define TFT_CS 8
#define TFT_RST -1
#define TFT_DC 7
#define SD_CS 6

// Mode Definitions
#define MODE_ATTRACT 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define MODE_4 4
#define MODE_5 5
#define MODE_6 6
#define MODE_7 7
#define MODE_8 8
#define MODE_9 9
#define MODE_10 10
#define MODE_11 11
#define MODE_12 12
#define MODE_13 13
#define MODE_14 14
#define MODE_15 15

// Mode pins
#define MODEPIN_0 2
#define MODEPIN_1 3
#define MODEPIN_2 4
#define MODEPIN_3 5
#define HITPIN 9

// Screen declaration
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Global variables
int currentMode = 0;
int hitState = false;

void setup() {
  pinMode(MODEPIN_0, INPUT);
  pinMode(MODEPIN_1, INPUT);
  pinMode(MODEPIN_2, INPUT);
  pinMode(MODEPIN_3, INPUT);
  pinMode(HITPIN, INPUT);
  
  Serial.begin(9600);
  Serial.print(F("Client TFT starting up..."));
  uint16_t msTime = millis();

  tft.initR(INITR_BLACKTAB);
  msTime = millis() - msTime;
  Serial.println(msTime, DEC);

  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  modeChange(MODE_ATTRACT);
  delay(1000);
}

void loop() {
  delay(250); // change the checks to interrupts?
  checkForHitChange();
  
  checkForModeChange();
}

void checkForHitChange() {
  if(!hitState && digitalRead(HITPIN) == HIGH) {
    Serial.print(F("A hit was triggered!"));
    recordHit();
    hitState = true;
    recordHit();
  }
}

void recordHit() {
  tft.invertDisplay(true);
  
}
void checkForModeChange() {
  int tMode = readMode();
  if(tMode != currentMode) {
    Serial.println(F("checkForModeChange() triggered"));
    modeChange(tMode);
  }
}

void modeChange(const int mode) {
  hitState = false; // clear the hit state on mode change
  loadMode(mode);
  currentMode = mode;
}

void loadMode(const int mode) {
  tft.invertDisplay(false);
  String str = "Loading mode " + String(mode, DEC);
  Serial.println(str.c_str());
  tftDrawText(str.c_str(), ST77XX_YELLOW);
}

int readMode() {
  int tMode = -1;
  
  bool p0 = false;
  bool p1 = false;
  bool p2 = false;
  bool p3 = false;
  
  if(digitalRead(MODEPIN_0) == HIGH) {
    p0 = true;
  }
  if(digitalRead(MODEPIN_1) == HIGH) {
    p1 = true;
  }
  if(digitalRead(MODEPIN_2) == HIGH) {
    p2 = true;
  }
  if(digitalRead(MODEPIN_3) == HIGH) {
    p3 = true;
  }

  if(p0) { // 1 X X X
    if(p1) { // 1 1 X X
      if(p2) { // 1 1 1 X
        if(p3) {
          tMode = MODE_15;
        } else {
          tMode = MODE_14;
        }
      } else { // 1 1 0 X
        // !p2
        if(p3) {
          tMode = MODE_13;
        } else {
          tMode = MODE_12;
        }
      }
    } else {
      //!p1
      if(p2) { // 1 0 1 X
        if(p3) {
          tMode = MODE_11;
        } else {
          tMode = MODE_10;
        }
      } else { // 1 0 0 X
        if(p3) {
          tMode = MODE_9;
        } else {
          tMode = MODE_8;
        }
      }
    }
  } else {
    // !p0 // 0 X X X
    if(p1) { // 0 1 X X
      if(p2) { // 0 1 1 X
        if(p3) {
          tMode = MODE_7;
        } else {
          tMode = MODE_6;
        }
      } else { // 0 1 0 X
        if(p3) {
          tMode = MODE_5;
        } else {
          tMode = MODE_4;
        }
      }
    } else { // 0 0 X X
      if(p2) {
        if(p3) {
          tMode = MODE_3;
        } else {
          tMode = MODE_2;
        }
      } else { // 0 0 0 X
        if(p3) {
          tMode = MODE_1;
        } else {
          tMode = MODE_ATTRACT;
        }
      }
    }
  }

  return tMode;
}

void tftDrawText(char *text, const uint16_t color) {
  /* ST77XX_[BLACK|WHITE|RED|GREEN|BLUE|CYAN|MAGENTA|YELLOW|ORANGE] */
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
