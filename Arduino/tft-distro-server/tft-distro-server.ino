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

// Hit Pins
#define HIT_1 12
#define HIT_2 11
#define HIT_3 10

/*#define HIT_4
#define HIT_5
#define HIT_6
#define HIT_7
#define HIT_8
#define HIT_9
#define HIT_10
*/

int currentMode = -1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println(F("Server starting up"));
  
  pinMode(MODEPIN_0, OUTPUT);
  pinMode(MODEPIN_1, OUTPUT);
  pinMode(MODEPIN_2, OUTPUT);
  pinMode(MODEPIN_3, OUTPUT);
  pinMode(HIT_1, OUTPUT);
  pinMode(HIT_2, OUTPUT);
  pinMode(HIT_3, OUTPUT);

  clearAllHits();

  currentMode = MODE_ATTRACT;
  setMode(currentMode);
}

void loop() {
  String str = "Current mode " + String(currentMode, DEC);
  
  int newMode = currentMode + 1;
  if(newMode > MODE_15) {
    newMode = MODE_ATTRACT;
  }

  str += ", new mode " + String(newMode, DEC);
  Serial.println(str.c_str());

  for(int i=0; i <= newMode; ++i) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  
  Serial.println(F("Looping mode change"));
  
  setMode(newMode);

  debug();

  delay(1000);
  setHit(HIT_1);

  delay(500);
  setHit(HIT_2);
  
  delay(500);
  setHit(HIT_3);
}

void setMode(const int mode) {
  String str = "setMode called with " + String(mode, DEC);
  Serial.println(str.c_str());
  
  if(currentMode == mode) {
    // Should the mode be reset??
    Serial.println(F("setMode no mode change"));
    return;
  }
  
  Serial.println(F("Passed setMode checks"));
  
  clearAllHits();
  
  switch(mode) {
    case MODE_ATTRACT:
      Serial.println("switch MODE_ATTRACT");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_1:
      Serial.println("switch MODE_1");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_2:
      Serial.println("switch MODE_2");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_3:
      Serial.println("switch MODE_3");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_4:
      Serial.println("switch MODE_4");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_5:
      Serial.println("switch MODE_5");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_6:
      Serial.println("switch MODE_6");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_7:
      Serial.println("switch MODE_7");
      digitalWrite(MODEPIN_0, LOW);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_8:
      Serial.println("switch MODE_8");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_9:
      Serial.println("switch MODE_9");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_10:
      Serial.println("switch MODE_10");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_11:
      Serial.println("switch MODE_11");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, LOW);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_12:
      Serial.println("switch MODE_12");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_13:
      Serial.println("switch MODE_13");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, LOW);
      digitalWrite(MODEPIN_3, HIGH);
      break;
    case MODE_14:
      Serial.println("switch MODE_14");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, LOW);
      break;
    case MODE_15:
      Serial.println("switch MODE_15");
      digitalWrite(MODEPIN_0, HIGH);
      digitalWrite(MODEPIN_1, HIGH);
      digitalWrite(MODEPIN_2, HIGH);
      digitalWrite(MODEPIN_3, HIGH);
      break;

   default:
     Serial.println(F("Mode not supported!!"));
  }
  currentMode = mode;
}

void setHit(const int p) {
  digitalWrite(p, HIGH);
}

void clearAllHits() {
  Serial.println(F("Clearing hit status"));
  digitalWrite(HIT_1, LOW);
  digitalWrite(HIT_2, LOW);
  digitalWrite(HIT_3, LOW);
}

void debug() {
  uint8_t p0 = digitalRead(MODEPIN_0);
  uint8_t p1 = digitalRead(MODEPIN_1);
  uint8_t p2 = digitalRead(MODEPIN_2);
  uint8_t p3 = digitalRead(MODEPIN_3);
  String str = "Mode pins are set to " + String(p0, DEC) + " ";
  str += String(p1, DEC) + " ";
  str += String(p2, DEC) + " ";
  str += String(p3, DEC);
  Serial.println(str.c_str());
}
