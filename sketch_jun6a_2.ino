#include <Wire.h> 
#include <Adafruit_TCS34725.h>
#include <Servo.h>

// Pines de control del L298N
const int IN1 = 2;
const int IN2 = 3;
const int ENA = 5;

const int IN3 = 4;
const int IN4 = 11;
const int ENB = 6;

// Pines del sensor ultrasónico
const int trigPin = 8;
const int echoPin = 10;

// Servo
Servo servo;
const int servoPin = 9;

// Sensor de color
Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Variables de calibración (luz ambiental)
uint16_t r_base = 0, g_base = 0, b_base = 0, c_base = 0;
float r_f = 0, g_f=0, b_f=0;
const float alpha = 0.5;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  servo.attach(servoPin);
  servo.write(90);

  if (colorSensor.begin()) {
    Serial.println("Sensor de color inicializado");
  } else {
    Serial.println("Error al inicializar sensor de color");
    while (1);
  }

  // === Calibración de luz ambiental ===
  Serial.println("Calibrando sensor");
  delay(2000); // Tiempo para estabilizar luz ambiental
  
  for (int i = 0; i < 3; i++) {
    calibracion();
  }

  avanzar();
}

void loop() {
  servo.write(90);
  avanzar();

  // Medición ultrasónica
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2;
  distancia *= 0.95;
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // === Lectura y corrección de color ===
  uint16_t r_raw, g_raw, b_raw, c_raw;
  colorSensor.getRawData(&r_raw, &g_raw, &b_raw, &c_raw);

  int r_corr = max(0, r_raw - r_base);
  int g_corr = max(0, g_raw - g_base);
  int b_corr = max(0, b_raw - b_base);
 // int c_corr = max(0, c_raw - c_base);

  r_f = alpha * r_corr + (1-alpha) * r_f;
  g_f = alpha * g_corr + (1-alpha) * g_f;
  b_f = alpha * b_corr + (1-alpha) * b_f;


  float total = r_f + g_f + b_f;
  float r_pct = (r_f/total)*100.0;
  float g_pct = (g_f/total)*100.0;
  float b_pct = (b_f/total)*100.0;


  Serial.print("R%: "); Serial.print(r_pct);
  Serial.print(" G%: "); Serial.print(g_pct);
  Serial.print(" B%: "); Serial.println(b_pct);

  // === Reacción a colores corregidos ===

  if (r_pct > 45 && g_pct < 30 && b_pct < 30) {
    Serial.println("Color rojo detectado: detener y girar servo");
    detenerMotores();
    servo.write(0); delay(1000);
    servo.write(90); delay(1000);
    servo.write(180); delay(1000);
    servo.write(90);
    avanzar();
  }
  else if (b_pct > 45 && r_pct < 30 && g_pct < 30) {
    Serial.println("Color azul detectado: giro izquierda");
    servo.write(180);
    girarIzquierda(); delay(1000);
    avanzar();
  }
  else if (g_pct > 45 && r_pct < 30 && b_pct < 30) {
    Serial.println("Color verde detectado: giro derecha");
    girarDerecha();
    servo.write(90); delay(1000);
    avanzar();
  }
  else if (distancia < 10) {
    Serial.println("Obstáculo detectado: retroceder y girar");
    retroceder(); delay(1000);
    girarDerecha(); delay(1000);
    //avanzar();
  }

  delay(500);
}


void calibracion(){
  uint16_t r, g, b, c;
  uint32_t r_sum = 0, g_sum = 0, b_sum = 0, c_sum = 0;
  for (int i = 0; i < 2; i++){
    colorSensor.getRawData(&r, &g, &b, &c);
    r_sum += r;
    g_sum += g;
    b_sum += b;
    c_sum += c;
    delay(50);
  }
 
  r_base = r_sum / 10;
  g_base = g_sum / 10;
  b_base = b_sum / 10;
  c_base = c_sum / 10;

  Serial.println("Calibración completa.");
  Serial.print("R_base: "); Serial.print(r_base);
  Serial.print(" G_base: "); Serial.print(g_base);
  Serial.print(" B_base: "); Serial.print(b_base);
  Serial.print(" C_base: "); Serial.println(c_base);

}


// === Control de motores ===

void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);
  Serial.println("Avanzando...");
}

void retroceder() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 150);
  Serial.println("Retrocediendo...");
}

void detenerMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("Motores detenidos");
}

void girarIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 150);
  Serial.println("Girando a la izquierda...");
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 150);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 150);
  Serial.println("Girando a la derecha...");
}




