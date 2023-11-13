const byte latchPin = 11; 
const byte clockPin = 10; 
const byte dataPin = 12; 

const byte segD1 = 4;
const byte segD2 = 5;
const byte segD3 = 6;
const byte segD4 = 7;

const byte lapButtonPin = A0;  
const byte startStopButtonPin = A1; 
const byte resetButtonPin = A2;  

const byte regSize = 8;

const byte displayCount = 4;
byte displayDigits[] = {
  segD1, segD2, segD3, segD4
};

unsigned long elapsedTime = 0;
unsigned int lapTime = 0;
unsigned int lastElapsedTime = 0; 
bool isRunning = false;

unsigned long lastButtonCheck = 0;
const int buttonCheckInterval = 50;

const int maxLaps = 4;
unsigned int lapTimes[maxLaps];
const int maxStoredPresses = 4;
unsigned long lapButtonPressTimes[maxStoredPresses];
int currentStoredPress = 0;
byte currentLap = 0;
byte currentDisplay = 3;  

const bool displayOff = HIGH;
const bool displayOn = LOW;


byte byteEncodings[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], displayOff);
  }

  pinMode(lapButtonPin, INPUT_PULLUP);
  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);

  displayInitialValue();  // "000.0"

  //vector pentru lapTimes 
  for (int i = 0; i < maxLaps; i++) {
    lapTimes[i] = 0;
  }
}

void displayInitialValue() {
  for (int i = 0; i < displayCount; i++) {
    byte encoding = byteEncodings[0];
    if (i == 2) {
      bitSet(encoding, 0);
    }
    turnOffDisplays();
    writeReg(encoding);
    turnOnDisplay(i);
    delay(5);
    writeReg(B00000000);
  }
}


void loop() {
  checkButtons();

  if (isRunning) {
    elapsedTime = millis() - lapTime;
    updateDisplay(elapsedTime / 10);
  } else {
    
    updateDisplay(elapsedTime / 10);
  }
}


void updateDisplay(unsigned long time) {
  byte currentDisplay = 3;

  byte tempDisplays[displayCount];
  for (int i = 0; i < displayCount; i++) {
    time /= 10;
    tempDisplays[i] = (time) % 10;
  }

  for (int i = 0; i < displayCount; i++) {
    byte lastDigit = tempDisplays[i];
    byte encoding = byteEncodings[lastDigit];

    if (currentDisplay == 2) {
      bitSet(encoding, 0);
    }
    
    turnOffDisplays();
    writeReg(encoding);
    turnOnDisplay(currentDisplay);
    delay(5);

    currentDisplay--;
    writeReg(B00000000);
  }
}


void checkButtons() {
  if (millis() - lastButtonCheck > buttonCheckInterval) {
    lastButtonCheck = millis();

    if (digitalRead(lapButtonPin) == LOW) {
      if (isRunning) {
        saveLapButtonPress();
      } else {
        resetSavedLaps();
      }
  }

    if (digitalRead(startStopButtonPin) == LOW) {
      toggleStartStop();
    }

    if (digitalRead(resetButtonPin) == LOW) {
      if (isRunning) {
        // Nu se intampla nimic daca este apasat in timpul functionarii
      } else {
        resetTimer();
      }
    }
  }
}

void saveLap() {
  if (currentLap < maxLaps) {
    lapTimes[currentLap] = elapsedTime;
    currentLap++;
    delay(500); 
  }
}

void resetSavedLaps() {
  if (!isRunning) {
    currentLap = 0;
    turnOffDisplays();
    updateDisplay(0); 
    delay(500);

    // afisez ultimele 4 apasari ale butonului
    displayLastLapButtonPresses();
  }
}

void toggleStartStop() {
  if (!isRunning) {
    // porneste timpul
    isRunning = true;
    lapTime = millis() - elapsedTime;
  } else {
    // oprste timpul
    isRunning = false;
    lastElapsedTime = elapsedTime;  // salvez ultimul timp in functiune cand cronometrul este pe pauza
  }
}

void resetTimer() {
  isRunning = false;
  elapsedTime = 0;
  lapTime = 0;
}

void turnOffDisplays() {
  for (byte i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], displayOff);
  }
}

void turnOnDisplay(byte displayNumber) {
  digitalWrite(displayDigits[displayNumber], displayOn);
}

void displayLastLapButtonPresses() {
  for (int i = 0; i < maxStoredPresses; i++) {
    if (lapButtonPressTimes[i] > 0) {
      unsigned long lapTime = lapButtonPressTimes[i] - lastElapsedTime;
      updateDisplay(lapTime);
      delay(500);
    }
  }
}

void resetLapButton() {
  pinMode(lapButtonPin, INPUT_PULLUP);
}

void saveLapButtonPress() {
  lapButtonPressTimes[currentStoredPress] = millis();
  currentStoredPress = (currentStoredPress + 1) % maxStoredPresses;
}

void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}
