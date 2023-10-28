const int floorButtonPins[] = {2, 3, 4};  // pinii pentru butoanele etajelor
const int floorLEDPins[] = {5, 6, 7};      // pinii pentru LED-urile etajelor
const int elevatorLEDPin = 8;               // pin pentru LED-ul de stare al ascensorului
const int buzzerPin = 9;                    // pin pentru semnalul buzzer-ului

int currentFloor = 0; // variabila pentru etajul curent
bool elevatorMoving = false; // flag pentru a indica dacă ascensorul se mișcă

void setup() {
  // inițializare pini
  pinMode(floorButtonPins[0], INPUT_PULLUP);
  pinMode(floorButtonPins[1], INPUT_PULLUP);
  pinMode(floorButtonPins[2], INPUT_PULLUP);
  
  pinMode(floorLEDPins[0], OUTPUT);
  pinMode(floorLEDPins[1], OUTPUT);
  pinMode(floorLEDPins[2], OUTPUT);
  
  pinMode(elevatorLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(floorButtonPins[i]) == LOW) {
      if (i != currentFloor && !elevatorMoving) {
        moveElevator(i);
      }
    }
  }
}

void playFloorSound() {
  tone(buzzerPin, 1000, 200);  // generez un sunet de 1000 Hz pentru 200 de milisecunde
  delay(200);  // aștept 200 de milisecunde între sunete
}
void elevatorMovingSound() {
  tone(buzzerPin, 1500, 200);  // generez un sunet de 1500 Hz pentru 200 de milisecunde
  delay(200); 
}
void moveElevator(int targetFloor) {
  elevatorMoving = true;
  
  int direction = (targetFloor > currentFloor) ? 1 : -1; // direcția ascensorului

  for (int floor = currentFloor; floor != targetFloor; floor += direction) {
    // aprind LED-ul corespunzător etajului curent
    digitalWrite(floorLEDPins[floor], HIGH);
    delay(500); // astept 0.5 secunde înainte de a trece la următorul etaj
    
    for (int i = 0; i < 3; i++) {
      elevatorMovingSound(); // reda sunetul când ascensorul este în mișcare, dar nu a ajuns încă la destinație
      delay(200); 
      digitalWrite(elevatorLEDPin, HIGH); // palpâie al patrulea LED când ascensorul este în mișcare
      delay(100); 
      digitalWrite(elevatorLEDPin, LOW);
      delay(100);
    }

    // sting LED-ul etajului curent
    digitalWrite(floorLEDPins[floor], LOW);
    // redă sunetul la trecerea prin etaj
    playFloorSound();
  }
  
  // am ajuns la etajul dorit, aprind LED-ul și activez buzzer-ul
  digitalWrite(floorLEDPins[targetFloor], HIGH);
  digitalWrite(buzzerPin, HIGH);  // activez buzzer-ul
  delay(500);
  digitalWrite(buzzerPin, LOW);  // dezactivez buzzer-ul
  digitalWrite(elevatorLEDPin, HIGH);
  

  // la final, actualizez etajul curent și starea de funcționare a ascensorului
  currentFloor = targetFloor;
  elevatorMoving = false;

  Serial.println("Ascensorul a ajuns la etajul: " + String(currentFloor));
}
