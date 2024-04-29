#include <Stepper.h>

const int distancia_seg = 10;
const int TRIG = 3;
const int ECHO = 2;
const int ledGreen = 7;
const int ledRed = 8;
const int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

bool motorAtivo = true; // Variável para controlar o estado do motor

  void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  myStepper.setSpeed(4); // Velocidade desejada do motor
  Serial.begin(9600);
}

void loop() {
  // Lendo o sensor enquanto o motor está em movimento
  int distancia = sensor_morcego(TRIG, ECHO);

  if (distancia <= distancia_seg) {
    Serial.print("Atenção: ");
    Serial.print(distancia);
    Serial.println("cm");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);

    if (motorAtivo) {
      myStepper.setSpeed(0); // Parando o motor quando a luz vermelha ascender
      motorAtivo = false;
    }
  } else {
    Serial.print("Livre: ");
    Serial.print(distancia);
    Serial.println("cm");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    
    if (!motorAtivo) {
      myStepper.setSpeed(2); // Reinicie o motor quando a luz verde ascender
      motorAtivo = true;
    }
  }

  // Gira o motor no sentido horário com a velocidade constante
  myStepper.step(90);

  delay(100); // Pequeno atraso entre as leituras do sensor
}

int sensor_morcego(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);

  return pulseIn(pinoecho, HIGH) / 58;
}
