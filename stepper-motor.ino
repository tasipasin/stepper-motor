// Inclusões do motor de passo
#include <AccelStepper.h>
#include <math.h>

#define MOTOR_YELLOW_PIN 4
#define MOTOR_ORANGE_PIN 0
#define MOTOR_RED_PIN 2
#define MOTOR_BROWN_PIN 15

// Define full step 4 wire
AccelStepper stepperMotor(AccelStepper::FULL4WIRE, MOTOR_BROWN_PIN, MOTOR_ORANGE_PIN, MOTOR_RED_PIN, MOTOR_YELLOW_PIN);
// Number of steps per internal motor revolution
const float STEPS_PER_REV = 32;
//  Amount of Gear Reduction
const float GEAR_RED = 64;
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

const float CM_PER_REV = 3.1;

const float TIME_TO_WALK = 10;

// 34,13 steps/seg

bool spin = true;
float debugAcc = 0;
bool ended = false;

/**
  Step Motor Initial Setup
*/
void setupstepperMotor() {
  stepperMotor.setMaxSpeed(999);
}

void setup() {
  Serial.begin(9600);

  setupstepperMotor();
}

void loop() {
  if (spin) {
    // Indica quantos centímetros devem ser enrolados/soltos
    float cmPull = 20;
    // Realiza cálculo de quantas voltas são necessárias
    //float revolutions = cmPull / CM_PER_REV;
    float revolutions = 1;
    // Realiza cálculo de quantidade de passos necessários
    long stepsToTake = round(revolutions * STEPS_PER_OUT_REV);
    Serial.print("Passos necessários: "); Serial.println(stepsToTake);
    // Calcula a velocidade necessária para realizar as voltas no tempo determinado
    int speedNeeded = round(stepsToTake / TIME_TO_WALK);
    Serial.print("Velocidade calculada: "); Serial.println(speedNeeded);
    Serial.println("Começou");
    stepperMotor.setSpeed(speedNeeded);
    stepperMotor.setAcceleration(50);
    stepperMotor.move(stepsToTake);
    spin = false;
  }
  stepperMotor.run();
  if (!stepperMotor.isRunning() && !ended) {
    ended = true;
    Serial.println("Acabou");
  }
}
