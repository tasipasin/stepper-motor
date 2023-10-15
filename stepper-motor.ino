// Inclusões do motor de passo
#include <Stepper.h>
#include <math.h>

// Definições para ESP32
#define MOTOR_IN_1_PIN 25
#define MOTOR_IN_2_PIN 26
#define MOTOR_IN_3_PIN 27
#define MOTOR_IN_4_PIN 14

// Definições para Arduino
//#define MOTOR_IN_1_PIN 8
//#define MOTOR_IN_2_PIN 9
//#define MOTOR_IN_3_PIN 10
//#define MOTOR_IN_4_PIN 11

// Number of steps per geared output rotation
const int STEPS_PER_OUT_REV = 2049;
// Define full step 4 wire
Stepper stepperMotor(STEPS_PER_OUT_REV, MOTOR_IN_1_PIN, MOTOR_IN_3_PIN, MOTOR_IN_2_PIN, MOTOR_IN_4_PIN);

const float CM_PER_REV = 7.6;

const float TIME_TO_WALK = 20;

bool took = true;
void setup() {
  Serial.begin(9600);
  // In rotations per minutes
  stepperMotor.setSpeed(10);
}
//35,9 43,5
void loop() {
  if (took) {
    // Indica quantos centímetros devem ser enrolados/soltos
    //float cmPull = 20;
    int cmPull = 10;
    // Realiza cálculo de quantas voltas são necessárias
    float revolutions = cmPull / CM_PER_REV;
    //int revolutions = 1;
    // Realiza cálculo de quantidade de passos necessários
    int stepsToTake = round(revolutions * STEPS_PER_OUT_REV);
    Serial.print("Passos necessários: "); Serial.println(stepsToTake);
    // Calcula a velocidade necessária para realizar as voltas no tempo determinado
    long speedNeeded = round(stepsToTake / TIME_TO_WALK);
    Serial.print("Velocidade calculada: "); Serial.println(speedNeeded);
    Serial.println("Começou");
    int steps = stepsToTake;
    delay(1000);
    stepperMotor.step(stepsToTake);
    delay(20000);
    stepperMotor.step(-2*stepsToTake);
    Serial.println("Acabou");
    took = false;
  }
}
