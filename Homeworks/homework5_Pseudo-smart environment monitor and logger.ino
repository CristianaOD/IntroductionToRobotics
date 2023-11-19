
//1.2
const int trigPin = 9;
const int echoPin = 10;
int ultrasonicThresholdValue = 500;
bool ultrasonicAlert = false;

//1.3
const int LDRPin = A0;
int LDRThresholdValue = 0;
bool LDRAlert = false;
bool automaticMode = false;
int LDRThresholdType = 0;  // 1 pentru minim, 2 pentru maxim

//3.1
bool continuousReading = false;
bool stopContinuousReadingFlag = false;

//3.2
int sensorsSamplingInterval = 0;

//3.3
const int bufferSize = 10;
int ultrasonicReadings[bufferSize];
int ldrReadings[bufferSize];
int currentIndex = 0;

//4.1
int manualRedValue = 0;
int manualGreenValue = 0;
int manualBlueValue = 0;

int savedRedValue = 0;
int savedGreenValue = 0;
int savedBlueValue = 0;

//4.2
const int rgbBluePin = 3;
const int rgbGreenPin = 5;
const int rgbRedPin = 6;



void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(LDRPin, INPUT);

  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);

  Serial.begin(9600);
  printMenu();
}

void loop() {
  if (Serial.available() > 0) {
    int userChoice = Serial.read() - '0'; 
    printMessage(userChoice);

    //verific daca utilizatorul a apasat 's' pentru a opri citirea continua (3.1)
    char userInput = Serial.read();
    if (userInput == 's') {
      stopContinuousReading();
    }
  }
  AutomaticMode(); //pentru pragul senzorilor
}

void printMenu() {
  Serial.println("\nMain Menu:");
  Serial.println("1. Sensor Settings");
  Serial.println("2. Reset Logger Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");
}


void printMessage(int option) {
  switch (option) {
    case 1:
      printSensorSettingsMenu();
      break;
    case 2:
      printResetLoggerDataMenu();
      break;
    case 3:
      printSystemStatusMenu();
      break;
    case 4:
      printRGBLEDControlMenu();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

//1. Sensor Settings
void printSensorSettingsMenu() {
  Serial.println("1. Sensor Settings:");
  Serial.println("  1. Sensors Sampling Interval");
  Serial.println("  2. Ultrasonic Alert Threshold");
  Serial.println("  3. LDR Alert Threshold");
  Serial.println("  4. Back");

  while (Serial.available() == 0) {
  }
  int subOption = Serial.read() - '0';
  processSensorSettingsOption(subOption);
}

void processSensorSettingsOption(int subOption) {
  switch (subOption) {
    case 1:
      setSensorsSamplingInterval();
      break;
    case 2:
      setUltrasonicAlertThreshold();
      break;
    case 3:
      setLDRAlertThreshold();
      break;
    case 4:
      printMenu();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

//1.1
void setSensorsSamplingInterval() {
  Serial.println("Sensors Sampling Interval:");
  Serial.println("Enter a value between 1 and 10 seconds:");

  while (Serial.available() == 0) {
  }

  sensorsSamplingInterval = Serial.parseInt();

  if (sensorsSamplingInterval >= 1 && sensorsSamplingInterval <= 10) {
    Serial.print("The value as a sampling rate for the sensors: ");
    Serial.print(sensorsSamplingInterval);
    Serial.println(" seconds.");
  } else {
    Serial.println("Invalid input. Please enter a value between 1 and 10 seconds.");
  }
  printMenu();
}



//1.2
void setUltrasonicAlertThreshold() {
  Serial.println("Ultrasonic Alert Threshold:");
  Serial.println("Enter a threshold value for the ultrasonic sensor:");

  while (Serial.available() == 0) {
  }

  ultrasonicThresholdValue = Serial.parseInt();

  Serial.print("Ultrasonic threshold set to: ");
  Serial.println(ultrasonicThresholdValue);
  printMenu();
}

int readUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //timp de revenire al ecou
  long duration = pulseIn(echoPin, HIGH);

  //convertirea timpului in distanta (cm)
  int distance = duration * 0.034 / 2;
  return distance;
}

int checkUltrasonicAlert() {
  int sensorValue = readUltrasonicSensor();

  if (sensorValue < ultrasonicThresholdValue) {
    ultrasonicAlert = true;
    return 1;  //alerta (led rosu)
  } else {
    ultrasonicAlert = false;
    return 0;  //nu alerta (led verde)
  }
}

//1.3
void setLDRAlertThreshold() {
  Serial.println("LDR Alert Threshold:");
  Serial.println("Enter a threshold value for the LDR sensor:");

  while (Serial.available() == 0) {
  }

  LDRThresholdValue = Serial.parseInt();

  Serial.print("LDR threshold set to: ");
  Serial.println(LDRThresholdValue);
  printMenu();
}

int checkLDRAlert() {
  int ldrValue = analogRead(LDRPin);

  //nu este prag setat
  if (LDRThresholdValue == 0) {
    LDRAlert = false;
    return 0;
  }

  //verificare pentru prag minim
  if (LDRThresholdType == 1) {
    if (ldrValue > LDRThresholdValue) {
      LDRAlert = true;
      return 1;  //alerta
    } else {
      LDRAlert = false;
      return 0;  //nu alerta
    }
  } else {
    // Verificare pentru prag maxim
    if (ldrValue < LDRThresholdValue) {
      LDRAlert = true;
      return 1; 
    } else {
      LDRAlert = false;
      return 0; 
    }
  }
}


//2. Reset Logger Data
void printResetLoggerDataMenu() {
  Serial.println("2. Reset Logger Data:");
  Serial.println("  1. Yes.");
  Serial.println("  2. No.");
  Serial.println("  3. Back");

  while (Serial.available() == 0) {
  }

  int subOption = Serial.read() - '0';
  processResetLoggerDataChoice(subOption);
}

void processResetLoggerDataChoice(int subOption) {
  switch (subOption) {
    case 1:
      //Serial.println("Yes");
      setYes();
      break;
    case 2:
      Serial.println("No");
      break;
    case 3:
      printMenu();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

void setYes() {
  Serial.println("Are you sure you want to reset all logger data?");
  Serial.println("  1. Yes");
  Serial.println("  2. No");

  while (Serial.available() == 0) {
  }

  int confirmationOption = Serial.read() - '0';

  if (confirmationOption == 1) {
    resetLoggerData();
    Serial.println("Logger data reset successfully.");
  } else {
    Serial.println("Reset canceled.");
  }
  printMenu();
}

void resetLoggerData() {
  ultrasonicThresholdValue = 500;
  ultrasonicAlert = false;

  sensorsSamplingInterval = 0;

  LDRThresholdValue = 0;
  LDRAlert = false;
  LDRThresholdType = 0;

  savedRedValue = 0;
  savedGreenValue = 0;
  savedBlueValue = 0;

  setColor(0, 0, 0);
}


//3. System Status
void printSystemStatusMenu() {
  Serial.println("3. System Status:");
  Serial.println("  1. Current Sensor Readings");
  Serial.println("  2. Current Sensor Settings");
  Serial.println("  3. Display Logged Data");
  Serial.println("  4. Back");

  while (Serial.available() == 0) {
  }

  int subOption = Serial.read() - '0';
  processSystemStatusOption(subOption);
}

void processSystemStatusOption(int subOption) {
  switch (subOption) {
    case 1:
      //Serial.println("Current Sensor Readings");
      setCurrentSensorReadingsMenu();
      break;
    case 2:
      //Serial.println("Current Sensor Settings");
      setCurrentSensorSettingsMenu();
      break;
    case 3:
      //Serial.println("Display Logged Data");
      setDisplayLoggedDataMenu();
      break;
    case 4:
      printMenu();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

//3.1
void setCurrentSensorReadingsMenu() {
  Serial.println("Continuous sensor reading started. Press to 's' to stop.");
  continuousReading = true;
  stopContinuousReadingFlag = false;

  //citeste si afiseaza citirile senzorilor
  while (continuousReading) {
    int ultrasonicValue = readUltrasonicSensor();
    int ldrValue = analogRead(LDRPin);

    // Salvati citirile in buffer
    ultrasonicReadings[currentIndex] = ultrasonicValue;
    ldrReadings[currentIndex] = ldrValue;
    currentIndex = (currentIndex + 1) % bufferSize;

    Serial.print("Ultrasonic Sensor Reading: ");
    Serial.println(ultrasonicValue);

    Serial.print("LDR Sensor Reading: ");
    Serial.println(ldrValue);

    //verific daca utilizatorul a apasat 's' pentru a opri citirea continua
    if (Serial.available() > 0) {
      char userInput = Serial.read();
      if (userInput == 's') {
        stopContinuousReading();
        break;
      }
    }

    delay(1000);
  }

  Serial.println("Continuous Sensor Reading stopped.");
  stopContinuousReadingFlag = false;
  printMenu();
}

void stopContinuousReading() {
  stopContinuousReadingFlag = true;
}


//3.2
void setCurrentSensorSettingsMenu() {
  Serial.println("Current Sensor Settings:");

  Serial.print("  - The value as a sampling rate for the sensors: ");
  Serial.print(sensorsSamplingInterval);
  Serial.println(" seconds.");

  Serial.print("  - Ultrasonic Alert Threshold: ");
  Serial.println(ultrasonicThresholdValue);
  Serial.println(" cm.");

  Serial.print("  - LDR Alert Threshold: ");
  Serial.println(LDRThresholdValue);

  printMenu();
}

//3.3
void setDisplayLoggedDataMenu() {
  Serial.println("Recent Sensor Readings:");

  for (int i = 0; i < bufferSize; i++) {
    int index = (currentIndex + i) % bufferSize;
    
    Serial.print("Ultrasonic Reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(ultrasonicReadings[index]);

    Serial.print("LDR Reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(ldrReadings[index]);
  }
  printMenu();
}


//4. RGB LED Control
void printRGBLEDControlMenu() {
  Serial.println("4. RGB LED Control:");
  Serial.println("  1. Manual Color Control");
  Serial.println("  2. LED: Toggle Automatic ON/OFF");
  Serial.println("  3. Back");

  while (Serial.available() == 0) {
  }

  int subOption = Serial.read() - '0';
  processRGBLEDControlOption(subOption);
}

void processRGBLEDControlOption(int subOption) {
  switch (subOption) {
    case 1:
      setManualColorControl();
      break;
    case 2:
      setToggleAutomaticMode();
      break;
    case 3:
      printMenu();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

//4.1
void setManualColorControl() {
  Serial.println("Manual Color Control:");
  Serial.println("Enter RGB values separated by commas (e.g., 255.0.0 for red):");

  while (Serial.available() == 0) {
  }
  
  String input = Serial.readStringUntil('\n'); //citire input

  //descompune input-ul in culori
  int commaIndex1 = input.indexOf('.');
  int commaIndex2 = input.indexOf('.', commaIndex1 + 1);

  if (commaIndex1 != -1 && commaIndex2 != -1) {
    manualRedValue = input.substring(0, commaIndex1).toInt();
    manualGreenValue = input.substring(commaIndex1 + 1, commaIndex2).toInt();
    manualBlueValue = input.substring(commaIndex2 + 1).toInt();

    setColor(manualRedValue, manualGreenValue, manualBlueValue);
  } else {
    Serial.println("Invalid input format. Please enter RGB values separated by commas.");
  }
  printMenu();
}

void setToggleAutomaticMode() {
  automaticMode = !automaticMode;

  if (automaticMode) {
    Serial.println("Automatic Mode: ON");
  } else {
    Serial.println("Automatic Mode: OFF");
    //daca modul automat este OFF se vor afisa ultimele valori salvate pentru culoarea LED-ului
    setColor(savedRedValue, savedGreenValue, savedBlueValue);
  }
}

//verific daca senzorii depasesc pragul
void AutomaticMode() {
  if (automaticMode) {
    int ultrasonicAlertStatus = checkUltrasonicAlert();
    int LDRAlertStatus = checkLDRAlert();

    f_ledAlert(ultrasonicAlertStatus, LDRAlertStatus);
  }
}

void f_ledAlert(int ultrasonicAlertStatus, int LDRAlertStatus) {
  if (ultrasonicAlertStatus == 1 || LDRAlertStatus == 1) {
    if (ultrasonicAlert) {
      Serial.println("Alert: Object too close!");
    } else if (LDRAlert) {
      Serial.println("Alert: Low light condition!");
    }
    setColor(255, 0, 0);  //culoare LED ROȘU
  } else {
    setColor(0, 255, 0);  //culoare LED VERDE
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(rgbRedPin, redValue);
  analogWrite(rgbGreenPin, greenValue);
  analogWrite(rgbBluePin, blueValue);

  savedRedValue = redValue;
  savedGreenValue = greenValue;
  savedBlueValue = blueValue;
}
