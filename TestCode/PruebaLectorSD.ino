/*
FICHERO DE PRUEBA BASADO EN Sdrampstest.zip DE http://reprap.org/wiki/Sdramps
SE HA TRADUCIDO Y SIMPLIFICADO PARA ÚNICAMENTE LEER LOS FICHEROS EXISTENTES EN LA TARJETA.
*/

const int chipSelect = 53;    
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
  Serial.begin(115200);
  Serial.print("\nInicializando tarjeta SD...");
  
  pinMode(53, OUTPUT);
  pinMode(48, OUTPUT);  
  digitalWrite(48,HIGH);
  pinMode(SPI_MISO_PIN, INPUT);
  pinMode(SPI_MOSI_PIN, OUTPUT);
  pinMode(SPI_SCK_PIN, OUTPUT);
  
  digitalWrite(SPI_MOSI_PIN,LOW);
  digitalWrite(SPI_SCK_PIN,LOW);
  digitalWrite(53,LOW);
  delay(1);
  
  SD.begin(53);
}


void loop () {
   if (!card.init(SPI_FULL_SPEED, chipSelect)) {
    Serial.println("ha fallado la inicializacion, cosas a verificar:");
    Serial.println("- Esta el lector correctamente conectado?");
    Serial.println("- Hay tarjeta en el lector?");
    Serial.println("- Has modificado el pin chipSelect para que coincida con el shield que estas usando?");
    delay (30000);
    return;
  } else {
   Serial.println("El cableado es correcto y se ha encontrado tarjeta.");
  }

  // MUESTRA EL TIPO DE TARJETA ENCONTRADA
  Serial.print("\nTipo de tarjeta: ");
  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Desconocida");
  }

  // AHORA SE INTENTA ABRIR EL VOLUMEN Y PARTICIÓN, TIENE QUE SER FAT16 O FAT32
  if (!volume.init(card)) {
    Serial.println("La tarjeta insertada no tiene particion FAT16 o FAT32.\nPor favor revisa el tipo de formato.");
    return;
  }

  Serial.print("Numero de bloques: ");
  Serial.println(card.cardSize());  // EL NÚMERO DE BLOQUES NO ES EL 

  // IMPRIME EL TIPO DEL VOLUMEN TIPO FAT
  Serial.print("\nParticion tipo FAT");
  Serial.println(volume.fatType(), DEC);
 
  Serial.println("\nFicheros encontrados en la tarjeta (nombre, fecha y tamano en bytes): ");
  root.openRoot(volume);
 
  // LISTADO DE TODOS LOS ARCHIVOS QUE HAY EN DIRECTORIO RAIZ DE LA TARJETA
  root.ls(LS_R | LS_DATE | LS_SIZE);
  delay (30000);
}
