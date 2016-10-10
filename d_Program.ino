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

    if (brewStage == 0 && switchState == HIGH) {
    	brewStage = 1;

    	terminal.println("PREPARING STRIKE WATER. STIR EVERY FEW MINUTES");
    	terminal.flush();
    	Blynk.notify(String("Brewbot message. Heating strike water"));

    	buzzer = HIGH;
    	buzzer = LOW;
    }
}

void heatTilMashTemp(){
		
}

void mashing(){
	
}

void heatTilBoil(){
	
}

void coolDown(){
	
}

void addYeast(){
	
}

void finish(){
	
}
