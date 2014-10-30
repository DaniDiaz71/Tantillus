// DEFINICIÓN POSICIÓN PINES
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define E0_STEP_PIN 26
#define E0_DIR_PIN 28
#define E0_ENABLE_PIN 24
#define E1_STEP_PIN 36
#define E1_DIR_PIN 34
#define E1_ENABLE_PIN 30

// FUNCIÓN PRINCIPAL DE INICIALIZACIÓN
void setup() {
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(E0_STEP_PIN, OUTPUT);
  pinMode(E0_DIR_PIN, OUTPUT);
  pinMode(E0_ENABLE_PIN, OUTPUT);
  pinMode(E1_STEP_PIN, OUTPUT);
  pinMode(E1_DIR_PIN, OUTPUT);
  pinMode(E1_ENABLE_PIN, OUTPUT);
}

// FUNCIÓN PARA MOVER UN MOTOR.
void step(int stepperPin, int steps, int dirPin, boolean dir){
  digitalWrite(dirPin,dir);
  delay(50);
  for(int i=0;i<steps;i++){
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);
  }
}


// FUNCIÓN BUCLE PRINCIPAL
void loop()
{
  digitalWrite(X_ENABLE_PIN, LOW );
  digitalWrite(Y_ENABLE_PIN, LOW );
  digitalWrite(Z_ENABLE_PIN, LOW );
  digitalWrite(E0_ENABLE_PIN, LOW );
  digitalWrite(E1_ENABLE_PIN, LOW );
  
  // AQUÍ ES DONDE INDICAMOS EL MOTOR A MOVER, LOS PASOS Y EN QUÉ DIRECCIÓN
  // PRIMERO MOVEMOS EN UN SENTIDO
  step(X_STEP_PIN, 200, X_DIR_PIN, true);
  step(Y_STEP_PIN, 200, Y_DIR_PIN, true);
  step(Z_STEP_PIN, 200, Z_DIR_PIN, true);
  step(E0_STEP_PIN, 200, E0_DIR_PIN, true);
  step(E1_STEP_PIN, 200, E1_DIR_PIN, true);
  delay(200);

  // LUEGO MOVEMOS EN EL OTRO SENTIDO
  step(X_STEP_PIN, 200, X_DIR_PIN, false);
  step(Y_STEP_PIN, 200, Y_DIR_PIN, false);
  step(Z_STEP_PIN, 200, Z_DIR_PIN, false);
  step(E0_STEP_PIN, 200, E0_DIR_PIN, false);
  step(E1_STEP_PIN, 200, E1_DIR_PIN, false);
  delay(200);
}
