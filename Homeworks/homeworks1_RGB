const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 11;

const int pwm_min = 0;
const int pwm_max = 255;

const int sensor_min = 0;
const int sensor_max = 1023;

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void loop() {
  int potValueRed = analogRead(potRedPin);
  int potValueGreen = analogRead(potGreenPin);
  int potValueBlue = analogRead(potBluePin);

  int pwmRed = map(potValueRed, sensor_min, sensor_max, pwm_min, pwm_max);
  int pwmGreen = map(potValueGreen, sensor_min, sensor_max, pwm_min, pwm_max);
  int pwmBlue = map(potValueBlue, sensor_min, sensor_max, pwm_min, pwm_max);

  analogWrite(ledRedPin, pwmRed);
  analogWrite(ledGreenPin, pwmGreen);
  analogWrite(ledBluePin, pwmBlue);
}
