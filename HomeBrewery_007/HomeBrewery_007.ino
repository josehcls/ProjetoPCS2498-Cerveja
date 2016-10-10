// Retirado de Arduino Serial USB,Terminal, leds, labeled value e button do blynk docs (25/09/2016):

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <SimpleTimer.h>

//Para medidor de temperatura e umidades ambientes
#include <DHT.h>
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

//Medidor de temperatura da cerveja em produção
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Display LCD
#include <LiquidCrystal_I2C.h>

//Led de próxima etapa
#define ledPin 6

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d839d81fcfab4cc5ac4496279be3abd2";
float tempRef = 0.0;
float tempWort = 0.0;
float tempOut = 0.0;
int estado = 0;
int proxestado = 0;
float tempo;

// Attach virtual serial terminal to Virtual Pin V0
WidgetTerminal terminal(V0);

//leds 1 e 2 para heaters 1 e 2
WidgetLED led1(V1);
WidgetLED led2(V2);

//Timer do app
SimpleTimer timer;

//Medidor de temp e umidade ambiente
DHT dht(DHTPIN, DHTTYPE);

//Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

void setup()
  {
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(auth, Serial);


   while (Blynk.connect() == false) {
   // Wait until connected
   }
   //Set interval timer
   timer.setInterval(1000L, atualizaApp);
   
   // This will print Blynk Software version to the Terminal Widget when
   // your hardware gets connected to Blynk Server
   terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
   terminal.flush();
   terminal.println("Temp e Tempo:");
   terminal.flush();

   //leds inicialmente desligados
   led1.off();
   led2.off();

   //Setup do medidor de temp e umidade ambiente
   dht.begin();

   //Setup do sensor de temperatura da cerveja em produção
   sensors.begin();
   sensors.setResolution(12);
   sensors.setWaitForConversion(false); 
   sensors.requestTemperatures();

   // Setup display lcd
   lcd.begin (16,2);
   }


// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V0)
  {
  //Estado de leitura de Temperatura de Referência
  if (estado == 0){
    //seta próximo estado
    proxestado = 1;
    //Save Reference Temperature
    tempRef = param.asFloat();
    
    // Send it back (começo)
    terminal.println("Temp de Referência:");
  }

  else if (estado == 1){
    //seta próximo estado
    proxestado = 0;
    //Save Reference Temperature
    tempo = param.asFloat();
    
    // Send it back (começo)
    terminal.print("Tempo:");
    //Mostra no App
    Blynk.virtualWrite(V31, tempo);
    }
  
  // Send it back (restante)
  terminal.write(param.getBuffer(), param.getLength());
  terminal.println();

  // Ensure everything is sent
  terminal.flush();

  //atualiza estado
  estado = proxestado;
  }

void atualizaApp()
{
  //Mostra Ref,Wort e Out Temp no app Android
  Blynk.virtualWrite(V28, tempRef);
  Blynk.virtualWrite(V29, tempWort);
  Blynk.virtualWrite(V30, tempOut);

  //Atualiza tempo
  if (tempo != 0){
    tempo = tempo - 1;
    digitalWrite(ledPin, LOW);
    if (tempo ==0){
      terminal.print("Prepare próxima etapa!");
      // Ensure everything is sent
      terminal.flush();
      //Led de próxima etapa
      digitalWrite(ledPin, HIGH);
    }
    //Mostra no App
    Blynk.virtualWrite(V31, tempo);
  }

  //blink leds 1 and 2
  if (led1.getValue()) {
    led1.off();
  } else {
    led1.on();
  }
  if (led2.getValue()) {
    led2.off();
  } else {
    led2.on();
  }

  
   lcd.setCursor(0,0);
   lcd.print("I:");
   lcd.print(tempWort);
   lcd.print(" ");
   lcd.print("Ref:");
   lcd.print(tempRef);

   lcd.setCursor(0,1);
   lcd.print("O:");
   lcd.print(tempOut);
   lcd.print(" ");
   lcd.print("Time:");
   lcd.print(tempo);
}

void loop()
{
  Blynk.run();
  timer.run();
  float humidity = dht.readHumidity();
  tempOut = dht.readTemperature();
  tempWort = sensors.getTempCByIndex(0);
  sensors.requestTemperatures();
}

