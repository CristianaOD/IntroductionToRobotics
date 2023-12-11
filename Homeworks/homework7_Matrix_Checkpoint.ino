#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

const int xPin = A0;
const int yPin = A1;
const int buttonPin = 13;

const int buttonDefaultState = LOW;  // starea implicita a butonului

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

// variabile pentru a retine pozitia sagetii
byte arrowRow = 1;
byte arrowCol = 0;

const int matrixBrightness = 8;
const int matrixSize = 8;
bool matrixChanged = true;
byte matrix[matrixSize][matrixSize];
const byte WALL = 1;

int playerX, playerY;
int bombX, bombY;

int wallPercentage = 60; // densitatea peretilor
int playerBlinkInterval = 500; // interval de clipire jucator
int bombBlinkInterval = 200; // interval de clipire bomba

unsigned long lastPlayerBlink = 0;
unsigned long lastBombBlink = 0;
unsigned long lastMoved = 0;

bool bombPlaced = false;
unsigned long bombTimer;
const int bombDuration = 3000;
unsigned long lastBlinkPlayer = 0; 

byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;
const int minThreshold = 100;
const int maxThreshold = 500;

bool gameStarted = false;

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte moveInterval = 200;

const byte MENU_START_GAME = 1;
const byte MENU_SETTINGS = 2;
const byte MENU_ABOUT = 3;
const byte MENU_EXIT = 4;

const byte MENU_LCD_BRIGHTNESS = 5;
const byte MENU_MATRIX_BRIGHTNESS = 6;

byte currentMenu = 0;


enum State {
  STATE_MENU,
  STATE_MENU_INACTIVE,
  STATE_START_GAME,
  STATE_GAME,
  STATE_SETTINGS,
  STATE_ABOUT
};

State currentState = STATE_MENU;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  initializeGame();

  // setez pinul butonului la starea implicita
  pinMode(buttonPin, INPUT);

  displayWelcomeMessage(); // afisare mesaj initial

  // asteapta pana cand butonul este apasat
  waitForUserInput();

  // valorile de luminozitate din EEPROM
  int lcdBrightness = EEPROM.read(0);
  int matrixBrightness = EEPROM.read(1);

  analogWrite(rs, lcdBrightness);
  lc.setIntensity(0, matrixBrightness);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMoved >= moveInterval) {
    updatePositions();
    lastMoved = currentMillis;
  }

  updateGame();

  Serial.print("Button State: ");
  Serial.println(digitalRead(buttonPin));
  
  if (digitalRead(buttonPin) == HIGH) {
    placeBomb();
  }

  updateMatrix();

  switch (currentState) {
    case STATE_MENU:
      displayMenu();
      handleMenuSelection();
      updateArrowPosition();
      break;

    case STATE_GAME:
      if (millis() - lastMoved > moveInterval) {
        updatePositions();
        lastMoved = millis();
      }

      if (digitalRead(buttonPin) == HIGH) {
        if (matrix[playerX][playerY] == WALL) {
          placeBomb();
        }
      }

      if (millis() - bombTimer > bombDuration) {
        placeBomb();
      }

      bool allWallsDestroyed = true;

      for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
          if (matrix[i][j] == WALL) {
            allWallsDestroyed = false;
            break;
          }
        }

        if (!allWallsDestroyed) {
          break;
        }
      }

      if (allWallsDestroyed) {
        displayEndMessage();
        waitForUserInput();
        currentState = STATE_MENU;
        displayMenu();
      }

      if (millis() - lastBlinkPlayer > playerBlinkInterval) {
        matrixChanged = true;
        lastBlinkPlayer = millis();
      }

      if (matrixChanged == true) {
        updateMatrix();
        matrixChanged = false;
      }
      break;

    case STATE_SETTINGS:
      break;

    case STATE_ABOUT:
      break;

    case STATE_START_GAME:
      displayGameStartMessage();
      delay(2000);  
      startGame(); 
      break;
  }
}

void initializeGame() {
  // pereti, jucator, bomba
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      matrix[i][j] = random(100) < wallPercentage ? 1 : 0;
    }
  }

  playerX = random(matrixSize);
  playerY = random(matrixSize);
  matrix[playerX][playerY] = 2; // jucator

  do {
    bombX = random(matrixSize);
    bombY = random(matrixSize);
  } while (matrix[bombX][bombY] != 0);

  matrix[bombX][bombY] = 3; // bomba
}

void displayWelcomeMessage() {
  lcd.begin(16, 2);
  lcd.print("Welcome!");

  delay(2000);
  lcd.clear();
}

void waitForUserInput() {
  while (digitalRead(buttonPin) != HIGH) {
    // asteapta pana cand butonul este apasat
  }
}

void displayEndMessage() {
  lcd.clear();
  lcd.print("Game Over");
  lcd.setCursor(0, 1);
  lcd.print("Press button to continue");
}

void displayGameStartMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button to start!");
  lcd.setCursor(0, 1);
  lcd.print("Move joystick to navigate");
  lcd.setCursor(0, 2);
  lcd.print("and press button to place bomb");
  lcd.setCursor(0, 3);
  lcd.print("Good luck!");
}

void startGame() {
  gameStarted = true;
  initializeGame();
  currentState = STATE_GAME;
  displayGameDetails();
}

// cronometreaza timpul facut
void displayGameDetails() {
  lcd.setCursor(0, 3);
  lcd.print("Time: ");
  lcd.print(millis() / 1000);
}


void displayAboutMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game: Bomberman");
  lcd.setCursor(0, 1);
  lcd.print("Author: ODC");
  lcd.setCursor(0, 2);
  lcd.print("GitHub: github.com/ODC");
}

void handleSettingsMenu() {
  displaySettingsMenu();
  while (currentMenu == MENU_SETTINGS) {
    if (digitalRead(buttonPin) == HIGH) {
      handleSettingsSubMenu();
    }
  }
}

void displaySettingsMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("a. LCD Brightness");
  lcd.setCursor(0, 1);
  lcd.print("b. Matrix Brightness");
}

void handleSettingsSubMenu() {
  lcd.clear();
  lcd.print("Select setting (a/b)");
  while (currentMenu == MENU_SETTINGS) {
    if (digitalRead(buttonPin) == HIGH) {
      int submenuSelection = 0;
      while (submenuSelection == 0) {
        if (digitalRead(buttonPin) == HIGH) {
          submenuSelection = currentMenu;
        }
      }
      switch (submenuSelection) {
        case MENU_LCD_BRIGHTNESS:
          handleLCDBrightness();
          break;
        case MENU_MATRIX_BRIGHTNESS:
          handleMatrixBrightness();
          break;
      }
    }
  }
}

void handleLCDBrightness() {
  int brightnessValue = 0;
  while (brightnessValue == 0) {
    brightnessValue = analogRead(A0);
  }

  EEPROM.write(0, brightnessValue);
  lcd.clear();
  lcd.print("LCD Brightness set");
  delay(2000);
  displaySettingsMenu();
}

void handleMatrixBrightness() {
  int brightnessValue = 0;
  while (brightnessValue == 0) {
    brightnessValue = analogRead(A1);
  }

  EEPROM.write(1, brightnessValue);
  lcd.clear();
  lcd.print("Matrix Brightness set");
  delay(2000);
  displaySettingsMenu();
}


void updateGame() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  int prevPlayerX = playerX;
  int prevPlayerY = playerY;

  // controlul joystick-ului
  if (xValue < 100 && playerX > 0) {
    playerX--;
  } else if (xValue > 900 && playerX < matrixSize - 1) {
    playerX++;
  }

  if (yValue < 100 && playerY > 0) {
    playerY--;
  } else if (yValue > 900 && playerY < matrixSize - 1) {
    playerY++;
  }

  // jucator = 2 pentru pozitia noua in matrice
  if (playerX != prevPlayerX || playerY != prevPlayerY) {
    matrix[prevPlayerX][prevPlayerY] = 0;
    matrix[playerX][playerY] = 2;
  }

  if (bombPlaced) {
    matrix[bombX][bombY] = 3; 
  }

  // clipire bomba
  if (millis() - lastBombBlink > bombBlinkInterval) {
    matrix[bombX][bombY] = !matrix[bombX][bombY];
    lastBombBlink = millis();
  }

  // clipire jucator
  if (millis() - lastPlayerBlink > playerBlinkInterval) {
    matrix[playerX][playerY] = !matrix[playerX][playerY];
    lastPlayerBlink = millis();
  }
}

void placeBomb() {
 
  int buttonState = digitalRead(buttonPin);

  if (matrixChanged && buttonState == HIGH && !bombPlaced) {
    // plasez bomba doar daca butonul joystick-ului este apasat si nu exista deja o bomba plasata
    bombX = playerX;
    bombY = playerY;
    bombPlaced = true;
    bombTimer = millis(); 
    matrixChanged = true;
  }

  // verific daca bomba a fost plasata si a trecut destul timp
  if (bombPlaced && millis() - bombTimer > bombDuration) {
    clearBomb(); // elimin bomba si efectele asociate
  }
}

void clearBomb() {
  // elimin coloana si randul corespunzatoare pozitiei bombei
  for (int i = 0; i < matrixSize; i++) {
    matrix[bombX][i] = 0;
    matrix[i][bombY] = 0;
  }
  // resetez pozitia bombei
  bombPlaced = false;
}

void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]); 
    }
  }
}

void updatePositions() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  int prevPlayerX = playerX;
  int prevPlayerY = playerY;

  movePlayer(xValue, yValue);

  // amplaseaza bomba cand butonul este apasat
  if (digitalRead(2) == LOW) {
    if (!bombPlaced) {
      matrix[playerX][playerY] = 3; // bomba
      bombPlaced = true;
    }
  }
}

void movePlayer(int xValue, int yValue) {
  byte newPosX = playerX;
  byte newPosY = playerY;

  if (xValue < 100 && playerX > 0) {
    if (matrix[playerX - 1][playerY] != 1) {
      newPosX = playerX - 1;
    }
  } else if (xValue > 900 && playerX < matrixSize - 1) {
    if (matrix[playerX + 1][playerY] != 1) {
      newPosX = playerX + 1;
    }
  }

  if (yValue < 100 && playerY > 0) {
    if (matrix[playerX][playerY - 1] != 1) {
      newPosY = playerY - 1;
    }
  } else if (yValue > 900 && playerY < matrixSize - 1) {
    if (matrix[playerX][playerY + 1] != 1) {
      newPosY = playerY + 1;
    }
  }

  // verific daca noul loc este liber (nu este perete sau bomba)
  if (matrix[newPosX][newPosY] != 1 && matrix[newPosX][newPosY] != 3) {
    matrixChanged = true;
    matrix[playerX][playerY] = 0;
    playerX = newPosX;
    playerY = newPosY;
    matrix[playerX][playerY] = 2;
  }
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu");

  byte optionOffset = currentMenu - MENU_START_GAME;

  for (byte i = 0; i < 2; i++) {
    lcd.setCursor(0, i);
    byte optionIndex = (optionOffset + i) % 3 + MENU_START_GAME;

    // afisez ">"
    if (i == arrowRow) {
      lcd.print("> ");
    } else {
      lcd.print("  ");
    }

    // afisez numele optiunii
    switch (optionIndex) {
      case MENU_START_GAME:
        lcd.print("Start Game");
        break;
      case MENU_SETTINGS:
        lcd.print("Settings");
        break;
      case MENU_ABOUT:
        lcd.print("About");
        break;
    }
  }
}

// actualizez pozitia sagetii
void updateArrowPosition() {
  int yValue = analogRead(yPin);

  // daca joystick-ul este miscat in jos
  if (yValue > maxThreshold) {
    arrowRow = 1;
  }
  // daca joystick-ul este miscat in sus
  else if (yValue < minThreshold) {
    arrowRow = 0;
  }
}

void handleMenuSelection() {
  int selection = 0;
  int lastYValue = analogRead(yPin);  // ultima valoare a axei Y
  int yThreshold = 100;  // prag pentru a evita schimbările bruste

  while (selection == 0) {
    if (digitalRead(buttonPin) == HIGH) {
      selection = currentMenu;
    }

    int yValue = analogRead(yPin);
    int xValue = analogRead(xPin);

    // daca joystick-ul este miscat in jos
    if (yValue > (lastYValue + yThreshold)) {
      // Trec la următoarea opțiune din meniu
      currentMenu++;
      if (currentMenu > MENU_ABOUT) {
        currentMenu = MENU_START_GAME;
      }
      displayMenu();
      delay(200);
    }
    // daca joystick-ul este miscat in sus
    else if (yValue < (lastYValue - yThreshold)) {
      // Trec la opțiunea anterioară din meniu
      currentMenu--;
      if (currentMenu < MENU_START_GAME) {
        currentMenu = MENU_ABOUT;
      }
      displayMenu();
      delay(200);
    }

    // Stanga - Dreapta
    if (xValue > maxThreshold) {
      currentMenu++;
      if (currentMenu > MENU_ABOUT) {
        currentMenu = MENU_START_GAME;
      }
      displayMenu();
      delay(200);
    } else if (xValue < minThreshold) {
      currentMenu--;
      if (currentMenu < MENU_START_GAME) {
        currentMenu = MENU_ABOUT;
      }
      displayMenu();
      delay(200);
    }

    lastYValue = yValue;  // ultima valoare a axei y
  }

  switch (selection) {
    case MENU_START_GAME:
      currentState = STATE_START_GAME;
      break;
    case MENU_SETTINGS:
      currentState = STATE_SETTINGS;
      break;
    case MENU_ABOUT:
      currentState = STATE_ABOUT;
      break;
    case MENU_EXIT:
      displayWelcomeMessage();
      currentState = STATE_MENU;
      break;
  }
}
