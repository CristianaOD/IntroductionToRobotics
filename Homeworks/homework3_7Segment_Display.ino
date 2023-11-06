const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

bool dpState = HIGH;
int currentSegment = 0;  // Segmentul curent
const int segmentPins[8] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};
bool segmentState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};  // Starea segmentelor

unsigned long lastBlinkMillis = 0;
unsigned long blinkInterval = 500;  // Intervalul de clipire pentru segmentul curent

const int segSize = 8;
int travelMatrix[segSize][4] = {
  // U   D   L   R
  {6,  3,  5,  1},  // A
  {6,  3,  5, -1},  // B
  {4, -1,  2,  7},  // C
  {-1,  0,  2,  7},  // D
  {4,  0,  2,  7},  // E
  {6, -1,  5,  0},  // F
  {4, -1, -1,  0},  // G
  {2, -1, -1, -1}    // DP (punct zecimal)
};

int joystickState = -1;  // -1 pentru IDLE
int joystickCenter = 512;
int joystickDeadZone = 50;


void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  for (int i = 0; i < segSize; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
  /*
  // Starea corectă a segmentelor
  segmentState[7] = HIGH; // DP este aprins
  for (int i = 0; i < 8; i++) {
    segmentState[i] = LOW; // Celelalte segmente sunt stinse
  }

  Serial.begin(9600);*/
for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }

  // Starea corectă a segmentelor
  segmentState[7] = HIGH;  // DP este inițial aprins
  dpState = HIGH;  // DP palpitează inițial

  // Palpitare DP în funcția de setup()
  for (int i = 0; i < 3; i++) {
    digitalWrite(segmentPins[7], dpState);
    delay(200);
    dpState = !dpState;
  }

  // Inițializare serial pentru debug
  Serial.begin(9600);

  
}

void handleMovement() {
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  
// Logica pentru detectarea directiei joystick-ului si actualizarea currentSegment
  if (yValue > joystickCenter + joystickDeadZone) {
    if (joystickState != 0) {
      Serial.println("DOWN");
      joystickState = 0;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = travelMatrix[currentSegment][0];
    }
  } else if (yValue < joystickCenter - joystickDeadZone) {
    if (joystickState != 1) {
      Serial.println("UP");
      joystickState = 1;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = travelMatrix[currentSegment][1];
    }
  } else if (xValue < joystickCenter - joystickDeadZone) {
    if (joystickState != 2) {
      Serial.println("LEFT");
      joystickState = 2;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = travelMatrix[currentSegment][2];
    }
  } else if (xValue > joystickCenter + joystickDeadZone) {
    if (joystickState != 3) {
      Serial.println("RIGHT");
      joystickState = 3;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = travelMatrix[currentSegment][3];
    }
  } else if (xValue > joystickCenter - joystickDeadZone && xValue < joystickCenter + joystickDeadZone &&
             yValue > joystickCenter - joystickDeadZone && yValue < joystickCenter + joystickDeadZone) {
    if (joystickState != -1) {
      joystickState = -1;
    }
  }else if (currentSegment == 7 && joystickState != -1) {
    currentSegment = travelMatrix[currentSegment][joystickState];
  }




// Logica pentru aprinderea segmentelor în functie de directie
  if (currentSegment == 0) { // A
    if (joystickState == 0) {
      // Ma duc in jos, aprind segmentul G
      segmentState[6] = HIGH;
      
    } else if (joystickState == 2) {
      // Ma duc în stanga, aprind segmentul F
      segmentState[5] = HIGH;
    } else if (joystickState == 3) {
      // Ma duc în dreapta, aprind segmentul B
      segmentState[1] = HIGH;
    }
  }else if (currentSegment == 1) { // B
    if (joystickState == 0) {
    // Ma duc în jos, aprinde segmentul G
      segmentState[6] = HIGH;
    } else if (joystickState == 2) {
      // Ma duc în stanga, aprinde segmentul F
      segmentState[5] = HIGH;
    }
  // Nu se intampla nimic pentru directia dreapta
  } else if (currentSegment == 2) { // C
     if (joystickState == 0) {
    // Ma duc in jos, aprinde segmentul D
    segmentState[3] = HIGH;
  } else if (joystickState == 2) {
    // Ma duc in stanga, aprinde segmentul E
    segmentState[2] = HIGH;
  } else if (joystickState == 1) {
    // Ma duc in sus, aprinde segmentul G
    segmentState[6] = HIGH;
  } else if (joystickState == 3) {
    // Ma duc in dreapta, aprinde segmentul DP
    segmentState[4] = HIGH;
  }
  } else if (currentSegment == 3) { // D
    if (joystickState == 1) {
    // Ma duc in sus, aprinde segmentul G
    segmentState[6] = HIGH;
  } else if (joystickState == 2) {
    // Ma duc an stanga, aprinde segmentul E
    segmentState[2] = HIGH;
  } else if (joystickState == 3) {
    // Ma duc in dreapta, aprinde segmentul C
    segmentState[1] = HIGH;
  }
  } else if (currentSegment == 4) { // E
    if (joystickState == 1) {
    // Ma duc in sus, aprinde segmentul G
    segmentState[6] = HIGH;
  } else if (joystickState == 3) {
    // Ma duc in dreapta, aprinde segmentul C
    segmentState[1] = HIGH;
  }
  // Nu se intampla nimic pentru directiile in jos si stanga
  } else if (currentSegment == 5) { // F
    if (joystickState == 0) {
    // Ma duc in jos, aprinde segmentul G
    segmentState[6] = HIGH;
  } else if (joystickState == 3) {
    // Ma duc in dreapta, aprinde segmentul B
    segmentState[0] = HIGH;
  }
  // Nu se intampla nimic pentru directiile in sus și stanga
  } else if (currentSegment == 6) { // G
    if (joystickState == 0) {
    // Ma duc in jos, aprinde segmentul D
    segmentState[3] = HIGH;
  } else if (joystickState == 1) {
    // Ma duc in sus, aprinde segmentul A
    segmentState[4] = HIGH;
  }
  // Nu se intampla nimic pentru directiile in stanga și dreapta
  }else if (currentSegment == 7) { // DP
    if (joystickState == 1) {
      // Ma duc in sus, aprinde segmentul DP
      segmentState[7] = HIGH;
    } else {
      // Daca nu ma duc in sus, stinge segmentul DP
      segmentState[7] = LOW;
    }
  }
}


void updateDisplay() {
  for (int i = 0; i < segSize; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  if (dpState == HIGH) {
    digitalWrite(segmentPins[currentSegment], HIGH);
  }

  for (int i = 0; i < segSize; i++) {
    if (segmentState[i] == HIGH) {
      digitalWrite(segmentPins[i], HIGH);
    }
  }
}

void loop() {
  handleMovement();

  // Verific daca butonul joystick este apasat
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(pinSW);

  if (buttonState == LOW && lastButtonState == HIGH) {
    segmentState[currentSegment] = !segmentState[currentSegment];
  }

  lastButtonState = buttonState;

  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkMillis >= blinkInterval) {
    dpState = !dpState;
    lastBlinkMillis = currentMillis;
  }

  updateDisplay();
}

