
/*
 * ADAPTACIÓN DEL CÓDIGO DE PRUEBA PARA TERMISTOR DE LA WEB DE ARDUINO
 * SE BASA EN LA ECUACIÓN Steinhart-Hart PARA OBTENER LA TEMPERATURA 
 * SEGÚN LA RESISTENCIA DEL TERMISTOR
 * ESTE EJEMPLO FUNCIONA BIEN CUANDO EL TERMISTOR ESTÁ ENTRE VCC Y 
 * EL PIN DE ARDUINO, EN CASO DE LA RAMPS 1.4 LA UBICACIÓN ES JUSTO LA INVERSA.
 * COMO CONSECUENCIA DE ESTO EL VALOR DE LA TEMPERATURA NO ES CORRECTO Y HAY QUE
 * AJUSTARLO.
 * 
 *    Temperatura en Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]3}
 *    donde A = 0.001129148, B = 0.000234125 y C = 8.76741E-08
 *
 * SE SUPONE QUE LOS COEFICIENTES SON PARTICULARES PARA CADA FABRICANTE Y MODELO DE
 * TERMISTOR, AUNQUE PARA PRUEBA DE FUNCIONAMIENTO DEL HOT-END ES SUFICIENTE
 *
 * ESQUEMA DE CONEXIÓN EN RAMPS:
 *   [GND] -- [TERMISTOR] -- | -- [RESISTENCIA RAMPS 4.7k] -- [Vcc (5v)]
 *                           |
 *                    PIN Nº 13 ANALÓGICO
 *
 *
 *   Rt = ((RawADC/1024.0)*pad) / (1-(RawADC/1024.0));
 *
 */

#include <math.h>

#define PIN_T0 13                       // PIN EN EL QUE SE ENCUENTRA EL TERMISTOR
#define PIN_HE 10                       // PIN EN EL QUE SE ENCUENTRA EL HOT END

float vcc = 5;                          // TENSIÓN DE ALIMENTACIÓN DE LA RAMPS
float pad = 4700;                       // VALOR DE LA RESISTENCIA DE CONEXIÓN A VCC EN LA RAMPS
float thermr = 100000;                  // RESISTENCIA NOMINAL DEL TERMISTOR EN EL J-HEAD MK-V. NO SE USA
boolean ActivaHotEnd = false;           //  
boolean Subiendo = false;               //
float LimInf = 60.0;                    // LIMITE INFERIOR DE TEMPERATURA PARA LA PRUEBA
float LimSup = 70.0;                    // LÍMITE SUPERIOR DE TEMPERATURA PARA LA PRUEBA

float TempTermistor(int RawADC) {
  float Rt;
  float Temp;  // Dual-Purpose variable to save space.

  // EL VALOR DE LA RESISTENCIA SE OBTIENE DE OTRA FORMA, EL TERMISTOR ESTÁ CONECTADO A GND NO A VCC
  Rt = ((RawADC/1024.0)*pad) / (1-(RawADC/1024.0));
  // Rt=pad*((1024.0 / RawADC) - 1); 
  
  Temp = log(Rt);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15 + 46;  // TEMPERATURA APROXIMADA CORREGIDA EN ºC. NO TOMAR COMO REFERENCIA PRECISA                     

  // DEPENDIENDO DE LA TEMPERATURA ACTIVA O DESACTIVA LA SALIDA QUE SE CONECTA CON LA RESISTENCIA DE
  // CALENTAMIENTO DEL HOT-END



  // BEGIN- Remove these lines for the function not to display anything
  // Serial.print("ADC: "); 
  // Serial.print(RawADC); 
  // Serial.print("/1024");
  // Serial.print(", vcc: ");
  // Serial.print(vcc,2);
  // Serial.print(", pad: ");
  // Serial.print(pad/1000,3);
  // Serial.print(" Kohms, Volts: "); 
  // Serial.print(((RawADC*vcc)/1024.0),3);   
  // Serial.print(", Rt: "); 
  // Serial.print((Rt/1024.0),1);
  // Serial.print(" Kohms, ");
  // END- Remove these lines for the function not to display anything

  return Temp;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_HE , OUTPUT);
}

void loop() {
  float temp;
  temp=TempTermistor(analogRead(PIN_T0));       // read ADC and  convert it to Celsius
  Serial.print("Temperatura J-HEAD: "); 
  Serial.print(temp,1);                             // display Celsius
  Serial.println("");
  
  // SI LA TEMPERATURA ES MENOR DE 60ºC SE ACTIVA LA SALIDA QUE PERMITE QUE LLEGUE CORRIENTE A LA RESISTENCIA DEL HOT-END
  if (temp<LimInf && Subiendo == false) {
    digitalWrite(PIN_HE, HIGH);
    Subiendo = true;
    Serial.println("Activado Hot-End");
  }
  
  // SI LA TEMPERATURA EL MAYOR DE 70ºC DESACTIVA EL HOT-END
  if (temp>LimSup && Subiendo == true) {
    digitalWrite(PIN_HE, LOW);
    Subiendo = false;
    Serial.println("Desactivado Hot-End");
  }

  delay(1000);
}
