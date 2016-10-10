float getImersionTemp ()
{
  sensors.requestTemperatures();
  return lcd.print(sensors.getTempCByIndex(0));
}

float getLocalTemp ()
{
  return lcd.print(dht.readTemperature());
}

float getLocalUmidity ()
{
  return dht.readHumidity();
}

void standBy(){
	lcd.setCursor(0,0);
	lcd.print("Estou pronta!");
	lcd.setCursor(0,1);
    lcd.print("Inicie no app!");

    if () { // ver quando recebe aperto de botao no app
    	terminal.println("Iniciando estágio de aquecimento de água");
    	terminal.flush();
    }
}

void heatTilMashTemp(){
		
}

void mashing(){
	lcd.setCursor(0,0);
	lcd.print("Agua quente, ver");
	lcd.setCursor(0,1);
    lcd.print("inst. no app");

	if ( immersionTemp < mashTemp - 2) {
		heater1 = HIGH;
	}

	else if ( immersionTemp > mashTemp + 2 ) {
		heater1 = LOW;
	}

	if (brewStage == 2 && switchState == HIGH) {
		brewStage = 3;
		terminal.println("THE MASH STARTS NOW. STIR EVERY FEW MINUTES TO ENSURE EVEN TEMPERATURE DISTRIBUTION. MAKE SURE NO GRAINS ARE CLOGGED TOGETHER ");

		terminal.flush();
		minutesCounter = 0;
		//timeEstimate = 0;

		buzzer = HIGH;
		buzzer = LOW;
	}
}

void heatTilBoil(){
	
}

void coolDown(){
	
}

void addYeast(){
	
}

void finish(){
	
}
