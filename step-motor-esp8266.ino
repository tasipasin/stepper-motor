#include <ArduinoJson.h>
// Inclusões do motor de passo
#include <AccelStepper.h>

#define MOTOR_YELLOW_PIN D0
#define MOTOR_ORANGE_PIN D1
#define MOTOR_RED_PIN D2
#define MOTOR_BROWN_PIN D3

// Define full step 4 wire
AccelStepper stepperMotor(AccelStepper::FULL4WIRE, MOTOR_BROWN_PIN, MOTOR_ORANGE_PIN, MOTOR_RED_PIN, MOTOR_YELLOW_PIN);
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

// 34,13 steps/seg

// Define o pino de leitura do botão
#define BUTTON_PIN D6

// Variáveis de teste
int position;

/**
  Step Motor Initial Setup
*/
void setupstepperMotor() {
  stepperMotor.setMaxSpeed(500);
}

void printPosition() {
  String result;
  DynamicJsonDocument doc(200);  // allocates in the heap
  doc["position"] = position;
  serializeJson(doc, Serial);
  Serial.print("\n");
}

void setup() {
  Serial.begin(9600);
  Serial.print("Inicio\n\n\n\n");
  // initialize the pushbutton pin as an pull-up input
  pinMode(BUTTON_PIN, INPUT);
  setupstepperMotor();
  position = 0;
}

void loop() {
  // Meia volta
  int stepsRequired = STEPS_PER_OUT_REV / 2;
  int rotBySec = 100 * STEPS_PER_OUT_REV
  stepperMotor.setSpeed(100);
  stepperMotor.step(stepsRequired);
  sleep(stepsRequired / 100);
}
