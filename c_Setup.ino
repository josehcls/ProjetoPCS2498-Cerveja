#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <BlynkSimpleStream.h>

// Pino Analogico do DHT11
#define DHTPIN A1
#define DHTTYPE DHT11

// Pino Digital de Dados do Sensor 18b20s (imersao)
#define ONE_WIRE_BUS 5

// Led
#define LEDPIN 6

// Led
#define LEDPIN 6

// Botão
#define NOT_BOTAO false

// Configutando uma instancia do OneWire para comunicacao com o 18b20s
OneWire oneWire(ONE_WIRE_BUS);

// Passando a referencia do OneWire para dispositivo Dallas Temperature
DallasTemperature sensors(&oneWire);

// Inicializa o display no endereco I2C 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

// Instancia sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

WidgetTerminal terminal(V0);

void setup()
{
 // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  
  lcd.begin (16,2);
  sensors.begin();
  dht.begin();
  pinMode(LEDPIN, OUTPUT);  
  
  time = millis() / 1000; //tempo em segundos

  delay(1000);
}
