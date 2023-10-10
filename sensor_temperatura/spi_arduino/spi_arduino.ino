#include <SPI.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
int slaveSelect = 2;
int delayTime = 250;

void setup() {
  pinMode (slaveSelect,OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  delay(1000);
  Serial.begin(9600);
  sensors.begin();   //Se inicia el sensor
}


void loop() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Configura la comunicación SPI
  SPI.transfer(temp); // Envía el valor por SPI
  SPI.endTransaction();
  delay(1000); // Espera un segundo antes de enviar el siguiente valor

  //Serial.print("Temperatura= ");
  Serial.println(temp);
  //Serial.println(" C");
  delay(100); 
  
  
}


 
